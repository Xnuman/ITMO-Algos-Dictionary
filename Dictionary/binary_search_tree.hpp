#ifndef ITMO_GAMEDEV_ALGOS_BST
#define ITMO_GAMEDEV_ALGOS_BST

#include <stack>

template<typename K, typename V>
class BST;

template<typename K, typename V, typename Function>
void infixTraverse(BST<K, V>* tree, Function func);

template<typename K, typename V, typename Function>
void prefixTraverse(BST<K, V>* tree, Function func);

template<typename K, typename V, typename Function>
void postfixTraverse(BST<K, V>* tree, Function func);

template<typename K, typename V>
class BST {
protected:
	size_t size;
	V value;
	K key;
	BST* left, * right;
	uint32_t height;

	BST(K key, V data, size_t size, uint32_t height);

public:

	size_t getSize();
	K getKey();
	V& getValue();
	BST * const getLeft();
	BST * const getRight();

public:
	BST();
	BST(K key, V data);
	BST(const BST& other);
	//BST(BST&& other);

	virtual ~BST();
	 
	virtual BST* insert(K key, V data);
	virtual void remove(K key);
	virtual BST* find(K key);


	/* Couldn't figure out how to make the explicit definition outside of the class scope */
	template<typename Function>
	friend void infixTraverse(BST* tree, Function func) {
		if (tree == nullptr || tree->size == 0) {
			return;
		}

		std::stack<BST*> S;

		while (tree != nullptr || !S.empty()) {
			while (tree != nullptr) {
				S.push(tree);
				tree = tree->left;
			}
			tree = S.top();
			S.pop();

			func(tree);

			tree = tree->right;
		}
	}

	/* Couldn't figure out how to make the explicit definition outside of the class scope */
	template<typename Function>
	friend void prefixTraverse(BST* tree, Function func) {
		if (tree == nullptr || tree->size == 0) {
			return;
		}

		std::stack<BST*> S;
		S.push(tree);

		while (!S.empty()) {
			func(S.top());
			tree = S.top();
			S.pop();
			if (tree->right) {
				S.push(tree->right);
			}
			if (tree->left) {
				S.push(tree->left);
			}
		}

		tree = tree->left;
	}

	/* Couldn't figure out how to make the explicit definition outside of the class scope */
	template<typename Function>
	friend void postfixTraverse(BST* tree, Function func) {
		if (tree == nullptr || tree->size == 0) {
			return;
		}

		std::stack<BST*> S;
		if (tree->right) {
			S.push(tree->right);
		}
		S.push(tree);
		tree = tree->left;


		while (!S.empty()) {
			while (tree) {
				if (tree->right) {
					S.push(tree->right);
				}
				if (tree) {
					S.push(tree);
				}
				tree = tree->left;
			}
			tree = S.top();
			S.pop();
			if (tree->right && !S.empty() && tree->right == S.top()) {
				S.pop();
				S.push(tree);
				tree = tree->right;
			}
			else {
				func(tree);
				tree = nullptr;
			}
		}
	}
};


#include "binary_search_tree_impl.hpp"

#endif
