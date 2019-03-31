import com.datastructure.*;
/*Jose*/
public class Josephus
{
	public static void main(String[] args)
	{
		int start = 0;
         	int number = 5;
	        int distance = 2;
		//init
		SeqList<String> list = new SeqList<String>(number);

		for(int i = 0;i < number;i++)
			list.insert(i,String.format("%c",'A' + i));
		System.out.println("Josephus环，初始人物：" + list.toString());
		//记录开始处
		int i = start;
		while(list.size() > 1)
		{
			i = (i + distance - 1)%list.size();
			System.out.println(list.remove(i).toString() + "死亡。剩余:" + list.toString());
		}
		System.out.println("恭喜" + list.get(0).toString() + ",你活下来了！！！");
	}
}
