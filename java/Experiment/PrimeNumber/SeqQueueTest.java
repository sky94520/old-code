import com.datastructure.*;

public class SeqQueueTest 
{
	final static Integer MAX_NUMBER = 10;
	public static void main(String[] args)
	{
		SeqQueue<Integer> queue = new SeqQueue<Integer>();
		//initialize
		for(int i = 2;i <= MAX_NUMBER;i++)
			queue.add(i);

		Integer[] a = new Integer[MAX_NUMBER];
		a[0] = 1;
		int j = 0;
		while(!queue.isEmpty()&&j<MAX_NUMBER)
		{
			//
			Integer key = queue.poll();
			//如果不是素数
			if(!isPrimer(a[j] + key))
			{
				a[++j] = key;
			//	System.out.println(a[j]);
			}
			else
				queue.add(key);
			
		}
		for(int i = 0;i < a.length;i++)
			System.out.println(a[i] + " ");
	}
	public static boolean isPrimer(Integer n)
	{
		int i =(int) Math.sqrt(n);
		int j = 2;
		while(j <= i)
		{
			if(n%j == 0)
				return true;
			j++;
		}
		return false;
	}
}
