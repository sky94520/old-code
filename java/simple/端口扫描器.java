import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.Scanner;
 
public class portTest {
	public static void portTest(String ip,int port) {
		Socket connect = new Socket();
        
        	try {
        	
        		connect.connect(new InetSocketAddress(ip,port),100);//��������
        		boolean res = connect.isConnected();//ͨ�����з����鿴��ͨ״̬
        		System.out.println(port+"�˿ڿ���");//trueΪ��ͨ
        	
        } catch (IOException e) {
            System.out.println(port+"�˿�δ����");//������ͨʱ��ֱ�����쳣���쳣���񼴿�
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
    	System.out.println("������ip��ַ��");
    	String ip = sc.nextLine();
    	System.out.println("��������ʼ�˿ںţ�");
    	int portbegin = sc.nextInt();
    	System.out.println("������ĩβ�˿ںţ�");
    	int portend = sc.nextInt();
    	for(int i=portbegin;i<portend+1;i++) {
    		portTest(ip,i);
    	}
    }
}