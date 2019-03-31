package com.ren.game;
// Timer��
//������java��Timer�࣬������ϰ���
public class Timer
{
	// ��ʱ��������ʱ��
	private long startTicks;
	// ��ʱ����ͣ�Ǳ����ʱ��
	private long pausedTicks;
	// ��ʱ��״̬
	private boolean paused;
	private boolean started;
	public Timer()
	{
		startTicks = 0;
	    pausedTicks = 0;
	    paused = false;
	    started = false;
	}
	// ������ʱ��
	public void start()
	{
	    started = true;
	    paused = false;
	    // ��ȡ��ǰʱ��ʱ��
	    startTicks = System.currentTimeMillis();
	}
	// ֹͣ��ʱ��
	public void stop()
	{
		started = false;
		paused = false;

		startTicks = 0;
	}
	public void pause()
	{
		if ((started == true) && (paused == false))
		{
			paused = true;
			pausedTicks = System.currentTimeMillis() - startTicks;
		}
	}
	public void unpause()
	{
		if (paused == true)
		{
	        paused = false;
	        startTicks = System.currentTimeMillis() - pausedTicks;
	        pausedTicks = 0;
		}
	}
	// ��ȡ��ʱ��ʱ��
	public long getTicks()
	{
		if (started == true)
		{
	        if (paused == true)
	            return pausedTicks;
	        else
	            return System.currentTimeMillis() - startTicks;
		}
		return 0;
	}
	// ����ʱ��״̬
	public boolean is_started()
	{
		return started;
	}
	boolean is_paused()
	{
		return paused;
	}
}
