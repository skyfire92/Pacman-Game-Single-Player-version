#pragma once

#include "model/model.h"
#include "main_window.h"

class InputHandler;
class GameLoop;
enum class GameResult;

class Controller : public QObject
{
Q_OBJECT

public slots:
    void viewportUpdateHandler();

    void startGame();
//    void togglePause();

public:
    Controller(Model& model, MainWindow& view);

    void subscribeToKeyEvents();
    void initializeFrontendEvents();

    void endGame(GameResult gameResult);

private:
    Model& model_;
    MainWindow& view_;

    InputHandler* inputHandler_{};
    GameLoop* gameLoop_{};
};