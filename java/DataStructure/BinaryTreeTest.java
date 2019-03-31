import com.datastructure.*;
public class BinaryTreeTest
{
	public static void main(String[] args)
	{
		String[] prelist = {"A","B","D",null,"G",null,null,null,"C","E",null,null,"F","H"};
		BinaryTree<String> tree = new BinaryTree<String>(prelist);
		System.out.println("isEmpty "+tree.isEmpty());
		System.out.println("�ڵ������"+tree.size());
		System.out.println("�߶� "+tree.height());
		tree.printGenList();
		//�ȸ�����
		System.out.println("�ȸ�����");
		tree.preorder();
		//�и�����
		System.out.println("\n�и�����");
		tree.inorder();
		//�������
		System.out.println("\n�������");
		tree.postorder();
		//��α���
		/*System.out.println("\n��α�����");
		tree.levelorder();*/
	}
}
