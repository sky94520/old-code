import com.ren.game.Rect;
import com.ren.game.TextureManager;


public class Food 
{
	//坐标
	private int x;
	private int y;
	//尺寸
	private int size;
	//蛇
	private Snake snake;
	//是否存在
	private boolean isExisted;
	//父窗口
	private Game gameP;
	//随即类对象
	private java.util.Random rand;
	
	public Food(Game game,Snake snake)
	{
		this.gameP=game;
		this.snake=snake;
		isExisted=false;
		this.size=50;
		rand=new java.util.Random();
	}
	public void draw(java.awt.Graphics g)
	{
		if(isExisted)
			TextureManager.getInstance().draw("apple",new Rect(0,0,size,size),new Rect(x,y,size,size), g);
	}
	public void update()
	{
		//不存在 则重置
		if(!isExisted)
			reset();
		else
		{
			//吃到食物
			if(isColliable(new Rect(snake.x,snake.y,snake.size,snake.size),new Rect(x,y,size,size)))
			{
				if(snake.length<snake.MAXLENGTH)
					snake.length++;
				isExisted=false;
			}
		}
	}
	public static boolean isColliable(Rect a,Rect b)
	{
		int leftA=a.x;
		int rightA=a.x+a.w;
		int topA=a.y;
		int bottomA=a.y+a.h;
		
		int leftB=b.x;
		int rightB=b.x+b.w;
		int topB=b.y;
		int bottomB=b.y+b.h;
		
		if(bottomA<=topB) return false;
		if(topA>=bottomB) return false;
		if(rightA<=leftB) return false;
		if(leftA>=rightB) return false;
		return true;
	}
	//重置
	public void reset()
	{
		//获取画布大小
		int width=800;
		int height=500;
		//设置 食物坐标
		x=Math.abs(rand.nextInt()%gameP.width);
		y=Math.abs(rand.nextInt()%gameP.height);
		
		isExisted=true;
	}
}
