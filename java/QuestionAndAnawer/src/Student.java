import java.io.Serializable;

public class Student implements Serializable,Comparable<Student>
{
	private String order = null;
	private String name = null;
	private String major = null;
	private float score = 0.f;
	
	public Student(String order, String name, String major,float score) 
	{
		super();
		this.order = order;
		this.name = name;
		this.major = major;
		this.score = score;
	}

	public String getOrder() {
		return order;
	}

	public void setOrder(String order) {
		this.order = order;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getMajor() {
		return major;
	}

	public void setMajor(String major) {
		this.major = major;
	}

	public float getScore() {
		return score;
	}

	public void setScore(float score) {
		this.score = score;
	}

	@Override
	public String toString() {
		return "[order=" + order + ", name=" + name + ", major="
				+ major + ", score=" + score + "]";
	}

	@Override
	public int compareTo(Student arg0) 
	{
		// TODO Auto-generated method stub
		if (this.score > arg0.getScore())
			return -1;
		else if (this.score < arg0.getScore())
			return 1;
		else
			return 0;
	}
	
}
