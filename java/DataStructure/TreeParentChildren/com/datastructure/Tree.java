package com.datastructure;

public class Tree<T>
{
	//���ڵ�
	public TreeNode<T> root;
	public Tree()
	{
	}
	//���
	public Tree(Tree<T> tree)
	{
		this.root=copy(tree.root,1);
	}
	private TreeNode<T> copy(TreeNode<T> root,int level)
	{
		//System.out.println(level);
		if(root==null)
			return null;
		TreeNode<T> p=new TreeNode<T>(root.data,level,null,null,null);
		p.child=copy(root.child,level+1);
		p.sibling=copy(root.sibling,level);
		return p;
	}
	//�ݹ��㷨
	//�ȸ�������������׸��ؼ���Ϊkey�Ľ��
	public TreeNode<T> search(T key)
	{
		if(key==null)
			return null;
		return search(this.root,key);
	}
	private TreeNode<T> search(TreeNode<T> p,T key)
	{
		if(p==null)
			return null;
		if(p.data.equals(key)==true)
			return p;
		TreeNode<T> p1=search(p.child,key);
		TreeNode<T> p2=search(p.sibling,key);
		if(p1!=null)
			return p1;
		if(p2!=null)
			return p2;
		return null;
	}
	//�ݹ�
	//�Ƚ��������Ƿ����
	public boolean equals(Object obj)
	{
		if(this==obj)
			return true;
		if(obj instanceof Tree)
		{
			Tree<T> temp=(Tree<T>)obj;
			return equals(this.root,temp.root);
		}
		else
			return false;
	}
	private boolean equals(TreeNode<T> p1,TreeNode<T> p2)
	{
		if(p1!=null&&p2!=null)
			return true;
		else if(p1!=null&&p2!=null)
			return (p1.equals(p2)&&equals(p1.child,p2.child)&&equals(p1.sibling,p2.sibling));
		else
			return false;
	}
	
	public boolean isEmpty()
	{
		return this.root==null;
	}
	//���ĺ��������
	public String toString()
	{
		return "���ĺ������ʾ��\n"+toString(this.root,"");
	}
	//�ȸ�������tabָ�����������ݹ��㷨
	private String toString(TreeNode<T> p,String tab)
	{
		if(p==null)
			return "";
		return tab+p.toString()+"\n"+toString(p.child,"\t")+toString(p.sibling,tab);
	}
	//��������
	public void printGenList()
	{
		System.out.println(printGenList(this.root));
	}
	//ʹ��StringBuffer
	private String printGenList(TreeNode<T> p)
	{
		StringBuilder builder=new StringBuilder();
		while(p!=null)
		{
			builder.append(p.data);
			if(p.child!=null)
			{
				p=p.child;
				builder.append("(");
			}
			else if(p.sibling !=null)
			{
				p=p.sibling;
				builder.append(",");
			}
			else
			{
				while(p.parent!=null)
				{
					p=p.parent;
					builder.append(")");
					if(p.sibling!=null)
					{
						p=p.sibling;
						break;
					}
				}
			}
		}
		return builder.toString();
	}
}
