import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;


//�ͻ���
public class Client 
{
	private ServerSocket server;
	private Socket client;
	public Client(int port)
	{
		try 
		{
			server=new ServerSocket(port);
			//�ȴ����ܷ����
			System.out.println("���ڵȴ������...");
			client=server.accept();
			//�������
			System.out.println("��������ӳɹ�!!!");
			new ChatFrame("��Сţ",client);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public static void main(String[] args)
	{
		new Client(13141);
	}
}
