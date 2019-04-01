import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;

import javax.swing.JTextField;

/**
 * 
 * @author ren
 * 角色类，目前仅保存了属性和名称
 */
public class Role
{
	private int m_id = 0;
	private String m_name;
	//属性
	private HashMap<String, Integer> m_properties;
	private static StringBuffer s_buffer = new StringBuffer();
	
	public Role()
	{
		m_name = new String();
		m_properties = new HashMap<>();
	}
	public int getID()
	{
		return m_id;
	}
	public void setID(int id)
	{
		m_id = id;
	}
	public String getName()
	{
		return m_name;
	}
	public void setName(String name)
	{
		m_name = name;
	}
	public Integer getProperty(String key)
	{
		Integer value = m_properties.get(key);
		
		if (value == null)
		{
			value = 0;
			m_properties.put(key, value);
		}
		return value;
	}
	public void setProperty(String key, int value)
	{
		m_properties.put(key, value);
	}
	
	public String getKeys()
	{
		Iterator<Map.Entry<String, Integer>> it = m_properties.entrySet().iterator();
		while (it.hasNext())
		{
			Map.Entry<String, Integer> entry = it.next();
			
			s_buffer.append(entry.getKey());
			
			if (it.hasNext())
				s_buffer.append(',');
		}
		String str = s_buffer.substring(0);
		
		s_buffer.delete(0, s_buffer.length());
		return str;
	}
	
	public String getValues()
	{
		Iterator<Map.Entry<String, Integer>> it = m_properties.entrySet().iterator();
		while (it.hasNext())
		{
			Map.Entry<String, Integer> entry = it.next();
			
			s_buffer.append(entry.getValue());
			
			if (it.hasNext())
				s_buffer.append(',');
		}
		String str = s_buffer.substring(0);
		
		s_buffer.delete(0, s_buffer.length());
		return str;
	}
}
