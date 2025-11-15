/*
File Processing
내용: AVL 트리 구현
작성자: 류시현(20223072)
*/

/*
* File Processing Report 2024 - Adelson-Velsky and Landis Tree skeleton code in C/C++
*
* 본 Skeleton code는 구현에 도움을 주기 위해 작성된 코드입니다.
* ❗️본 Skeleton code는 과제의 요구 조건을 완전히 충족시키지 않을 수 있습니다.❗️
* ❗️최종 점수 산정은 과제 PDF에 명시된 요구 사항을 기준으로 이루어집니다.❗️
*
* ❗️출력과 clear 관련 부분은 실제 코드를 제시하였으니, 이 부분을 꼭 활용하여 코드를 작성하세요.❗️
*/

#include <iostream>
#include <stack>

// std::pair, std::max, assert는 예외적으로 허용하겠습니다.
#include <utility> // std::pair
#include <algorithm> // std::max
#include <cassert> // assert: 디버깅에 활용하세요.

template <class Tp> class Node;
template <class Tp> class AVL;

typedef enum {
NO = 0,
LL = 1,
LR = 2,
RL = 3,
RR = 4,
} ROTATION;

////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Tp>
class Node {
private: // Member types
typedef Tp               _key_type;
typedef Node<_key_type>* _node_pointer_type;

private: // Member variables
_key_type            _key;   // node's key
_node_pointer_type   _left;   // root node of left subtree
_node_pointer_type   _right;   // root node of right subtree

unsigned _height;   // node height included subtree
unsigned _size;      // node size included subtree
int _bf;      // balance factor

public: // Constructor
Node() : _key(_key_type()), _left(nullptr), _right(nullptr), _height(1), _size(1), _bf(0) {}
Node(const _key_type& key) : _key(key), _left(nullptr), _right(nullptr), _height(1), _size(1), _bf(0) {}

public: // Getter
_key_type get_key() const { return _key; }
_node_pointer_type get_left_node() const { return _left; }
_node_pointer_type get_right_node() const { return _right; }

int get_height() const { return _height; }
int get_size() const { return _size; }
int get_bf() const { return _bf; }

public: // Setter
void set_key(const _key_type& key) { _key = key; }
void set_left_node(_node_pointer_type nodeP) { _left = nodeP; }
void set_right_node(_node_pointer_type nodeP) { _right = nodeP; }
void set_height()
{
if (_left == nullptr && _right == nullptr)
{
_height = 1;
}
else if (_left == nullptr || _right == nullptr)
{
if (_left == nullptr) _height = 1 + _right->get_height();
else _height = 1 + _left->get_height();
}
else
{
_height = 1 + std::max(_left->get_height(), _right->get_height());
}
}
void set_size()
{
if (_left == nullptr && _right == nullptr)
{
_size = 1;
}
else if (_left == nullptr || _right == nullptr)
{
if (_left == nullptr) _size = 1 + _right->get_size();
else _size = 1 + _left->get_size();
}
else
{
_size = 1 + _left->get_size() + _right->get_size();
}
}
void set_bf()
{
if (_left == nullptr && _right == nullptr)
{
_bf = 0;
}
else if (_left == nullptr || _right == nullptr)
{
if (_left == nullptr) _bf = -_right->get_height();
else _bf = _left->get_height();
}
else
{
_bf = _left->get_height() - _right->get_height();
}
}

public:
// node가 가진 속성을 현재 상태에 맞춰 update하는 함수(높이, 크기, 균형인수 - 단말 노드부터)
void update_node_data()
{
set_height();
set_size();
set_bf();
}

friend std::ostream& operator<<(std::ostream& os, const _node_pointer_type& np)
{
if (np != nullptr)
os << "<" << np->get_left_node() << " " << np->get_key() << " " << np->get_right_node() << ">";
return os;
}
};

// Node의 높이를 반환하는 함수
template <class NodePtr>
unsigned _height(NodePtr _x)
{
assert(_x != nullptr); // nullptr이 들어왔을 때, 오류
return _x->get_height();
}

