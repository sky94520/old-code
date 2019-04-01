import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.Scanner;
 
public class portTest {
	public static void portTest(String ip,int port) {
		Socket connect = new Socket();
        
        	try {
        	
        		connect.connect(new InetSocketAddress(ip,port),100);//建立连接
        		boolean res = connect.isConnected();//通过现有方法查看连通状态
        		System.out.println(port+"端口开启");//true为连通
        	
        } catch (IOException e) {
            System.out.println(port+"端口未开启");//当连不通时，直接抛异常，异常捕获即可
        }finally{
            try {
                connect.close();
            } catch (IOException e) {
                System.out.print("false");
            }
        }
		
	}
    public static void main(String[] args){
    	Scanner sc = new Scanner(System.in);
    	System.out.println("请输入ip地址：");
    	String ip = sc.nextLine();
    	System.out.println("请输入起始端口号：");
    	int portbegin = sc.nextInt();
    	System.out.println("请输入末尾端口号：");
    	int portend = sc.nextInt();
    	for(int i=portbegin;i<portend+1;i++) {
    		portTest(ip,i);
    	}
    }
}