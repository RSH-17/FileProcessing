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

// 노드를 정의하는 클래스
template <class _Tp>
class Node {
	public: // Member types
		typedef _Tp					__key_type;				// key의 종류
		typedef Node<__key_type>*	__node_pointer_type;	// 위에서 정한 타입의 key 값을 갖는 노드를 가르키는 포인터
	
	public: // Member variables
		__key_type			__key_;							// 실제 키 값이 저장될 변수
		__node_pointer_type	__left_;						// 왼쪽 서브트리의 루트 노드를 가르키는 변수
		__node_pointer_type	__right_;						// 오른쪽 서브트리의 루트 노드를 가르키는 변수

		unsigned __height_;										// 트리의 높이를 나타내는 변수
		unsigned __size_;										// 트리의 크기를 나타내는 변수
	
	public: // Constructor
		Node(): __key_(__key_type()), __left_(nullptr), __right_(nullptr), __height_(1), __size_(1) {}					// __key_type()의 기본값으로 key값 초기화한 노드 생성자
		Node(const __key_type& key): __key_(key), __left_(nullptr), __right_(nullptr), __height_(1), __size_(1) {}		// 입력 받은 key값 노드 생성장  (const 주소 형태이기 때문에 상수도 받을 수 있음.)

    // 출력 연산자 << 을 오버로딩하는 형태 (std::cout << np 할 때의 결과), inorder 함수 대체
	friend std::ostream& operator<<(std::ostream& os, const __node_pointer_type& np) {
		// np가 nullptr이 아니라면 지정된 형식으로 출력 (left, right도 __node_pointer_type이기 때문에 stack의 형식으로 실행)
		if (np != nullptr)
			os << "<" << np->__left_ << " " << np->__key_ << " " << np->__right_ << ">";
		return os;
	}
};

// int 두 개를 비교하여 큰 수를 반환하는 함수
unsigned max(unsigned a, unsigned b)
{
	return (a > b) ? a : b;
}

// 노드의 높이를 반환하는 함수
template <class _NodePtr> // _NodePtr은 이미 주소를 넘겨받는다.
unsigned __height(_NodePtr __x) {  // unsigned int의 약어
	// 주어진 노드의 높이를 재귀적으로 구하는 법
	/*if (__x == nullptr)
		return 0;

	unsigned lh = __height(__x->__left_);
	unsigned rh = __height(__x->__right_);

	return (lh > rh) ? lh + 1 : rh + 1;*/

	// 노드의 높이를 멤버 변수로 넣었을 때
	return __x  ? __x->__height_ : 0u;
}

// 노드의 크기를 반환하는 함수
template <class _NodePtr>
unsigned __size(_NodePtr __x) {
	// 주어진 노드의 크기를 재귀적으로 구하는 법
	/*if (__x == nullptr)
		return 0;
	
	return __size(__x->__left_) + __size(__x->__right_)  + 1;*/

	// 노드의 크기를 멤버 변수로 넣었을 때
	return __x ? __x->__size_ : 0u;
}

// 주어진 노드를 루트 노드로 하는 트리에서 최소 key값을 가진 노드를 찾는 함수
template <class _NodePtr>
_NodePtr __tree_min(_NodePtr __x, std::stack<_NodePtr>& stk) {
	// 왼쪽을 따라가면 나옴
	while (__x->__left_ != nullptr) 
	{
		stk.push(__x);
		__x = __x->__left_;
	}
	return __x;
}

// 주어진 노드를 루트 노드로 하는 트리에서 최대 key값을 가진 노드를 찾는 함수
template <class _NodePtr>
_NodePtr __tree_max(_NodePtr __x, std::stack<_NodePtr>& stk) {
	// 오른쪽을 따라가면 나옴
	while (__x->__right_ != nullptr)
	{
		stk.push(__x);
		__x = __x->__right_;
	}
	return __x;
}

// inorder 방식으로 트리 순회(재귀)
// 현재 코드에서는 사용 X (연산자 오버로딩으로 대체함)
template <class _NodePtr>
void __inorder(_NodePtr __x) {
	// "<" + left + " " + root_key + " " + right + ">"
	std::cout << "<";
	__inorder(__x->__left_);
	std::cout << " " << __x.__key_ << " ";
	__inorder(__x->__right_);
	std::cout << ">";
}

// 입력 받은 _Tp타입으로 노드를 생성하는 함수
template <class _NodePtr, class _Tp>
_NodePtr __getNodeBST(_Tp key) {
	return new Node<_Tp>(key);
}