// Node의 크기를 반환하는 함수
template <class NodePtr>
unsigned _size(NodePtr _x)
{
assert(_x != nullptr); // nullptr이 들어왔을 때, 오류
return _x->get_size();
}

///////////////////////////////////////////////////////////////////////////////////////////

// _x를 root node로 하는 BST의 최솟값을 찾고, _x에서부터 해당 노드의 부모 노드까지의 path와 해당 노드를 반환하는 함수
template <class NodePtr>
std::pair<NodePtr, std::stack<NodePtr> > _tree_min(NodePtr _x)
{
assert(_x != nullptr); // nullptr이 들어왔을 때, 오류

std::stack<NodePtr> stk;
while (_x->get_left_node() != nullptr)
{
stk.push(_x);
_x = _x->get_left_node();
}
return std::make_pair( _x, stk );
}

// _x를 root node로 하는 BST의 최댓값을 찾고, _x에서부터 해당 노드의 부모 노드까지의 path와 해당 노드를 반환하는 함수
template <class NodePtr>
std::pair<NodePtr, std::stack<NodePtr> > _tree_max(NodePtr _x)
{
assert(_x != nullptr); // nullptr이 들어왔을 때, 오류

std::stack<NodePtr> stk;
while (_x->get_right_node() != nullptr)
{
stk.push(_x);
_x = _x->get_right_node();
}
return std::make_pair( _x, stk );
}

// _x를 root node로 하는 트리를 inorder 방식으로 순회하는 함수
template <class NodePtr>
void _inorder(NodePtr _x)
{
if (_x == nullptr) {
return;
}

std::cout << "<";
_inorder(_x->get_left_node());
std::cout << " " << _x->get_key() << " ";
_inorder(_x->get_right_node());
std::cout << ">";
}

// _x를 root node로 하는 트리의 모든 원소를 삭제(post order)하는 함수
template <class NodePtr>
void _clear(NodePtr& _x)
{
NodePtr p = _x;
NodePtr temp = nullptr;
std::stack<NodePtr> stk;

while (p != nullptr)
{
if (p->get_left_node() != nullptr)         // 왼쪽 서브트리가 있을 때
{
stk.push(p);
temp = p->get_left_node();
p->set_left_node(nullptr);            // 이 이후에 p를 다시 방문했을 땐, 왼쪽 서브트리는 다 지워진 채로 방문하게 되기 때문에 nullptr를 미리 대입
p = temp;
continue;
}
else if (p->get_right_node() != nullptr)   // 오른쪽 서브트리가 있을 때
{
stk.push(p);
temp = p->get_right_node();
p->set_right_node(nullptr);            // 이 이후에 p를 다시 방문했을 땐, 오른쪽 서브트리는 다 지워진 채로 방문하게 되기 때문에 nullptr를 미리 대입
p = temp;
continue;
}
else                              // 단말노드일 때
{
delete p;
if (!stk.empty())
{
p = stk.top();
stk.pop();
}
else {                           // 스택이 비었다면, root 노드까지 delete 된 상태이므로 p를 nullptr로 (while 종료)
p = nullptr;
}
}
}

_x = nullptr; // root 가리키는 포인터 nullptr 초기화
}

// 매개변수 key를 key 값으로 만든 node를 반환하는 함수
template <class NodePtr, class Tp>
NodePtr _getNodeBST(Tp key)
{
return new Node<Tp>(key);
}

