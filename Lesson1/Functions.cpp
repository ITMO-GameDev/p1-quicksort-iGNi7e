#include "Functions.h"
#include <random>

void fillArrayFloat( float *arrayVal, int length ) {
	for( int i = 0; i < length; i++ )
	{
		arrayVal[i] = static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX );
	}
}

void fillArrayInt( int *arrayVal, int length ) {
	for( int i = 0; i < length; i++ )
	{
		arrayVal[i] = rand();
	}
}
