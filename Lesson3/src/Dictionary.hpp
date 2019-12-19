#pragma once
#include <utility>
#include <iostream>
#include "LLRBTree.hpp"

template <typename K, typename V>
class Dictionary final {
private:
	LLRBTree<K, V > tree;
	DictNode<K, V> * array;
	int capacity;
	int sz = 0;
public:
	//Создает пустой ассоциативный массив
	Dictionary( int _capacity = 8 ) {
		capacity = _capacity > 0 ? _capacity : 8;
		sz = 0;
		array = new DictNode<K, V>[capacity];
	};

	//copy constuctor
	Dictionary( const Dictionary<K, V> &obj ) :
		capacity( obj.capacity ), sz( obj.sz )
	{
		array = new DictNode<K, V>[capacity];
		for( int i = 0; i < capacity; i++ ) {
			array[i].key = {};
			array[i].value = {};
		}
		for( int i = 0; i < capacity; i++ ) {
			array[i].key = obj.array[i].key;
			array[i].value = obj.array[i].value;
		}
		tree = obj.tree;
	};

	//Деструктор освобождает память, выделенную под хранение элементов. При необходимости, при освобождении памяти вызываются деструкторы хранимых элементов
	~Dictionary() {
		delete[] array;
	};

	//Оператор индексирования позволяет обратиться к элементу
	//ассоциативного массива по ключу для чтения и для записи.Если элемента
	//с таким ключом нет, то неконстантный оператор должен его создать и
	//добавить в ассоциативный массив со значением по умолчанию.
	//Константная версия оператора должна просто вернуть значение по умолчанию
	const DictNode<K, V>& operator []( const K& key ) const;
	DictNode<K, V>& operator []( const K& key );
	DictNode<K, V>& operator []( int index );

	DictNode<K, V> * expansionArray( DictNode<K, V> *arr, int sz, int& _capacity );

	//Добавляет переданную пару ключ-значение в ассоциативный массив. Если такой ключ уже существует, связанное с ним значение должно быть заменено на переданное
	void put( const K& key, const V& value );

	DictNode<K, V> * removeValueInArray( DictNode<K, V> * arr, int sz, int& _capacity, DictNode<K, V> * _element );

	//Удаляет элемент с указанным ключом из ассоциативного массива
	void remove( const K& key );

	//Возвращает true , если в ассоциативном массиве существует элемент с указанным ключом
	bool contains( const K& key );

	//Возвращает текущий размер (количество реально существующих в ассоциативном массиве элементов)
	int size() const {
		return sz;
	};

	class Iterator {
	private:
		Dictionary<K, V> * arr;
		int posIterator = 0;
	public:
		Iterator( Dictionary<K, V> * array ) {
			this->arr = array;
		}
		const K& key() const; //Получает ключ в текущей позиции итератора
		const V& get() const; //Получает значение в текущей позиции итератора
		void set( const V& value ); //Устанавливает значение в текущей позиции итератора, сохраняя значение ключа.Ключ отдельно изменить нельзя
		void next(); //Перемещает текущую позицию итератора на следующий элемент ассоциативного массива.Порядок обхода неважен, но итератор должен гарантировать, что будут просмотрены все элементы массива, и каждый элемент будет встречен только один раз
		void prev(); //Перемещает текущую позицию итератора на предыдущий элемент
		bool hasNext() const; //Возвращает true , если итератор может перейти к следующему элементу, или false, если итератор позиционирован на последний элемент.
		bool hasPrev() const; //Возвращает true , если итератор может перейти к предыдущему элементу, или false, если итератор позиционирован на первый элемент
	};

	//Возвращает итератор, указывающий на первый элемент массива
	Iterator * get_iterator()
	{
		Iterator * iterator = new Iterator( this );
		return iterator;
	}
};

template<typename K, typename V>
const DictNode<K, V>& Dictionary<K, V>::operator []( const K& key ) const
{
	try
	{
		if( tree.search( key )->key != 0 && sz > 0 )
			return tree.search( key );
		else
			throw "Invalid index!";
	}
	catch( const char* msg )
	{
		std::cout << msg << std::endl;
	}
}

