import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Scanner;


public class ManageSystem
{
	private HashMap<String,ArrayList<Student>> studentMap = null;
	private ArrayList<Question> questionList = null;
	
	@SuppressWarnings("unchecked")
	public void initlize()
	{
		//��ȡѧ���б�
		FileInputStream file;
		ObjectInputStream inStream;
		
		try {
			file = new FileInputStream("student");
			inStream = new ObjectInputStream(file);
			
			studentMap = (HashMap<String,ArrayList<Student>>) inStream.readObject();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			studentMap = new HashMap<>();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			file = new FileInputStream("question");
			inStream = new ObjectInputStream(file);
			
			questionList = (ArrayList<Question>) inStream.readObject();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			questionList = new ArrayList<>();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	//�������ݵı���
	public void end()
	{
		try {
			FileOutputStream file;
			ObjectOutputStream outputStream;
			file = new FileOutputStream("student");
			outputStream = new ObjectOutputStream(file);
			
			outputStream.writeObject(studentMap);
			outputStream.close();
			file.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			FileOutputStream file;
			ObjectOutputStream outputStream;
			file = new FileOutputStream("question");
			outputStream = new ObjectOutputStream(file);
			
			outputStream.writeObject(questionList);
			outputStream.close();
			file.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	public static void outputMainScene()
	{
		System.out.println("1.����ѧ����Ϣ");
		System.out.println("2.ɾ��ѧ����Ϣ");
		System.out.println("3.�޸�ѧ����Ϣ");
		System.out.println("4.����ѧ����Ϣ");
		System.out.println("5.�ɼ�����");
		System.out.println("6.�����Ŀ");
		System.out.println("7.��ʾ������Ŀ");
		System.out.println("8.����");
		System.out.println("0.�˳�");
	}
	public void addStu(Scanner scan)
	{
		System.out.println("---����ѧ��---");
		System.out.println("ѧ�� ���� רҵ �ɼ�");
		
		String order = scan.next();
		String name = scan.next();
		String major = scan.next();
		float score = scan.nextFloat();
		//������ѧ������
		Student stu = new Student(order,name,major,score);
		ArrayList<Student> studentList = null;
		
		if (studentMap.containsKey(major))
		{
			studentList = studentMap.get(major);
		}
		else
		{
			studentList = new ArrayList<>();
			studentMap.put(major, studentList);
		}
		studentList.add(stu);
		
		System.out.println("��ӳɹ�");
	}
	public void delStu(Scanner scan)
	{
		System.out.println("---ɾ��ѧ��---");
		System.out.println("������Ҫɾ���Ķ�Ӧѧ����ѧ��");
		
		String order = scan.next();
		boolean bRet = false;
		
		for (String key : studentMap.keySet())
		{
			ArrayList<Student> studentList = studentMap.get(key);
			
			for (Student stu : studentList)
			{
				if (stu.getOrder() == order)
				{
					studentList.remove(stu);
					bRet = true;
					break;
				}
			}
			if (bRet) break;
		}
		//TODOɾ����Ӧ�Ŀγ�
		if (bRet)
			System.out.println("ɾ���ɹ�");
		else
			System.out.println("���޴���");
	}
	public void modifyStu(Scanner scan)
	{
		System.out.println("������Ҫ�޸ĵ�ѧ�� ��Ϣ(��ѧ�Ž���ƥ�� ѧ�Ų����޸�)");
	
		String order = scan.next();
		String name = scan.next();
		String major = scan.next();
		float score = scan.nextFloat();
	
		boolean bRet = false;
		
		for (String key : studentMap.keySet())
		{
			ArrayList<Student> studentList = studentMap.get(key);
			
			for (Student stu : studentList)
			{
				if (stu.getOrder() == order)
				{
					stu.setMajor(major);
					stu.setScore(score);
					stu.setName(name);
					bRet = true;
					break;
				}
			}
			if (bRet) break;
		}
		if (bRet)
			System.out.println("�޸ĳɹ�");
		else
			System.out.println("���޴��ˣ��޸�ʧ��");
	}
	public void searchStu(Scanner scan)
	{
		System.out.println("��ѯ");
		System.out.println("1.ѧ�� 2.����");
		System.out.println("����ѡ���������������ѧ�Ż�������");
		
		String condition = scan.next();
		String str = scan.next();
		boolean bRet = false;
		//����
		for (String key : studentMap.keySet())
		{
			ArrayList<Student> studentList = studentMap.get(key);
			
			for (Student stu : studentList)
			{
				if (condition.equals("1") && stu.getOrder().equals(str)
					|| condition.equals("2") && stu.getName().equals(str))
				{
					System.out.println(stu.toString());
					bRet = true;
				}
			}
		}
		if (!bRet)
			System.out.println("δ�ҵ���ѧ��");
	}
	public void sortStu(Scanner scan)
	{
		for (String key : studentMap.keySet())
		{
			ArrayList<Student> studentList = studentMap.get(key);
			int number = 0;
			
			Collections.sort(studentList);
			
			System.out.println("major:" + key);
			
			for (Student stu:studentList)
			{
				System.out.println(stu.toString());
				
				if (stu.getScore() > 60.f)
				{
					number += 1;
				}
			}
			float rate = (float)number/studentList.size();
			System.out.println("�ϸ���" + rate * 100 + "%");
		}
	}
	public void addQuestion(Scanner scan)
	{
		System.out.println("������ ��� �ĸ�����Լ���ȷ�𰸵�����");
		
		String str1 = scan.next();
		ArrayList<String> answers = new ArrayList<>();
		
		for(int i = 0;i < 4;i++)
		{
			String answer = scan.next();
			answers.add(answer);
		}
		int curIndex = scan.nextInt();
		
		Question question = new Question(str1,answers,curIndex);
		
		questionList.add(question);
	}
	public void outputAllQuestion()
	{
		System.out.println(questionList.toString());
	}
	public void examinate(Scanner scan)
	{
		int successfulNum = 0;
		int size = questionList.size();
		
		for (int i = 0;i < size;i++)
		{
			Question question = questionList.get(i);
			
			System.out.println( (i+1) +"/" + size +" " + question.getQuestion());
			for(String answer:question.getAnswerList())
			{
				System.out.println(answer);
			}
			System.out.println("��������ȷ��");
			String result = scan.next();
			
			String answer = String.valueOf(question.getAnswerStr());
			if (result.equalsIgnoreCase(answer))
			{
				successfulNum++;
			}
		}
		System.out.println("������"+ successfulNum + "����");
		System.out.println("��ȷ��Ϊ" + (float)successfulNum / size * 100 + "%");
	}
	public static void main(String[] args)
	{
		//��������ϵͳ
		ManageSystem system = new ManageSystem();
		Scanner scan = new Scanner(System.in);
		//����ϵͳ��ʼ���������ļ��Ķ�ȡ���븳ֵ
		system.initlize();
		int key = 0;
		boolean quit = false;
		//���������
		do
		{	
			ManageSystem.outputMainScene();
			key = scan.nextInt();
			
			switch(key)
			{
			case 1:{system.addStu(scan);}break;
			case 2:{system.delStu(scan);}break;
			case 3:{system.modifyStu(scan);}break;
			case 4:{system.searchStu(scan);}break;
			case 5:{system.sortStu(scan);}break;
			case 6:{system.addQuestion(scan);}break;
			case 7:{system.outputAllQuestion();}break;
			case 8:{system.examinate(scan);}break;
			case 0:{quit = true;}break;
			}
			
		}while(!quit);
		//�������ݵı���
		system.end();
		scan.close();
	}	
}
