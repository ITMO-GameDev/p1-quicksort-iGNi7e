#pragma once

void fillArrayFloat( float*, int );
void fillArrayInt( int*, int );

template < typename T, typename Compare>
void InsertSort( T *a, T *b, Compare comp );

template < typename T, typename Compare>
void QuickSort( T *first, T *last, Compare comp );

template <typename T, typename Compare>
void sort( T *first, T *last, Compare comp );


//—ортировка вставками
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

//Ѕыстра€ сортировка
template < typename T, typename Compare>
void QuickSort( T *first, T *last, Compare comp ) {

	int length = ( last - first ) + 1;

	if( length < 2 )
		return;

	T middle = first[length / 2];
	T median = first[0];

	//Find median
	if( first[0] > middle ) {
		if( last[0] > first[0] ) {
			median = first[0];
			std::swap( first[0], first[length / 2] );
		}
	}
	else {
		if( last[0] > middle ) {
			median = middle;
		}
		else {
			if( first[0] > last[0] ) {
				median = first[0];
				std::swap( first[0], first[length / 2] );
			}
			else {
				median = last[0];
				std::swap( last[0], first[length / 2] );
			}
		}
	}

	int f = 0;
	int l = length - 1;

	do
	{
		while( comp( median, first[f] ) ) f++; // >
		while( comp( first[l], median ) ) l--; // >
		if( f <= l ) //перестановка элементов
		{
			std::swap( first[f], first[l] );
			f++;
			l--;
		}
	} while( f < l );

	if( l > 0 ) sort( first, first + l, comp );

	if( length > f ) sort( first + f, last, comp );
};

const int experimentalValue = 25; //значение, ниже которого используетс€ Inserting Sort, при сортировке которого получаетс€ наименьший результат на моей машине.

template <typename T, typename Compare>
void sort( T *first, T *last, Compare comp ) {
	int length = ( last - first ) + 1;

	if( length < experimentalValue )
		InsertSort( first, last, comp );
	else
		QuickSort( first, last, comp );
}