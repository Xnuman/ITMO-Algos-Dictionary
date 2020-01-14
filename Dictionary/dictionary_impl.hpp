#ifndef ITMO_GAMEDEV_ALGOS_DICTIONARY_IMPL
#define ITMO_GAMEDEV_ALGOS_DICTIONARY_IMPL


#include "dictionary.hpp"

template<typename K, typename V>
inline Dictionary<K, V>::Dictionary() : Dictionary(treeType::RBT) {
}

template<typename K, typename V>
inline Dictionary<K, V>::Dictionary(treeType type)
{
	switch (type) {
	case treeType::BST:
		tree = new BST<K, V>();
		break;
	case treeType::RBT:
		tree = new RBT<K, V>();
		//tree = new RBT<K, V>();
		break;
	}

	traversalTreePointer = tree;

	defaultValue = static_cast<V>(0);
}

template<typename K, typename V>
inline Dictionary<K, V>::~Dictionary()
{
	delete tree;
}

template<typename K, typename V>
inline void Dictionary<K, V>::put(const K& key, const V& value)
{
	tree->insert(key, value);
}

template<typename K, typename V>
inline void Dictionary<K, V>::remove(const K& key)
{
	tree->remove(key);
}

template<typename K, typename V>
inline bool Dictionary<K, V>::contains(const K& key) const
{
	return tree->find(key) != nullptr;
}

template<typename K, typename V>
inline const V& Dictionary<K, V>::operator[](const K& key) const
{
	return const_cast<const V&>((const_cast<Dictionary<K, V>*>(this))->operator[](key));
}

template<typename K, typename V>
inline V& Dictionary<K, V>::operator[](const K& key)
{
	BST<K, V>* tmp = tree->find(key);
	if (tmp) {
		return tmp->getValue();
	}
	else {
		return tree->insert(key, defaultValue)->getValue();
	}

}

template<typename K, typename V>
inline size_t Dictionary<K, V>::size() const
{
	return tree->getSize();
}

template<typename K, typename V>
typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator()
{
	BST<K, V>* tmp = tree;

	//while (tmp && tmp->getLeft()) {
	//	tmp = tmp->getLeft();
	//}

	Iterator it(this, tree->getKey());

	it.next();

	return it;
}



template<typename K, typename V>
inline const K& Dictionary<K, V>::Iterator::key() const
{
	return itKey;
}
template<typename K, typename V>
inline const V& Dictionary<K, V>::Iterator::get() const
{
	return container->operator[](itKey);
}
template<typename K, typename V>
inline void Dictionary<K, V>::Iterator::set(const V& value)
{
	container->put(itKey, value);
}
template<typename K, typename V>
inline void Dictionary<K, V>::Iterator::next(){

	if (container->tree == nullptr || container->tree->getSize() == 0) {
		return;
	}

	K k;
	int count = 0;

	infixTraverse(container->tree, [&k, &count, this](BST<K, V>* t_tree) {

		if (count == container->traversalPosition) {
			k = t_tree->getKey();
		}
		count++;
		});

	itKey = k;
	container->traversalPosition++;
}
template<typename K, typename V>
inline void Dictionary<K, V>::Iterator::prev()
{
	container->traversalPosition -= 2;
	next();
}
template<typename K, typename V>
inline bool Dictionary<K, V>::Iterator::hasNext(){

	bool res = false;
	int count = 0;

	infixTraverse(container->tree, [&count, &res, this](BST<K, V>* t_tree) {

		count++;
		
		if (count < container->traversalPosition) {
			res = false;
		}
		else {
			res = true;
		}

		});

	return res;
}
template<typename K, typename V>
inline bool Dictionary<K, V>::Iterator::hasPrev()
{
	return container->traversalPosition > 0;
}


#endif
