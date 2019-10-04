#include "pch.h"
#include "Class.h"

//Сортировка вставками
template < typename T, typename Compare>
void InsertSort( T *a, T *b, Compare comp ) {

	int length = ( b - a ) + 1;
	if( length < 2 )
		return;

	T temp = a[0];
	int item = 0;
	for( int i = 1; i < length; i++ )
	{
		temp = a[i];
		item = i - 1;
		while( item >= 0 && comp( a[item], temp ) )
		{
			a[item + 1] = a[item];
			a[item] = temp;
			item--;
		}
	}
};