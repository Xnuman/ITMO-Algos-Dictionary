#ifndef ITMO_GAMEDEV_ALGOS_RBT_IMPL
#define ITMO_GAMEDEV_ALGOS_RBT_IMPL

#include "red_black_tree.hpp"


template<typename K, typename V>
std::string colorToString(typename RBT<K, V>::Color col) {
	if (col == RBT<K, V>::Color::Red) {
		return std::string("Red");
	}
	else {
		return std::string("Black");
	}
}

template<typename K, typename V>
RBT<K, V>* RBT<K, V>::getGrandparent() {
	if (parent) {
		return parent->parent;
	}
	else {
		return nullptr;
	}
}

template<typename K, typename V>
RBT<K, V>* RBT<K, V>::getUncle() {
	RBT<K, V>* gp = getGrandparent();
	if (!gp) {
		return nullptr;
	}

	if (parent == dynamic_cast<RBT<K, V>*>(gp->left)) {
		return dynamic_cast<RBT<K, V>*>(gp->right);
	}
	else {
		return dynamic_cast<RBT<K, V>*>(gp->left);
	}
}

template<typename K, typename V>
RBT<K, V>* RBT<K, V>::getSibling() {
	if (this == dynamic_cast<RBT<K, V>*>(this->parent->left)) {
		return dynamic_cast<RBT<K, V>*>(this->parent->right);
	}
	else {
		return dynamic_cast<RBT<K, V>*>(this->parent->left);
	}
}

template<typename K, typename V>
RBT<K, V>::RBT() : parent(nullptr) {
	color = Color::Black;
}
//private
template<typename K, typename V>
RBT<K, V>::RBT(K key, V value, Color color) : BST<K, V>(key, value), color(color), parent(nullptr) {}

//public
template<typename K, typename V>
RBT<K, V>::RBT(K key, V value) : RBT(key, value, Color::Black) {}


template<typename K, typename V>
RBT<K, V>::RBT(const RBT<K, V>& other, RBT<K, V>* parent) : BST<K, V>(other.key, other.value, other.size, other.height), parent(parent) {

	this->key = other.key;
	this->value = other.value;
	this->size = other.size;
	this->height = other.height;
	this->parent = parent;
	this->color = other.color;

	if (other.left != nullptr) {
		RBT<K, V>* tmp = dynamic_cast<RBT<K, V>*>(other.left);
		this->left = new RBT<K, V>(*(dynamic_cast<RBT<K, V>*>(other.left)), this);
	}
	else {
		this->left = nullptr;
	}

	if (other.right != nullptr) {
		this->right = new RBT<K, V>(*(dynamic_cast<RBT<K, V>*>(other.right)), this);
	}
	else {
		this->right = nullptr;
	}

}

template<typename K, typename V>
RBT<K, V>::RBT(const RBT<K, V>& other) : RBT(other, nullptr) {

}

