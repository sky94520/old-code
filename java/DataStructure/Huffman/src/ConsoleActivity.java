import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import com.datastructure.HuffmanTree;


public class ConsoleActivity 
{
	Class
	//»´æ÷ ‰»Î
	static Scanner in=new Scanner(System.in);
	static int key;
	public static void main(String[] args)
	{
		//HuffmanTree.encode(new File("test.txt"));
		try 
		{
			String string=HuffmanTree.decode(new File("test.binary"),new File("test.password"));
			System.out.println(string);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace(); 
		}
	}
}
