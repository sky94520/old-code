import com.datastructure.*;

public class SeqListTest
{
	public static void main(String[] args)
	{
		Integer[] values = {7,5,12,5};
		SinglyList<Integer> list = new SinglyList<Integer>(values);
		SinglyList<Integer> list2 = new SinglyList<Integer>(values);

		System.out.println(list.toString());
		//list.insert(1,8);
		System.out.println("equals"+list.equals(list2));
		System.out.println("remove[0,2)"+list.remove(0,2).toString());
		System.out.println("\n"+list.toString());
	}
}
