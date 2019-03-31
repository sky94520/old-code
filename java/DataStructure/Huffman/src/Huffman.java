import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Scanner;

import com.datastructure.HuffmanTree;


public class Huffman 
{
	private HuffmanTree huffmanTree;
	//�����ļ�
	public Huffman()
	{
	}
	//�ļ��������� �������ı� �����Ʒ���
	public static void saveBinaryToFile(String fileName,String text) throws IOException
	{
		//���ļ�
		File file=new File(fileName);
		if(!file.exists())
			file.createNewFile();
		//�������
		FileOutputStream output=new FileOutputStream(file);
		byte temp=0;
		int times=text.length()-text.length()%8;
		//�����������ֽڲ�д��  Byte 1 Byte=8 bit
		for(int i=0;i<times;i+=8)
		{
			temp=parseByte(text.substring(i,i+8),2);
			
			//System.out.println(temp);
			output.write(temp);
		}
		//���µ�λ��[0,7].����ǰ�汣�����
		//���µ��м�λ
		output.write((byte)(text.length()%8));
		try
		{
			temp=Byte.parseByte(text.substring(times),2);
			//8�ı�������Ϊ0
		}catch(java.lang.NumberFormatException e)
		{
			temp=0;
		}
		output.write(temp);
		output.close();
	}
	//���ļ�����ȡ������
	public static String openBinaryFile(String fileName) throws IOException
	{
		File file=new File(fileName);
		FileInputStream input=new FileInputStream(file);
		//�����ֽ��������� String
		byte[] get=new byte[(int)file.length()];
		//��ȡ
		input.read(get);
		input.close();
		String str="";
		for(int i=0;i<get.length-2;i++)
			str+=toBinaryString(get[i]);
		//����ʣ�µ�λ��
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
		//�����ֽ��������� String
		byte[] get=new byte[(int)file.length()];
		//��ȡ
		input.read(get);
		input.close();
		String str="";
		for(int i=0;i<get.length-2;i++)
			str+=toBinaryString(get[i]);
		//����ʣ�µ�λ��
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
		//����8λ����0���
		String str="";
		for(int j=0;j<8-temp.length();j++)
			str+="0";
		return str+temp;
	}
}
