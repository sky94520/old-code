import com.datastructure.*;
public class CirSinglyListTest
{
	public static void main(String[] args)
	{
		Integer[] values = {1,3,5,9,10};
		CirSinglyList<Integer> list = new CirSinglyList<Integer>(values);
		CirSinglyList<Integer> list2 = new CirSinglyList<Integer>(list);
		//����
		list2.insert(new Integer(11));
		//Ѱ��
		Node<Integer> temp=list2.search(9);
		System.out.println("search:"+temp==null?"tempΪ��":temp.toString());
		//�ж��Ƿ����
		System.out.println("equals?"+list.equals(list2));
		//������
		System.out.println(list.toString());
		System.out.println(list2.toString());
	}
}
