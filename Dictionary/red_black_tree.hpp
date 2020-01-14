#ifndef ITMO_GAMEDEV_ALGOS_RBT
#define ITMO_GAMEDEV_ALGOS_RBT

#include "binary_search_tree.hpp"
#include <string>

template<typename K, typename V>
class RBT : public BST<K, V> {
private:
public:
	enum class Color {
		Black,
		Red
	};

	Color color;
private:
	RBT* parent;
	RBT(K key, V value, Color color);
	RBT(const RBT& other, RBT* parent);

	RBT* getGrandparent();
	RBT* getUncle();
	RBT* getSibling();

	void rotateLeft();
	void rotateRight();

	void insert_case1();
	void insert_case2();
	void insert_case3();
	void insert_case4();
	void insert_case5();

	void replace_node(RBT<K,V>* node, RBT<K,V>* child);
	void delete_one_child(RBT<K, V>* node);

	void delete_case1(RBT<K,V>* node);
	void delete_case2(RBT<K,V>* node);
	void delete_case3(RBT<K,V>* node);
	void delete_case4(RBT<K,V>* node);
	void delete_case5(RBT<K,V>* node);
	void delete_case6(RBT<K,V>* node);


public:
	RBT();
	RBT(K key, V value);
	RBT(const RBT& other);
	//RBT(RBT&& other);
	virtual RBT* insert(K key, V value);
	virtual void remove(K key);
	virtual ~RBT();
};




#include "red_black_tree_impl.hpp"
















#endif
