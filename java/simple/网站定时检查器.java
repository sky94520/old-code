import requests
import time
import smtplib
from email import encoders
from email.header import Header
from email.mime.text import MIMEText
from email.utils import parseaddr, formataddr

my_sender='15850683150@163.com' #�����������˺ţ�Ϊ�˺�������ά��������д���˱���
my_user='1148705128@qq.com' #�ռ��������˺ţ�Ϊ�˺�������ά��������д���˱���
def mail():
    try:
        msg=MIMEText('��վ�򲻿�','plain','utf-8')
        msg['From']=formataddr(["����",my_sender])   #������Ķ�Ӧ�����������ǳơ������������˺�
        msg['To']=formataddr(["����",my_user])   #������Ķ�Ӧ�ռ��������ǳơ��ռ��������˺�
        msg['Subject']="python�ʼ�" #�ʼ������⣬Ҳ����˵�Ǳ���

        server=smtplib.SMTP("smtp.163.com",25)  #�����������е�SMTP���������˿���25
        server.login(my_sender,"818818818df")    #�����ж�Ӧ���Ƿ����������˺š���������
        server.sendmail(my_sender,[my_user,],msg.as_string())   #�����ж�Ӧ���Ƿ����������˺š��ռ��������˺š������ʼ�
        server.quit()   #����ǹر����ӵ���˼
    except Exception:   #���try�е����û��ִ�У����ִ�������ret=False
        print('�ʼ����Ͳ���')

headers = {
    "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36"
}
url = "https://www.google.com/"
while 1:
    try:
        response= requests.get(url, headers=headers, timeout=5).status_code
        print(response)
        if response== 200:
            print('�ɴ�')
        else:
            print("��վ�򲻿�")
            mail()
    except Exception as e:
            print("��վ�򲻿�")
            mail()
    time.sleep(10)