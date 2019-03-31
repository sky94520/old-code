package com.ren.game;
// Timer类
//区别与java的Timer类，建议加上包名
public class Timer
{
	// 计时器启动的时间
	private long startTicks;
	// 计时器暂停是保存的时间
	private long pausedTicks;
	// 计时器状态
	private boolean paused;
	private boolean started;
	public Timer()
	{
		startTicks = 0;
	    pausedTicks = 0;
	    paused = false;
	    started = false;
	}
	// 启动计时器
	public void start()
	{
	    started = true;
	    paused = false;
	    // 获取当前时钟时间
	    startTicks = System.currentTimeMillis();
	}
	// 停止计时器
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
	// 获取计时器时间
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
	// 检查计时器状态
	public boolean is_started()
	{
		return started;
	}
	boolean is_paused()
	{
		return paused;
	}
}
