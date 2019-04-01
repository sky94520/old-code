#! /usr/bin/python3.6
# -*-coding:utf-8 -*-

import requests
from lxml import etree
import sys

def get_host_ip(): 
    """
    查询本机ip地址
    :return: ip
    """ 
    import socket 
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
        s.connect(('8.8.8.8', 80)) 
        ip = s.getsockname()[0] 
    finally:
        s.close() 
        return ip 

headers = {
    'User-Agent' : 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36'
}

ip = '127.0.0.1'
#获取命令行参数
if len(sys.argv) > 1:
    ip = sys.argv[1]
else:
    ip = get_host_ip()

params = {
    'ip': ip,
}

response = requests.get("https://www.ip.cn/index.php", headers = headers, params = params)

if response.status_code != 200:
    print('网页访问错误')
    exit(1)

#获取标签
selector = etree.HTML(response.text)
result = selector.xpath('//div[@id="result"]/div[@class="well"]/p/code/text()')

if len(result) > 0:
    print(result)
else:
    print('查询失败')
