import java.util.Random;
public class train {
	public static void isluck() {
		Random random = new Random();
		int gg = random.nextInt(7)+1;
		switch(gg){
			case 1:
				System.out.print("今天运势为1");
				break;
			case 2:
				System.out.print("今天运势为2");
				break;
			case 3:
				System.out.print("今天运势为3");
				break;
			case 4:
				System.out.print("今天运势为4");
				break;
			case 5:
				System.out.print("今天运势为5");
				break;
			case 6:
				System.out.print("今天运势为6");
				break;
			case 7:
				System.out.print("今天运势为7");
				break;
		}
	
	}
	public static void main(String[] args) {
		isluck();
	}
}