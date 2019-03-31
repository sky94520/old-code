public class GenListTest
{
	public static void main(String[] args)
	{
		GenList<Integer> list = new GenList<Integer>();
		list.insert(11);
		list.insert(12);
		list.insert(44);
		GenList<Integer> list2 = new GenList<Integer>();
		list2.insert(11);
		list2.insert(12);
		list2.insert(44);
		
		list.insert(1,list2);
		System.out.println(list.toString());
	}
}