// _root를 root node로 하는 tree에서 key 값의 노드를 추가하고, 해당 노드의 주소를 반환하는 함수 (생성 완료하면 bool=true)
template <class NodePtr, class Tp>
std::pair<NodePtr, bool> _insertBST(NodePtr& _root, const Tp& key)
{
NodePtr p = _root;         // 새로 만들 노드의 위치를 찾는 포인터 (위치 X)
NodePtr q = nullptr;      // 새로 만들 노드의 부모 노드
std::stack<NodePtr> stk;   // 루트 노드 -> 새로 만들 노드의 부모 노드까지의 path

// p가 nullptr이 아니라면 (새로 만들 노드의 위치에 도달 못 했다면)
while (p != nullptr) {
// key값이 이미 있다면, {p, false}를 return
if (key == p->get_key()) return std::pair<NodePtr, bool>(p, false);

// q를 부모노드로 하고, key 값에 따라 p를 q의 자식 노드로 내려간다.
q = p;
stk.push(q);
if (key < p->get_key()) p = p->get_left_node();
else p = p->get_right_node();
}

// 새 노드 생성
NodePtr newNode = _getNodeBST<NodePtr, Tp>(key);

// 트리에 노드를 삽입
if (_root == nullptr) _root = newNode;
else if (key < q->get_key()) q->set_left_node(newNode);
else q->set_right_node(newNode);

// stack에는 지금까지 거쳐온 부모 노드의 path가 저장됨
// stack의 내부가 비어있지 않다면, 각 노드의 높이와 크기를 다시 설정
while (!stk.empty())
{
q = stk.top();
stk.pop();

q->update_node_data();
}

return std::pair<NodePtr, bool>(newNode, true); // 새 노드의 주소와 true를 return한다.
}

// _root를 root node로 하는 tree에서 key 값의 노드를 찾고, _root에서부터 해당 노드의 부모 노드까지의 path와 해당 노드를 반환하는 함수
template <class NodePtr, class Tp>
std::pair<NodePtr, std::stack<NodePtr> > _searchBST(NodePtr& _root, const Tp& key)
{
NodePtr q = nullptr;
NodePtr p = _root;

std::stack<NodePtr> stk;

while (p != nullptr && key != p->get_key())
{
q = p;
stk.push(q);

if (key < p->get_key()) p = p->get_left_node();
else p = p->get_right_node();
}

// key 값이 없는 경우에도 key 값이 삽입되어있다는 가정 하의 root 노드부터 부모 노드까지 path - stack 반환 (이 경우 p = nullptr)
return std::make_pair( p, stk );
}

