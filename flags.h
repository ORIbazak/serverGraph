#pragma once
#include "Header/usings.h"

#define SUCCESS_RESPONSE 0
#define ERROR_RESPONSE 1 
#define TERMINATE_RESPONSE 2
#define AES_BLOCK_SIZE 16
#define BASE_64_BLOCK 3


enum flags
{
	HAS_X_2_HAS_Y = 'K',
	Y_BOOL_2_VAL = 'Y',
	DATA_SWAP = 'B',
	END_OF_DATA = 'p'


};

