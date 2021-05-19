#pragma once
#include "chess.h"

inline square coordsToSquare(coords c)
{
    return c.col + 8 * c.row;
}