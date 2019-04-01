public class train {
	public int price;
	public int id;
	public int left;
	public train(int price,int id,int left) {
		this.price = price;
		this.id = id;
		this.left = left;
	}
	
	public void sole(train a) {
		if(a.left < 0||a.left==0) {
			System.out.println("没有库存了");
			
		}
		else {
			a.left = a.left - 1;
		}
	}
	public void total(train a) {
		int t = a.left * a.price;
		System.out.print("总价为："+t);
	}
	
	 public static class store extends train{

		public store(int price, int id, int left) {
			super(price, id, left);
		}
		public void sole(store a) {
			super.sole(a);
		}
		public void total(store a) {
			super.total(a);
		}
	}

public static void main(String[] args) {
		store s = new store(7,1,5);
		s.sole(s);
		s.total(s);
	
}
}