template<typename K, typename V>
DictNode<K, V>& Dictionary<K, V>::operator []( const K& key ) {
	try
	{
		if( tree.search( key ) == nullptr ) {
			put( key, {} );
		}
		if( tree.search( key )->key != 0 && sz > 0 )
			return tree.search( key );
		else
			throw "Invalid index!";
	}
	catch( const char* msg )
	{
		std::cout << msg << std::endl;
	}
}

template<typename K, typename V>
DictNode<K, V>& Dictionary<K, V>::operator []( int index ) {
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

template<typename K, typename V>
DictNode<K, V> * Dictionary<K, V>::expansionArray( DictNode<K, V> *arr, int sz, int& _capacity )
{
	_capacity *= 1.618f;
	DictNode<K, V> *arr2 = new DictNode<K, V>[_capacity];
	for( int i = 0; i < _capacity; i++ ) {
		arr2[i].key = {};
		arr2[i].value = {};
	}
	for( int i = 0; i < sz - 1; i++ ) {
		arr2[i].key = arr[i].key;
		arr2[i].value = arr[i].value;
	}
	delete[] arr;
	return arr2;
}

template<typename K, typename V>
void Dictionary<K, V>::put( const K& key, const V& value )
{
	DictNode<K, V> * el = tree.search( key );
	if( el != nullptr ) {
		el->value = value;
		return;
	}
	if( capacity < ++sz ) {
		array = expansionArray( array, sz, capacity );
	}
	array[sz - 1] = DictNode<K, V>{ key, value };
	int curSize = 0;
	for( int i = 0; i < sz ; i++ )
	{
		curSize += sizeof( array[i] );
	}
	tree.insert( array + ( sz - 1 ) * curSize / sizeof( array[0] ) );
}

template <typename K, typename V>
DictNode<K, V> * Dictionary<K, V>::removeValueInArray( DictNode<K, V> * arr, int sz, int& _capacity, DictNode<K, V> * _element )
{
	try
	{
		DictNode<K, V> *arr2 = new DictNode<K, V>[_capacity];
		for( int i = 0; i < _capacity; i++ ) {
			arr2[i].key = {};
			arr2[i].value = {};
		}
		int i = 0;
		while( arr2[i].key != _element->key ) {
			arr2[i].key = arr[i].key;
			arr2[i].value = arr[i].value;
		}
		i;
		while( i < sz ) {
			arr2[i].key = arr[i + 1].key;
			arr2[i].value = arr[i + 1].value;
		}
		delete[] arr;
		return arr2;
	}
	catch( const char* msg )
	{
		std::cout << msg << std::endl;
	}
}


template<typename K, typename V>
void Dictionary<K, V>::remove( const K& key ) {
	DictNode<K, V> * el = tree.search( key );
	if( el != nullptr ) {
		tree.remove( key );
		array = removeValueInArray( array, sz, capacity, el );
		sz -= 1;
	}
}

template<typename K, typename V>
bool Dictionary<K, V>::contains( const K& key ) {
	if( tree.search( key ) != nullptr )
		return true;
	return false;
}

#pragma region Iterator

template <typename K, typename V>
const V& Dictionary<K, V>::Iterator::get() const {
	return arr->array[posIterator].value;
}

template <typename K, typename V>
const K& Dictionary<K, V>::Iterator::key() const {
	return arr->array[posIterator].key;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::set( const V& value ) {
	Dictionary<K, V>::Iterator::arr->put( arr->array[posIterator].key, value );
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::next() {
	if( hasNext() )
		posIterator++;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::prev() {
	if( hasPrev() )
		posIterator--;
}

template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasNext() const {
	return Dictionary<K, V>::Iterator::arr->sz > posIterator;
}

template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasPrev() const {
	return 0 < posIterator;
}
#pragma endregion