import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import javazoom.jl.decoder.JavaLayerException;
import javazoom.jl.player.*;
//播放音频类
public class Music extends Thread{
    Player player;
    InputStream input;
    //构造
    public Music(InputStream input) {
        this.input = input;
    }
    @Override
    public synchronized void run() {
        // TODO Auto-generated method stub
        super.start();
        try {
            play();
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (JavaLayerException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    //播放方法
    public void play() throws FileNotFoundException, JavaLayerException {

            BufferedInputStream buffer = new BufferedInputStream(input);
            player = new Player(buffer);
            player.play();
    }
    
    
    public static void main(String[] args) throws FileNotFoundException, JavaLayerException {
    	File file=new File("E:\\CloudMusic\\1.mp3");
		FileInputStream fis=new FileInputStream(file);
		BufferedInputStream stream=new BufferedInputStream(fis);
		Player player=new Player(stream);
		player.play();

    }
}