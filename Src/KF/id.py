# -*- coding=utf-8 -*-

import sys


#for line in contents_lines:
#    print line
reload(sys)
sys.setdefaultencoding('utf-8')
contents_lines=[]
id_dic={}
f=open("/Users/wuyinghao/Desktop/myCodeLib/Src/KF/id.txt","r")
#f.readline()
content_lines=f.readlines()
f.close()
for line in content_lines:
    content_list=line.split(" ")
    id_num=int(content_list[1])
    id_dic[id_num]=content_list[2][:-1]
    
    
    #print content_list[1] + " " + content_list[2]
for key in id_dic:
    if key%10000 <> 0 :
        if key%100 <> 0 :
            id_dic[key]=id_dic[key/10000*10000] + id_dic[key/100*100] +id_dic[key]

for key in id_dic:
    if key % 10000 <> 0 and key %100 ==0 :
        id_dic[key]=id_dic[key/10000*10000] + id_dic[key]
            
    
print "{"
i=1
for key in id_dic:
    if id_dic[key][-1:]=="\n":
        id_dic[key] =id_dic[key][:-1]
    if i == 5 :
        print str(key)+":"+"\""+id_dic[key] + "\","
        i=0
    else:
        print str(key)+":"+"\""+id_dic[key] + "\",",
        i+=1
    
    #print content_list[1] + " " + content_list[2]

#print id_dic