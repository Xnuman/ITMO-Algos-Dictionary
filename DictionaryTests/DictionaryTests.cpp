#include "pch.h"
#include "CppUnitTest.h"

#include "../Dictionary/dictionary.hpp"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Trees
{
	TEST_CLASS(BSTTests)
	{
	public:

		BST<int, float> testTree;
		
		TEST_METHOD(ConstructEmptyTree)
		{
			BST<std::string, int> tree1; //empty tree
			Assert::IsTrue(tree1.getSize() == 0);
		}

		TEST_METHOD(ConstructTree) {
			BST < std::string, int> tree1("name", 1);
			Assert::IsTrue(
				tree1.getSize() == 1 &&
				tree1.getKey() == "name" &&
				tree1.getValue() == 1
			);
		}

		TEST_METHOD(Insertion) {
			testTree.insert(0, 1.5f);
			testTree.insert(1, 288.0f);

			Assert::IsTrue(
				testTree.getSize() == 2 &&
				testTree.getKey() == 0 && testTree.getValue() == 1.5f &&
				testTree.getLeft() == nullptr &&
				testTree.getRight()->getKey() == 1 && testTree.getRight()->getValue() == 288.0f);
		}

		TEST_METHOD(Find) {

			testTree.insert(0, 1.5f);
			testTree.insert(1, 288.0f);
			testTree.insert(-2, 87);
			testTree.insert(7, 26.0f);

			Assert::IsTrue(testTree.find(1)->getValue() == 288.0f);

		}

		TEST_METHOD(Remove) {
			testTree.insert(0, 1.5f);
			testTree.insert(1, 288.0f);
			testTree.insert(-2, 87);
			testTree.insert(7, 26.0f);

			testTree.remove(1);

			Assert::IsNull(testTree.find(1));
		}

		TEST_METHOD(InorderTraverse) {

			/*   Test tree is:

			                6 
			              /   \
			             /     \
						/       \
					   2         7
				     /  \         \
					1    5         9
					    /           \
					   3             10
			*/




			testTree.insert(6, 0);
			testTree.insert(2, 0);
			testTree.insert(7, 0);
			testTree.insert(9, 0);
			testTree.insert(5, 0);
			testTree.insert(10, 0);
			testTree.insert(1, 0);
			testTree.insert(3, 0);

			std::vector<int> testVec1 = { 1, 2, 3, 5, 6, 7, 9, 10 };
			std::vector<int> testVec2;

			infixTraverse(&testTree, [&testVec2](BST<int, float>* t_tree) {
				testVec2.push_back(t_tree->getKey());
				});

			Assert::IsTrue(testVec2.size() == 8);

			Assert::IsTrue(testVec1 == testVec2);


		}

		TEST_METHOD(PreorderTraverse) {
			/*   Test tree is:

							6
						  /   \
						 /     \
						/       \
					   2         7
					 /  \         \
					1    5         9
						/           \
					   3             10
			*/




			testTree.insert(6, 0);
			testTree.insert(2, 0);
			testTree.insert(7, 0);
			testTree.insert(9, 0);
			testTree.insert(5, 0);
			testTree.insert(10, 0);
			testTree.insert(1, 0);
			testTree.insert(3, 0);

			std::vector<int> testVec1 = { 6, 2, 1, 5, 3, 7, 9, 10 };
			std::vector<int> testVec2;

			prefixTraverse(&testTree, [&testVec2](BST<int, float>* t_tree) {
				testVec2.push_back(t_tree->getKey());
				});

			Assert::IsTrue(testVec2.size() == 8);

			Assert::IsTrue(testVec1 == testVec2);
		}

		TEST_METHOD(PostorderTraverse) {
			/*   Test tree is:

							6
						  /   \
						 /     \
						/       \
					   2         7
					 /  \         \
					1    5         9
						/           \
					   3             10
			*/




			testTree.insert(6, 0);
			testTree.insert(2, 0);
			testTree.insert(7, 0);
			testTree.insert(9, 0);
			testTree.insert(5, 0);
			testTree.insert(10, 0);
			testTree.insert(1, 0);
			testTree.insert(3, 0);

			std::vector<int> testVec1 = { 1, 3, 5, 2, 10, 9, 7, 6 };
			std::vector<int> testVec2;

			postfixTraverse(&testTree, [&testVec2](BST<int, float>* t_tree) {
				testVec2.push_back(t_tree->getKey());
				});

			Assert::IsTrue(testVec2.size() == 8);

			Assert::IsTrue(testVec1 == testVec2);
		}
	};

	TEST_CLASS(RBTTests) {

	public:
		RBT<int, float> testTree;

		// won't check methods which inherited from BST

		TEST_METHOD(InsertionAndBalancing) {

			testTree.insert(6, 0);
			testTree.insert(2, 0);
			testTree.insert(7, 0);
			testTree.insert(9, 0);
			testTree.insert(5, 0);
			testTree.insert(10, 0);
			testTree.insert(1, 0);
			testTree.insert(3, 0);

			/*   Test tree before insertion:

							6(B)
						  /   \
						 /     \
						/       \
					   2(R)      9(B)
					 /  \       / \
					1(B) 5(B) 7(R) 10(R)
						/           
					   3(R)             
			*/

			testTree.insert(8, 0);

						/*   Test tree after insertion:

							6(B)
						  /   \
						 /     \
						/       \
					   2(R)      9(R)
					 /  \       / \
					1(B) 5(B) 7(B) 10(B)
						/       \    
					   3(R)      8(R)       
					*/

			std::vector<int> testVec1 = { 1, 3, 5, 2, 8, 7, 10, 9, 6 };
			std::vector<int> testVec2;

			postfixTraverse(&testTree, [&testVec2](BST<int, float>* t_tree) {
				testVec2.push_back(t_tree->getKey());
				});

			Assert::IsTrue(testVec2.size() == 9);

			Assert::IsTrue(testVec1 == testVec2);

		}

		TEST_METHOD(DeletionAndBalancing) {
			testTree.insert(6, 0);
			testTree.insert(2, 0);
			testTree.insert(7, 0);
			testTree.insert(9, 0);
			testTree.insert(5, 0);
			testTree.insert(10, 0);
			testTree.insert(1, 0);
			testTree.insert(3, 0);

			/*   Test tree before deletion:

							6(B)
						  /   \
						 /     \
						/       \
					   2(R)      9(B)
					 /  \       / \
					1(B) 5(B) 7(R) 10(R)
						/
					   3(R)
			*/

			testTree.remove(9);

			/*   Test tree after deletion:

				6(B)
			  /   \
			 /     \
			/       \
		   2(R)      10(B)
		 /  \       / 
		1(B) 5(B) 7(R) 
			/
		   3(R)
*/

			std::vector<int> testVec1 = { 1, 3, 5, 2, 7, 10, 6 };
			std::vector<int> testVec2;

			postfixTraverse(&testTree, [&testVec2](BST<int, float>* t_tree) {
				testVec2.push_back(t_tree->getKey());
				});

			Assert::IsTrue(testVec2.size() == 7);

			Assert::IsTrue(testVec1 == testVec2);

		}

	};
}

