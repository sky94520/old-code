package com.ren.game;

import java.awt.event.KeyEvent;

public class InputHandler 
{
	//
	public static int KEY_DOWN=0;
	public static int KEY_UP=1;
	public static int KEY_RIGHT=2;
	public static int KEY_LEFT=3;
	//¿Õ¸ñ
	public static int KEY_SPACE=4;
	
	private boolean[] keyStates;
	private static InputHandler gInstance=null;
	public static InputHandler getInstance()
	{
		if(gInstance==null)
			gInstance=new InputHandler();
		return gInstance;
	}
	private  InputHandler()
	{
		keyStates=new boolean[4];
	}
	public boolean isKeyDown(int key)
	{
		if(key>=keyStates.length)
			return false;
		return keyStates[key];
	}
	public void update(int keyCode,boolean isPressed)
	{
		switch(keyCode)
		{
		case KeyEvent.VK_DOWN:
			keyStates[KEY_DOWN]=isPressed?true:false;
			break;
		case KeyEvent.VK_UP:
			keyStates[KEY_UP]=isPressed?true:false;
			break;
		case KeyEvent.VK_LEFT:
			keyStates[KEY_LEFT]=isPressed?true:false;
			break;
		case KeyEvent.VK_RIGHT:
			keyStates[KEY_RIGHT]=isPressed?true:false;
			break;	
		case KeyEvent.VK_SPACE:
			keyStates[KEY_SPACE]=isPressed?true:false;
			break;	
		}
	}
}
