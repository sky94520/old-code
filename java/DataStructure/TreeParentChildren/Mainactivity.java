import com.datastructure.*;


public class Mainactivity 
{
	public static void main(String[] args)
	{
		String prelist[]={"中国","\t北京","\t江苏","\t\t南京","\t\t苏州","韩国","\t首尔"};
		
		Tree<String> tree=Tree_city.create(prelist);
		//深拷贝
		Tree<String> tree2=new Tree<String>(tree);
		//树的横向凹入法
		System.out.println(tree.toString());
		//equals
		TreeNode<String> p=tree.search("北京");
		System.out.println("相等？"+tree.equals(tree2));
		//树的广义表表示
		System.out.println("树的广义表表示：");
		tree.printGenList();
	}
}
