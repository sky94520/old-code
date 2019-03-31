
public class TBFS extends TEight
{
	public TBFS(String fname) 
	{
		super(fname);
	}
	public TBFS(TBFS t)
	{
		p=new Integer[9];
		for(int i=0;i<9;i++)
			p[i]=t.p[i];
		
		this.last=t.last;
		this.spac=t.spac;
		this.total=t.total;
	}
	public TBFS(Integer[]p,Integer[]q1,int last,int spac)
	{
		this.p=new Integer[9];
		q=new int[9];
		for(int i=0;i<9;i++)
		{
			this.p[i]=p[i];
			q[i]=q1[i];
		}
		this.last=last;
		this.spac=spac;
	}
	public int Repeat(SinglyList<TBFS> list)
	{
		return list.repeat(this);
	}
    public boolean Find()
    {
    	for(int i=0;i<9;i++)
			if(p[i]!=q[i])
				return false;
		return true;
    }
    public boolean equals(Object obj)
    {
    	if(obj instanceof TBFS)
    	{
    		TBFS temp=(TBFS)obj;
    		for(int i=0;i<9;i++)
    			if(p[i]!=temp.p[i])
    				return false;
    		return true;
    	}
    	return false;
    }
	@Override
	public void Search() 
	{
		TBFS T=this;  
	    SinglyList<TBFS> L=new SinglyList<TBFS>();  
	    L.insert(T);  
	    int head=0,tail=0;
	    
	    while(head<=tail)  
	    {  
	        for(int i=0;i<4;i++)  
	        {
	            T=L.getData(head);
	            if(T.Extend(i) && L.repeat(T)>tail)  
	            {  
	                T.last=head;  
	                L.insert(T);  
	                tail++;  
	            }  
	            if(T.Find())
	            {
	            	System.out.println("∆•≈‰≥…π¶");
	                T.Printf();  
	                return;  
	            }  
	        }  
	        head++;  
	    }  
	}
	public void Printl(SinglyList<TBFS> L)
	{
		TBFS T=this;  
	    if(T.last==-1)  
	        return;  
	    else  
	    {  
	        T=L.getData(T.last);  
	        T.Printl(L);
	        T.Printf();
	    }  
	}
	public String toString()
	{
		StringBuilder builder=new StringBuilder();
		for(int i=0;i<9;i++)
		{
			builder.append(p[i]+((i+1)%3==0?"\n":" "));
		}
		return builder.toString();
	}
}
