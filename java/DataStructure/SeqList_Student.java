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
		System.out.println("ѧ�����ϣ�" + list.toString() +"\n��"+list.size()+"�ˣ��ɼ�ͳ��");
		for(int i = 0;i < titles.length;i++)
			System.out.println(titles[i] + result[i] +"��");
		System.out.println();
	}
	public static void main(String[] args)
	{
		Student[] group = {
			new Student("����",85),new Student("����",75)
			,new Student("��ǿ",90),new Student("������",80)
			,new Student("����ŵ",60),new Student("����",65)};
		SeqList<Student> lista = new SeqList<Student>(group);
		lista.insert(new Student("������",70));
		int[] grade = {0,60,70,80,90,100};

		String[] titles = {"������","����","�е�","����","����"};
		int[] result = groupCount(lista,grade);
		printCount(lista,titles,result);

		String name = "������";
		Student key = new Student(name,0);
		System.out.println("\\"+name+"\\�ĳɼ��ǣ�"+lista.get(lista.search(key)).score);
		System.out.println("delete" + lista.remove(key));

		SeqList<Student> slistb = new SortedSeqList<Student>(lista);
		result = groupCount(slistb,grade);
		printCount(slistb,titles,result);

		int score = 70;
		key = new Student("",score);
		System.out.println("�ɼ�Ϊ"+ score +"�ֵ�ѧ���ǣ�"+slistb.get(slistb.search(key)).name);
	}
}
