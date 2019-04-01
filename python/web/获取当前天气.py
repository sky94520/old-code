#! /usr/bin/python3.6
# -*-coding:utf-8 -*-
import sys

def getWeather(city):
    '''
    根据市获取天气
    @param city 城市名称
    @return {'province': '', 'city':'', 'address':''}
    '''
    import requests
    from bs4 import BeautifulSoup

    headers = {
        'User-Agent' : 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36'
    }
    params = {
            'theCityName': city,
    }
    response = requests.get(
        url = "http://ws.webxml.com.cn/WebServices/WeatherWebService.asmx/getWeatherbyCityName",
        headers = headers,
        params = params)
    
    #失败
    if response.status_code != 200:
        print(response.text)
        print(response.status_code)
        return None
    
    #获取有用的标签
    soup = BeautifulSoup(response.text, 'xml')
    arr = soup.find_all(name = 'string')

    return {
        'province': arr[0].text,
        'city': arr[1].text,
        'curTime': arr[4].text,
        'description': arr[-1].text,
        'weathers': [
            {
                'temp': arr[5].text,
                'situation': arr[6].text,
                'wind': arr[7].text,
            },
            {
                'temp': arr[12].text,
                'situation': arr[13].text,
                'wind': arr[14].text,
            },
            {
                'temp': arr[17].text,
                'situation': arr[18].text,
                'wind': arr[19].text,
            },
        ]
    }

if __name__ == '__main__':
    #获取命令行参数
    if len(sys.argv) > 1:
        city = sys.argv[1]
    else:
        city = '苏州'

    d = getWeather(city)

    weathers = d['weathers']
    for weather in weathers:
        print(weather['situation'])
        print(weather['temp'])
        print(weather['wind'])
        print("")
