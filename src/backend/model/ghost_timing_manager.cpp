#include "ghost_timing_manager.h"
#include "config.h"

GhostTimingManager::GhostTimingManager(const std::chrono::seconds& moveOutOfTheStartingBoxTimeout)
{
    initializeTimers(moveOutOfTheStartingBoxTimeout);
}

void GhostTimingManager::reset()
{
    timeToLeaveStartingBox_ = false;
    timeToLeaveStartingBoxTimer.start();

    scaredBlueStateTimer_.stop();
    scaredWhiteStateTimer_.stop();
}

void GhostTimingManager::startLeaveStartingBoxTimer()
{
    timeToLeaveStartingBoxTimer.start();
}

void GhostTimingManager::startScaredBlueTimer()
{
    scaredWhiteStateTimer_.stop();
    scaredBlueStateTimer_.start();
}

void GhostTimingManager::startScaredWhiteTimer()
{
    scaredBlueStateTimer_.stop();
    scaredWhiteStateTimer_.start();
}

void GhostTimingManager::changeToScaredWhite()
{
    //    ghost_.setScaredWhiteState();
    startScaredWhiteTimer();
}

void GhostTimingManager::changeToNoScared()
{
    //    ghost_.resetScaredState();
    //    ghost_.setSlowedDown(false);
    //    resetSpeed();
}

void GhostTimingManager::initializeTimers(const std::chrono::seconds& moveOutOfTheStartingBoxTimeout)
{
    scaredBlueStateTimer_.setSingleShot(true);
    scaredBlueStateTimer_.setInterval(Config::Timing::Ghost::SCARED_BLUE_TIME);

    scaredWhiteStateTimer_.setSingleShot(true);
    scaredWhiteStateTimer_.setInterval(Config::Timing::Ghost::SCARED_WHITE_TIME);

    timeToLeaveStartingBoxTimer.setSingleShot(true);
    timeToLeaveStartingBoxTimer.setInterval(moveOutOfTheStartingBoxTimeout);

    timeToLeaveStartingBoxTimer.callOnTimeout([this]()
                                              {
                                                  timeToLeaveStartingBox_ = true;
                                              });

    connect(&scaredBlueStateTimer_, &QTimer::timeout, this, &GhostTimingManager::changeToScaredWhite);
    connect(&scaredWhiteStateTimer_, &QTimer::timeout, this, &GhostTimingManager::changeToNoScared);
}
