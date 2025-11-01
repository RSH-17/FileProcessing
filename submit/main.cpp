/*
* File Processing Report 2024 - Binary Search Tree skeleton code in C/C++
*
* 본 Skeleton code는 구현에 도움을 주기 위해 작성된 코드입니다.
* ❗️본 Skeleton code는 과제의 요구 조건을 완전히 충족시키지 않을 수 있습니다.❗️
* ❗️최종 점수 산정은 과제 PDF에 명시된 요구 사항을 기준으로 이루어집니다.❗️
*
* 미리 말씀드리면, skeleton code가 다소 어려울 수 있습니다.
* C++ 스러운 코딩 스타일과 코드 설계 방식에 관한 고찰이 담겨있으니, 충분한 시간을 들여 분석해보시기 바랍니다.
* 또, 재사용성을 고려하여 설계된 코드인 만큼 처음에는 이해하기 어려울 수 있습니다.
* 이후 AVL-Tree, B-Tree 과제에서도 그대로 사용되니, 이번 BST에서 잘 이해하고 넘어가시길 바랍니다.
*
*/

#include <iostream>
#include <stack>

template <class _Tp> class Node;
template <class _Tp> class BST;

/*
* 아래는 반드시 사용해야하는 Node 클래스입니다.
* height, size를 제외한 멤버 변수는 추가, 삭제 및 변경이 불가능합니다.
*/
template <class _Tp>
class Node {
	public: // Member types
		typedef _Tp					__key_type;
		typedef Node<__key_type>*	__node_pointer_type;
	
	public: // Member variables
		__key_type			__key_;
		__node_pointer_type	__left_;
		__node_pointer_type	__right_;
	
	public: // Constructor
		Node(): __key_(__key_type()), __left_(nullptr), __right_(nullptr) {} // __key_type()의 기본값으로 키값 초기화
		Node(const __key_type& key): __key_(key), __left_(nullptr), __right_(nullptr) {} // const 주소 형태이기 때문에 상수도 받을 수 있음.

	/*
	* 아래는 inorder traversal을 대체할 수 있는 operator<< 입니다.
	* 반드시 아래의 함수를 사용해야할 필요는 없습니다.
	*/
    // 출력 연산자 << 을 오버로딩하는 형태 (std::cout << np 할 때의 결과)
	friend std::ostream& operator<<(std::ostream& os, const __node_pointer_type& np) {
		// write your own code here
		// os << "print할 내용"
		if (np != nullptr)
			os << "<" << np->__left_ << " " << np->__key_ << " " << np->__right_ << ">";
		return os;
	}
};

/*
* 아래 함수들의 설계 방식은 Tree와 Node의 구동부를 구현하기 위해 추천드리는 설계 방식입니다.
* 반드시 아래의 설계 방식을 따라야 하는 것은 아닙니다.
*/

template <class _NodePtr> // _NodePtr은 이미 주소를 넘겨받는다.
unsigned __height(_NodePtr __x) {  // unsigned int의 약어
	if (__x == nullptr)
		return 0;

	unsigned lh = __height(__x->__left_);
	unsigned rh = __height(__x->__right_);

	return (lh > rh) ? lh + 1 : rh + 1;
	// 이 재귀 함수를 stack에 넣어야 하나? 일단 pass
}

template <class _NodePtr>
unsigned __size(_NodePtr __x) {
	if (__x == nullptr)
		return 0;
	
	return __size(__x->__left_) + __size(__x->__right_)  + 1;
	// 이 재귀 함수를 stack에 넣어야 하나? 일단 pass
}

/*
* 아래 함수는 minNode와 동일한 역할을 하는 함수입니다.
* 매개 변수 타입과 반환 타입을 참조 타입으로 수정하셔도 무방합니다.
*/
template <class _NodePtr>
_NodePtr __tree_min(_NodePtr __x) { // 왼쪽을 따라가면 나옴
	if (__x->__left_ == nullptr) return __x;
	return __tree_min(__x->__left_);
}

/*
* 아래 함수는 maxNode와 동일한 역할을 하는 함수입니다.
* 매개 변수 타입과 반환 타입을 참조 타입으로 수정하셔도 무방합니다.
*/
template <class _NodePtr>
_NodePtr __tree_max(_NodePtr __x) { // 오른쪽을 따라가면 나옴
	if (__x->__right_ == nullptr) return __x;
	return __tree_max(__x->__right_);
}

