class book{
	private String name;
	private int page;
	private int num;
	private int inout;
	public book(String name,int page,int num) {
		this.name = name;
		this.page = page;
		this.num  = num;
		this.inout = 0;
	}
	public void getinfo() {
		String state;
		if(this.inout == 1)
		{
			state = "�ѽ��";
		}
		else {
			state = "δ���";
		}
		System.out.println("������"+this.name);
		System.out.println("ҳ����"+this.page);
		System.out.println("��ţ�"+this.num);
		System.out.println("�Ƿ�����"+state);
			
	}
	public void lend() {
		this.inout = 1;
	}
	public void back() {
		this.inout = 0;
	}
}
public class train {

public static void main(String[] args) {
	book a = new book("python",100,100);
	a.lend();
	a.getinfo();
	a.back();
	a.getinfo();
	
}
}