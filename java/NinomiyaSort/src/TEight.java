import java.io.DataInputStream;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;


public abstract class TEight
{
	public static int Num=9;
	protected Integer[] p;  
	protected int last=-1,spac;  
	protected static int[] q;
	protected static int d[]={-3,3,-1,1};
	protected int total =0;
	//
	public abstract void Search();
	public TEight()
	{
	}
	//打开文件
	public  TEight(String fname)
	{
		File file=new File("init.txt");
		try 
		{
			DataInputStream input=new DataInputStream(new FileInputStream(file));
			//static initlize
			p=new Integer[9];
			q=new int[9];
			int ch;
			//读取初始状态
			for(int i=0;i<9;i++)
			{
				ch=input.readByte();
				p[i]=ch-'1'+1;
				if(p[i]==0)
					spac=i;
			}
			//省略 '\n'
			input.skipBytes(2);
			//读取最终状态
			for(int i=0;i<9;i++)
			{
				ch=input.readByte();
				q[i]=ch-'1'+1;
			}
			//
			System.out.println("读取成功");
		}catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}catch(EOFException e){
			e.printStackTrace();
		}
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	protected void Printf()
	{
		StringBuilder builder=new StringBuilder();
		for(int i=0;i<9;i++)
		{
			builder.append(p[i]+((i+1)%3==0?"\n":" "));
		}
		System.out.println(builder.toString());
	}
	protected boolean Extend(int i)
	{
		if(i==0 && spac<3 || i==1 && spac>5   
				|| i==2 && spac%3==0 || i==3 && spac%3==2)  
			return false;  
		int temp=spac;  
		spac+=d[i];  
		//System.out.println("d["+i+"]="+d[i]+"spac"+spac);
		p[temp]=p[spac];  
		p[spac]=0;
		//System.out.println(" first spac="+temp+"end spac"+spac);
		return true;  
	}
	public String toString()
	{
		StringBuilder builder=new StringBuilder();
		for(int i=0;i<9;i++)
		{
			builder.append(p[i]+(i%3==0?'\n':' '));
		}
		return builder.toString();
	}
};  
