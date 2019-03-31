import com.datastructure.*;
class CirDoublyListTest
{
	public static void main(String[] args)
	{
		Integer[] values = {1,8,11,4,55};
		CirDoublyList<Integer> list = new CirDoublyList<Integer>(values);
		list.remove(55);

		System.out.println(list.toString());
		System.out.println("isEmpty?"+list.isEmpty());
		System.out.println("contains 8?"+list.contains(8));
		System.out.println("size"+list.size());
		System.out.println("set(2)"+list.set(2,99));
		System.out.println("get(2)"+list.get(2));
	}
}
