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
				System.out.println("�Բ���û�з�����");
			}
			else {
			this.room = room - 1;
			System.out.println("���仹��"+room+"��");
			}
		}
		
		public void info() {
			if(this.room == 0) {
				System.out.println("�Բ�����û�ж������䣡");
			}
			else {
			System.out.println("�Ƶ����ǣ�"+this.name);
			System.out.println("�Ƶ�۸��ǣ�"+this.price+"ÿ��");
			System.out.println("Ԥ��ʱ���ǣ�"+this.time);
		}
		}

public static void main(String[] args) {
	train a = new train("7��",100);
	a.book();
	a.info();
}