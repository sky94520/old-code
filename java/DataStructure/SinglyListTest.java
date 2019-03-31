
import com.datastructure.*;

public class SinglyListTest 
{
	public static void main(String[] args)
	{
		Integer[] values = {2,5,99,100,50};
		SinglyList<Integer> list = new SinglyList<Integer>(values);
		SinglyList<Integer> list2 = new SinglyList<Integer>(list);

		System.out.println("是否相等。list1 == list2" + list.equals(list2));

		System.out.println("初始值:" + list.toString());
		System.out.println("是否为空:" + list.isEmpty());
		System.out.println("插入:" + list.insert(9,8));
		System.out.println("操作后链表:" + list.toString());
		System.out.println("查找值 99:位置:"+ list.search(99).toString());
		System.out.println("删除第[3]位置:" + list.remove(3));
		System.out.println("操作后链表:" + list.toString());
		System.out.println("唯一插入:"+ list.insertDifferent(99));
		System.out.println("操作后链表:" + list.toString());

		System.out.println("copy:list2:" + list2.toString());
		System.out.println("是否相等。list1 == list2" + list.equals(list2));
	}
}
