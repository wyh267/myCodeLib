# -*- coding=utf-8 -*-

import os
import urllib2
import re
import progressbar
import time

def to_unicode_or_bust(obj,encoding='utf-8'):
    if isinstance(obj, basestring):
        if not isinstance(obj, unicode):
            obj = unicode(obj, encoding)
    return obj


def searchBaseUrl(url,local=0):
    print url
    if(local==0):
        f=urllib2.urlopen(url,timeout=5)
        content=f.read()
        return to_unicode_or_bust(content,'gbk')
    else:
        f=open("/Users/wuyinghao/Desktop/test/base.txt","r")
        content=f.read()
        f.close()
        return content
    
    
    
def findAllUrls(base_url):
    contents=searchBaseUrl(base_url,1)
    #print "writing...."
    urls=re.findall(r"<a href=\"(http://\w*?\.163\.com/[A-Za-z0-9/]*?\.html)\"",contents) #<a href=\"(http://.*?html).*?>
    return urls
    
    
#pro = progressbar.ProgressBar().start()
#for i in range(80):
#  time.sleep(0.01)
#  pro.update(i+1)
#pro.finish()

urls=findAllUrls("http://news.163.com/")

for i in urls:
    print i
#    searchBaseUrl(i)