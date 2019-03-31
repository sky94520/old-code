import java.io.IOException;
import java.io.InterruptedIOException;
import java.net.InetSocketAddress;
import java.net.Socket;


public class Server 
{
	private Socket socket;
	public Server(int port)
	{
		socket=new Socket();
		try 
		{
			socket.connect(new InetSocketAddress("127.0.0.1",port),1000);
			System.out.println("客户端连接成功");
			new ChatFrame("老婆",socket);
		}
		catch(InterruptedIOException ex)
		{
			System.out.println("连接超时！");
		}
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
	public static void main(String[] args)
	{
		new Server(13141);
	}
}
