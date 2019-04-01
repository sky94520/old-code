package com.example.demo.util;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.MalformedURLException;
import java.nio.charset.Charset;

import org.apache.commons.net.ftp.FTPClient;
import org.apache.commons.net.ftp.FTPFile;
import org.apache.commons.net.ftp.FTPReply;
import org.apache.http.Consts;
import org.apache.http.HttpEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.ContentType;
import org.apache.http.entity.mime.MultipartEntityBuilder;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.entity.mime.content.StringBody;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

public class FTPUtils {

	// ftp��������ַ
	private static String hostname = "";
	// ftp�������˿ں�Ĭ��Ϊ21
	private static Integer port = 21;
	// ftp��¼�˺�
	private static String username = "";
	// ftp��¼����
	private static String password = "";

	private static FTPClient ftpClient = null;

	/**
	 * ��ʼ��ftp������
	 */

	public static void connect(String host, Integer por, String user, String passwd) {
		hostname = host;
		port = por;
		username = user;
		password = passwd;
		initFtpClient();
	}

	public static void initFtpClient() {
		ftpClient = new FTPClient();
		ftpClient.setControlEncoding("utf-8");
		try {
			// System.out.println("connecting...ftp������:"+hostname+":"+port);
			ftpClient.connect(hostname, port); // ����ftp������
			ftpClient.login(username, password); // ��¼ftp������
			int replyCode = ftpClient.getReplyCode(); // �Ƿ�ɹ���¼������
			if (!FTPReply.isPositiveCompletion(replyCode)) {
				// System.out.println("connect failed...ftp������:"+hostname+":"+port);
			}
			// System.out.println("connect successfully...ftp������:"+hostname+":"+port);
		} catch (MalformedURLException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * �ϴ��ļ�
	 * 
	 * @param pathname       ftp���񱣴��ַ
	 * @param fileName       �ϴ���ftp���ļ���
	 * @param originfilename ���ϴ��ļ������ƣ����Ե�ַ�� *
	 * @return
	 */
	public static boolean uploadFile(String pathname, String fileName, String originfilename) {
		boolean flag = false;
		InputStream inputStream = null;
		try {
			// System.out.println("��ʼ�ϴ��ļ�");
			inputStream = new FileInputStream(new File(originfilename));
			// initFtpClient();
			ftpClient.setFileType(ftpClient.BINARY_FILE_TYPE);

			CreateDirecroty(pathname);
			ftpClient.makeDirectory(pathname);
			ftpClient.changeWorkingDirectory(pathname);
			ftpClient.enterLocalPassiveMode();
			boolean res = ftpClient.storeFile(fileName, inputStream);
			// System.out.println(res);
			inputStream.close();
			ftpClient.logout();
			flag = true;
			// System.out.println("�ϴ��ļ��ɹ�");
		} catch (Exception e) {
			// System.out.println("�ϴ��ļ�ʧ��");
			e.printStackTrace();
		} finally {
			if (null != inputStream) {
				try {
					inputStream.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		return true;
	}

	/**
	 * �ϴ��ļ�
	 * 
	 * @param pathname    ftp���񱣴��ַ
	 * @param fileName    �ϴ���ftp���ļ���
	 * @param inputStream �����ļ���
	 * @return
	 */
	public static boolean uploadFile(String pathname, String fileName, InputStream inputStream) {
		boolean flag = false;
		try {
			// System.out.println("��ʼ�ϴ��ļ�");
			// initFtpClient();
			ftpClient.setFileType(ftpClient.BINARY_FILE_TYPE);
			CreateDirecroty(pathname);
			ftpClient.makeDirectory(pathname);
			ftpClient.changeWorkingDirectory(pathname);
			ftpClient.enterLocalPassiveMode();
			ftpClient.storeFile(fileName, inputStream);
			inputStream.close();
			ftpClient.logout();
			flag = true;
			// System.out.println("�ϴ��ļ��ɹ�");
		} catch (Exception e) {
			// System.out.println("�ϴ��ļ�ʧ��");
			e.printStackTrace();
		} finally {
			if (null != inputStream) {
				try {
					inputStream.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		return true;
	}

	// �ı�Ŀ¼·��
	public static boolean changeWorkingDirectory(String directory) {
		boolean flag = true;
		try {
			flag = ftpClient.changeWorkingDirectory(directory);
			if (flag) {
				// System.out.println("�����ļ���" + directory + " �ɹ���");

			} else {
				// System.out.println("�����ļ���" + directory + " ʧ�ܣ���ʼ�����ļ���");
			}
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}
		return flag;
	}

	// �������Ŀ¼�ļ��������ftp�������Ѵ��ڸ��ļ����򲻴���������ޣ��򴴽�
	public static boolean CreateDirecroty(String remote) throws IOException {
		boolean success = true;
		String directory = remote + "/";
		// ���Զ��Ŀ¼�����ڣ���ݹ鴴��Զ�̷�����Ŀ¼
		if (!directory.equalsIgnoreCase("/") && !changeWorkingDirectory(new String(directory))) {
			int start = 0;
			int end = 0;
			if (directory.startsWith("/")) {
				start = 1;
			} else {
				start = 0;
			}
			end = directory.indexOf("/", start);
			String path = "";
			String paths = "";
			while (true) {
				String subDirectory = new String(remote.substring(start, end).getBytes("GBK"), "iso-8859-1");
				path = path + "/" + subDirectory;
				if (!existFile(path)) {
					if (makeDirectory(subDirectory)) {
						changeWorkingDirectory(subDirectory);
					} else {
						// System.out.println("����Ŀ¼[" + subDirectory + "]ʧ��");
						changeWorkingDirectory(subDirectory);
					}
				} else {
					changeWorkingDirectory(subDirectory);
				}

				paths = paths + "/" + subDirectory;
				start = end + 1;
				end = directory.indexOf("/", start);
				// �������Ŀ¼�Ƿ񴴽����
				if (end <= start) {
					break;
				}
			}
		}
		return success;
	}

	// �ж�ftp�������ļ��Ƿ����
	public static boolean existFile(String path) throws IOException {
		boolean flag = false;
		FTPFile[] ftpFileArr = ftpClient.listFiles(path);
		if (ftpFileArr.length > 0) {
			flag = true;
		}
		return flag;
	}

	// ����Ŀ¼
	public static boolean makeDirectory(String dir) {
		boolean flag = true;
		try {
			flag = ftpClient.makeDirectory(dir);
			if (flag) {
				// System.out.println("�����ļ���" + dir + " �ɹ���");

			} else {
				// System.out.println("�����ļ���" + dir + " ʧ�ܣ�");
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return flag;
	}

	/**
	 * * �����ļ� *
	 * 
	 * @param pathname  FTP�������ļ�Ŀ¼ *
	 * @param filename  �ļ����� *
	 * @param localpath ���غ���ļ�·�� *
	 * @return
	 */
	public static boolean downloadFile(String pathname, String filename, String localpath) {
		boolean flag = false;
		OutputStream os = null;
		try {
			// System.out.println("��ʼ�����ļ�");
			initFtpClient();
			// �л�FTPĿ¼
			ftpClient.changeWorkingDirectory(pathname);
			ftpClient.enterLocalPassiveMode();
			FTPFile[] ftpFiles = ftpClient.listFiles();
			for (FTPFile file : ftpFiles) {
				if (filename.equalsIgnoreCase(file.getName())) {
					File localFile = new File(localpath + "/" + file.getName());
					os = new FileOutputStream(localFile);
					ftpClient.retrieveFile(file.getName(), os);
					os.close();
				}
			}
			ftpClient.logout();
			flag = true;
			// System.out.println("�����ļ��ɹ�");
		} catch (Exception e) {
			// System.out.println("�����ļ�ʧ��");
			e.printStackTrace();
		} finally {
			if (null != os) {
				try {
					os.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		return flag;
	}

	/**
	 * * ɾ���ļ� *
	 * 
	 * @param pathname FTP����������Ŀ¼ *
	 * @param filename Ҫɾ�����ļ����� *
	 * @return
	 */
	public static boolean deleteFile(String pathname, String filename) {
		boolean flag = false;
		try {
			// System.out.println("��ʼɾ���ļ�");
			// initFtpClient();
			// �л�FTPĿ¼
			ftpClient.changeWorkingDirectory(pathname);
			ftpClient.enterLocalPassiveMode();
			ftpClient.dele(filename);
			ftpClient.logout();
			flag = true;
			// System.out.println("ɾ���ļ��ɹ�");
		} catch (Exception e) {
			// System.out.println("ɾ���ļ�ʧ��");
			e.printStackTrace();
		}
		return flag;
	}

	public static void disconnect() {
		try {
			ftpClient.disconnect();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static void main(String[] args) throws FileNotFoundException {
		FTPUtils.connect("47.106.83.33", 2001, "root", "818818df!");
		FileInputStream inputStream = new FileInputStream(new File("F://b6fe710.PNG"));
		FTPUtils.uploadFile("/", "ckcore.txt", inputStream);
		//FTPUtils.uploadFile("/", "b6fe710.PNG", "F://b6fe710.PNG");
		// FTPUtils.downloadFile("/", "qrcode.png", "C://");
		// FTPUtils.deleteFile("/", "cloud.png");
		FTPUtils.disconnect();

	}
}