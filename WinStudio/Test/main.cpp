#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;

typedef struct TreeNode
{
	int n;
	char from;
	char to;
	TreeNode*left;
	TreeNode*right;
	TreeNode*parent;
public:
	TreeNode(int n,char from,char to)
		:n(n),from(from),to(to),left(nullptr),right(nullptr),parent(nullptr)
	{
	}
	TreeNode(int n,char from,char to,TreeNode*left,TreeNode*right,TreeNode*parent)
		:n(n),from(from),to(to),left(left),right(right),parent(parent){}
};
//计算中间值
int getWith(char from,char to)
{
	string str = "ABC";
	for(auto iter = str.begin();iter != str.end();++iter)
	{
		auto ch = *iter;
		if(ch != from && ch != to)
			return ch;
	}
	return -1;
}
int main()
{
	queue<TreeNode*> m_queue;
	//汉诺塔的盘子数
	int n = 3;
	//定义头节点
	TreeNode*head = new TreeNode(n,'A','C');
	m_queue.push(head);
	while(!m_queue.empty())
	{
		auto p = m_queue.front();
		m_queue.pop();
		//判断是否应该退出循环
		if(p->n - 1 <= 0)
			break;
		//获取子节点
		auto with = getWith(p->from,p->to);
		auto leftChild = new TreeNode(p->n-1,p->from,with);
		auto rightChild = new TreeNode(p->n-1,with,p->to);
		//赋值
		leftChild->parent = p;
		rightChild->parent = p;

		p->left = leftChild;
		p->right = rightChild;
		//放入队列
		m_queue.push(leftChild);
		m_queue.push(rightChild);
	}

	stack<TreeNode*> m_stack;
	auto p = head;

	while(p != nullptr || !m_stack.empty())
	{
		while(p)
		{
			m_stack.push(p);
			p = p->left;
		}
		p = m_stack.top();
		m_stack.pop();

		cout<<p->n<<p->from<<"-->"<<p->to<<endl;
		p = p->right;
	}
	return 0;
}