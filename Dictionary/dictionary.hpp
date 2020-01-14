#ifndef ITMO_GAMEDEV_ALGOS_DICTIONARY
#define ITMO_GAMEDEV_ALGOS_DICTIONARY

#include "binary_search_tree.hpp"
#include "red_black_tree.hpp"
#include <stack>

enum class treeType {
	BST,
	RBT
};

template<typename K, typename V>
class Dictionary final{
public:

	class Iterator {
		K itKey;
		Dictionary<K, V>* container;
		Iterator(Dictionary<K, V>* enclosing, K key) : container(enclosing), itKey(key) {}
		friend Dictionary<K, V>;
	public:

		const K& key() const;
		const V& get() const;
		void set(const V& value);
		void next();
		void prev();
		bool hasNext();
		bool hasPrev();
	};

	Dictionary();
	Dictionary(treeType type);
	~Dictionary();
	void put(const K& key, const V& value);
	void remove(const K& key);
	bool contains(const K& key) const;
	const V& operator[](const K& key) const;
	V& operator[](const K& key);
	size_t size() const;

	Iterator iterator();

private:
	BST<K, V>* tree, *traversalTreePointer;
	V defaultValue;
	std::stack<BST<K, V>*> traversalStack;
	int traversalPosition = 0;
};

#include "dictionary_impl.hpp"

#endif
