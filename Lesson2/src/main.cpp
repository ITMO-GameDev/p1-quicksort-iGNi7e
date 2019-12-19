#include <iostream>
#include "Array.hpp"

int main() {

	Array< int > a;
	for( int i = 0; i < 10; ++i )
		a.insert( i );
	a.insert( 7, 11 );
	std::cout << a.size() << std::endl;
	for( int i = 0; i < a.size(); ++i )
		a[i] *= 2;
	a.remove( 2 );
	std::cout << a.size() << std::endl;
	std::cout << " " << std::endl;
	for( auto it = a.get_iterator(); it->hasNext(); it->next() )
		std::cout << it->get() << std::endl;

	Array<int> b = a;
	std::cout << " " << std::endl;
	for( auto it = b.get_iterator(); it->hasNext(); it->next() )
		std::cout << it->get() << std::endl;
	a.remove( -2 );

	system( "pause" );
}