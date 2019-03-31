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
		//读取学生列表
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
	//进行数据的保存
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
		System.out.println("1.增加学生信息");
		System.out.println("2.删除学生信息");
		System.out.println("3.修改学生信息");
		System.out.println("4.查找学生信息");
		System.out.println("5.成绩排序");
		System.out.println("6.添加题目");
		System.out.println("7.显示所有题目");
		System.out.println("8.做题");
		System.out.println("0.退出");
	}
	public void addStu(Scanner scan)
	{
		System.out.println("---增加学生---");
		System.out.println("学号 姓名 专业 成绩");
		
		String order = scan.next();
		String name = scan.next();
		String major = scan.next();
		float score = scan.nextFloat();
		//保存至学生链表
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
		
		System.out.println("添加成功");
	}
	public void delStu(Scanner scan)
	{
		System.out.println("---删除学生---");
		System.out.println("请输入要删除的对应学生的学号");
		
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
		//TODO删除对应的课程
		if (bRet)
			System.out.println("删除成功");
		else
			System.out.println("查无此人");
	}
	public void modifyStu(Scanner scan)
	{
		System.out.println("请输入要修改的学生 信息(以学号进行匹配 学号不可修改)");
	
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
			System.out.println("修改成功");
		else
			System.out.println("查无此人，修改失败");
	}
	public void searchStu(Scanner scan)
	{
		System.out.println("查询");
		System.out.println("1.学号 2.姓名");
		System.out.println("请在选择条件后接着输入学号或者姓名");
		
		String condition = scan.next();
		String str = scan.next();
		boolean bRet = false;
		//查找
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
			System.out.println("未找到该学生");
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
			System.out.println("合格率" + rate * 100 + "%");
		}
	}
	public void addQuestion(Scanner scan)
	{
		System.out.println("请输入 题干 四个题干以及正确答案的索引");
		
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
			System.out.println("请输入正确答案");
			String result = scan.next();
			
			String answer = String.valueOf(question.getAnswerStr());
			if (result.equalsIgnoreCase(answer))
			{
				successfulNum++;
			}
		}
		System.out.println("你答对了"+ successfulNum + "道题");
		System.out.println("正确率为" + (float)successfulNum / size * 100 + "%");
	}
	public static void main(String[] args)
	{
		//创建管理系统
		ManageSystem system = new ManageSystem();
		Scanner scan = new Scanner(System.in);
		//管理系统初始化，进行文件的读取，与赋值
		system.initlize();
		int key = 0;
		boolean quit = false;
		//输出主界面
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
		//进行数据的保存
		system.end();
		scan.close();
	}	
}
