import java.util.*;
import com.datastructure.*;
public class MyString
{
	//public static void main(String[] args)
	{
		int number=5;
		int start=0;
		int distance=2;
		SeqList<String> list= new SeqList<String>(number);
		for(int i=0;i<number;i++)
		list.insert(String.format("%c",'A'+i));
		
		System.out.println(list.toString());
		int i = start;
		while(list.size()>1)
		{
			i=(i+distance-1)%list.size();
			System.out.println("删除"+list.remove(i).toString());
			System.out.println(list.toString());
		}
		System.out.println("恭喜"+list.get(0).toString()+"!你被赦免了");
		System.out.println("删除"+list.remove("C"));
		System.out.println(list.toString());
	}
}
