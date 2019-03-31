public class Person 
{
	public String name;
	public String sex;
	public String birthday;
	public String province;
	public String city;
	public Person(String n,String s,String b,String p,String c)
	{
		this.name = n;this.sex = s;this.birthday = b;
		this.province = p;this.city = c;
	}
	public String toString()
	{
		StringBuffer buffer = new StringBuffer();
		buffer.append(this.name+",");
		buffer.append(this.sex+",");
		buffer.append(this.birthday+",");
		buffer.append(this.province+",");
		buffer.append(this.city);
		return buffer.toString();
	}
	public boolean equals(Person p)
	{
		return this==p||p!=null&&this.name.equals(p.name)
				&&this.sex.equals(p.sex)&&this.birthday.equals(p.birthday)
				&&this.province.equals(p.province)&&this.city.equals(p.city);
	}
}
