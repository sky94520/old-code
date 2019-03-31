import com.datastructure.*;
public class BinaryTreeTest
{
	public static void main(String[] args)
	{
		String[] prelist = {"A","B","D",null,"G",null,null,null,"C","E",null,null,"F","H"};
		BinaryTree<String> tree = new BinaryTree<String>(prelist);
		System.out.println("isEmpty "+tree.isEmpty());
		System.out.println("节点个数："+tree.size());
		System.out.println("高度 "+tree.height());
		tree.printGenList();
		//先根次序
		System.out.println("先根次序：");
		tree.preorder();
		//中根次序
		System.out.println("\n中根次序：");
		tree.inorder();
		//后根次序
		System.out.println("\n后根次序：");
		tree.postorder();
		//层次遍历
		/*System.out.println("\n层次遍历：");
		tree.levelorder();*/
	}
}
