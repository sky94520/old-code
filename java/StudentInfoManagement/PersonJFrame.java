import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.event.*;

public class PersonJFrame extends JFrame implements ActionListener,ListSelectionListener
{
	//����������
	protected PersonJPanel personJPanel;
	//
	protected JList<Person> jList;
	protected DefaultListModel<Person> listModel;
	protected JComboBox<String> comboxs[];
	
	public PersonJFrame(PersonJPanel person,Person[] values)
	{
		super("ѧ���ɼ���Ϣ����ϵͳ");
		this.personJPanel = person;
		
		JPanel rightJPanel = new JPanel(new BorderLayout());
		JSplitPane split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,this.personJPanel,rightJPanel);
		//�ұ߿�����
		this.listModel = new DefaultListModel<Person>();
		for(int i = 0;i<values.length;i++)
			this.listModel.addElement(values[i]);
		this.jList = new JList<Person>(this.listModel);
		this.jList.addListSelectionListener(this);
		//�����Ӱ����б��Ĺ�������
		rightJPanel.add(new JScrollPane(this.jList));
		JPanel buttonJPanel = new JPanel();
		rightJPanel.add(buttonJPanel,"South");
		//��Ӱ�ť
		String[][] str = {{"���","ɾ��","ɾ��ѡ����"},{"���ҹؼ���","����ؼ���"},{"����","��������"}};
		for(int i = 0;i < str[0].length;i++)
		{
			JButton button = new JButton(str[0][i]);
			button.addActionListener(this);
			buttonJPanel.add(button);
		}
		//��Ӳ��ң�����ؼ�����Ͽ�
		this.comboxs = new JComboBox[str[1].length];
		for(int i = 0;i < str[1].length;i++)
		{
			buttonJPanel.add(new JLabel(str[1][i]));
			buttonJPanel.add(this.comboxs[i] = new JComboBox<String>(str[2]));
			this.comboxs[i].addActionListener(this);
		}
		this.getContentPane().add(split);
		//��Ļ����
		this.pack();
	}
	public void valueChanged(ListSelectionEvent ev)
	{
		this.personJPanel.set((Person)this.jList.getSelectedValue());
	}
	public void actionPerformed(ActionEvent ev) 
	{
		if(ev.getActionCommand().equals("���"))
			this.listModel.addElement(this.personJPanel.get());
		if(ev.getActionCommand().equals("ɾ��"))
			if(!this.listModel.removeElement(this.personJPanel.get()))
				JOptionPane.showMessageDialog(PersonJFrame.this,"����ʧ��"+this.personJPanel.get().toString());
		if(ev.getActionCommand().equals("ɾ��ѡ����"))
			if(this.listModel.getSize() == 0)
				JOptionPane.showMessageDialog(PersonJFrame.this, "�б���Ϊ�գ�����ɾ��");
			else
			{
				int i = this.jList.getSelectedIndex();
				if(i == -1)
					JOptionPane.showMessageDialog(PersonJFrame.this,"��ѡ���б��������");
				else
					this.listModel.removeElementAt(i);
			}
		if(ev.getSource() == this.comboxs[0])
		{
			;
		}
		if(ev.getSource() == this.comboxs[1])
		{
			;
		}
	}
}
