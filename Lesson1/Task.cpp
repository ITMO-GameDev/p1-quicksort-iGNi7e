#include "Functions.h"
#include <iostream>
#include <algorithm>
#include <time.h> 

int main() {
	
	const int length = 200000;
	int a[length];
	fillArrayInt( a, length );

	auto lambda = [] ( int a, int b ) { return a > b; };

	clock_t start = clock();

	sort( a, a + length - 1, lambda );

	clock_t end = clock();
	double seconds = (double)( end - start ) / CLOCKS_PER_SEC;
	printf( "The time: %f seconds\n", seconds );

	//Output
	for( int i = 0; i < ( sizeof( a ) / sizeof( a[0] ) ); i++ )
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

	system( "pause" );
}