/*
* PDF에 명시되어있는 출력 형식에 유의하세요.
* ❗️잘못된 출력 형식은 0점 처리됩니다.❗️
*/
template <class _NodePtr>
void __inorder(_NodePtr __x) {
	// "<" + left + " " + root_key + " " + right + ">"
	std::cout << "<";
	__inorder(__x->__left_);
	std::cout << " " << __x.__key_ << " ";
	__inorder(__x->__right_);
	std::cout << ">";
}

/*
* 아래 함수는 삽입된 노드의 위치와 삽입 여부를 반환합니다.
* 예시) 이미 같은 키 값이 존재하는 경우: return std::pair<_NodePtr, bool>(__p, false);
*/
template <class _NodePtr, class _Tp>
_NodePtr __getNodeBST(_Tp key) {
	return new Node<_Tp>(key);
}

template <class _NodePtr, class _Tp>
std::pair<_NodePtr, bool> __insertBST(_NodePtr& __root, const _Tp& key) {
	_NodePtr __p = __root;
	_NodePtr __q = nullptr;

	while (__p != nullptr) {
		if (key == __p->__key_) return std::pair<_NodePtr, bool>(__p, false);
		__q = __p;
		if (key < __p->__key_) __p = __p->__left_;
		else __p = __p->__right_;
	}

	_NodePtr __newNode = __getNodeBST<_NodePtr, _Tp>(key);

	if (__root == nullptr) __root = __newNode;
	else if (key < __q->__key_) __q->__left_ = __newNode;
	else __q->__right_ = __newNode;

	return std::pair<_NodePtr, bool>(__newNode, true);
}

/*
* Root node가 삭제되는 경우를 고려하여 매개 변수 "__root" 를 참조 타입으로 받도록 설계하였습니다.
* "__root = 대체될 노드"로 BST class의 멤버 변수 __root_ 값을 변경할 수 있습니다.
* 현재 로직에서 존재하지 않는 key를 erase하려고 할 때, nullptr을 반환해야 정상 작동하도록 설계되어 있습니다.
*/
template <class _NodePtr, class _Tp>
_NodePtr __searchBST(_NodePtr __root, const _Tp& key) {
	_NodePtr __p = __root;
	if (__p == nullptr) return nullptr;
	else if (key == __p->__key_) return __p;
	else if (key < __p->__key_) return __searchBST(__p->__left_, key);
	else return __searchBST(__p->__right_, key);
}

template <class _NodePtr, class _Tp>
_NodePtr __searchParent(_NodePtr __root, const _Tp& key) {
	_NodePtr __q = nullptr;
	_NodePtr __p = __root;
	
	while (__p != nullptr)
	{
		if (key == __p->__key_) return __q;
		
		__q = __p;
		if (key < __p->__key_) __p = __p->__left_;
		else __p = __p->__right_;
	}
	
	return nullptr;
}

template <class _NodePtr, class _Tp>
_NodePtr __eraseBST(_NodePtr& __root, const _Tp& key) {
	_NodePtr __p = __searchBST(__root, key);
	_NodePtr __q = __searchParent(__root, key);

	if (__p == nullptr) return __q; // __root에 삭제할 노드가 없는 경우

	// 삭제 노드 차수 0
	if (__p->__left_ == nullptr && __p->__right_ == nullptr) 
	{   
		if (__q == nullptr) // 만약 __p가 루트 노드라면
		{
			__root = nullptr; // 참조자로 받은 이유
			return __p;
		}
		if (__q->__left_ == __p) __q->__left_ = nullptr;
		else __q->__right_ = nullptr;

		return __p;
	} 
	// 삭제 노드 차수 1
	else if (__p->__left_ == nullptr || __p->__right_ == nullptr) 
	{ 
		if (__q == nullptr) // 만약 __p가 루트 노드라면
		{
			if (__p->__left_ != nullptr) __root = __p->__left_;						// p의 왼쪽 서브트리가 있다면
			else __root = __p->__right_;											// p의 오른쪽 서브트리가 있다면
				
		}
		else 
		{
			if (__p->__left_ != nullptr) 							// p의 왼쪽 서브트리가 있다면
			{
				if (__q->__left_ == __p) __q->__left_ = __p->__left_;
				else __q->__right_ = __p->__left_;
			}
			else 													// p의 오른쪽 서브트리가 있다면
			{

				if (__q->__left_ == __p) __q->__left_ = __p->__right_;
				else __q->__right_ = __p->__right_;
			}
		}

		return __p;
	} 
	// 삭제 노드 차수 2
	else 
	{ 
		_NodePtr __r;
		bool isLeft;
		
		// 서브 트리의 높이 비교
		if (__height(__p->__left_) > __height(__p->__right_))
		{
			__r = __tree_max(__p->__left_);
			isLeft = true;
		}
		else if (__height(__p->__left_) < __height(__p->__right_))
		{
			__r = __tree_min(__p->__right_);
			isLeft = false;
		}
		else // (__height(__p->__left_) == __height(__p->__right_))
		{
			// 각 서브 트리의 높이가 같다면 각 서브 트리의 크기를 비교
			if (__size(__p->__left_) >= __size(__p->__right_)) 
			{
				__r = __tree_max(__p->__left_);
				isLeft = true;
			}
			else 
			{
				__r = __tree_min(__p->__right_);
				isLeft = false;
			}
		}

		__p->__key_ = __r->__key_;
		if (isLeft == true) return __eraseBST(__p->__left_, __r->__key_);
		else return __eraseBST(__p->__right_, __r->__key_);
	}
}