// key값의 노드를 BST 트리 내에 삽입하는 함수
template <class _NodePtr, class _Tp>
std::pair<_NodePtr, bool> __insertBST(_NodePtr& __root, const _Tp& key) {
	_NodePtr __p = __root;		// 넣을 위치 따라가는 변수
	_NodePtr __q = nullptr;		// 넣을 위치의 부모 노드를 나타내는 변수

	std::stack<_NodePtr> __stPtr;	// 높이 계산을 위한 변수

	// __p 변수의 값이 nullptr이 아니라면
	while (__p != nullptr) {
		if (key == __p->__key_) return std::pair<_NodePtr, bool>(__p, false);	// 이미 key가 BST 트리 내부에 있는 경우, 해당 key 노드의 주소와 false를 return 한다.

		__q = __p;									// __q에 __p를 저장
		__stPtr.push(__q);							// 부모 노드를 stack에 push
		if (key < __p->__key_) __p = __p->__left_;	// key값 작다면 왼쪽 서브트리로
		else __p = __p->__right_;					// key값 크다면 오른쪽 서브트리로
	} // 나왔을 때, __p = nullptr, __q = 새 노드의 부모 노드

	_NodePtr __newNode = __getNodeBST<_NodePtr, _Tp>(key);	// 새 노드 생성

	if (__root == nullptr) __root = __newNode;				// root 노드가 nullptr이면 이 노드를 root노드로(참조형으로 받은 이유)
	else if (key < __q->__key_) __q->__left_ = __newNode;	// 부모(__q) 노드의 key 값보다 작다면 왼쪽에 노드로 추가
	else __q->__right_ = __newNode;							// 부모(__q) 노드의 key 값보다 크다면 오른쪽에 노드로 추가

	// stack에는 지금까지 거쳐온 부모 노드의 path가 저장됨
	while (!__stPtr.empty()) // stack의 내부가 비어있지 않다면
	{
		__q = __stPtr.top();											// stack의 제일 위의 값을 __q 변수에 저장
		__stPtr.pop();													// stack 제일 위 제거

		// __q의 높이는 왼쪽과 오른쪽 트리의 높이 중 큰 값에 +1한 값이다.
		__q->__height_ = 1 + max(__height(__q->__left_), __height(__q->__right_));
		// __q의 크기는 왼쪽과 오른쪽 트리의 크기의 합에 +1한 값이다.
		__q->__size_ = 1 + __size(__q->__left_) + __size(__q->__right_);
	} 

	return std::pair<_NodePtr, bool>(__newNode, true); // 새 노드의 주소와 true를 return한다.
}

// key값의 노드를 BST 트리 내에서 찾는 함수
template <class _NodePtr, class _Tp>
_NodePtr __searchBST(_NodePtr __root, const _Tp& key, std::stack<_NodePtr>& stk) {
	_NodePtr __q = nullptr;
	_NodePtr __p = __root;

	while (__p != nullptr && key != __p->__key_)
	{
		__q = __p;
		stk.push(__q);
		
		if (key == __p->__key_) break;
		else if (key < __p->__key_) __p = __p->__left_;
		else __p = __p->__right_;
	}

	return __p;
}

