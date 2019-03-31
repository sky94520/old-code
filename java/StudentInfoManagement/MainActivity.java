
public class MainActivity 
{
	public static void main(String[] args)
	{
		java.awt.EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				Person[] person = {new Person("任继位","男","1994.12.14","河南省","商丘市"),
								new Person("jhon","男","1995.8.18","江苏省","南京市 ")};
				PersonJFrame frame = new PersonJFrame(new PersonJPanel(),person);
				frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
				//将窗口置于屏幕中央
				frame.setLocationRelativeTo(null);
				frame.setVisible(true);
			}
		});
	}
}
