#! /usr/bin/python3.6
# -*-coding:utf-8 -*-
import sys

def getAddressByZipCode(zipCode):
    '''
    根据邮编获取 省 县 村
    @param zipCode 邮编
    @preturn {'province': '', 'city':'', 'address':''}
    '''
    import requests
    from bs4 import BeautifulSoup

    headers = {
        'User-Agent' : 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36'
    }
    params = {
        'theZipCode': zipCode,
        'userID': '',
    }
    response = requests.get(
        url = "http://ws.webxml.com.cn/WebServices/ChinaZipSearchWebService.asmx/getAddressByZipCode",
        headers = headers,
        params = params)
    
    #失败
    if response.status_code != 200:
        print(response.text)
        print(response.status_code)
        return None
    
    #获取有用的标签
    soup = BeautifulSoup(response.text, 'xml')
    zipInfo = soup.find(name = 'ZipInfo')
    
    return {
        'province': zipInfo.PROVINCE.text,
        'city': zipInfo.CITY.text,
        'address': zipInfo.ADDRESS.text
    }

if __name__ == '__main__':
    #获取命令行参数
    if len(sys.argv) > 1:
        zipCode = sys.argv[1]
    else:
        zipCode = '476900'
    
    d = getAddressByZipCode(zipCode)
    
    print('邮编', zipCode)
    print('对应的位置是 %s,%s,%s' % (d['province'], d['city'], d['address']))
