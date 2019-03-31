import com.ren.game.TextureManager;


public class Ribbon 
{
	//ͼƬ
	private String id;
	//ͷ
	private int x;
	//���� �� �߶�
	private int pWidth;
	private int pHeight;
	//�������
	private int width;
	private int moveSpeed;
	//�����ƶ���־
	private boolean isMoveRight;
	//�����ƶ���־
	private boolean isMoveLeft;
	
	public Ribbon(int moveSpeed,String id,int width,int height,boolean isRight)
	{
		this.moveSpeed=moveSpeed;
		this.id=id;
		
		pWidth=width;
		pHeight=height;
		//ͼƬ���
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
