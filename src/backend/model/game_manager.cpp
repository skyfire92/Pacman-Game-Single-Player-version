#include "model/game_manager.h"
#include "spdlog/spdlog.h"
#include "model.h"
#include "game_loop.h"

//STATE TRANSITIONS

//FROM READY TO START ---> RUNNING


//FROM RUNNING ---> PAUSED
//FROM RUNNING ---> STOPPED


//FROM PAUSED ---> RUNNING

//FROM STOPPED ---> READY_TO_START




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
    shouldDrawBackground_ = true;
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

    shouldDrawBackground_ = true;
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
    shouldDrawBackground_ = false;
    gameState_ = GameState::STOPPED;

    gameResult_ = gameResult;

    gameLoop_->stop();
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

const bool& GameManager::getShouldDrawBackground() const
{
    return shouldDrawBackground_;

    //    if(gameStateManager_->isStopped())
    //    {
    //        shouldDrawBackground_ = false;
    ////        return false;
    //    }
    //    else
    //    {
    //        shouldDrawBackground_ = true;
    ////        return true;
    //    }
}

void GameManager::prepareGameToStart()
{
    spdlog::debug("Prepare game to start");
    model_.reset();

    gameState_ = GameState::READY_TO_START;
}
