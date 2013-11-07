# -*- coding=utf-8 -*-

import urllib2
import re
import sys
import socket
    
def to_unicode_or_bust(obj,encoding='utf-8'):
    if isinstance(obj, basestring):
        if not isinstance(obj, unicode):
            obj = unicode(obj, encoding)
    return obj


   
    
def get(num):  
    fw=open("/Users/wuyinghao/Desktop/myCodeLib/Src/textDiff/piao.txt","w")
    for i in range(1,num+1):
        response = urllib2.urlopen("http://bj.58.com/piao/pn"+str(i)+"/")
        print "GET Main Page " + str(i) +" :::::http://bj.58.com/piao/pn"+str(i)+"/"
        content=to_unicode_or_bust(response.read())
        urlre=r"IM_SendMessage.*?url:\"(http.*?)\""
        m=re.findall(urlre,content)
        print m
        for i in m:
            #if i[:4] != "http":
            #    i="http://bj.58.com"+i
            print "Content Page :::" + i
            response = urllib2.urlopen(i)
            res=to_unicode_or_bust(response.read())
            title=r"<h1>(.*?)</h1>"
            price=r"id=\"minprice\">(.*?)</b>"
            phone=r"<span class=\"l_phone\">(.*?)</span>"
            title_contents=re.findall(title,res)
            price_contents=re.findall(price,res)
            phone_contents=re.findall(phone,res)
            print "====================================================="
            write_string=u"标题:::: " + title_contents[0] + "\r\n" + u"价格:::: " + price_contents[0] + "\r\n" + u"电话:::: " + phone_contents[0] + "\r\n==============\r\n" 
            print write_string
            fw.write(write_string.decode())
    fw.close()
  
print sys.getdefaultencoding()
reload(sys)
sys.setdefaultencoding('utf-8')  
#print socket.gethostbyaddr("http://bj.58.com/piao/pn1/")
get(3)