// Dangling pointer를 방지하기 위해 __x를 참조 타입으로 받도록 설계하였습니다.
template <class _NodePtr>
void __clear(_NodePtr& __x) {
	// write your own code here
	// post order
	if (__x == nullptr) return;

	__clear(__x->__left_);
	__clear(__x->__right_);
	delete __x;
}

// 아래는 반드시 사용해야하는 BST 클래스입니다.
template <class _Tp>
class BST {
	public: // Member types
		typedef _Tp						key_type;
		typedef std::size_t				size_type;
		typedef Node<key_type>*			pointer;
		typedef const Node<key_type>*	const_pointer;
	
	private: // Member variables
		pointer	__root_;
	
	public: // Constructor
		BST(): __root_(nullptr) {}
	
	/*
	* 아래는 반드시 구현해야하는 부분입니다.
	* 위의 추천드리는 설계 방식을 이용하여 구현하는 것을 추천합니다.
	* 추전드리는 설계 방식을 이용하지 않고 새로 구현하셔도 무방합니다.
	*/

	public: // Capacity
		size_type height() const {
			// use __height or write your own code here
			return __height(__root_);
		}

		size_type size() const {
			// use __size or write your own code here
			return __size(__root_);
		}
	
	public: // Lookup
		void inorder() const {
			// use __inorder or write your own code here
			__inorder(__root_);
			std::cout << std::endl;
		}
		
	public: // Modifier
		std::pair<const_pointer, bool> insert(const key_type& key) {
			// use __insertBST or write your own code here
			return __insertBST(__root_, key);
		}

		const_pointer erase(const key_type& key) {
			// use __eraseBST or write your own code here
			pointer __r = __eraseBST(__root_, key);

			// Client still needs to destruct/deallocate it
			// Or memory leak will occur
			delete __r;

			return __r; 
		}

		void clear() {
			// use __clear or write your own code here
			__clear(__root_);
		}
	
	/*
	* 아래는 inorder traversal을 대체할 수 있는 operator<< 입니다.
	* 반드시 아래의 함수를 사용해야할 필요는 없습니다.
	*/
	friend std::ostream& operator<<(std::ostream& os, const BST& tree) {
		os << tree.__root_;
		return os;
	}
};

/*
* 아래는 추천드리는 main 함수의 예시입니다.
* 반드시 아래의 main 함수를 사용해야할 필요는 없습니다.
* ❗️새로 구현하실 경우, 출력 형식에 주의하세요.❗️
*/
int main(int argc, char **argv) {
	BST<int>	tree;
	char		command;
	int			key;

	while (std::cin >> command >> key) {
		switch ((int)command) {
			case (int)'i':
				if (tree.insert(key).second == false) {
					std::cerr << "i " << key << ": The key already exists" << std::endl;
					continue;
				}
				break;
			case (int)'d':
				if (tree.erase(key) == nullptr) {
					std::cerr << "d " << key << ": The key does not exist" << std::endl;
					continue;
				}
				break;
			default:
				std::cerr << "Invalid command: " << command << std::endl;
				return (1);
				break;
		}
		std::cout << tree << std::endl;
	}

	// 프로그램 종료 전, 메모리 누수가 발생하지 않도록 할당받은 메모리를 반드시 해제해야 합니다.
	tree.clear();

	return (0);
}
