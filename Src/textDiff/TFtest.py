
# -*- coding=utf-8 -*-

import os
import math
from texttable import Texttable
import time

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
    file_contents=file_contents.lower()
    file_contents=file_contents.replace("\t","")
    file_contents=file_contents.replace("\r","")
    file_contents=file_contents.replace("\n","")
    file_contents=file_contents.replace("_","")
    file_contents=file_contents.replace("|","")
    file_contents=file_contents.replace("*","")
    file_contents=file_contents.replace("\\","")
    file_contents=file_contents.replace("/","")
    file_contents=file_contents.replace("=","")
    file_contents=file_contents.replace("-","")
    file_contents=file_contents.replace("}","")
    file_contents=file_contents.replace("{","")
    file_contents=file_contents.replace(")","")
    file_contents=file_contents.replace("(","")
    file_contents=file_contents.replace("1","")
    file_contents=file_contents.replace("2","")
    file_contents=file_contents.replace("3","")
    file_contents=file_contents.replace("4","")
    file_contents=file_contents.replace("5","")
    file_contents=file_contents.replace("6","")
    file_contents=file_contents.replace("7","")
    file_contents=file_contents.replace("8","")
    file_contents=file_contents.replace("9","")
    file_contents=file_contents.replace("0","")
    file_contents=file_contents.replace("<","")
    file_contents=file_contents.replace(">","")
    file_contents=file_contents.replace("!","")
    file_contents=file_contents.replace("@","")
    file_contents=file_contents.replace("^","")
    file_contents=file_contents.replace("$","")
    file_contents=file_contents.replace("#","")
    file_contents=file_contents.replace("%","")
    file_contents=file_contents.replace("&","")
    file_contents=file_contents.replace(".","")
    file_contents=file_contents.replace(",","")
    file_contents=file_contents.replace("?","")
    file_contents=file_contents.replace("[","")
    file_contents=file_contents.replace("]","")
    file_contents=file_contents.replace("\"","")
    file_contents=file_contents.replace("'","")
    file_contents=file_contents.replace(":","")
    f.close()
    return file_contents
    




def inWords(str):
    dw=["the","is","and","in","of","for","to","a","be","will","with","this","from","but"]
    if str in dw:
        return False
    return True



def splitContents(content,k=5):
    
    word_contents=file_contents.split(" ")
    content_split={}
    for word in word_contents:
        if inWords(word)== True and len(word)>0:
            if word in content_split:
                content_split[word]=content_split[word]+1
            else:
                content_split[word]=1
    
    return content_split



#print math.log(16,2)

#file_contents=readFile("/Users/wuyinghao/Desktop/test/data/games/")
file_path1="/Users/wuyinghao/Desktop/test/data/law/"
file_path2="/Users/wuyinghao/Desktop/test/data/occult/"
file_name_list=[]
file_names=[]
for parent,dirnames,filenames in os.walk(file_path1):
        #print filenames
    for file_name in filenames:
        if(file_name[-4:] == ".txt" ):
            file_name_list.append(file_path1+file_name)
            file_names.append(file_name+"_1")
            
for parent,dirnames,filenames in os.walk(file_path2):
        #print filenames
    for file_name in filenames:
        if(file_name[-4:] == ".txt" ):
            file_name_list.append(file_path2+file_name)
            file_names.append(file_name+"_2")

start = time.time()
N=len(file_name_list)
all_words_dic={}
all_contents_list=[]
all_contents=[]
for file_name in file_name_list:
    file_contents=readFile(file_name)
    content_dic=splitContents(file_contents,5)
    words_list=[]
    for i in content_dic:
        all_words_dic[i]=1
        words_list.append([content_dic[i],i])
    words_list.sort()
    all_contents.append(content_dic)
    #words_list.().reverse()
    for i in words_list:
        i.append(float(i[0])/words_list[len(words_list)-1][0])
    all_contents_list.append(words_list)

end = time.time()
print end-start

for contents in all_contents_list:
    for i in contents:
        i.append(0)
        if i[1] in all_words_dic:
            i[3]=i[3]+1
        #for con in all_words_dic:#all_contents:
        #    if i[1] in con:
        #        i[3]=i[3]+1

end = time.time()
print end-start

for content in  all_contents_list:
    for words in content:
        if words[3]==0:
            print words
        words.append(math.log(float(N)/float(words[3]),2.0)*words[0])
        #print words

end = time.time()
print end-start

          
res=[]
for content in all_contents_list:
    sub_res=[]
    for i in content:
        sub_res.append([i[3],i[1]])
    sub_res.sort()
    res.append(sub_res)
    
end = time.time()
print end-start


fres=[]
for i in res:
    ff=[]
    for k in i[:10]:
        ff.append(k[1])
    fres.append(ff)


end = time.time()
print end-start


res1=[]
for i in range(len(fres)):
    for k in range(len(fres)):
        if k > i :
            all_key={}
            for w1 in fres[i]:
                all_key[w1]=1
            for w2 in fres[k]:
                all_key[w2]=1
            
            BJ=len(all_key)
            #print BJ
            JJ=0       
            for w in fres[i]:
                if w in fres[k]:
                    JJ=JJ+1
           
            #print JJ
            res1.append([float(JJ)/float(BJ),file_names[i],file_names[k]])
            #print float(JJ)/float(BJ)



end = time.time()
print end-start


res1.sort()
res1.reverse()
table = Texttable()
table.set_deco(Texttable.HEADER)
table.set_cols_dtype(['t',  # text 
                      't',  # float (decimal)
                      'a']) # automatic
table.set_cols_align(["l", "l", "l"])
rows=[]
rows.append([u"TextA",u"TextB", u"Similarity"])
for i in res1[:50]:
    rows.append([i[1],i[2],i[0]])
table.add_rows(rows)
print table.draw()



