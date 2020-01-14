
#include "red_black_tree.hpp"

#include <iostream>
#include "dictionary.hpp"


int main() {


	RBT<int, int> tree;

	tree.insert(6, 0);
	tree.insert(2, 0);
	tree.insert(7, 0);
	tree.insert(9, 0);
	tree.insert(5, 0);
	tree.insert(10, 0);
	tree.insert(1, 0);
	tree.insert(3, 0);

	tree.remove(9);

	Dictionary<int, int> a;

	a.put(0, 1);

	a.remove(0);

	bool s = a.contains(0);

	

	std::cout << "Inorder traverse: " << std::endl;
	infixTraverse(&tree, [](BST<int, int>* tree) {
		std::cout << tree->getKey() << ": " << tree->getValue() << ": " << colorToString<int, int>(dynamic_cast<RBT<int, int>*>(tree)->color) << std::endl;
		}
		);
	std::cout << std::endl;

	std::cout << "Preorder traverse " << std::endl;
	prefixTraverse(&tree, [](BST<int, int>* tree) {
		std::cout << tree->getKey() << ": " << tree->getValue() << ": " << colorToString<int, int>(dynamic_cast<RBT<int,int>*>(tree)->color) << std::endl;
		});
	std::cout << std::endl;

	std::cout << "Postorder traverse " << std::endl;
	postfixTraverse(&tree, [](BST<int, int>* tree) {
		std::cout << tree->getKey() << ": " << tree->getValue() << ": " << colorToString<int, int>(dynamic_cast<RBT<int, int>*>(tree)->color) << std::endl;
		});

	std::cout << std::endl;

	system("pause");

}