// key 값의 노드를 BST 트리에서 삭제하는 함수
template <class _NodePtr, class _Tp>
_NodePtr __eraseBST(_NodePtr& __root, const _Tp& key) {
	std::stack<_NodePtr> __stPtr;	// root노드에서 삭제하려는 노드까지의 path가 들어갈 스택

	_NodePtr __p = __searchBST(__root, key, __stPtr);											// 삭제하려는 노드
	_NodePtr __q = (!__stPtr.empty()) ? __stPtr.top() : nullptr;								// 삭제하려는 노드의 부모 노드(root면 empty stack)

	if (__p == nullptr) return nullptr;								// __root에 삭제할 key 값의 노드가 없는 경우

	// 삭제할 노드의 차수가 2인 경우
	if (__p->__left_ != nullptr && __p->__right_ != nullptr)	
	{
		_NodePtr __tempNode = __p;	// 삭제하려는 노드 임시 저장
		__stPtr.push(__p);			// 삭제하려는 노드 stack에 저장(나중에 높이, 크기 계산의 위해)

		// 왼쪽 서브트리의 높이가 오른쪽 서브트리의 높이보다 작거나, 높이가 같을 때 왼쪽 서브트리의 노드 수가 오른쪽 서브트리의 노드 서브트리의 노드 수 보다 작다면
		if ((__height(__p->__left_) < __height(__p->__right_)) || ((__height(__p->__left_) == __height(__p->__right_)) && (__size(__p->__left_) < __size(__p->__right_))))
		{
			// 오른쪽 서브트리에서 최소값 찾기
			__p = __p->__right_;
			__p = __tree_min(__p, __stPtr);
		}
		// 왼쪽 서브트리의 높이가 오른쪽 서브트리의 높이보다 높거나, 높이가 같을 때 왼쪽 서브트리의 노드 수가 오른쪽 서브트리의 노드 서브트리의 노드 수 보다 크다면
		else 
		{
			// 왼쪽 서브트리에서 최대값 찾기
			__p = __p->__left_;
			__p = __tree_max(__p, __stPtr);
		}

		__tempNode->__key_ = __p->__key_;		// 삭제할 노드의 key 값을 대신할 노드의 key 값 대입
		__q = __stPtr.top();					// 대신한 노드의 부모 노드
	}

	// 차수가 2 였던 경우, 위의 조건문을 통해 root 노드의 왼쪽 서브트리의 최대 key 값 단말노드 혹은 오른쪽 서브트리의 최소 key 값 단말노드로 __p가 되고, __q는 __p의 부모 노드가 되므로, 차수가 0이 됨
	// 현재 차수가 0 또는 1인 경우
	if (__p->__left_ != nullptr)		// 삭제할 노드의 왼쪽 서브트리가 존재할 때
	{
		if (__q == nullptr) __root = __root->__left_;					// __p가 root 노드인 경우
		else if (__q->__left_ == __p) __q->__left_ = __p->__left_;		// __q의 왼쪽 서브트리의 root노드가 __p인 경우
		else __q->__right_ = __p->__left_;								// __q의 오른쪽 서브트리의 root노드가 __p인 경우
	}
	else if (__p->__right_ != nullptr)	// 삭제할 노드의 오른쪽 서브트리가 존재할 때
	{
		if (__q == nullptr) __root = __root->__right_;					// __p가 root 노드인 경우
		else if (__q->__left_ == __p) __q->__left_ = __p->__right_;		// __q의 왼쪽 서브트리의 root노드가 __p인 경우
		else __q->__right_ = __p->__right_;								// __q의 오른쪽 서브트리의 root노드가 __p인 경우
	}
	else								// 삭제할 노드의 서브트리가 없을 때
	{
		if (__q == nullptr) __root = nullptr;						// __p가 root 노드인 경우
		else if (__q->__left_ == __p) __q->__left_ = nullptr;		// __q의 왼쪽 서브트리의 root노드가 __p인 경우
		else __q->__right_ = nullptr;								// __q의 오른쪽 서브트리의 root노드가 __p인 경우
	}

	while (!__stPtr.empty())
	{
		__q = __stPtr.top();
		__stPtr.pop();

		// __q의 높이는 왼쪽과 오른쪽 트리의 높이 중 큰 값에 +1한 값이다.
		__q->__height_ = 1 + max(__height(__q->__left_), __height(__q->__right_));
		// __q의 크기는 왼쪽과 오른쪽 트리의 크기의 합에 +1한 값이다.
		__q->__size_ = 1 + __size(__q->__left_) + __size(__q->__right_);
	}

	return __p; // 삭제할 노드를 return

	/*
	// 교안에 나온 수도 코드를 바탕으로 만든 코드
	// 삭제 노드 차수 0
	if (__p->__left_ == nullptr && __p->__right_ == nullptr) 
	{   
		if (__q == nullptr)								// 만약 __p가 루트 노드(차수 0)라면
		{
			__root = nullptr;							// root를 nullptr로 만들기 (BST 트리 완전히 비워짐, 참조자로 받은 이유)
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
	*/

}

// __x를 root 노드로 가지는 트리를 전부 해제하는 함수
template <class _NodePtr>
void __clear(_NodePtr& __x) {
	_NodePtr __p = __x;
	_NodePtr __temp = nullptr;
	std::stack<_NodePtr> stk;

	while (__p != nullptr)
	{
		if (__p->__left_ != nullptr)		// 왼쪽 서브트리가 있을 때
		{
			stk.push(__p);
			__temp = __p->__left_;
			__p->__left_ = nullptr;	// 이 이후에 __p를 다시 방문했을 땐, 왼쪽 서브트리는 다 지워진 채로 방문하게 되기 때문에 nullptr를 미리 대입
			__p = __temp;

			continue;
		}
		else if (__p->__right_ != nullptr)	// 오른쪽 서브트리가 있을 때
		{
			stk.push(__p);
			__temp = __p->__right_;
			__p->__right_ = nullptr;	// 이 이후에 __p를 다시 방문했을 땐, 오른쪽 서브트리는 다 지워진 채로 방문하게 되기 때문에 nullptr를 미리 대입
			__p = __temp;
			continue;
		}
		else								// 단말노드일 때
		{
			delete __p;
			if (!stk.empty())
			{
				__p = stk.top();
				stk.pop();
			}
			else {
				__p = nullptr;
			}
		}
	}

	__x = nullptr;

	/*
	// 재귀로 구현
	if (__x == nullptr) return;
	__clear(__x->__left_);
	__clear(__x->__right_);
	delete __x;
	*/
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

			// dangling pointer
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
int main() {
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
