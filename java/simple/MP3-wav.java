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
	 * MP3ת��PCM�ļ�����
	 * @param mp3filepath ԭʼ�ļ�·��
	 * @param pcmfilepath ת���ļ��ı���·��
	 * @throws Exception 
	 */
	public static void mp3Convertpcm(String mp3filepath,String pcmfilepath) throws Exception{
		File mp3 = new File(mp3filepath);
		File mav = new File(pcmfilepath);
		//ԭMP3�ļ�תAudioInputStream
		AudioInputStream mp3audioStream = AudioSystem.getAudioInputStream(mp3);
		//��AudioInputStream MP3�ļ� ת��ΪPCM AudioInputStream
		AudioInputStream pcmaudioStream = AudioSystem.getAudioInputStream(AudioFormat.Encoding.PCM_SIGNED, mp3audioStream);
		//׼��ת�����������OutputStream
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