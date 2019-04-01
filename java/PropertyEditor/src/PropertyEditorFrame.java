import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.Random;

import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class PropertyEditorFrame extends JFrame implements ListSelectionListener, ActionListener, NameChangeInterface
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	//显示列表
	private DefaultListModel<String> m_model = null;
	private JList<String> m_list = null;
	private final String[] FIELD_LIST = {"Max HP", "Attack", "Mana Attack", "Agility", "Exp"
									   , "Max MP", "Defense", "Mana Defense", "Luck", "Gold"};
	
	private ArrayList<Role> m_roles = new ArrayList<>();
	//上一次的选中项
	private int m_lastSelectedIndex = -1;
	//属性输入框
	private HashMap<String, JTextField> m_properties = new HashMap<>();
	//名字输入框
	private JTextField m_nameField = null;
	
	public PropertyEditorFrame()
	{
		//创建面板
		JPanel panel = new JPanel();
		this.add(panel);
		//创建菜单
		this.createMenu();
		//创建列表
		this.createList(panel);
		//创建属性
		this.createProperties(panel);
		
		m_list.setSelectedIndex(0);
	}
	//创建菜单
	private void createMenu()
	{
		JMenuBar menuBar = new JMenuBar();
		this.setJMenuBar(menuBar);
		//文件菜单
		JMenu fileMenu = new JMenu("文件");
		menuBar.add(fileMenu);
		//菜单项
		ActionListener listener = new MenuItemListener(this);

		JMenuItem openItem = new JMenuItem("打开文件");
		openItem.addActionListener(listener);
		fileMenu.add(openItem);
		//保存
		JMenuItem saveItem = new JMenuItem("保存文件");
		saveItem.addActionListener(listener);
		fileMenu.add(saveItem);
		//另存为
		JMenuItem saveOther = new JMenuItem("另存为");
		saveOther.addActionListener(listener);
		fileMenu.add(saveOther);
	}
	
	private void createList(JPanel parentPanel)
	{
		JPanel panel = new JPanel();
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
		parentPanel.add(panel, BorderLayout.WEST);
		//标签
		JLabel label = new JLabel("角色");
		panel.add(label);
		//滚动条 List
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setPreferredSize(new Dimension(150,400));
		//List
		m_model = new DefaultListModel<>();
		this.setItem(1);
		
		m_list = new JList<>(m_model);
		m_list.addListSelectionListener(this);
		
		scrollPane.getViewport().setView(m_list);
		panel.add(scrollPane);
		//按钮
		JButton changeBtn = new JButton("改变最大值");
		changeBtn.addActionListener(this);
		panel.add(changeBtn);
	}
	
	private void setItem(int number)
	{
		int size = m_model.getSize();
		
		//新增项
		if (number > size)
		{
			for (int i = size; i < number; i++)
			{
				String name = String.format("%03d", i + 1);
				m_model.addElement(name);
				
				Role role = new Role();
				role.setID(i + 1);
				m_roles.add(role);
			}
		}
		//减少项
		else if (number < size)
		{
			for (int i = size; i > number; i--)
			{
				//先更换选中
				if (m_list.getSelectedIndex() == i -1)
					m_list.setSelectedIndex(number - 1);
				//移除
				m_model.removeElementAt(i - 1);
				m_roles.remove(i - 1);
			}
		}
	}
	//根据当前列表选中来更新对应的Role的值
	private void updateRole(int index)
	{
		Role role = m_roles.get(index);
		
		role.setName(m_nameField.getText());

		for (Entry<String, JTextField> entry: m_properties.entrySet())
		{
			String value = entry.getValue().getText();
			role.setProperty(entry.getKey(), Integer.valueOf(value));
		}
	}
	private void createProperties(JPanel parentPanel)
	{
		JPanel panel = new JPanel();
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
		panel.setPreferredSize(new Dimension(400, 400));
		parentPanel.add(panel, BorderLayout.EAST);
		
		JPanel namePanel = new JPanel();
		panel.add(namePanel);
		//名字标签
		namePanel.add(new JLabel("名字"));
		//名字输入框
		m_nameField = new JTextField();
		m_nameField.setPreferredSize(new Dimension(100, 30));
		//添加监听事件
		m_nameField.getDocument().addDocumentListener(new NameListener(this));
		namePanel.add(m_nameField);
		//随机属性按钮
		JButton randBtn = new JButton("随机属性");
		randBtn.addActionListener(new ActionListener() 
		{
			@Override
			public void actionPerformed(ActionEvent arg0) {
				Random random = new Random();
				for (Entry<String, JTextField> entry: m_properties.entrySet())
				{
					int value = random.nextInt(100);
					entry.getValue().setText(String.valueOf(value));
				}
			}
			
		});
		namePanel.add(randBtn);
		
		//属性
		JPanel propPanel = new JPanel();
		propPanel.setLayout(new GridLayout(5, 4));
		panel.add(propPanel);
		//添加属性
		for (String fieldName: FIELD_LIST)
		{
			propPanel.add(new JLabel(fieldName));
			JTextField field = new JTextField();
			field.setText(String.valueOf(0));
			propPanel.add(field);
			m_properties.put(fieldName, field);
		}
	}
	@Override
	public void valueChanged(ListSelectionEvent arg0) 
	{
		//鼠标按下和释放会触发两次，添加此处则仅仅触发一次
		if (arg0.getValueIsAdjusting())
			return ;
		int index = m_list.getSelectedIndex();
		//选中另一项 先保存先前的角色的值
		if (m_lastSelectedIndex != -1)
		{
			this.updateRole(m_lastSelectedIndex);
		}
		//更新角色属性更新控件的值
		Role role = m_roles.get(index);
		
		m_nameField.setText(role.getName());
		for (Entry<String, JTextField> entry: m_properties.entrySet())
		{
			int value = role.getProperty(entry.getKey());
			entry.getValue().setText(String.valueOf(value));
		}	
		m_lastSelectedIndex = index;
	}
	@Override
	public void nameChanged(String name) 
	{
		int index = m_list.getSelectedIndex();
		String text = String.format("%03d %s", index + 1, name);
		m_model.set(index, text);
	}
	@Override
	public void actionPerformed(ActionEvent arg0) 
	{
		String command = arg0.getActionCommand();
		
		if (command == "改变最大值")
		{
			SpinnerDialog dialog = new SpinnerDialog(PropertyEditorFrame.this, "更改最大值", true);
			int size = m_model.getSize();
			
			dialog.setMinimum(1);
			dialog.setValue(size);
			//只有点击确认才会更改
			boolean ret = dialog.showDialog();
			if (ret)
			{
				int value = dialog.getValue();
				this.setItem(value);
			}
		}//end if
	}
	
	public void writeToFile(File file)
	{
		//先更新角色属性
		this.updateRole(m_list.getSelectedIndex());
		//尝试写入
		try {
			//不存在文件，则先创建
			if (!file.exists())
				file.createNewFile();
			
			FileWriter writer = new FileWriter(file);
			//写入
			for (int i = 0; i < m_roles.size(); i++)
			{
				Role role = m_roles.get(i);
				if (i == 0)
				{
					writer.write("ID,Name,");
					writer.write(role.getKeys());
				}
				writer.write('\n');
				
				writer.write(String.valueOf(role.getID()));
				writer.write(',');
				writer.write(role.getName());
				writer.write(',');
				writer.write(role.getValues());
			}
			writer.close();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public void readFromFile(File file)
	{
		BufferedReader reader = null;
		ArrayList<String> keys = new ArrayList<>();
		
		try {
			reader = new BufferedReader(new FileReader(file));
			String line;
			String value;
			int lineNum = 1;
			//逐行读取
			while ((line = reader.readLine()) != null)
			{
				line += ",";
				int begin = 0;
				int end = line.indexOf(',');
				int index = 0;
				Role role = null;
				
				//从第二行开始，每次都新建
				if (lineNum != 1)
				{
					this.setItem(lineNum - 1);
					role = m_roles.get(lineNum - 2);
				}
				//读取属性并赋值
				while (end != -1)
				{
					//获取字段
					value = line.substring(begin, end);
					
					//第一行为属性名称
					if (lineNum == 1)
						keys.add(value);
					//设置值
					else
					{
						if (keys.get(index).equals("ID"))
							role.setID(Integer.valueOf(value));
						else if (keys.get(index).equals("Name"))
							role.setName(value);
						else
							role.setProperty(keys.get(index), Integer.valueOf(value));
					}
					
					//获取下一个字段
					begin = end + 1;
					end = line.indexOf(',', end + 1);
					
					index++;
				}
				//角色填充完毕
				if (lineNum - 2 == m_list.getSelectedIndex())
				{
					//更新角色属性更新控件的值
					m_nameField.setText(role.getName());
					for (Entry<String, JTextField> entry: m_properties.entrySet())
					{
						int num = role.getProperty(entry.getKey());
						entry.getValue().setText(String.valueOf(num));
					}
				}
				//更新 list的名称
				else if (role != null)
				{
					String text = String.format("%03d %s", role.getID(), role.getName());
					m_model.set(role.getID() - 1, text);	
				}
				lineNum++;
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
