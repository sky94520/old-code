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
//�����м�ֵ
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
	//��ŵ����������
	int n = 3;
	//����ͷ�ڵ�
	TreeNode*head = new TreeNode(n,'A','C');
	m_queue.push(head);
	while(!m_queue.empty())
	{
		auto p = m_queue.front();
		m_queue.pop();
		//�ж��Ƿ�Ӧ���˳�ѭ��
		if(p->n - 1 <= 0)
			break;
		//��ȡ�ӽڵ�
		auto with = getWith(p->from,p->to);
		auto leftChild = new TreeNode(p->n-1,p->from,with);
		auto rightChild = new TreeNode(p->n-1,with,p->to);
		//��ֵ
		leftChild->parent = p;
		rightChild->parent = p;

		p->left = leftChild;
		p->right = rightChild;
		//�������
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