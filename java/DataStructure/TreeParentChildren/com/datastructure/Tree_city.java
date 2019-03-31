package com.datastructure;

public class Tree_city 
{
	//横向凹入法表示构造树
	public static Tree<String> create(String[] prelist)
	{
		Tree<String> tree=new Tree<String>();
		if(prelist.length==0)
			return tree;
		tree.root=new TreeNode<String>(prelist[0],1);
		TreeNode<String> p=tree.root;
		for(int i=1;i<prelist.length;i++)
		{
			//统计前缀
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
				//寻找同级节点
				while(n<p.level-1)
					p=p.parent;
				p.sibling=new TreeNode<String>(str,p.level,p.parent,null,null);
				
				p=p.sibling;
			}
		}
		return tree;
	}
}
