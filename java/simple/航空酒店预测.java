import java.util.Calendar;

import java.util.Date;
import java.text.SimpleDateFormat;
public class train {
		private String name;
		private int price;
		private String time;
		private static int room = 10;
		
		public train(String name,int price) {
			this.name = name;
			this.price = price;
			SimpleDateFormat format = new SimpleDateFormat("YY/MM/dd HH:MM");
			Calendar c = Calendar.getInstance();
			c.setTime(new Date());
		    Date m = c.getTime();
		    this.time = format.format(m);
		}
		
		public void book() {
			if(this.room == 0) {
				System.out.println("对不起，没有房间了");
			}
			else {
			this.room = room - 1;
			System.out.println("房间还有"+room+"间");
			}
		}
		
		public void info() {
			if(this.room == 0) {
				System.out.println("对不起，您没有订到房间！");
			}
			else {
			System.out.println("酒店名是："+this.name);
			System.out.println("酒店价格是："+this.price+"每晚");
			System.out.println("预定时间是："+this.time);
		}
		}

public static void main(String[] args) {
	train a = new train("7天",100);
	a.book();
	a.info();
}