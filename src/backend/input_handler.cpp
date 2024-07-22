#include <QtGui/QKeyEvent>
#include "input_handler.h"
#include "model/model.h"
#include "config.h"

InputHandler::InputHandler(Model& model) : model_(model)
{}

void InputHandler::processKeyPressedEvent(QKeyEvent* keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Left:
        case Qt::Key_A:
//            if(model_.getGameStateManager().isRunning())
//            {
                model_.getPacman().setNextDirection(Direction::LEFT);
//            }
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
//            if(model_.getGameStateManager().isRunning())
//            {
                model_.getPacman().setNextDirection(Direction::RIGHT);
//            }
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
//            if(model_.getGameStateManager().isRunning())
//            {
                model_.getPacman().setNextDirection(Direction::UP);
//            }
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
//            if(model_.getGameStateManager().isRunning())
//            {
                model_.getPacman().setNextDirection(Direction::DOWN);
//            }
            break;

        case Qt::Key_P:
            emit togglePauseRequested();
            break;

        case Qt::Key_Space:
            emit startOrRestartGameRequested();
            break;
    }
}
