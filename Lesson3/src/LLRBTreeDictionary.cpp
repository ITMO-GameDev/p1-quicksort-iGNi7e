#include <iostream>
#include <vector>
#include <cstdlib>
#include <memory>
#include <stack>

template<class K, class V>
class LLRBTreeDictionary {
private:
	static const bool COLOR_RED = true;
	static const bool COLOR_BLACK = false;
	int sz = 0;

	class Node {
	public:
		K key;
		V val;
		Node * right;
		Node * left;
		bool   color;
		Node( K key, V val ) {
			this->key = key;
			this->val = val;
			this->color = COLOR_RED;
			this->right = nullptr;
			this->left = nullptr;
		}
	};

	Node * root;

	Node * rotateLeft( Node * h ) {
		Node * x = h->right;
		h->right = x->left;
		x->left = h;
		x->color = h->color;
		h->color = COLOR_RED;
		return x;
	}

	Node * rotateRight( Node * h ) {
		Node * x = h->left;
		h->left = x->right;
		x->right = h;
		x->color = h->color;
		h->color = COLOR_RED;
		return x;
	}

	Node * moveRedLeft( Node * h ) {
		flipColors( h );
		if( isRed( h->right->left ) ) {
			h->right = rotateRight( h->right );
			h = rotateLeft( h );
			flipColors( h );
		}
		return h;
	}

	Node * moveRedRight( Node * h ) {
		flipColors( h );
		if( isRed( h->left->left ) ) {
			h = rotateRight( h );
			flipColors( h );
		}
		return h;
	}

	void flipColors( Node * h ) {
		h->color = !h->color;
		h->left->color = !h->left->color;
		h->right->color = !h->right->color;
	}

	bool isRed( const Node * h ) const {
		if( h == nullptr ) return false;
		return h->color == COLOR_RED;
	}

	Node * fixUp( Node * h ) {
		if( isRed( h->right ) && !isRed( h->left ) )       h = rotateLeft( h );
		if( isRed( h->left ) && isRed( h->left->left ) ) h = rotateRight( h );
		if( isRed( h->left ) && isRed( h->right ) )          flipColors( h );

		return h;
	}

	Node * insert( Node * h, K key, V val ) {
		if( h == nullptr )
			return new Node( key, val );

		if( key == h->key ) h->val = val;
		else if( key < h->key ) h->left = insert( h->left, key, val );
		else                   h->right = insert( h->right, key, val );

		h = fixUp( h );

		return h;
	}

	//This routine probably likes memory
	Node * deleteMin( Node * h ) {
		if( h->left == nullptr ) return nullptr;
		if( !isRed( h->left ) && !isRed( h->left->left ) )
			h = moveRedLeft( h );
		h->left = deleteMin( h->left );
		return fixUp( h );
	}

	Node * minNode( Node * h ) {
		return ( h->left == nullptr ) ? h : minNode( h->left );
	}

	//This routine leaks memory like no other!! I've added a few cleanups
	Node * remove( Node * h, K key ) {
		if( key < h->key ) {
			if( !isRed( h->left ) && !isRed( h->left->left ) )
				h = moveRedLeft( h );
			h->left = remove( h->left, key );
		}
		else {
			if( isRed( h->left ) )
				h = rotateRight( h );
			if( key == h->key && h->right == nullptr )
				return nullptr;
			if( !isRed( h->right ) && !isRed( h->right->left ) )
				h = moveRedRight( h );
			if( key == h->key ) {
				Node * mn = minNode( h->right );
				h->val = mn->val;
				h->key = mn->key;
				h->right = deleteMin( h->right );
			}
			else {
				h->right = remove( h->right, key );
			}
		}

		return fixUp( h );
	}

	void traverse( const Node * h ) const {
		if( h == nullptr )
			return;
		traverse( h->left );
		std::cout << h->key << "=" << h->val << std::endl;
		traverse( h->right );
	}

public:
	LLRBTreeDictionary() {
		root = nullptr;
	}

	~LLRBTreeDictionary() {
		delete root;
	}

	void traverse() const {
		traverse( root );
	}

	Node* search( K key ) {
		Node * x = root;
		while( x != nullptr ) {
			if( key == x->key ) return x;
			else if( key < x->key ) x = x->left;
			else                    x = x->right;
		}

		return nullptr;
	}

	void put( const K& key, const V& val ) {
		root = insert( root, key, val );
		root->color = COLOR_BLACK;
		sz++;
	}

	void remove( const K& key ) {
		if( contains( key ) == false )
			return;
		root = remove( root, key );
		root->color = COLOR_BLACK;
	}

	bool contains( const K& key ) {
		K defaultK = K{};
		Node * sear = search( key );
		if( sear == nullptr )
			return false;
		if( sear->key != defaultK ) {
			return true;
		}
		return false;
	}

	const Node& operator []( const K& key ) const
	{
		try
		{
			Node * searchNde = search( key );
			if( searchNde != nullptr && sz > 0 )
				return *searchNde;
			else
				throw "Invalid index!";
		}
		catch( const char* msg )
		{
			std::cout << msg << std::endl;
		}
	}

	Node& operator []( const K& key )
	{
		try
		{
			Node * searchNde = search( key );
			if( searchNde != nullptr && sz > 0 )
				return *searchNde;
			else
				throw "Invalid index!";
		}
		catch( const char* msg )
		{
			std::cout << msg << std::endl;
		}
	}

	class Iterator {
	private:
		std::stack<Node*> nextStack;
		std::stack<Node*> prevStack;
		LLRBTreeDictionary<K, V> * tree;
		Node* currentNode;
	public:
		Iterator( LLRBTreeDictionary<K, V>* _dict ) {
			this->tree = _dict;
			currentNode = tree->root;
		}
		const K& key() const
		{
			return currentNode->key;
		};
		const V& get() const {
			return currentNode->val;
		};
		void set( const V& value )
		{
			currentNode->val = value;
		};
		void next() {
			if( currentNode == nullptr )
				return;

			prevStack.push( currentNode );
			if( currentNode->right != nullptr ) {
				nextStack.push( currentNode->right );
			}
			if( currentNode->left != nullptr ) {
				currentNode = currentNode->left;
			}
			else {
				if( nextStack.empty() == false ) {
					currentNode = nextStack.top();
					nextStack.pop();
				}
				else {
					currentNode = nullptr;
				}
			}
		};
		void prev() {
			if( currentNode != tree->root ) {
				currentNode = prevStack.top();
				prevStack.pop();
			}
		};
		bool hasNext() const {
			if( currentNode == nullptr )
				return false;
			return true;
		};
		bool hasPrev() const {
			if( prevStack.empty() == true )
				return false;
			if( prevStack.top() != nullptr )
				return true;
			return false;
		};
	};

	Iterator * get_iterator()
	{
		Iterator * iterator = new Iterator( this );
		return iterator;
	}
};