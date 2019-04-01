import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.DefaultListSelectionModel;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.JTextField;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
/**
 * 
 * @author ren
 * 多文件命名工具，只能对同一文件夹下的文件命名
 */
public class BatchRenameFrame extends JFrame implements ActionListener, ListSelectionListener
{
	private JLabel m_dirLabel = null;
	private JList<String> m_list = null;
	private JTextField m_filterField = null;
	private DefaultListModel<String> m_model = null;
	private JSpinner m_indexSpinner = null;
	private int m_lastIndex = -1;
	private BatchRename m_batch = null;
	
	public BatchRenameFrame()
	{
		m_batch = new BatchRename();
		
		JPanel panel = new JPanel();
		this.add(panel);
		//滚动条 List
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setPreferredSize(new Dimension(600,400));
		panel.add(scrollPane, BorderLayout.WEST);
		//List
		m_model = new DefaultListModel<>();
		
		m_list = new JList<>(m_model);
		m_list.addListSelectionListener(this);
		//再次点击取消选中
		m_list.setSelectionModel(new DefaultListSelectionModel()
		{
			public void setSelectionInterval(int index1, int index2)
			{
				if (index1 == index2 && isSelectedIndex(index1))
				{
					this.removeSelectionInterval(index1, index2);
					m_lastIndex = -1;
					return;
		}
				super.setSelectionInterval(index1, index2);
			}
		});
		
		scrollPane.getViewport().setView(m_list);
		//另一个Panel 各种按钮
		JPanel btnPanel = new JPanel();
		btnPanel.setLayout(new BoxLayout(btnPanel, BoxLayout.Y_AXIS));
		panel.add(btnPanel, BorderLayout.EAST);
		
		//打开文件夹
		m_dirLabel = new JLabel("未选择文件夹");
		btnPanel.add(m_dirLabel);
		
		JButton openBtn = new JButton("打开文件夹");
		openBtn.addActionListener(this);
		btnPanel.add(openBtn);
		//过滤器
		JLabel label = new JLabel("过滤器");
		btnPanel.add(label);
		
		m_filterField = new JTextField();
		btnPanel.add(m_filterField);
		//索引从何处开始
		JLabel indexLabel = new JLabel("索引");
		btnPanel.add(indexLabel);
		SpinnerNumberModel numberModel = new SpinnerNumberModel();
		numberModel.setMinimum(0);
		numberModel.setStepSize(1);
		m_indexSpinner = new JSpinner(numberModel);
		m_indexSpinner.setValue(1);
		btnPanel.add(m_indexSpinner);
		
		//确认按钮
		JButton okBtn = new JButton("开始转换");
		okBtn.addActionListener(this);
		btnPanel.add(okBtn);
		
		this.pack();
	}

	private File openFileChooser()
	{
		JFileChooser chooser = new JFileChooser();
		//仅仅可以选择文件夹
		chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY); 

		//获取选项
		int returnVal = chooser.showOpenDialog(this);
		if (returnVal == JFileChooser.APPROVE_OPTION)
		{
			File dir = chooser.getSelectedFile();
			return dir;
		}
		return null;
	}
	@Override
	public void actionPerformed(ActionEvent e) 
	{
		String btnName = e.getActionCommand();
		
		switch (btnName)
		{
			case "打开文件夹":
			{
				File dir = this.openFileChooser();
				if (dir != null)
				{
					m_dirLabel.setText(dir.getAbsolutePath());
					//填充
					m_model.removeAllElements();
					//获取该目录下的所有文件
					File[] files = dir.listFiles();
					m_batch.setFiles(files);
					
					for (File file: files)
						m_model.addElement(file.getName());
				}
			}
			break;
			case "开始转换":
			{
				//是否符合条件
				if (m_batch.getFiles() == null)
				{
					JOptionPane.showMessageDialog(this, "请选择文件夹");
					return;
				}
				else if (m_filterField.getText().isEmpty())
				{
					JOptionPane.showMessageDialog(this, "请输入过滤字符串(如images##.png)");
					return;
				}
				else if (!m_batch.renameAll(m_filterField.getText(), (int)m_indexSpinner.getValue(), m_model))
				{
					JOptionPane.showMessageDialog(this, "请输入正确的过滤字符串(如images##.png)");
				}
			}
			break;
		}
	}
	@Override
	public void valueChanged(ListSelectionEvent arg0) 
	{
		//鼠标按下和释放会触发两次，添加此处则仅仅触发一次
		if (arg0.getValueIsAdjusting())
			return ;
		int index = m_list.getSelectedIndex();
		
		if (index == m_lastIndex || m_lastIndex == -1 || index == -1)
		{
			m_lastIndex = index;
			return;
		}
		//更换显示
		String temp = m_model.get(index);
		m_model.set(index, m_model.get(m_lastIndex));
		m_model.set(m_lastIndex, temp);
		//更换文件顺序
		m_batch.swap(index, m_lastIndex);
		//解除选中
		m_list.clearSelection();
		m_lastIndex = -1;
	}
}
