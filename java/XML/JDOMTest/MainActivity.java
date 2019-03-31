import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

import org.jdom2.*;
import org.jdom2.input.SAXBuilder;
public class MainActivity 
{
	public static void main(String[] args)
	{
		SAXBuilder builder = new SAXBuilder();
		Document doc;
		try 
		{
			InputStream tmx=MainActivity.class.getResourceAsStream("/resources/map1.tmx");
			doc = builder.build(tmx);
			Element root = doc.getRootElement();
			//获得所有子元素
			List<Element> list=root.getChildren();
			for(Element e:list)
			{
				if(e.getName().equals("layer"))
				{
					Element t=e.getChild("data");
					System.out.println(t.getText().trim());
				}
			}
		} catch (JDOMException e) 
		{
			System.out.println("JDOMException");
		}catch(IOException e)
		{
			System.out.println("IOException");
		}
        
	}
}
