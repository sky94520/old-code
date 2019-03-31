import com.datastructure.*;
public class SortedSeqListTest
{
	public static void main(String[] args)
	{
		Integer[] values = {4,50,1,55,2,77};
		SeqList<Integer> list1 = new SeqList<Integer>(values);
		SortedSeqList<Integer> slist = new SortedSeqList<Integer>(list1);

		System.out.println("list1:" + list1.toString());
		System.out.println("slist:" + slist.toString());
	}
}