// _root를 root node로 하는 tree에서 key 값의 노드를 삭제하고, 해당 노드의 주소를 반환하는 함수 (삭제 불가하면 nullptr 반환)
template <class NodePtr, class Tp>
NodePtr _eraseBST(NodePtr& _root, const Tp& key)
{
std::pair<NodePtr, std::stack<NodePtr> > search = _searchBST(_root, key);    // key node와 root node 부터 key 노드까지의 path
std::pair<NodePtr, std::stack<NodePtr> > _tempStack;                         // 차수가 2일 때, 삭제할 key 노드부터 대체할 노드까지의 path

NodePtr p = search.first;                                                   // key 노드 (삭제하려는 노드)
NodePtr q = (!search.second.empty()) ? search.second.top() : nullptr;       // 삭제하려는 노드의 부모 노드(root면 empty stack)

// __root에 삭제할 key 값의 노드가 없는 경우
if (p == nullptr) return nullptr;

// 삭제할 노드의 차수가 2인 경우
if (p->get_left_node() != nullptr && p->get_right_node() != nullptr)
{
NodePtr _tempNode = p;         // 삭제하려는 노드 임시 저장
search.second.push(p);         // 삭제하려는 노드 stack에 저장(나중에 높이, 크기 계산의 위해)

// 서브트리의 높이가 왼쪽 서브트리가 높거나, 만약 높이가 동일하다면 크기가 왼쪽이 오른쪽 보다 크거나 같은 경우
if (_height(p->get_left_node()) > _height(p->get_right_node()) 
|| (_height(p->get_left_node()) == _height(p->get_right_node()) && _size(p->get_left_node()) >= _size(p->get_right_node())))
{
// 왼쪽 서브트리의 최댓값을 찾는다.
p = p->get_left_node();
_tempStack = _tree_max(p);
p = _tempStack.first;
}
else
{
// 오른쪽 서브트리의 최솟값을 찾는다.
p = p->get_right_node();
_tempStack = _tree_min(p);
p = _tempStack.first;
}

_tempNode->set_key(p->get_key());      // 삭제할 노드의 key 값을 대신할 노드의 key 값 대입
q = (!_tempStack.second.empty()) ? _tempStack.second.top() : _tempNode;           // 대신한 노드의 부모 노드
}

// 차수가 2 였던 경우, 위의 조건문을 통해 root 노드의 왼쪽 서브트리의 최대 key 값 단말노드 혹은 오른쪽 서브트리의 
// 최소 key 값 단말노드로 p가 되고, q는 p의 부모 노드가 되므로, 차수가 0이 됨
// 현재 차수가 0 또는 1인 경우
if (p->get_left_node() != nullptr)         // 삭제할 노드의 왼쪽 서브트리가 존재할 때
{
if (q == nullptr) _root = _root->get_left_node();                  // p가 root 노드인 경우
else if (q->get_left_node() == p) q->set_left_node(p->get_left_node());   // q의 왼쪽 서브트리의 root노드가 p인 경우
else q->set_right_node(p->get_left_node());                        // q의 오른쪽 서브트리의 root노드가 p인 경우
}
else if (p->get_right_node() != nullptr)   // 삭제할 노드의 오른쪽 서브트리가 존재할 때
{
if (q == nullptr) _root = _root->get_right_node();                     // p가 root 노드인 경우
else if (q->get_left_node() == p) q->set_left_node(p->get_right_node());   // q의 왼쪽 서브트리의 root노드가 p인 경우
else q->set_right_node(p->get_right_node());                        // q의 오른쪽 서브트리의 root노드가 p인 경우
}
else                              // 삭제할 노드의 서브트리가 없을 때
{
if (q == nullptr) _root = nullptr;                        // __p가 root 노드인 경우
else if (q->get_left_node() == p) q->set_left_node(nullptr);   // __q의 왼쪽 서브트리의 root노드가 __p인 경우
else q->set_right_node(nullptr);                        // __q의 오른쪽 서브트리의 root노드가 __p인 경우
}

// 삭제할 key 노드부터 대체할 노드까지의 path의 노드 높이와 크기 조정
while (!_tempStack.second.empty())
{
q = _tempStack.second.top();
_tempStack.second.pop();

q->update_node_data();
}

// root node 부터 삭제할 key 노드까지의 path의 노드 높이와 크기 조정
while (!search.second.empty())
{
q = search.second.top();
search.second.pop();

q->update_node_data();
}

return p; // 삭제할 노드를 return
}

///////////////////////////////////////////////////////////////////////////////////////////
/*
함수 설명: 
- tree를 _x를 기준으로 RR회전을 진행한다.

반환 값 설명:
- 반환하지 않음

매개변수 설명:
- _root : 불균형이 일어난 노드의 부모 노드를 자식 변경해주기 위해 인자로 받음
- _x    : 불균형이 일어난 노드
*/
template <class NodePtr>
void _tree_left_rotate(NodePtr& _root, NodePtr _x)
{
assert(_root != nullptr);

std::stack<NodePtr> stk = _searchBST(_root, _x->get_key()).second;

NodePtr p = _x->get_right_node();
_x->set_right_node(p->get_left_node());
p->set_left_node(_x);

// 원래 _x를 가리키던 포인터를 변경해줌
if (!stk.empty())
{
if (stk.top()->get_key() < _x->get_key()) stk.top()->set_right_node(p);
else stk.top()->set_left_node(p);
}
else 
{
// key까지의 path가 없다는 말은, _x가 root 노드였음을 의미
_root = p;
}
}

