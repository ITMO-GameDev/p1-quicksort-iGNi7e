#pragma once
#include <utility>
#include <iostream>

template <typename T>
class Array final
{
private:
	T * array; //������
	int capacity; //�����������
	int sizeArr; //������� �����

public:

	//����������� ������������ ������, ����������� ��� �������� ���������� ���������� ���������.
	Array( int = 8 );

	//copy constuctor
	Array( const Array &obj );

	//���������� ����������� ������, ���������� ��� �������� ���������.
	~Array();

	//��������� ���������� �������� � ����� �������, ��� � ��������� �������,
	//���������� ������ ������� �� 1 �, ��� �������������, �������
	//������������ �������� ������
		//���� ������ ��� ���������� ��������
		//������������, �� ���������������� ������, ������� ��� ������������
		//�������� � ����� �������.
	void insert( const T& value );
	void insert( int index, const T& value );

	//������� ������� �� ��������� ������� �������, ������� ��������� �������� �����
	void remove( int index );

	//�������� �������������� ��������� ���������� � �������� ������� �� ������� ��� ������ � ��� ������.
	const T& operator[]( int index ) const;
	T& operator[]( int index );

	//���������� ������� ������( ���������� ������� ������������ � ������� ) ���������.
	int size() const;

	class Iterator {
	private:
		Array<T> * arr;
		int posIterator = 0;
	public:
		Iterator( Array<T> * array ) {
			this->arr = array;
		}
		const T& get() const; //�������� �������� ������� � ������� ������� ���������

		void set( const T& value ); //������������� �������� � ������� ������� ���������

		void insert( const T& value ); //��������� �������� � ������� ������� ���������, �������
										//��������������� ��������( ������� � �������� ) ������.�������� �����
										//������� �������� ����������������� �� ����� �������.

		void remove(); //������� �������� �� ������� ������� ���������

		void next(); //���������� ������� ������� ��������� �� 1 ������, �������� � ���������� ��������.

		void prev(); //���������� ������� ������� ��������� �� 1 �����, �������� � ����������� ��������.

		void toIndex( int index ); //������������� ������� ��������� �� ������� � ��������� ��������.

		bool hasNext() const; //���������� true, ���� �������� ����� ������� � ���������� ��������, ��� false, ���� �������� �������������� �� ��������� �������.

		bool hasPrev() const; //���������� true, ���� �������� ����� ������� � ����������� ��������, ��� false, ���� �������� �������������� �� ������ �������.

		//������ begin � end �� �����??
	};

	Iterator * get_iterator()
	{
		Iterator * iterator = new Iterator( this );
		return iterator;
	}
};

#pragma region Array class realisation

template <typename T>
Array<T>::Array( int _capacity ) {
	capacity = _capacity > 0 ? _capacity : 8;
	sizeArr = 0;
	array = new T[capacity];
}

template <typename T>
Array<T>::Array( const Array &obj ) :
	capacity( obj.capacity ), sizeArr( obj.sizeArr )
{
	array = new T[capacity];
	for( int i = 0; i < capacity; i++ )
		array[i] = 0;
	for( int i = 0; i < capacity; i++ )
		array[i] = obj.array[i];
}

template <typename T>
Array<T>::~Array() {
	delete[] array;
}

template <typename T>
T * expansionArray( T *arr, int sz, int& _capacity )
{
	_capacity *= 1.618f;
	T *arr2 = new T[_capacity];
	for( int i = 0; i < _capacity; i++ )
		arr2[i] = 0;
	for( int i = 0; i < sz; i++ )
		arr2[i] = arr[i];
	delete[] arr;
	return arr2;
}

template <typename T>
void Array<T>::insert( const T& value ) {
	if( capacity < ++sizeArr ) {
		array = expansionArray( array, sizeArr, capacity );
	}
	array[sizeArr - 1] = value;
}

