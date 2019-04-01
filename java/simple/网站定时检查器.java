import requests
import time
import smtplib
from email import encoders
from email.header import Header
from email.mime.text import MIMEText
from email.utils import parseaddr, formataddr

my_sender='15850683150@163.com' #发件人邮箱账号，为了后面易于维护，所以写成了变量
my_user='1148705128@qq.com' #收件人邮箱账号，为了后面易于维护，所以写成了变量
def mail():
    try:
        msg=MIMEText('网站打不开','plain','utf-8')
        msg['From']=formataddr(["董峰",my_sender])   #括号里的对应发件人邮箱昵称、发件人邮箱账号
        msg['To']=formataddr(["董峰",my_user])   #括号里的对应收件人邮箱昵称、收件人邮箱账号
        msg['Subject']="python邮件" #邮件的主题，也可以说是标题

        server=smtplib.SMTP("smtp.163.com",25)  #发件人邮箱中的SMTP服务器，端口是25
        server.login(my_sender,"818818818df")    #括号中对应的是发件人邮箱账号、邮箱密码
        server.sendmail(my_sender,[my_user,],msg.as_string())   #括号中对应的是发件人邮箱账号、收件人邮箱账号、发送邮件
        server.quit()   #这句是关闭连接的意思
    except Exception:   #如果try中的语句没有执行，则会执行下面的ret=False
        print('邮件发送不了')

headers = {
    "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36"
}
url = "https://www.google.com/"
while 1:
    try:
        response= requests.get(url, headers=headers, timeout=5).status_code
        print(response)
        if response== 200:
            print('可打开')
        else:
            print("网站打不开")
            mail()
    except Exception as e:
            print("网站打不开")
            mail()
    time.sleep(10)