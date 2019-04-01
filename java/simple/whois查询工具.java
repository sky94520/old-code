import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.Scanner;
public class whois {
	
	public static String getipadd(String domain) throws IOException {
	
            //创建一个URL实例
            URL url = new URL("http://api.juheapi.com/japi/beian?type=1&keyword="+domain+"&v=1.0&key=d1e9eacc45c773293eb1de4c3250b788");

         
                //通过URL的openStrean方法获取URL对象所表示的自愿字节输入流
                InputStream is = url.openStream();
                InputStreamReader isr = new InputStreamReader(is,"utf-8");

                //为字符输入流添加缓冲
                BufferedReader br = new BufferedReader(isr);
                String data = br.readLine();//读取数据
                String gg = data;
                
                //while (data!=null){//循环读取数据
                //  System.out.println(data);//输出数据
                //    data = br.readLine();
                //}
                br.close();
                isr.close();
                is.close();
                return gg;
	}
    public static void main(String[] args) throws IOException{
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入域名(例：baidu.com)");
        String domain = sc.nextLine();
    	String info = getipadd(domain);
        System.out.println(info);
      }
}