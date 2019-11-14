#pragma once

template<typename K, typename V>
struct DictNode {
	K key;
	V value;
};

template<typename K, typename V>
class LLRBTree {
private:
	static const bool COLOR_RED = true;
	static const bool COLOR_BLACK = false;

	class Node {
	public:
		DictNode<K, V> * dictNode;
		Node * right;
		Node * left;
		bool   color;
		Node( DictNode<K, V> * _dictNode ) {
			this->dictNode = _dictNode;
			this->color = COLOR_RED;
			this->right = nullptr;
			this->left = nullptr;
		}
	};

	Node* root;

	Node* rotateLeft( Node* h ) {
		Node* x = h->right;
		h->right = x->left;
		x->left = h;
		x->color = h->color;
		h->color = COLOR_RED;
		return x;
	}

	Node* rotateRight( Node* h ) {
		Node* x = h->left;
		h->left = x->right;
		x->right = h;
		x->color = h->color;
		h->color = COLOR_RED;
		return x;
	}

	Node* moveRedLeft( Node* h ) {
		flipColors( h );
		if( isRed( h->right->left ) ) {
			h->right = rotateRight( h->right );
			h = rotateLeft( h );
			flipColors( h );
		}
		return h;
	}

	Node* moveRedRight( Node* h ) {
		flipColors( h );
		if( isRed( h->left->left ) ) {
			h = rotateRight( h );
			flipColors( h );
		}
		return h;
	}

	void flipColors( Node* h ) {
		h->color = !h->color;
		h->left->color = !h->left->color;
		h->right->color = !h->right->color;
	}

	bool isRed( const Node* h ) const {
		if( h == nullptr ) return false;
		return h->color == COLOR_RED;
	}

	Node* fixUp( Node* h ) {
		if( isRed( h->right ) && !isRed( h->left ) )       h = rotateLeft( h );
		if( isRed( h->left ) && isRed( h->left->left ) ) h = rotateRight( h );
		if( isRed( h->left ) && isRed( h->right ) )          flipColors( h );

		return h;
	}

	Node* insert( Node* h, DictNode<K, V> * _dictNode ) {
		if( h == nullptr )
			return new Node( _dictNode );

		if( _dictNode->key == h->dictNode->key ) h->dictNode->value = _dictNode->value;
		else if( _dictNode->key < h->dictNode->key ) h->left = insert( h->left, _dictNode );
		else                   h->right = insert( h->right, _dictNode );

		h = fixUp( h );

		return h;
	}

	//This routine probably likes memory
	Node* deleteMin( Node* h ) {
		if( h->left == nullptr ) return nullptr;
		if( !isRed( h->left ) && !isRed( h->left->left ) )
			h = moveRedLeft( h );
		h->left = deleteMin( h->left );
		return fixUp( h );
	}

	Node* minNode( Node* h ) {
		return ( h->left == nullptr ) ? h : minNode( h->left );
	}

	//This routine leaks memory like no other!! I've added a few cleanups
	Node* remove( Node* h, K key ) {
		if( key < h->dictNode->key ) {
			if( !isRed( h->left ) && !isRed( h->left->left ) )
				h = moveRedLeft( h );
			h->left = remove( h->left, key );
		}
		else {
			if( isRed( h->left ) )
				h = rotateRight( h );
			if( key == h->dictNode->key && h->right == nullptr )
				return nullptr;
			if( !isRed( h->right ) && !isRed( h->right->left ) )
				h = moveRedRight( h );
			if( key == h->dictNode->key ) {
				Node* mn = minNode( h->right );
				h->dictNode->value = mn->dictNode->value;
				h->dictNode->key = mn->dictNode->key;
				h->right = deleteMin( h->right );
			}
			else {
				h->right = remove( h->right, key );
			}
		}

		return fixUp( h );
	}

	void traverse( const Node* h ) const {
		if( h == nullptr )
			return;
		traverse( h->left );
		std::cout << h->dictNode.key << "=" << h->dictNode.value << std::endl;
		traverse( h->right );
	}
public:

	LLRBTree() {
		root = nullptr;
	}

	void traverse() const {
		traverse( root );
	}

	DictNode<K, V> * search( K key ) {
		Node* x = root;
		while( x != nullptr ) {
			if( key == x->dictNode->key ) return x->dictNode;
			else if( key < x->dictNode->key ) x = x->left;
			else                    x = x->right;
		}

		return nullptr;
	}

	void insert( DictNode<K, V> * _dictNode ) {
		root = insert( root, _dictNode );
		root->color = COLOR_BLACK;
	}

	void remove( K key ) {
		root = remove( root, key );
		root->color = COLOR_BLACK;
	}
};