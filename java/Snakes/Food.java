import com.ren.game.Rect;
import com.ren.game.TextureManager;


public class Food 
{
	//����
	private int x;
	private int y;
	//�ߴ�
	private int size;
	//��
	private Snake snake;
	//�Ƿ����
	private boolean isExisted;
	//������
	private Game gameP;
	//�漴�����
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
		//������ ������
		if(!isExisted)
			reset();
		else
		{
			//�Ե�ʳ��
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
	//����
	public void reset()
	{
		//��ȡ������С
		int width=800;
		int height=500;
		//���� ʳ������
		x=Math.abs(rand.nextInt()%gameP.width);
		y=Math.abs(rand.nextInt()%gameP.height);
		
		isExisted=true;
	}
}