/*
함수 설명: 
- tree를 _x를 기준으로 LL회전을 진행한다.

반환 값 설명:
- 반환하지 않음

매개변수 설명:
- _root : 불균형이 일어난 노드의 부모 노드를 자식 변경해주기 위해 인자로 받음
- _x    : 불균형이 일어난 노드
*/
template <class NodePtr>
void _tree_right_rotate(NodePtr& _root, NodePtr _x)
{
std::stack<NodePtr> stk = _searchBST(_root, _x->get_key()).second;

NodePtr p = _x->get_left_node();
_x->set_left_node(p->get_right_node());
p->set_right_node(_x);

// 원래 _x를 가리키던 포인터를 변경해줌
if (!stk.empty())
{
if (stk.top()->get_key() < _x->get_key()) stk.top()->set_right_node(p);
else stk.top()->set_left_node(p);
}
else
{
// key까지의 path가 없다는 말은, _x가 root 노드였음을 의미
_root = p;
}
}

template <class NodePtr>
void preorder(NodePtr _root)
{
if (_root == nullptr)
return; 

std::cerr << _root->get_key() << " | height :" << _root->get_height() << ", size :"  << _root->get_size() << ", bf :" << _root->get_bf() << "\n";
preorder(_root->get_left_node());
preorder(_root->get_right_node());
}

/*
함수 설명:
- tree의 구조가 현재 불균형한지 파악하는 함수

반환 값 설명:
- 불균형 노드와 회전 타입을 반환

매개변수 설명:
- _root : tree의 루트 노드, root에서 key까지의 balance 이상 여부 확인 위해 입력
- key    : 새로 삽입된 key값 혹은 삭제한 노드의 부모노드의 key값(차수 0), 반대편 같은 레벨의 key값(차수1), 대체당해 사라진 노드의 부모노드 key값(차수2)
*/
//  불균형 노드와 회전 타입을 반환하는 함수
template <class NodePtr, class Tp>
std::pair<NodePtr, ROTATION> _checkBalance(NodePtr _root, const Tp& key)
{
// _insertBST와 _eraseBST에서 각각 node의 데이터를 마지막에 최신화시키기에 항상 모든 노드의 balance factor는 최신화된 상태이다. (새로 삽입된 노드에서부터 root까지가 전부 bf가 바뀌었다.)
// 여기에서 말하는 key는 새로 삽입된 key이다.
if (_root == nullptr) return std::make_pair((NodePtr)0, ROTATION(NO));

std::pair<NodePtr, std::stack<NodePtr> > insertPath = _searchBST(_root, key);
NodePtr p = insertPath.first;

    if (p == _root) insertPath.second.push(p);

// 불균형한 노드가 아니라면 stack을 계속 비우면서 올라가봐라
if (!(p != nullptr && (p->get_bf() > 1 || p->get_bf() < -1)))
{
// key값이 존재하고, root부터 key까지의 경로가 있다면
while (!insertPath.second.empty() && insertPath.first != nullptr)
{
p = insertPath.second.top();


// 불균형 노드가 존재한다면.
if (p->get_bf() > 1 || p->get_bf() < -1)
break;

insertPath.second.pop();
}
}

// 불균형 노드 bf가 2일 때, 자식 노드 bf가 0이면 LL
// 불균형 노드 bf가 -2일 때, 자식 노드 bf가 0이면 RR

if (p == nullptr || insertPath.second.empty()) // 새로 삽입된 키가 root인 경우 또는 불균형 노드가 발생하지 않은 경우
return std::make_pair( p, ROTATION(NO) );
else if (p->get_bf() > 1) // 왼쪽 서브트리에 새로운 key가 삽입됨
{
if (p->get_left_node()->get_bf() >= 0) return std::make_pair( p, ROTATION(LL) );
else return std::make_pair( p, ROTATION(LR) );
}
else if (p->get_bf() < -1)
{
if (p->get_right_node()->get_bf() > 0) return std::make_pair( p, ROTATION(RL));
else return std::make_pair( p, ROTATION(RR) );
}

return std::make_pair((NodePtr)0, ROTATION(NO));
}

