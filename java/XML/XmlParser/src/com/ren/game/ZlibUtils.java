package com.ren.game;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.zip.DataFormatException;
import java.util.zip.Deflater;
import java.util.zip.Inflater;

public class ZlibUtils 
{
	//Ñ¹Ëõ
	public static byte[] compress(byte[] data)
	{
		byte[] output=new byte[0];
		Deflater compresser=new Deflater();
		compresser.reset();
		compresser.setInput(data);
		compresser.finish();
		
		ByteArrayOutputStream bos=new ByteArrayOutputStream(data.length);
		try
		{
			byte[] buf=new byte[1024];
			while(!compresser.finished())
			{
				int i=compresser.deflate(buf);
				bos.write(buf,0,i);
			}
			output=bos.toByteArray();
		}catch(Exception ex)
		{
			output=data;
			ex.printStackTrace();
		}finally
		{
			try
			{
				bos.close();
			}catch(IOException e)
			{
				e.printStackTrace();
			}
		}
		compresser.end();
		return output;
	}
	public static byte[] uncompress(byte[] data)
	{
		byte[] output=new byte[0];
		Inflater uncompresser=new Inflater();
		uncompresser.reset();
		uncompresser.setInput(data);
		ByteArrayOutputStream o=new ByteArrayOutputStream(data.length);
		//DataOutputStream o=new DataOutputStream();
		try
		{
			byte[] buf=new byte[1024];
			while(!uncompresser.finished())
			{
				int i=uncompresser.inflate(buf);
				o.write(buf,0,i);
			}
			output=o.toByteArray();
			
		}catch(DataFormatException e)
		{
			output=data;
			e.printStackTrace();
		}finally
		{
			try
			{
				o.close();
			}catch(IOException e)
			{
				e.printStackTrace();
			}
		}
		uncompresser.end();
		return output;
	}
}
