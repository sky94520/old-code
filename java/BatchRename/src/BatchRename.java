import java.io.File;

import javax.swing.DefaultListModel;

public class BatchRename 
{
	private File[] m_files = null;
	
	public boolean renameAll(String filterStr, int start, DefaultListModel<String> model)
	{
		//拆分过滤字符串
		int begin = filterStr.indexOf('#');
		int end = filterStr.lastIndexOf('#');

		//不满足规则，不进行转换
		if (begin == -1)
			return false;
		
		String prefix = filterStr.substring(0, begin);
		String suffix = filterStr.substring(end + 1);

		String format = prefix + "%0" + String.valueOf(end - begin + 1) + "d" + suffix;
		
		String path = m_files[0].getParent();
		model.removeAllElements();
		//尝试重命名
		for (int i = 0; i < m_files.length; i++)
		{
			File file = m_files[i];
			File newFile = new File(path + File.separator + String.format(format, i + start));
			//重命名
			boolean ret = file.renameTo(newFile);
			m_files[i] = newFile;
			model.addElement(newFile.getName());
			
			if (!ret)
				System.out.println("文件" + file.getName() + "命名失败");
		}
		//重置
		return true;
	}
	
	public void swap(int index1, int index2)
	{
		File temp = m_files[index1];
		m_files[index1] = m_files[index2];
		m_files[index2] = temp;
	}

	public File[] getFiles() {
		return m_files;
	}

	public void setFiles(File[] files) {
		this.m_files = files;
	}
}
