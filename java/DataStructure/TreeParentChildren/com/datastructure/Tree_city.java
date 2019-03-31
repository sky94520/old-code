package com.datastructure;

public class Tree_city 
{
	//�����뷨��ʾ������
	public static Tree<String> create(String[] prelist)
	{
		Tree<String> tree=new Tree<String>();
		if(prelist.length==0)
			return tree;
		tree.root=new TreeNode<String>(prelist[0],1);
		TreeNode<String> p=tree.root;
		for(int i=1;i<prelist.length;i++)
		{
			//ͳ��ǰ׺
			int n=0;
			while(n<prelist[i].length()&&prelist[i].charAt(n)=='\t')
				n++;
			String str=prelist[i].substring(n);
			if(n==p.level)
			{
				p.child=new TreeNode<String>(str,p.level+1,p,null,null);
				p=p.child;
			}
			else
			{
				//Ѱ��ͬ���ڵ�
				while(n<p.level-1)
					p=p.parent;
				p.sibling=new TreeNode<String>(str,p.level,p.parent,null,null);
				
				p=p.sibling;
			}
		}
		return tree;
	}
}
