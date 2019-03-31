import com.datastructure.*;

public class Test
{
	public static void main(String[] args)
	{
		SeqList<String> list1 = new SeqList<String>(5);
		SeqList<String> list2 = null;
		for(int i = 0;i < 5;i++)
		{
			list1.insert(i,String.format("%c",'a' + i));
		}
		list2 = new SeqList<String>(list1);
		//test1
		System.out.println(list1.toString());
		System.out.println(list2.toString());
		
		list2.addAll(list1);
		System.out.println(list2.toString());
	}
}
