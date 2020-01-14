template<typename T>
BST<T>::BST() : data(static_cast<T>(0)), left(nullptr), right(nullptr) {}

template<typename T>
BST<T>::BST(T data) : data(data), left(nullptr), right(nullptr) {}

template<typename T>
BST<T>::BST(const BST& other) : data(other.data) {
	if (other.left == nullptr && other.right == nullptr) {
		this->left = nullptr;
		this->right = nullptr;
	}
	else {
		this->left = BST(other.left);
		this->right = BST(other.right);
	}
}