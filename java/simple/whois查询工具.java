import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.Scanner;
public class whois {
	
	public static String getipadd(String domain) throws IOException {
	
            //����һ��URLʵ��
            URL url = new URL("http://api.juheapi.com/japi/beian?type=1&keyword="+domain+"&v=1.0&key=d1e9eacc45c773293eb1de4c3250b788");

         
                //ͨ��URL��openStrean������ȡURL��������ʾ����Ը�ֽ�������
                InputStream is = url.openStream();
                InputStreamReader isr = new InputStreamReader(is,"utf-8");

                //Ϊ�ַ���������ӻ���
                BufferedReader br = new BufferedReader(isr);
                String data = br.readLine();//��ȡ����
                String gg = data;
                
                //while (data!=null){//ѭ����ȡ����
                //  System.out.println(data);//�������
                //    data = br.readLine();
                //}
                br.close();
                isr.close();
                is.close();
                return gg;
	}
    public static void main(String[] args) throws IOException{
        Scanner sc = new Scanner(System.in);
        System.out.println("����������(����baidu.com)");
        String domain = sc.nextLine();
    	String info = getipadd(domain);
        System.out.println(info);
      }
}