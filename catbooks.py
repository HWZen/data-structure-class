import time
from datetime import datetime
import requests
import csv
import re

rawfile = open('goodbook.csv', mode='a',encoding='utf-8')
csvfile = csv.writer(rawfile)


"""请求网页"""

"""反反爬"""
headers = {
    'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 11_2_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.90 Safari/537.36'
}

response = requests.get(
    'https://www.douban.com/doulist/128350348/?start=50&sort=seq&playable=0&sub_type=', headers=headers)
# print(response.request.headers)
html = response.text

"""解析网页"""

links = re.findall(
    '<div class="title">\\n      <a href="(.*?)/" target="_blank">\\n        .*?\\n      </a>', html
)

for link in links:
    response = requests.get(
        link, headers=headers)
    html = response.text
    html = html.replace('\n', '').replace('\r', '').replace(' ', '')
    date = re.findall(
        '点击看大图"alt="(.*?)".*?作者.*?href=".*?>(.*?)</a>.*?出版社:</span>(.*?)<.*?出版年:</span>(.*?)<.*?定价:</span>(.*?)<.*?ISBN:</span>(.*?)<', html)
    print(date[0])
    csvfile.writerow(date[0])

rawfile.close()
