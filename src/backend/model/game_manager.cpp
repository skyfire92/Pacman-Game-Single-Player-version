#include "model/game_manager.h"
#include "spdlog/spdlog.h"
#include "model.h"

//STATE TRANSITIONS

//FROM READY TO START ---> RUNNING

//FROM RUNNING ---> PAUSED
//FROM RUNNING ---> STOPPED

//FROM PAUSED ---> RUNNING

//FROM STOPPED ---> READY_TO_START

//============

//READY TO START

//What is displayed:
//Background
//Characters
//Balls
//Score display
//Screen text press space to start


//RUNNING

//What is displayed:
//Background
//Characters
//Balls
//Score display
//NO SCREEN TEXT

//PAUSED

//What is displayed:
//Background
//Characters
//Balls
//Score display
//Screen text PAUSED

//STOPPED

//What is displayed:
//NO BACKGROUND
//NO CHARACTERS
//NO BALLS
//NO SCORE DISPLAY
//Screen text Game over/Congratulations etc.

GameManager::GameManager(Model& model) : model_(model)
{
    gameState_ = GameState::READY_TO_START;
}

void GameManager::processStartOrRestartGameRequest()
{
    spdlog::debug("Processing start or restart game request");

    if(gameState_ == GameState::READY_TO_START)
    {
        startGame();
    }
    else if(gameState_ == GameState::STOPPED)
    {
        prepareGameToStart();
    }
    else
    {
        spdlog::debug("Game is not in READY_TO_START state. Start or restart game request rejected");
    }
}

void GameManager::processTogglePauseRequest()
{
    spdlog::debug("Processing toggle pause request");

    if(gameState_ == GameState::PAUSED || gameState_ == GameState::RUNNING)
    {
        togglePause();
    }
    else
    {
        spdlog::debug("Game is not in PAUSED or RUNNING state. Toggle pause request rejected");
    }
}

void GameManager::startGame()
{
    spdlog::debug("Starting game");

    gameState_ = GameState::RUNNING;

    gameLoop_->start();
}

void GameManager::togglePause()
{
    spdlog::debug("Toggling pause");

    if(gameState_ == GameState::PAUSED)
    {
        gameState_ = GameState::RUNNING;
        gameLoop_->start();
    }
    else if(gameState_ == GameState::RUNNING)
    {
        gameState_ = GameState::PAUSED;
        gameLoop_->stop();
    }
    else
    {
        spdlog::debug("Game is not in PAUSED or RUNNING state. Cannot toggle pause");
    }
}

void GameManager::endGame(GameResult gameResult)
{
    gameState_ = GameState::STOPPED;

    model_.getPacman().hide();
    model_.getBlueGhost().hide();
    model_.getOrangeGhost().hide();
    model_.getPurpleGhost().hide();
    model_.getRedGhost().hide();

    model_.getScoreDisplay()->hide();

    model_.getBallItemsManager().hideAllBalls();

    gameResult_ = gameResult;
    gameLoop_->stop();

    model_.getWhatToDrawManager()->drawBackground_ = false;
}

bool GameManager::isRunning() const
{
    return gameState_ == GameState::RUNNING;
}

bool GameManager::isPaused() const
{
    return gameState_ == GameState::PAUSED;
}

bool GameManager::isReadyToStart() const
{
    return gameState_ == GameState::READY_TO_START;
}

bool GameManager::isStopped() const
{
    return gameState_ == GameState::STOPPED;
}

void GameManager::prepareGameToStart()
{
    spdlog::debug("Prepare game to start");
    model_.reset();

    model_.getPacman().show();
    model_.getBlueGhost().show();
    model_.getOrangeGhost().show();
    model_.getPurpleGhost().show();
    model_.getRedGhost().show();

    model_.getScoreDisplay()->show();

    model_.getBallItemsManager().showAllBalls();

    model_.getWhatToDrawManager()->drawBackground_ = true;

    gameState_ = GameState::READY_TO_START;
}
