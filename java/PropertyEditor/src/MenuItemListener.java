import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

public class MenuItemListener implements ActionListener
{
	private PropertyEditorFrame m_frame = null;
	private File m_file = null;
	private JFileChooser m_chooser = null;
	
	public MenuItemListener(PropertyEditorFrame frame)
	{
		m_frame = frame;
		m_chooser = new JFileChooser();
		FileNameExtensionFilter filter = new FileNameExtensionFilter("csv", "csv");
		m_chooser.setFileFilter(filter);
	}
	@Override
	public void actionPerformed(ActionEvent e) 
	{
		String name = e.getActionCommand();
		
		if (name == "打开文件")
		{
			int returnVal = m_chooser.showOpenDialog(m_frame);
			if (returnVal == JFileChooser.APPROVE_OPTION)
			{
				m_file = m_chooser.getSelectedFile();
				//读取文件
				m_frame.readFromFile(m_file);
			}
		}
		else if (name == "保存文件")
		{
			//直接保存即可
			if (m_file == null)
			{
				int returnVal = m_chooser.showOpenDialog(m_frame);
				
				if (returnVal == JFileChooser.APPROVE_OPTION)
				{
					m_file = m_chooser.getSelectedFile();
					
					/*
					if (m_file.getName().indexOf(".csv") == -1)
					{
						String path = m_file.getParent();
						File newFile = new File(path + file.separator + file.getName() + ".csv");
						file = newFile;
					}
					*/
				}
			}
			//保存文件
			if (m_file != null)
				m_frame.writeToFile(m_file);
		}
		else if (name == "另存为")
		{
			int returnVal = m_chooser.showOpenDialog(m_frame);
			
			if (returnVal == JFileChooser.APPROVE_OPTION)
			{
				File file = m_chooser.getSelectedFile();
				//另存为
				m_frame.writeToFile(file);
			}
		}
	}
}
