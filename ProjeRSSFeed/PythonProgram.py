
import urllib2

import serial

import time


from xml.dom.minidom import parseString

# Hangi Porta bağlanacaksa onu seçebilirsiniz. COM3 Portunu kullanmaktadır. 
ser = serial.Serial("\\.\COM3", 9600)
i = 1

time.sleep(5)
while i == 1:
     #RSS Dosyasının indirileceği adres, Bunu değiştirebilirsiniz.
     file = urllib2.urlopen('http://news.sky.com/feeds/rss/world.xml')
     
     data = file.read()
     
     file.close()
    
     dom = parseString(data)
     
     xmlTag = dom.getElementsByTagName('title')[2].toxml()
     
     xmlData=xmlTag.replace('<title>','').replace('</title>','')
     
     ser.write('~')
     time.sleep(5)
     
     nums = xmlData.split(' ')
     
     for num in nums:
         
          ser.write(num)
          
          ser.write(' ')
          
          time.sleep(2)
     
     ser.write('~')
     
     time.sleep(300) 