public class train {
		private String name;
		private float average;
		private int exam;
		private int homework;
		private String level;
		public train(String name,float average,int exam,int homework,String level){
			this.name = name;
			this.average = average;
			this.exam = exam;
			this.homework = homework;
			this.level = level;
		}
		
		public train(String name,int exam,int homework) {
			this.name = name;
			this.exam = exam;
			this.homework = homework;
		}
		
		public void getaverage(train a) {
			float average = (a.exam + a.homework)/2;
			System.out.println("成绩平均分为："+average);
		}
		
		public void getlevel(train a) {
			float average = (a.exam + a.homework)/2;
			if(0<average&&average<60)
				System.out.println("等级为：D");
			if(59<average&&average<80)
				System.out.println("等级为：C");
			if(79<average&&average<90)
				System.out.println("等级为：B");
			if(89<average)
				System.out.println("等级为：A");
		}

public static void main(String[] args) {
	train a = new train("董峰",100,100);
	a.getaverage(a);
	a.getlevel(a);
}
}