template <typename T>
T * addValueInArray( T *arr, int sz, int& _capacity, int index, const T& value )
{
	try
	{
		if( index < 0 || index > _capacity )
			throw "Invalid index!";

		T *arr2 = new T[_capacity];
		for( int i = 0; i < _capacity; i++ )
			arr2[i] = 0;
		for( int i = 0; i <= index - 1; i++ )
			arr2[i] = arr[i];
		arr2[index] = value;
		for( int i = index; i < sz; i++ )
			arr2[i + 1] = arr[i];
		delete[] arr;
		return arr2;
	}
	catch( const char* msg )
	{
		std::cout << msg << std::endl;
	}
}

template <typename T>
void Array<T>::insert( int index, const T& value ) {
	try
	{
		if( index < -1 || index > capacity ) {
			throw "Invalid index!";
		}
		if( capacity < ++sizeArr ) {
			array = expansionArray( array, sizeArr, capacity );
		}
		array = addValueInArray( array, sizeArr, capacity, index, value );
	}
	catch( const char* msg )
	{
		std::cout << msg << std::endl;
	}
}

template <typename T>
T * removeValueInArray( T *arr, int sz, int& _capacity, int index )
{
	try
	{
		if( index < 0 || index > _capacity )
			throw "Invalid index!";

		T *arr2 = new T[_capacity];
		for( int i = 0; i < _capacity; i++ )
			arr2[i] = 0;
		for( int i = 0; i < index; i++ )
			arr2[i] = arr[i];
		for( int i = index; i < sz; i++ )
			arr2[i] = arr[i + 1];
		delete[] arr;
		return arr2;
	}
	catch( const char* msg )
	{
		std::cout << msg << std::endl;
	}
}

template <typename T>
void Array<T>::remove( int index ) {
	try
	{
		if( index <= -1 || index > capacity ) {
			throw "Invalid index!";
		}
		array = removeValueInArray( array, sizeArr, capacity, index );
		sizeArr -= 1;
	}
	catch( const char* msg )
	{
		std::cout << msg << std::endl;
	}
}


//��������� �������� ��� ������� ������
template <typename T>
const T& Array<T>::operator[] ( int index ) const {
	try
	{
		if( index > -1 || index < capacity )
			return array[index];
		else
			throw "Invalid index!";
	}
	catch( const char* msg )
	{
		std::cout << msg << std::endl;
	}
}

//��������� ��������
template <typename T>
T& Array<T>::operator[]( int index ) {
	try
	{
		if( index > -1 || index < capacity )
			return array[index];
		else
			throw "Invalid index!";
	}
	catch( const char* msg )
	{
		std::cout << msg << std::endl;
	}
}

//������ �������
template <typename T>
int Array<T>::size() const {
	return sizeArr; //sizeof( array ) / sizeof( array[0] )
}

#pragma endregion

#pragma region ��������

template <typename T>
const T& Array<T>::Iterator::get() const {
	return arr->operator[]( posIterator );
}

template <typename T>
void Array<T>::Iterator::set( const T& value ) {
	arr->array[posIterator] = value;
}

template <typename T>
bool Array<T>::Iterator::hasNext() const {
	return arr->sizeArr > posIterator;
}

template <typename T>
bool Array<T>::Iterator::hasPrev() const {
	return 0 < posIterator;
}

template <typename T>
void Array<T>::Iterator::toIndex( int index ) {
	try
	{
		if( index > -1 || index < arr->capacity )
			return posIterator = index;
		else
			throw "Invalid index!";
	}
	catch( const char* msg )
	{
		std::cout << msg << std::endl;
	}
}

template <typename T>
void Array<T>::Iterator::prev() {
	if( hasPrev() )
		posIterator--;
}

template <typename T>
void Array<T>::Iterator::next() {
	if( hasNext() )
		posIterator++;
}

template <typename T>
void Array<T>::Iterator::remove() {
	Array<T>::Iterator::arr->remove( posIterator );
}

template <typename T>
void Array<T>::Iterator::insert( const T& value ) {
	Array<T>::Iterator::arr->insert( posIterator, value );
}
#pragma endregion