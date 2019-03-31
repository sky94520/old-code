
public class Student extends Object implements Comparable<Student>
{
	public String name;
	public int score;
	public Student(String name,int score)
	{
		this.name = name;
		this.score = score;
	}
	public String toString()
	{
		return "(" + this.name + "," + this.score + ")";
	}
	public boolean equals(Object obj)
	{
		return this == obj || (obj instanceof Student) && 
			this.name.equals(((Student)obj).name);

	}
	public int compareTo(Student stu)
	{
		return this.score - stu.score;
	}
}
