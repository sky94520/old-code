import java.math.BigInteger;
import java.security.MessageDigest;
import sun.misc.BASE64Decoder;
import sun.misc.BASE64Encoder;
public class train {
	public static final String KEY_MD5 = "MD5";
	public static final String KEY_SHA = "SHA";
	//base64����
	public static String encryptBASE64(byte[] key)throws Exception{
		return (new BASE64Encoder()).encodeBuffer(key);
	}
	//base64����
	public static byte[] decryptBASE64(String key)throws Exception{
		return (new BASE64Decoder()).decodeBuffer(key);
	}
	//md5����
	public static String getMD5Result(String inputStr) {
		System.out.println("����ǰ����Ϣ�ǣ�"+inputStr);
		BigInteger bigInteger = null;
		try {
			MessageDigest md = MessageDigest.getInstance(KEY_MD5);
			byte[] inputData = inputStr.getBytes();
			md.update(inputData);
			bigInteger = new BigInteger(md.digest());
		}
		catch(Exception e) {e.printStackTrace();}
		System.out.println("MD5���ܺ�"+bigInteger.toString(16));
		return bigInteger.toString(16);
	}
	//sha����
	public static String getSHAResult(String inputStr) {
		System.out.println("����ǰ����Ϣ�ǣ�"+inputStr);
		BigInteger sha = null;
		byte[] inputData =  inputStr.getBytes();
		try {
			MessageDigest messageDigest = MessageDigest.getInstance(KEY_SHA);
			messageDigest.update(inputData);
			sha = new BigInteger(messageDigest.digest());
			System.out.println("SHA���ܺ�"+sha.toString(32));
		}
		catch(Exception e){
			e.printStackTrace();
		}
		return sha.toString(32);
	}
	public static void main(String[] args) {
		try {
			Scanner sc = new Scanner(System.in);
			String test = sc.nextLine();
			getMD5Result(test);
			getSHAResult(test);
			String result1 = train.encryptBASE64(test.getBytes());
			System.out.println("result1=====��������========"+result1);
			byte[] result2 = train.decryptBASE64(result1);
			String str2 = new String(result2);
			System.out.println("str2========��������========"+str2);
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
}