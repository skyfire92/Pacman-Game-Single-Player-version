#pragma once

#include <QtGui/QPixmap>
#include "common.h"

class AbstractPixmapProvider
{
public:
    virtual ~AbstractPixmapProvider() = default;
    [[nodiscard]] virtual QPixmap getPixmap(Direction direction, int animationPhase) const = 0;
};
