import com.ren.game.TextureManager;


public class Ribbon 
{
	//图片
	private String id;
	//头
	private int x;
	//窗口 宽 高度
	private int pWidth;
	private int pHeight;
	//背景宽度
	private int width;
	private int moveSpeed;
	//向右移动标志
	private boolean isMoveRight;
	//向左移动标志
	private boolean isMoveLeft;
	
	public Ribbon(int moveSpeed,String id,int width,int height,boolean isRight)
	{
		this.moveSpeed=moveSpeed;
		this.id=id;
		
		pWidth=width;
		pHeight=height;
		//图片宽度
		this.width=TextureManager.getInstance().getDimensionById(id).width;
		
		isMoveRight=isRight;
		isMoveLeft=false;
	}
	public void draw(java.awt.Graphics g)
	{
		TextureManager.getInstance().draw(id,0, 0, pWidth, pHeight, x, 0,width+x, pHeight, g);
		TextureManager.getInstance().draw(id,0, 0, pWidth, pHeight, x-width, 0,x, pHeight, g);
	}
	public void update()
	{
		x=(x+moveSpeed)%width;
		//System.out.println(x-width);
	}
}
