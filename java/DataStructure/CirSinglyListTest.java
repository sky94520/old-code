import com.datastructure.*;
public class CirSinglyListTest
{
	public static void main(String[] args)
	{
		Integer[] values = {1,3,5,9,10};
		CirSinglyList<Integer> list = new CirSinglyList<Integer>(values);
		CirSinglyList<Integer> list2 = new CirSinglyList<Integer>(values);
		//list.insertDifferent(11);
	//	System.out.println("delete the two?"+list.remove(2));
		System.out.println(list.toString());
		System.out.println("equals?"+list.equals(list2));
	}
}