template<typename K, typename V>
RBT<K, V>::~RBT() {
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
void RBT<K, V>::rotateLeft() {

	if (!this->right) {
		return;
	}

	RBT<K, V>* pivot = dynamic_cast<RBT<K, V>*>(this->right);

	pivot->parent = this->parent;

	if (this->parent) {
		if (this->parent->left == this) {
			this->parent->left = pivot;
		}
		else {
			this->parent->right = pivot;
		}
	}

	this->right = pivot->left;
	if (pivot->left) {
		dynamic_cast<RBT<K, V>*>(pivot->left)->parent = this;
	}

	this->parent = pivot;
	pivot->left = this;

}

template<typename K, typename V>
void RBT<K, V>::rotateRight() {

	if (!this->left) {
		return;
	}

	RBT<K, V>* pivot = dynamic_cast<RBT<K, V>*>(this->left);

	pivot->parent = this->parent;

	if (this->parent) {
		if (this->parent->left == this) {
			this->parent->left = pivot;
		}
		else {
			this->parent->right = pivot;
		}
	}

	this->left = pivot->right;
	if (pivot->right) {
		dynamic_cast<RBT<K, V>*>(pivot->right)->parent = this;
	}

	this->parent = pivot;
	pivot->right = this;

}

/* If inserted node is a root, paint it to BLACK */
template<typename K, typename V>
void RBT<K, V>::insert_case1() {
	if (!this->parent) {
		color = Color::Black;
	}
	else {
		insert_case2();
	}
}

/* If father of the inserted node is BLACK, then do nothing (because adding RED node as a child of BLACK doesn't break the tree */
template<typename K, typename V>
void RBT<K, V>::insert_case2() {
	if (this->parent->color == Color::Black) {
		return;
	}
	else {
		insert_case3();
	}
}
/* If both father and uncle are RED we can paint them to BLACK and grandfather to RED
 * But because repainting the grandfather could damage the tree we need to repeat this step
 * recursively until all the nodes are painted correctly
 */
template<typename K, typename V>
void RBT<K, V>::insert_case3() {
	RBT<K, V>* uncle, * grandparent;

	uncle = getUncle();

	if (uncle && uncle->color == Color::Red) { //father is RED because we got here 
		this->parent->color = Color::Black;
		uncle->color = Color::Black;
		grandparent = getGrandparent();
		grandparent->color = Color::Red;
		grandparent->insert_case1();
	}
	else {
		insert_case4();
	}
}

/* If we are right son and father is left son (or opposite), then we need first perform rotation */

template<typename K, typename V>
void RBT<K, V>::insert_case4() {

	RBT<K, V>* grandparent = getGrandparent();

	if ((this->parent == dynamic_cast<RBT<K, V>*>(grandparent->left)) && this == dynamic_cast<RBT<K, V>*>(this->parent->right)) {
		parent->rotateLeft();

		auto left = dynamic_cast<RBT<K, V>*>(this->left);

		//this->key = left->key;
		//this->value = left->value;
		//this->left = left->left;
		//this->right = left->right;
		//this->size = left->size;
		//this->height = left->height;
		//this->color = left->color;
		//this->parent = left->parent;

		left->insert_case5();
		return;
	}
	else if ((this->parent == dynamic_cast<RBT<K, V>*>(grandparent->right)) && this == dynamic_cast<RBT<K, V>*>(this->parent->left)) {
		parent->rotateRight();

		auto right = dynamic_cast<RBT<K, V>*>(this->right);

		//this->key = right->key;
		//this->value = right->value;
		//this->left = right->left;
		//this->right = right->right;
		//this->size = right->size;
		//this->height = right->height;
		//this->color = right->color;
		//this->parent = right->parent;

		right->insert_case5();
		return;

	}

	this->insert_case5();

}

/* If we and father are both right (or left), when we need to rotate tree (around grandparent) to the left (to the right) */

template<typename K, typename V>
void RBT<K, V>::insert_case5() {

	RBT<K, V>* grandparent = getGrandparent();

	this->parent->color = Color::Black;
	grandparent->color = Color::Red;

	if (this == dynamic_cast<RBT<K, V>*>(this->parent->left) && this->parent == dynamic_cast<RBT<K, V>*>(grandparent->left)) {
		grandparent->rotateRight();
	}
	else {
		grandparent->rotateLeft();
	}

}




template<typename K, typename V>
RBT<K, V>* RBT<K, V>::insert(K key, V value) {

	RBT<K, V>* newnode = new RBT<K, V>(key, value, Color::Red);
	RBT<K, V>* root = this;

	if (this->size == 0) {
		this->key = key;
		this->value = value;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
		this->size++;
		this->height++;
		delete newnode;
		return this;
	}

	RBT<K, V>* x = this;
	RBT<K, V>* y = nullptr;

	while (x) {

		if (key == x->key) {
			x->value = value;
			delete newnode;
			return this;
		}

		// at the end of cycle y will contain the parent of x, and x is a key we are looking for or a leaf
		y = x;
		if (key < x->key) {
			x = dynamic_cast<RBT<K, V>*>(x->left);
		}
		else {
			x = dynamic_cast<RBT<K, V>*>(x->right);
		}
	}

	if (x) {
		delete x;
	}

	if (!y) {
		y = newnode;
		if (this->size == 0) {
			this->size++;
		}
		if (this->height == 0) {
			this->height++;
		}
	}
	else if (key < y->key) {
		y->left = newnode;
		root->height++;
		root->size++;
	}
	else if (key > y->key) {
		y->right = newnode;
		root->height++;
		root->size++;
	}

	newnode->parent = y;

	//starts rebalancing of tree
	newnode->insert_case1();

	return newnode;
}

template<typename K, typename V>
inline void RBT<K, V>::replace_node(RBT<K, V>* node, RBT<K, V>* child) {
	if (child) {
		child->parent = node->parent;
	}
	if (node->parent) {
		node->parent->left == node ? node->parent->left = child : node->parent->right = child;
	}

}

template<typename K, typename V>
inline void RBT<K, V>::delete_one_child(RBT<K, V>* node) {

	RBT<K, V>* child = node->right == nullptr ? dynamic_cast<RBT<K, V>*>(node->left) : dynamic_cast<RBT<K, V>*>(node->right);

	replace_node(node, child);

	if (node->color == Color::Black) {
		if (child && child->color == Color::Red) {
			child->color = Color::Black;
		}
		else {
			delete_case1(child);
		}
	}
	if (node->parent) {
		delete node;
	}
	else {
		node->size = 0;
	}

}
template<typename K, typename V>
inline void RBT<K, V>::delete_case1(RBT<K, V>* node) {

	if (node && node->parent) {
		delete_case2(node);
	}

}

template<typename K, typename V>
inline void RBT<K, V>::delete_case2(RBT<K, V>* node) {
	RBT<K, V>* sibling = getSibling();

	if (sibling->color == Color::Red) {
		node->parent->color = Color::Red;
		sibling->color = Color::Black;
		if (node == dynamic_cast<RBT<K, V>*>(node->parent->left)) {
			node->parent->rotateLeft();
		}
		else {
			node->parent->rotateRight();
		}
	}
	else {
		delete_case3(node);
	}
}

template<typename K, typename V>
inline void RBT<K, V>::delete_case3(RBT<K, V>* node) {

	RBT<K, V>* sibling = getSibling();

	if (node->parent->color == Color::Black &&
		sibling->color == Color::Black &&
		dynamic_cast<RBT<K, V>*>(sibling->left)->color == Color::Black &&
		dynamic_cast<RBT<K, V>*>(sibling->right)->color == Color::Black) {

		sibling->color = Color::Red;
		delete_case1(node->parent);
	}
	else {
		delete_case4(node);
	}

}

template<typename K, typename V>
inline void RBT<K, V>::delete_case4(RBT<K, V>* node) {

	RBT<K, V>* sibling = getSibling();

	if (node->parent->color == Color::Red &&
		sibling->color == Color::Black &&
		dynamic_cast<RBT<K, V>*>(sibling->left)->color == Color::Black &&
		dynamic_cast<RBT<K, V>*>(sibling->right)->color == Color::Black) {

		sibling->color = Color::Red;
		node->parent->color = Color::Black;
	}
	else {
		delete_case5(node);
	}
}

template<typename K, typename V>
inline void RBT<K, V>::delete_case5(RBT<K, V>* node) {

	RBT<K, V>* sibling = getSibling();

	if (sibling->color == Color::Black) {
		if ((node == dynamic_cast<RBT<K, V>*>(node->parent->left)) &&
			(dynamic_cast<RBT<K, V>*>(sibling->left)->color == Color::Red) &&
			(dynamic_cast<RBT<K, V>*>(sibling->right)->color == Color::Black)) {

			sibling->color = Color::Red;
			dynamic_cast<RBT<K, V>*>(sibling->left)->color = Color::Black;
			sibling->rotateRight();
		}
		else if ((node == dynamic_cast<RBT<K, V>*>(node->parent->right)) &&
			(dynamic_cast<RBT<K, V>*>(sibling->left)->color == Color::Black) &&
			(dynamic_cast<RBT<K, V>*>(sibling->right)->color == Color::Red)) {

			sibling->color = Color::Red;
			dynamic_cast<RBT<K, V>*>(sibling->right)->color = Color::Black;
			sibling->rotateLeft();
		}
	}
	delete_case6(node);
}

template<typename K, typename V>
inline void RBT<K, V>::delete_case6(RBT<K, V>* node) {

	RBT<K, V>* sibling = getSibling();

	sibling->color = node->parent->color;
	node->parent->color = Color::Black;

	if (node == dynamic_cast<RBT<K, V>*>(node->parent->left)) {
		dynamic_cast<RBT<K, V>*>(sibling->right)->color = Color::Black;
		node->parent->rotateLeft();
	}
	else {
		dynamic_cast<RBT<K, V>*>(sibling->left)->color = Color::Black;
		node->parent->rotateRight();
	}

}

template<typename K, typename V>
void RBT<K, V>::remove(K key) {

	RBT<K, V>* root = this;

	RBT<K, V>* x = this;
	RBT<K, V>* y = nullptr;

	while (x) {
		if (x->key == key) {
			break;
		}

		y = x;

		if (key < x->key) {
			x = dynamic_cast<RBT<K, V>*>(x->left);
		}
		else {
			x = dynamic_cast<RBT<K, V>*>(x->right);
		}
	}

	if (x == nullptr) {
		return;
	}

	if (x->left == nullptr && x->right == nullptr) {
		if (x->color == Color::Red) {
			dynamic_cast<RBT<K, V>*>(x->parent->left) == x ? x->parent->left = nullptr : x->parent->right = nullptr;
			delete x;
		}
		else {
			delete_one_child(x);
		}
	}
	else if ((x->right && !x->left) || (!x->right && x->left)) {
		delete_one_child(x);
	}
	else {
		if (dynamic_cast<RBT<K, V>*>(x->right)->left == nullptr) {
			x->key = dynamic_cast<RBT<K, V>*>(x->right)->key;
			x->value = dynamic_cast<RBT<K, V>*>(x->right)->value;
			RBT<K, V>* tmp = dynamic_cast<RBT<K, V>*>(dynamic_cast<RBT<K, V>*>(x->right)->right);
			dynamic_cast<RBT<K, V>*>(x->right)->right = nullptr;
			delete x->right;
			//dynamic_cast<RBT<K, V>*>(x->right) = tmp;
			x->right = tmp;
		}
		else {
			RBT<K, V>* tmp = dynamic_cast<RBT<K, V>*>(x->right);
			while (tmp && tmp->left) {
				tmp = dynamic_cast<RBT<K, V>*>(tmp->left);
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
