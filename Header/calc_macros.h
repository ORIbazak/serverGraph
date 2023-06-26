#pragma once
#include "Header/Graph.h"

#define POSITIVE true
#define NEGATIVE false




#define Y_INTERSECT_FLAG 0.15f
#define INTEGER_JUMP static_cast<int>(1 / static_cast<float>(X_STEP)) //jump of 1 or smaller (if rounded)
#define JUMP static_cast<int>(INTEGER_JUMP /2) //jump of 1/2 or smaller (rounded)

#define CLOSE_Y_FLAG 0.4f
#define reccursive_jump 0.01
#define ALMOST_ZERO 0.01f

#define X_INTERSECT_FLAG 0.2f //flag for capturing intersect with x

#define MIN_MAX_CLOSE_TO_BOUNDRY_FLAG 0.3f