namespace Dictionary_ {
	TEST_CLASS(DictionaryTests) {

public:

	TEST_METHOD(ConstructWithBST) {
		Dictionary<int, int> d(treeType::BST);
	}

	TEST_METHOD(ConstructWithRBT) {
		Dictionary<int, int> d(treeType::RBT);
	}

	TEST_METHOD(Construct) {
		Dictionary<int, int> d;
	}

	TEST_METHOD(Put) {
		Dictionary<int, int> d;

		d.put(0, 1);

		Assert::IsTrue(d.contains(0));
	}

	TEST_METHOD(Contains) {

		Dictionary<int, int> d;

		d.put(1, 5);

		Assert::IsFalse(d.contains(0));
		Assert::IsTrue(d.contains(1));

	}

	TEST_METHOD(Remove) {

		Dictionary<int, int> d;

		d.put(1, 5);
		d.remove(1);

		Assert::IsFalse(d.contains(1));

	}

	TEST_METHOD(Indexing) {

		Dictionary<int, int> d;

		d.put(1, 7);

		Assert::IsTrue(d[1] == 7);

		d[1] = 9;

		Assert::IsTrue(d[1] == 9);

	}


	};

	TEST_CLASS(IteratorTests) {

public:

	TEST_METHOD(IteratorIntegratingTest) {
		Dictionary<int, int> npc(treeType::BST);

		npc.put(1, 20);
		npc.put(0, 5);
		npc.put(2, 10);
		npc.put(4, 10);
		npc.put(3, 5);

		std::vector<int> keyVec;
		std::vector<int> valueVec;

		for (auto it = npc.iterator(); it.hasNext(); it.next()) {
			keyVec.push_back(it.key());
			valueVec.push_back(it.get());
		}

		std::vector<int> testVec1 = { 0, 1, 2, 3, 4 };
		std::vector<int> testVec2 = { 5, 20, 10, 5, 10 };

		Assert::IsTrue(testVec1 == keyVec);
		Assert::IsTrue(testVec2 == valueVec);
	}

	};
}
