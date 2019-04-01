import java.util.Date;
import java.text.SimpleDateFormat;
public class train {
		private String filename;
		private String lendtime;
		private String deadtime;
		private int price;
		public train(String filename,String lendtime,String deadtime,int price){
			this.filename = filename;
			this.lendtime = lendtime;
			this.deadtime = deadtime;
			this.price = price;
		}
		public train(String filename) {
			this.filename = filename;	
			SimpleDateFormat format = new SimpleDateFormat("MM/dd");
			this.lendtime = format.format(new Date());
		    Calendar c = Calendar.getInstance();
			c.setTime(new Date());
		    c.add(Calendar.MONTH, +1);
		    Date m = c.getTime();
		    this.deadtime = format.format(m);	 
		}
		public int getprice(train a) {
			String deadtime = a.deadtime;
			int deadtimemouth = Integer.parseInt(deadtime.substring(0,2));
			int deadtimeday = Integer.parseInt(deadtime.substring(3,5));
			SimpleDateFormat format = new SimpleDateFormat("MM/dd");
			Calendar c = Calendar.getInstance();
			c.setTime(new Date());
		    Date m = c.getTime();
		    String time = format.format(m);
			int timemouth = Integer.parseInt(time.substring(0,2));
			int timeday = Integer.parseInt(time.substring(3,5));
			int price = (Math.abs(timemouth-deadtimemouth)*30 + Math.abs(timeday-deadtimeday)) * 1;
			return price;
		}
	

public static void main(String[] args) {
		train t = new train("霸王别姬");
		System.out.println("影片名:"+t.filename);
		System.out.println("借书时间:"+t.lendtime);
		System.out.println("到期时间:"+t.deadtime);
		int price = t.getprice(t);
		System.out.println("逾期费用:"+price+"元");
}
}