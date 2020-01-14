#ifndef ITMO_GAMEDEV_ALGOS_BST_IMPL
#define ITMO_GAMEDEV_ALGOS_BST_IMPL

#include "binary_search_tree.hpp"
#include <stack>

template<typename K, typename V>
BST<K, V>::BST() : left(nullptr), right(nullptr), size(0), height(0u) {}

template<typename K, typename V>
BST<K, V>::BST(K key, V value) : key(key), value(value), left(nullptr), right(nullptr), size(1), height(1u) {}

template<typename K, typename V>
BST<K, V>::BST(K key, V value, size_t size, uint32_t height) : left(nullptr), right(nullptr), key(key), value(value),  size(size), height(height) {}

template<typename K, typename V>
BST<K, V>::BST(const BST& other) : key(other.key), value(other.value), size(other.size), height(other.height) {

	if (other.left != nullptr) {
		this->left = new BST<K, V>(*other.left);
	}
	else {
		this->left = nullptr;
	}

	if (other.right != nullptr) {
		this->right = new BST<K, V>(*other.right);
	}
	else {
		this->right = nullptr;
	}
}

//template<typename K, typename V>
//BST<K, V>::BST(BST&& other) {
//	this->value = std::move(other.value);
//	this->size = std::move(other.size);
//	this->left = std::move(other.left);
//	this->right = std::move(other.right);
//	this->height = std::move(other.height);
//}

template<typename K, typename V>
BST<K, V>::~BST() {

	if (this->left) {
		delete this->left;
		this->left = nullptr;
	}
	if (this->right) {
		delete this->right;
		this->right = nullptr;
	}
	
}

template<typename K, typename V>
K BST<K, V>::getKey() {
	return key;
}

template<typename K, typename V>
V& BST<K, V>::getValue() {
	return value;
}

template<typename K, typename V>
size_t BST<K, V>::getSize() {
	return size;
}

template<typename K, typename V>
BST<K, V>* const BST<K, V>::getLeft() {
	return const_cast<BST<K, V>* const>(this->left);
}

template<typename K, typename V>
BST<K, V>* const BST<K, V>::getRight() {
	return const_cast<BST<K, V>* const>(this->right);
}

template<typename K, typename V>
BST<K, V>* BST<K, V>::find(K key) {
	BST<K, V>* x = this;

	if (size == 0) {
		return nullptr;
	}

	while (x) {

		if (x->key == key) {
			return x;
		}

		if (key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	return nullptr;
}

template<typename K, typename V>
BST<K, V>* BST<K, V>::insert(K key, V value) {

	BST<K, V>* newnode = new BST<K, V>(key, value);
	BST<K, V>* root = this;

	if (size == 0) {
		this->key = key;
		this->value = value;
		this->left = nullptr;
		this->right = nullptr;
		this->size++;
		this->height++;
		delete newnode;
		return this;
	}

	BST<K, V>* x = this;
	BST<K, V>* y = nullptr;

	while (x) {

		if (key == x->key) {
			x->value = value;
			delete newnode;
			return this;
		}

		// at the end of cycle y will contain the parent of x, and x is a key we are looking for or a leaf
		y = x;
		if (key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	if (x) {
		delete x;
	}

	if (!y) {
		y = newnode;
		if (size == 0) {
			size++;
		}
		if (height == 0) {
			height++;
		}
	}
	else if (key < y->key) {
		y->left = newnode;
		root->height++;
		root->size++;
	}
	else if (key > y->key){
		y->right = newnode;
		root->height++;
		root->size++;
	}

	return newnode;
}

template<typename K, typename V>
void BST<K, V>::remove(K key) {
	BST<K, V>* root = this;

	BST<K, V>* x = this;
	BST<K, V>* y = nullptr;

	//if (this->key == key) {
	//	this->size = 0;
	//	this->height = 0;
	//	if (this->left) {
	//		delete left;
	//	}
	//	this->left = nullptr;
	//	if (this->right) {
	//		delete right;
	//	}
	//	this->right = nullptr;
	//	return;
	//}

	while (x) {
		if (x->key == key) {
			break;
		}

		y = x;

		if (key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	if (x == nullptr) {
		return;
	}

	if (x->left == nullptr && x->right == nullptr) {
		y->left == x ? y->left = nullptr : y->right = nullptr;
		delete x;
	}
	else if (x->left == nullptr && x->right != nullptr) {
		x->key = x->right->key;
		x->value = x->right->value;
		x->size = x->right->size;
		x->height = x->right->height;

		BST<K, V>* tmp = x->right->left;
		x->left = tmp;
		x->right->left = nullptr;

		tmp = x->right->right;
		x->right->right = nullptr;
		delete x->right;
		x->right = tmp;
	}
	else if (x->left != nullptr && x->right == nullptr) {
		x->key = x->left->key;
		x->value = x->left->value;
		x->size = x->left->size;
		x->height = x->left->height;

		BST<K, V>* tmp = x->right->right;
		x->right = tmp;
		x->left->right = nullptr;

		tmp = x->left->left;
		x->left->left = nullptr;
		delete x->left;
		x->left = tmp;
	}
	else {
		if (x->right->left == nullptr) {
			x->key = x->right->key;
			x->value = x->right->value;
			BST<K, V>* tmp = x->right->right;
			x->right->right = nullptr;
			delete x->right;
			x->right = tmp;
		}
		else {
			BST<K, V>* tmp = x->right;
			while (tmp && tmp->left) {
				tmp = tmp->left;
			}
			x->key = tmp->key;
			x->value = tmp->value;
			x->size = tmp->size;
			x->value = tmp->value;
			tmp->remove(key);
		}
	}
}

#endif


