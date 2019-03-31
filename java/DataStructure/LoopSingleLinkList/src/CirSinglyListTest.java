import com.datastructure.*;
public class CirSinglyListTest
{
	public static void main(String[] args)
	{
		Integer[] values = {1,3,5,9,10};
		CirSinglyList<Integer> list = new CirSinglyList<Integer>(values);
		CirSinglyList<Integer> list2 = new CirSinglyList<Integer>(list);
		//插入
		list2.insert(new Integer(11));
		//寻找
		Node<Integer> temp=list2.search(9);
		System.out.println("search:"+temp==null?"temp为空":temp.toString());
		//判断是否相等
		System.out.println("equals?"+list.equals(list2));
		//操作后
		System.out.println(list.toString());
		System.out.println(list2.toString());
	}
}
