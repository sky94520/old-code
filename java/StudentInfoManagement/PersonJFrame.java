import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.event.*;

public class PersonJFrame extends JFrame implements ActionListener,ListSelectionListener
{
	//左边人物界面
	protected PersonJPanel personJPanel;
	//
	protected JList<Person> jList;
	protected DefaultListModel<Person> listModel;
	protected JComboBox<String> comboxs[];
	
	public PersonJFrame(PersonJPanel person,Person[] values)
	{
		super("学生成绩信息管理系统");
		this.personJPanel = person;
		
		JPanel rightJPanel = new JPanel(new BorderLayout());
		JSplitPane split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,this.personJPanel,rightJPanel);
		//右边框内容
		this.listModel = new DefaultListModel<Person>();
		for(int i = 0;i<values.length;i++)
			this.listModel.addElement(values[i]);
		this.jList = new JList<Person>(this.listModel);
		this.jList.addListSelectionListener(this);
		//面板添加包含列表框的滚动窗口
		rightJPanel.add(new JScrollPane(this.jList));
		JPanel buttonJPanel = new JPanel();
		rightJPanel.add(buttonJPanel,"South");
		//添加按钮
		String[][] str = {{"添加","删除","删除选中项"},{"查找关键字","排序关键字"},{"姓名","出生日期"}};
		for(int i = 0;i < str[0].length;i++)
		{
			JButton button = new JButton(str[0][i]);
			button.addActionListener(this);
			buttonJPanel.add(button);
		}
		//添加查找，排序关键字组合框
		this.comboxs = new JComboBox[str[1].length];
		for(int i = 0;i < str[1].length;i++)
		{
			buttonJPanel.add(new JLabel(str[1][i]));
			buttonJPanel.add(this.comboxs[i] = new JComboBox<String>(str[2]));
			this.comboxs[i].addActionListener(this);
		}
		this.getContentPane().add(split);
		//屏幕适配
		this.pack();
	}
	public void valueChanged(ListSelectionEvent ev)
	{
		this.personJPanel.set((Person)this.jList.getSelectedValue());
	}
	public void actionPerformed(ActionEvent ev) 
	{
		if(ev.getActionCommand().equals("添加"))
			this.listModel.addElement(this.personJPanel.get());
		if(ev.getActionCommand().equals("删除"))
			if(!this.listModel.removeElement(this.personJPanel.get()))
				JOptionPane.showMessageDialog(PersonJFrame.this,"操作失败"+this.personJPanel.get().toString());
		if(ev.getActionCommand().equals("删除选中项"))
			if(this.listModel.getSize() == 0)
				JOptionPane.showMessageDialog(PersonJFrame.this, "列表项为空，不能删除");
			else
			{
				int i = this.jList.getSelectedIndex();
				if(i == -1)
					JOptionPane.showMessageDialog(PersonJFrame.this,"请选中列表框数据项");
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
