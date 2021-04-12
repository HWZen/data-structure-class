"""Created by summerpray"""
import time
from datetime import datetime
import requests
import csv
import re

"""请求网页"""

"""反反爬"""
headers = {
    'User-Agent':'Mozilla/5.0 (Macintosh; Intel Mac OS X 11_2_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.90 Safari/537.36'
}

response = requests.get('https://cn.investing.com/commodities/crude-oil', headers=headers)
# print(response.request.headers)
html = response.text

"""解析网页"""
oil_price = re.findall('<span class="arial_26 inlineblock pid-8849-last" id="last_last" dir="ltr">(.*?)</span>', html)
"""执行脚本"""
month = ''
day = ''

while(datetime.now().weekday()!=6 and datetime.now().weekday()!=5):
    response = requests.get('https://cn.investing.com/commodities/crude-oil', headers=headers)
    html = response.text
    month_last = month
    day_last = day
    now = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    month = now[5:7]
    day = now[8:10]
    filename = now[0:4] + "Y" + month + "M" + day + "D" + "oilprice" + ".csv"
    if (day != day_last or month != month_last):
        with open(filename, 'a') as csvfile:
            csv_write = csv.writer(csvfile)
            csv_head = ["oil_price", "time"]
            csv_write.writerow(csv_head)
    else:
        oil_price_last = oil_price
        oil_price = str(re.findall('id="last_last" dir="ltr">(.*?)</span>', html))
        time_temp = now
        list = [oil_price, time_temp]
        # if (oil_price_last != oil_price):
        with open(filename, 'a', newline='') as csvfile:
            csv_write = csv.writer(csvfile)
            csv_write.writerow(list)
    if now[11:16]=='23:59':
        exit()
    while(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())[17:19]!='00'):
        time.sleep(0.6)
# print(day)

