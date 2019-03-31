
import com.datastructure.*;

public class SinglyListTest 
{
	public static void main(String[] args)
	{
		Integer[] values = {2,5,99,100,50};
		SinglyList<Integer> list = new SinglyList<Integer>(values);
		SinglyList<Integer> list2 = new SinglyList<Integer>(list);

		System.out.println("�Ƿ���ȡ�list1 == list2" + list.equals(list2));

		System.out.println("��ʼֵ:" + list.toString());
		System.out.println("�Ƿ�Ϊ��:" + list.isEmpty());
		System.out.println("����:" + list.insert(9,8));
		System.out.println("����������:" + list.toString());
		System.out.println("����ֵ 99:λ��:"+ list.search(99).toString());
		System.out.println("ɾ����[3]λ��:" + list.remove(3));
		System.out.println("����������:" + list.toString());
		System.out.println("Ψһ����:"+ list.insertDifferent(99));
		System.out.println("����������:" + list.toString());

		System.out.println("copy:list2:" + list2.toString());
		System.out.println("�Ƿ���ȡ�list1 == list2" + list.equals(list2));
	}
}
