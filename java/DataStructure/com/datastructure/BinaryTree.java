package com.datastructure;
/**基本二叉树 实现功能不多 用处不大
 * */
public class BinaryTree<T>
{
	protected BinaryNode<T> root;
	public BinaryTree()
	{
		this.root = null;
	}
	//先根
	public BinaryTree(T prelist[])
	{
		this.root = create(prelist);
	}
	private int i=0;
	private BinaryNode<T> create(T prelist[])
	{
		BinaryNode<T> p = null;
		if(i<prelist.length)
		{
			T elem=prelist[i++];
			if(elem !=null)
			{
				p=new BinaryNode<T>(elem);
				p.left=create(prelist);
				p.right=create(prelist);
			}
		}
		return p;
	}
	//
	public boolean isEmpty()
	{
		return this.root == null;
	}
	//返回节点个数
	public int size()
	{
		return size(this.root);
	}
	private int size(BinaryNode<T> p)
	{
		if(p!=null)
		{
			return size(p.left)+size(p.right)+1;
		}
		return 0;
	}
	//返回高度
	public int height()
	{
		return height(this.root);
	}
	private int height(BinaryNode<T> p)
	{
		if(p!=null)
		{
			int n1=height(p.left);
			int n2=height(p.right);
			return Math.max(n1,n2)+1;
		}
		return 0;
	}
	public void clear()
	{
		this.root = null;
	}
	public String toString()
	{
		return toString(this.root);
	}
	public String toString(BinaryNode<T> p)
	{
		if(p == null)
			return "^";
		return p.toString() +" "+ toString(p.left) + toString(p.right)+" ";
	}
	public void printGenList()
	{
		//System.out.println("二叉树的广义表表示：");
		printGenList(this.root);
		System.out.println();
	}
	public void printGenList(BinaryNode<T> p)
	{
		if(p==null)
			System.out.print("^");
		else
		{
			System.out.print(p.toString());
			if(p.left!=null||p.right!=null)
			{
				System.out.print("(");
				printGenList(p.left);
				System.out.print(",");
				printGenList(p.right);
				System.out.print(")");
			}
		}
	}
	//先根次序输出
	public void preorder()
	{
		preorder(this.root);
	}
	private void preorder(BinaryNode<T> p)
	{
		if(p!=null)
		{
			System.out.printf(" %s ",p.toString());
			preorder(p.left);
			preorder(p.right);
		}
	}
	//中跟次序输出
	public void inorder()
	{
		inorder(this.root);
	}
	public void inorder(BinaryNode<T> p)
	{
		if(p!=null)
		{
			preorder(p.left);
			System.out.printf(" %s ",p.toString());
			preorder(p.right);
		}
	}
	//后根次序输出
	public void postorder()
	{
		postorder(this.root);	
	}
	public void postorder(BinaryNode<T> p)
	{
		if(p!=null)
		{
			preorder(p.left);
			preorder(p.right);
			System.out.printf(" %s ",p.toString());
		}
	}
	//层次遍历输出  ????
	public void levelorder()
	{
		levelorder(this.root);
	}
	public void levelorder(BinaryNode<T> p)
	{
		if(p!=null)
		{
			System.out.printf("%s ",p.toString()+);
		}
	}
	//插入
	public BinaryNode<T> insert(T x)
	{
		return this.root.left = new BinaryNode<T>(x,this.root,null);
	}
	public BinaryNode<T> insert(BinaryNode<T> parent,T x,boolean leftChild)
	{
		if(x==null)
			return null;
		if(leftChild)
			return parent.left = new BinaryNode<T>(x,parent.left,null);
		return parent.right=new BinaryNode<T>(x,null,parent.right);
	}
	//delete
	public void remove(BinaryNode<T> parent,boolean leftChild)
	{
		if(leftChild)
			parent.left=null;
		else
			parent.right=null;
	}
	public void clear()
	{
		this.root = null;
	}
}