/*
함수 설명:
- checkBalance함수를 통해 받은 불균형 노드와 회전 방향에 따라 tree를 회전시키는 함수

반환 값 설명:
- 반환하지 않음

매개변수 설명:
- _root : tree의 루트 노드, root에서 key까지의 balance 이상 여부 확인 위해 입력
- key    : 새로 삽입된 key값 혹은 삭제한 노드의 부모노드의 key값(차수 0), 반대편 같은 레벨의 key값(차수1), 대체당해 사라진 노드의 부모노드 key값(차수2)

레포트 형식 변경 : _rotateTree(T) -> _rotateTree(T, key) :  매개변수 - 구현 상 key 값 필요하여 추가
*/
template <class NodePtr, class Tp>
void _rotateTree(NodePtr& _root, const Tp& key)
{
std::pair<NodePtr, ROTATION> balance = _checkBalance(_root, key);

std::pair<NodePtr, std::stack<NodePtr> > search;
if (balance.first != nullptr)
search = _searchBST(_root, balance.first->get_key());  // stack의 마지막 두개는 불균형 노드와 삽입 노드의 부모이다.

// tree의 balance가 깨지지 않은 경우, 바로 return
if (balance.second == ROTATION(NO)) return;
else if (balance.second == ROTATION(LL)) // LL 회전
{
search.second.push(search.first->get_left_node());
search.second.push(search.first);
search.second.push(search.first->get_left_node()->get_left_node());

// 회전
_tree_right_rotate(_root, balance.first);
}
else if (balance.second == ROTATION(LR)) // LR 회전
{
search.second.push(search.first->get_left_node()->get_right_node());
search.second.push(search.first);
search.second.push(search.first->get_left_node());

// 회전
NodePtr p = balance.first->get_left_node();
_tree_left_rotate(_root, p);
_tree_right_rotate(_root, balance.first);
}
else if (balance.second == ROTATION(RL)) // RL 회전
{
search.second.push(search.first->get_right_node()->get_left_node());
search.second.push(search.first);
search.second.push(search.first->get_right_node());

// 회전
NodePtr p = balance.first->get_right_node();
_tree_right_rotate(_root, p);
_tree_left_rotate(_root, balance.first);

}
else if (balance.second == ROTATION(RR)) // RR 회전
{
search.second.push(search.first->get_right_node());
search.second.push(search.first);
search.second.push(search.first->get_right_node()->get_right_node());

// 회전
_tree_left_rotate(_root, balance.first);
}

// search.second.pop();
while (!search.second.empty())
{
search.second.top()->update_node_data();
search.second.pop();
}
}

/*
함수 설명:
- AVL Tree에 key 값의 노드를 삽입하는 함수

반환 값 설명:
- 삽입된 노드의 주소와 삽입되었는지 확인하는 논리값

매개변수 설명:
- _root : tree의 루트 노드
- key    : 새로 삽입할 key값
*/
template <class NodePtr, class Tp>
std::pair<NodePtr, bool> _insertAVL(NodePtr& _root, const Tp& key)
{
std::pair<NodePtr, bool> newNode = _insertBST(_root, key);
if (newNode.second == false) return newNode;            // 노드가 이미 있는 경우, 바로 return

// new key를 삽입 완료했다면, 이후 balance factor를 확인하고, 불균형하다면 tree 회전
_rotateTree(_root, key);

return newNode;
}

