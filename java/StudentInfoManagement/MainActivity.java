
public class MainActivity 
{
	public static void main(String[] args)
	{
		java.awt.EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				Person[] person = {new Person("�μ�λ","��","1994.12.14","����ʡ","������"),
								new Person("jhon","��","1995.8.18","����ʡ","�Ͼ��� ")};
				PersonJFrame frame = new PersonJFrame(new PersonJPanel(),person);
				frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
				//������������Ļ����
				frame.setLocationRelativeTo(null);
				frame.setVisible(true);
			}
		});
	}
}
