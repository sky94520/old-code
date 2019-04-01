import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;
 
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
/**
 */
public class MP3ToWav {
	/**
	 * MP3转换PCM文件方法
	 * @param mp3filepath 原始文件路径
	 * @param pcmfilepath 转换文件的保存路径
	 * @throws Exception 
	 */
	public static void mp3Convertpcm(String mp3filepath,String pcmfilepath) throws Exception{
		File mp3 = new File(mp3filepath);
		File mav = new File(pcmfilepath);
		//原MP3文件转AudioInputStream
		AudioInputStream mp3audioStream = AudioSystem.getAudioInputStream(mp3);
		//将AudioInputStream MP3文件 转换为PCM AudioInputStream
		AudioInputStream pcmaudioStream = AudioSystem.getAudioInputStream(AudioFormat.Encoding.PCM_SIGNED, mp3audioStream);
		//准备转换的流输出到OutputStream
		OutputStream os = new FileOutputStream(mav);
		int bytesRead = 0;
		byte[] buffer = new byte[8192];
		while ((bytesRead=pcmaudioStream.read(buffer, 0, 8192))!=-1) {
			os.write(buffer, 0, bytesRead);
		}
		os.close();
		pcmaudioStream.close();
	}
	
	public static void main(String[] args) throws Exception {
		String mp3 = "E:\\CloudMusic\\df.mp3";
		String pcm = "E:\\CloudMusic\\g.wav";
		mp3Convertpcm(mp3,pcm);
		
	}
}