import com.datastructure.*;


public class Mainactivity 
{
	public static void main(String[] args)
	{
		String prelist[]={"�й�","\t����","\t����","\t\t�Ͼ�","\t\t����","����","\t�׶�"};
		
		Tree<String> tree=Tree_city.create(prelist);
		//���
		Tree<String> tree2=new Tree<String>(tree);
		//���ĺ����뷨
		System.out.println(tree.toString());
		//equals
		TreeNode<String> p=tree.search("����");
		System.out.println("��ȣ�"+tree.equals(tree2));
		//���Ĺ�����ʾ
		System.out.println("���Ĺ�����ʾ��");
		tree.printGenList();
	}
}
