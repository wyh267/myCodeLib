# -*- coding=utf-8 -*-


import os
import re
import sys

def to_unicode_or_bust(obj,encoding='utf-8'):
    if isinstance(obj, basestring):
        if not isinstance(obj, unicode):
            obj = unicode(obj, encoding)
    return obj


#############################################
#
# 读取文件，保存到一个字符串中
# 输入： 文件名完整路径
# 输出： 文件内容
#
#############################################
def readFile(file_name):
    f=open(file_name,"r")
    file_contents=f.read()
    file_contents=file_contents.replace("\t","")
    file_contents=file_contents.replace("\r","")
    file_contents=file_contents.replace("\n","")
    f.close()
    return to_unicode_or_bust(file_contents)
    
    
    
    
def getInfoFromString(content):
    #text="<content>Hi</content> hello <content>Hiddddd</content>"
    m=re.findall(r"<content>(.*?)</content>",content)
    return m
    
    
a={1:2,2:3}
b={2:4,3:5}
c=dict(a, **b)
print c
a=[1,2,3]
print a[:1]

reload(sys)                         # 2
sys.setdefaultencoding('utf-8') 
contents =readFile("/Users/wuyinghao/Desktop/test/all.txt")


content_list=getInfoFromString(contents)
file_name_pre="/Users/wuyinghao/Desktop/test/"
file_name_num=0
for v in content_list:
    print v
    print "==================="
    if len(v)>0:
        file_name=file_name_pre + str(file_name_num) + ".txt"
        file_name_num=file_name_num+1
        f=open(file_name,"w")
        f.write(v)
        f.close()

print len(content_list)









