import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JOptionPane;

import com.datastructure.SeqStack;
import com.datastructure.Stack;

public class ExampleFrame extends SortFrame
{
	JButton nextBtn;
	Stack<TBFS> stack;
	
	
	public ExampleFrame()
	{
		super("演示");
		//设置4*3界面
		this.setLayout(new GridLayout(4,3));
	}
	protected void initlize()
	{
		super.initlize();
		JButton btn1= new JButton("");
		btn1.setEnabled(false);
		this.add(btn1);
		nextBtn=new JButton("下一步");
		this.add(nextBtn);
		nextBtn.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				if(!stack.isEmpty())
				{
					System.out.println("changed");
					TBFS temp=stack.pop();
					System.out.println(temp.toString());
					m_integer=temp.p;
					for(int i=0;i<9;i++)
						m_label[i].setText(""+(m_integer[i]==0?"":m_integer[i]));
					if(isWin())
						JOptionPane.showMessageDialog(ExampleFrame.this,"你赢啦，恭喜");
				}
			}
		});
		Search();
	}
	public void Search()
	{
		//获得到达目的的队列
		TBFS bfs=new TBFS(m_integer,m_result,-1,m_mark);
		SinglyList<TBFS> L=new SinglyList<TBFS>();
		L.insert(bfs);
		
		int head=0,tail=0;
	    
	    while(head<=tail)  
	    {  
	        for(int i=0;i<4;i++)
	        {
	            TBFS T=new TBFS(L.getData(head));
	            if(T.Extend(i) && L.repeat(T)>tail)
	            {  
	                T.last=head;  
	                L.insert(T);  
	                tail++;
	                //System.out.println(T.toString());
	            } 
	            if(T.Find())
	            {
	            	System.out.println("匹配成功");
	            	stack=new SeqStack<TBFS>();
	            	TBFS temp=T;
	            	do
	            	{
	            		stack.push(temp);
	            		temp=L.getData(temp.last);
	            		//System.out.println(temp.toString());
	            	}while(temp.last!=-1);	
	                return;
	            }  
	        }  
	        head++;  
	    }  
		System.out.println("程序结束");
	}
}
