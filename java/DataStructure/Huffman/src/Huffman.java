import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Scanner;

import com.datastructure.HuffmanTree;


public class Huffman 
{
	private HuffmanTree huffmanTree;
	//解析文件
	public Huffman()
	{
	}
	//文件保存名字 ，保存文本 二进制分析
	public static void saveBinaryToFile(String fileName,String text) throws IOException
	{
		//打开文件
		File file=new File(fileName);
		if(!file.exists())
			file.createNewFile();
		//打开输出流
		FileOutputStream output=new FileOutputStream(file);
		byte temp=0;
		int times=text.length()-text.length()%8;
		//分析整个的字节并写入  Byte 1 Byte=8 bit
		for(int i=0;i<times;i+=8)
		{
			temp=parseByte(text.substring(i,i+8),2);
			
			//System.out.println(temp);
			output.write(temp);
		}
		//余下的位数[0,7].另在前面保存个数
		//余下的有几位
		output.write((byte)(text.length()%8));
		try
		{
			temp=Byte.parseByte(text.substring(times),2);
			//8的倍数，设为0
		}catch(java.lang.NumberFormatException e)
		{
			temp=0;
		}
		output.write(temp);
		output.close();
	}
	//打开文件，读取并返回
	public static String openBinaryFile(String fileName) throws IOException
	{
		File file=new File(fileName);
		FileInputStream input=new FileInputStream(file);
		//根据字节数来定义 String
		byte[] get=new byte[(int)file.length()];
		//读取
		input.read(get);
		input.close();
		String str="";
		for(int i=0;i<get.length-2;i++)
			str+=toBinaryString(get[i]);
		//解析剩下的位数
		if(get[get.length-2]!=0)
		{
			String str2=toBinaryString(get[get.length-1]);
			str2=str2.substring(str2.length()-get[get.length-2]);
		
			str+=str2;
		}
		//System.out.println(str);
		return str;
	}
	public static String openBinaryFile(File file) throws IOException
	{
		FileInputStream input=new FileInputStream(file);
		//根据字节数来定义 String
		byte[] get=new byte[(int)file.length()];
		//读取
		input.read(get);
		input.close();
		String str="";
		for(int i=0;i<get.length-2;i++)
			str+=toBinaryString(get[i]);
		//解析剩下的位数
		if(get[get.length-2]!=0)
		{
			String str2=toBinaryString(get[get.length-1]);
			str2=str2.substring(str2.length()-get[get.length-2]);
		
			str+=str2;
		}
		//System.out.println(str);
		return str;
	}
	public static void main(String[] args) throws IOException
	{
		String text="00001111 1110 0101 1011 1110";
		           //00001111 1110 0101 1011 1110 00
		//saveBinaryToFile("example.txt",text);
		System.out.println(openBinaryFile("example.txt"));
	}
	public static byte parseByte(String str,int radix)
	{
		int temp=Integer.parseInt(str,2);
		if(str.charAt(0)=='1')
			temp-=256;
		return (byte)temp;
	}
	public static String toBinaryString(int i)
	{
		String temp=Integer.toBinaryString(i);
		if(temp.length()>8)
			return temp.substring(temp.length()-8);
		//不满8位，以0填充
		String str="";
		for(int j=0;j<8-temp.length();j++)
			str+="0";
		return str+temp;
	}
}
