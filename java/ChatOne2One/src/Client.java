import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;


//客户端
public class Client 
{
	private ServerSocket server;
	private Socket client;
	public Client(int port)
	{
		try 
		{
			server=new ServerSocket(port);
			//等待接受服务端
			System.out.println("正在等待服务端...");
			client=server.accept();
			//接收完成
			System.out.println("服务端连接成功!!!");
			new ChatFrame("任小牛",client);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public static void main(String[] args)
	{
		new Client(13141);
	}
}
