import com.datastructure.*;

public class SeqList_Student
{
	//
	public static int[] groupCount(SeqList<Student> list,int grade[])
	{
		int result[] = new int[grade.length];
		for(int i = 0;i < list.size();i++)
		{
			Student stu = list.get(i);
			for(int j = 0;j < grade.length;j++)
			{
				if(stu.score >= grade[j] && stu.score< grade[j + 1])
				{
					result[j] ++;
					break;
				}
			}
		}
		return result;
	}
	public static void printCount(SeqList<Student> list,String titles[],int result[])
	{
		System.out.println("学生集合：" + list.toString() +"\n共"+list.size()+"人，成绩统计");
		for(int i = 0;i < titles.length;i++)
			System.out.println(titles[i] + result[i] +"人");
		System.out.println();
	}
	public static void main(String[] args)
	{
		Student[] group = {
			new Student("王红",85),new Student("张明",75)
			,new Student("李强",90),new Student("崔晓兵",80)
			,new Student("陈新诺",60),new Student("吴宁",65)};
		SeqList<Student> lista = new SeqList<Student>(group);
		lista.insert(new Student("崔晓兵",70));
		int[] grade = {0,60,70,80,90,100};

		String[] titles = {"不及格","及格","中等","良好","优秀"};
		int[] result = groupCount(lista,grade);
		printCount(lista,titles,result);

		String name = "崔晓兵";
		Student key = new Student(name,0);
		System.out.println("\\"+name+"\\的成绩是："+lista.get(lista.search(key)).score);
		System.out.println("delete" + lista.remove(key));

		SeqList<Student> slistb = new SortedSeqList<Student>(lista);
		result = groupCount(slistb,grade);
		printCount(slistb,titles,result);

		int score = 70;
		key = new Student("",score);
		System.out.println("成绩为"+ score +"分的学生是："+slistb.get(slistb.search(key)).name);
	}
}
