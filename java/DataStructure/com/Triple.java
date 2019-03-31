public class Triple implements Comparable<Triple>,Addibale<Triple>
{
	int row,column,value;
	//指定 行号 列号 元素值 
	public Triple(int row,int column,int value)
	{
		if(row>=0&&column>=0)
		{
			this.row = row;
			this.column = column;
			this.value = value;
		}
		else
			throw IllegalArgumentException("行列号不能为负号：row="+row+",column="+column);
	}
	public Triple(Triple tri)
	{
		this(tri.row,tri.column,tri.value);
	}
	public String toString()
	{
		return "("+row+","+column+","+value+")";
	}
	public int compareTo(Tripe tri)
	{
		if(this.row == tri.row&&this.column==tri.column)
			return 0;
		return (this.row<tri.row||this.row==tri.row&&this.column<tri.column)?-1:1;
	}
	public boolean equals(Object obj)
	{
		if(obj instanceof Triple)
		{
			Triple tri = (Triple)obj;
			return this.row==tri.row&&this.column==tri.column&&this.value==tri.value;
		}
		return false;
	}
	public void add(Triple term)
	{
		if(this.compareTo(term)==0)
			this.value+=term.value;
		else
			throw new IllegalArgumentException("两项的指数不同，不能相加");
	}
	//约定删除条件，不存储值为0的元素
	public boolean removeable()
	{
		return this.value == 0;
	}
	//返回矩阵对称的三元组
	public Triple toSymmetry()
	{
		return new Triple(this.column,this.row,this.value);
	}
}
