import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

import javax.swing.border.TitledBorder;

public class PersonJPanel extends JPanel
{
	private JTextField textField_name,textField_date;
	private JRadioButton[] radioButton_sex;
	
	private JComboBox combox_province,combox_city;
	private static String[] provinces = {"����ʡ","����ʡ","�㽭ʡ"};
	private static String[][] cities = {{"֣����","������"},{"�Ͼ���","������","������"},{"������","������","������"}};
	public PersonJPanel()
	{
		//������������
		this.setBorder(new TitledBorder("Person"));
		//�������Ϊ���񲼾� 5 �� 1��
		this.setLayout(new GridLayout(5,1));
		//����
		textField_name = new JTextField("����");
		this.add(this.textField_name);
		//��������
		textField_date = new JTextField("��������");
		this.add(this.textField_date);
		//�Ա�ѡ��
		JPanel panel_sex = new JPanel(new GridLayout(1,2));
		ButtonGroup buttonGroup = new ButtonGroup();
		radioButton_sex = new JRadioButton[2];
		panel_sex.add(this.radioButton_sex[0] = new JRadioButton("��"));
		panel_sex.add(this.radioButton_sex[1] = new JRadioButton("Ů"));
		buttonGroup.add(this.radioButton_sex[0]);
		buttonGroup.add(this.radioButton_sex[1]);
		//���panel
		this.add(panel_sex);
		//��Ӹ�ѡ��
		this.add(this.combox_province = new JComboBox(this.provinces));
		this.add(this.combox_city = new JComboBox(this.cities[0]));
		//Ϊcombox_province����¼�
		this.combox_province.addActionListener(new ActionListener()
							{
								public void actionPerformed(ActionEvent ac)
								{
									int i = combox_province.getSelectedIndex();
									if(cities != null && i!= -1)
									{
										//���������Ͽ���ԭ������
										combox_city.removeAllItems();
										for(int j = 0;j < PersonJPanel.cities[i].length;j++)
											combox_city.addItem(PersonJPanel.cities[i][j]);
									}
								}
							});
	}
	//��������ֱ���ʾp���������
	public void set(Person p)
	{
		if(p == null)
			return;
		textField_name.setText(p.name);
		textField_date.setText(p.birthday);
		if(p.sex.equals("��"))
			radioButton_sex[0].setSelected(true);
		else
			radioButton_sex[1].setSelected(true);
		this.combox_province.setSelectedItem(p.province);
		this.combox_city.setSelectedItem(p.city);
	}
	public Person get()
	{
		String sex = radioButton_sex[0].isSelected()==true?"��":"Ů";
		return new Person(textField_name.getText(),textField_date.getText(),
				sex,(String)combox_province.getSelectedItem(),(String)combox_city.getSelectedItem());
	}
}