/*
함수 설명:
- AVL Tree에 key 값의 노드를 삭제하는 함수

반환 값 설명:
- tree에서 삭제한 노드의 주소를 반환(아직 메모리 할당 해제 x)

매개변수 설명:
- _root : tree의 루트 노드
- key    : 삭제할 key값
*/
template <class NodePtr, class Tp>
NodePtr _eraseAVL(NodePtr& _root, const Tp& key)
{
// 1. 일단 key를 찾는다.
std::pair<NodePtr, std::stack<NodePtr> > searchKey = _searchBST(_root, key);  // key값의 노드와 key까지의 경로가 저장된 변수
std::pair<NodePtr, std::stack<NodePtr> > keyToSub; // 차수가 2일 때, key부터 대체될 노드까지의 경로가 저장될 변수

// 2. key가 tree 내부에 존재하는지 확인
if (searchKey.first == nullptr) return searchKey.first;

// 3. key의 차수가 2인지 확인한다.
if (searchKey.first->get_left_node() != nullptr && searchKey.first->get_right_node() != nullptr)
{
// 만약 차수가 2인데, 왼쪽 서브트리의 높이가 더 크거나, 높이가 같은 경우 크기가 왼쪽이 더 크거나 같을 때, 왼쪽 서브트리의 최댓값
if (_height(searchKey.first->get_left_node()) > _height(searchKey.first->get_right_node()) 
|| (_height(searchKey.first->get_left_node()) == _height(searchKey.first->get_right_node()) && _size(searchKey.first->get_left_node()) >= _size(searchKey.first->get_right_node())))
{
keyToSub = _tree_max(searchKey.first->get_left_node());
}
else
{
// 오른쪽 서브트리의 최솟값을 찾는다.
keyToSub = _tree_min(searchKey.first->get_right_node());
}
}

// 4. Key Node를 지운다.
NodePtr eraseNode = _eraseBST(_root, key);

// 5. 차수가 2인 경우와 아닌 경우를 나누어서 생각하기
if (!keyToSub.second.empty())
{
// 삭제하려 했던 노드의 차수가 2인 경우 (단, 이 경우 root 노드가 차수가 2인 경우는 포함되어 있지 않음)
// 삭제한 단말노드의 부모노드의 key값을 바탕으로 rotateTree
_rotateTree(_root, keyToSub.second.top()->get_key());
}
else
{
if (_root == searchKey.first) // 차수가 2일 때, root인 경우
{
_rotateTree(_root, key);
}
else if (searchKey.first->get_left_node() != nullptr || searchKey.first->get_right_node() != nullptr)
{
if (searchKey.second.empty()) // 차수가 1일 때, root인 경우
_rotateTree(_root, key);
// root가 아닌 경우
else if (searchKey.second.top()->get_key() > key) // 왼쪽
_rotateTree(_root, searchKey.second.top()->get_left_node()->get_key());
else // 오른쪽
_rotateTree(_root, searchKey.second.top()->get_right_node()->get_key());
}
else
{
if (searchKey.second.empty())
_rotateTree(_root, key); // 차수가 0일 때, root인 경우
else
_rotateTree(_root, searchKey.second.top()->get_key());
}

}

// preorder(_root);

return eraseNode;
}

///////////////////////////////////////////////////////////////////////////////////////////

// 아래는 반드시 사용해야하는 AVL-Tree 클래스입니다.
template <class _Tp>
class AVL {
public: // Member types
typedef _Tp                  key_type;
typedef std::size_t            size_type;
typedef Node<key_type>* pointer;
typedef const Node<key_type>* const_pointer;

private: // Member variables
pointer   _root;

public: // Constructor
AVL() : _root(nullptr) {}

public: // Capacity
size_type height() const {
return _height(_root);
}

size_type size() const {
return _size(_root);
} 

public: // Lookup
void inorder() const {
_inorder(_root);
std::cout << std::endl;
}

public: // Modifier
std::pair<const_pointer, bool> insert(const key_type& key) {
return _insertAVL(_root, key);
}

const_pointer erase(const key_type& key) {
pointer _r = _eraseAVL(_root, key);

// Client still needs to destruct/deallocate it Or memory leak will occur
delete _r;

return _r;
}

void clear() {
_clear(_root);
}

friend std::ostream& operator<<(std::ostream& os, const AVL& tree) {
os << tree._root;
return os;
}
};

///////////////////////////////////////////////////////////////////////////////////////////

int main() {
AVL<int>   tree;
char      command;
int         key;

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
}
std::cout << tree << std::endl;
}

// 프로그램 종료 전, 메모리 누수가 발생하지 않도록 할당받은 메모리를 반드시 해제해야 합니다.
tree.clear();

return (0);
}

///////////////////////////////////////////////////////////////////////////////////////////
