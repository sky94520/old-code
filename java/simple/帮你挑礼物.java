import java.util.Random;
import java.util.Date;
import java.text.SimpleDateFormat;
public class train {
	public static void givegift() {
		Random random = new Random();
		String[] birthday = {"01/18","08/18"};
		Scanner sc = new Scanner(System.in);
		ArrayList<String> gift = new ArrayList<String>();
		String test = sc.nextLine();
		for(;;) {
		if(!gift.contains(test)&&!test.equals("g")) {
			gift.add(test);
			test = sc.nextLine();
		}
		else if(test.contentEquals("g")){
			break;
		}
		else {
			break;
		}
		}
		SimpleDateFormat df = new SimpleDateFormat("MM/dd");//设置日期格式
		String data = df.format(new Date());
        for(int i=0;i<birthday.length;i++)
        	if(birthday[i].equals(data)) {
        		int index = gift.size();
        		int gg = random.nextInt(index);
        		System.out.println(gift.get(gg));
        		System.out.print("去淘宝店买");
        	}
	}
	public static void main(String[] args) {
		givegift();
	}
}