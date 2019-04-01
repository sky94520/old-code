import javax.swing.JList;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.BadLocationException;
import javax.swing.text.Document;

public class NameListener implements DocumentListener
{
	private NameChangeInterface m_entry = null;
	
	public NameListener(NameChangeInterface entry)
	{
		m_entry = entry;
	}
	
	@Override
	public void changedUpdate(DocumentEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void insertUpdate(DocumentEvent arg0) {
		// TODO Auto-generated method stub
		Document doc = arg0.getDocument();
		try 
		{
			String name = doc.getText(0, doc.getLength());
			m_entry.nameChanged(name);
		}
		catch (BadLocationException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void removeUpdate(DocumentEvent arg0) {
		// TODO Auto-generated method stub
		Document doc = arg0.getDocument();
		try 
		{
			String name = doc.getText(0, doc.getLength());
			m_entry.nameChanged(name);
		}
		catch (BadLocationException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
