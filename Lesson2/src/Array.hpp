#pragma once
#include <utility>
#include <iostream>

template <typename T>
class Array final
{
private:
	T * array; //массив
	int capacity; //вместимость
	int sizeArr; //текущая длина

public:

	//Конструктор распределяет память, необходимую для хранения некоторого количества элементов.
	Array( int = 8 );

	//copy constuctor
	Array( const Array &obj );

	//Деструктор освобождает память, выделенную под хранение элементов.
	~Array();

	//Вставляет переданное значение в конец массива, или в указанную позицию,
	//увеличивая размер массива на 1 и, при необходимости, сдвигая
	//существующие элементы вправо
		//Если памяти для добавления элемента
		//недостаточно, то перераспределяет память, копируя уже существующие
		//элементы в новую область.
	void insert( const T& value );
	void insert( int index, const T& value );

	//Удаляет элемент из указанной позиции массива, сдвигая остальные элементы влево
	void remove( int index );

	//Оператор индексирования позволяет обратиться к элементу массива по индексу для чтения и для записи.
	const T& operator[]( int index ) const;
	T& operator[]( int index );

	//Возвращает текущий размер( количество реально существующих в массиве ) элементов.
	int size() const;

	class Iterator {
	private:
		Array<T> * arr;
		int posIterator = 0;
	public:
		Iterator( Array<T> * array ) {
			this->arr = array;
		}
		const T& get() const; //Получает значение массива в текущей позиции итератора

		void set( const T& value ); //Устанавливает значение в текущей позиции итератора

		void insert( const T& value ); //Вставляет значение в текущую позицию итератора, сдвигая
										//соответствующие элементы( начиная с текущего ) вправо.Итератор после
										//вставки остается позиционированным на новый элемент.

		void remove(); //Удаляет значение из текущей позиции итератора

		void next(); //Перемещает текущую позицию итератора на 1 вправо, переходя к следующему элементу.

		void prev(); //Перемещает текущую позицию итератора на 1 влево, переходя к предыдущему элементу.

		void toIndex( int index ); //Устанавливает позицию итератора на элемент с указанным индексом.

		bool hasNext() const; //Возвращает true, если итератор может перейти к следующему элементу, или false, если итератор позиционирован на последний элемент.

		bool hasPrev() const; //Возвращает true, если итератор может перейти к предыдущему элементу, или false, если итератор позиционирован на первый элемент.

		//методы begin и end не нужны??
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


//получение значения без функции записи
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

//установка значения
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

//размер массива
template <typename T>
int Array<T>::size() const {
	return sizeArr; //sizeof( array ) / sizeof( array[0] )
}

#pragma endregion

#pragma region Итератор

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