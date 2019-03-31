import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import javax.swing.border.TitledBorder;

public class PersonJPanel extends JPanel
{
	private JTextField textField_name,textField_date;
	private JRadioButton[] radioButton_sex;
	
	private JComboBox combox_province,combox_city;
	private static String[] provinces = {"河南省","江苏省","浙江省"};
	private static String[][] cities = {{"郑州市","商丘市"},{"南京市","苏州市","无锡市"},{"杭州市","宁波市","温州市"}};
	public PersonJPanel()
	{
		//设置面板带标题
		this.setBorder(new TitledBorder("Person"));
		//设置面板为网格布局 5 行 1列
		this.setLayout(new GridLayout(5,1));
		//姓名
		textField_name = new JTextField("姓名");
		this.add(this.textField_name);
		//出生日期
		textField_date = new JTextField("出生日期");
		this.add(this.textField_date);
		//性别选择
		JPanel panel_sex = new JPanel(new GridLayout(1,2));
		ButtonGroup buttonGroup = new ButtonGroup();
		radioButton_sex = new JRadioButton[2];
		panel_sex.add(this.radioButton_sex[0] = new JRadioButton("男"));
		panel_sex.add(this.radioButton_sex[1] = new JRadioButton("女"));
		buttonGroup.add(this.radioButton_sex[0]);
		buttonGroup.add(this.radioButton_sex[1]);
		//添加panel
		this.add(panel_sex);
		//添加复选框
		this.add(this.combox_province = new JComboBox(this.provinces));
		this.add(this.combox_city = new JComboBox(this.cities[0]));
		//为combox_province添加事件
		this.combox_province.addActionListener(new ActionListener()
							{
								public void actionPerformed(ActionEvent ac)
								{
									int i = combox_province.getSelectedIndex();
									if(cities != null && i!= -1)
									{
										//清楚城市组合框中原有内容
										combox_city.removeAllItems();
										for(int j = 0;j < PersonJPanel.cities[i].length;j++)
											combox_city.addItem(PersonJPanel.cities[i][j]);
									}
								}
							});
	}
	//设置组件分别显示p对象的属性
	public void set(Person p)
	{
		if(p == null)
			return;
		textField_name.setText(p.name);
		textField_date.setText(p.birthday);
		if(p.sex.equals("男"))
			radioButton_sex[0].setSelected(true);
		else
			radioButton_sex[1].setSelected(true);
		this.combox_province.setSelectedItem(p.province);
		this.combox_city.setSelectedItem(p.city);
	}
	public Person get()
	{
		String sex = radioButton_sex[0].isSelected()==true?"男":"女";
		return new Person(textField_name.getText(),textField_date.getText(),
				sex,(String)combox_province.getSelectedItem(),(String)combox_city.getSelectedItem());
	}
}