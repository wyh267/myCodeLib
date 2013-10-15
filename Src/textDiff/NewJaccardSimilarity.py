# -*- coding=utf-8 -*-

#
#
#
#
# 利用jaccard similarity 计算文本相似度,优化版本
#
#
#
#

import os


#全局变量，提供全局字典，用于存储每个字符串对应的整数hash值
g_hash={}
g_val=0




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
    

    
#############################################
#
# 分割字符串，使用k-shingle方式进行分割，并且更新全局字典
# 输入：字符串，k值
# 输出：分割好的字符串，存入数组中
#
#############################################
def splitContents(content,k=5):
    global g_hash
    global g_val
    content_split=[]
    for i in range(len(content)-k):
        content_split.append(content[i:i+k])
        
    for v in content_split:
        if v in g_hash:
            pass
        else:
            g_hash[v]=g_val
            g_val=g_val+1
    return content_split
    
    
    

#############################################
#
# 计算某个文档的简易hash值
# 输入：文档词语数组
# 输出：一个词频的简易hash表，用list保存
#
#############################################
def storeIntHash(content_list):
    global g_hash
    hash_list=[0]*len(g_hash)    

    for v in content_list:
        hash_list[g_hash[v]]=hash_list[g_hash[v]]+1
    
    return hash_list





#测试输出显示
def display(list,end,string):
    print string + "::\t",
    for i in range(end):
        print str(list[i])+ "\t",
    print ""


#############################################
#
# 数据整形
# 输入：所有数据
# 输出：整形后的数据
#
#############################################
def adjContentList(hash_contents):
    global g_hash
    index=0
    for i in hash_contents:
        extend=len(g_hash)-len(i)
        hash_contents[index].extend([0]*extend)
        index=index+1
    



#############################################
#
# hash生成函数，使用 A*x+1 mod N 的形式
# 输入：hash序列数，参数
# 输出：生成的hash函数
#
#############################################
def calcMinHash(A,N,hash_list):
    min_hash=[]
    for i in hash_list:
        min_hash.append((A*i+1)%N)
    return min_hash


#############################################
#
# 从某个文本文件获取一个集合，该集合保存了文本中单词的出现频率
# 输入：文件名，k值,默认为5
# 输出：一个词频的hash表
#
#############################################
def getHashInfoFromFile(file_name,k=2):
    content=readFile(file_name)
    content_list = splitContents(content,k)
    return storeIntHash(content_list)
  



#############################################
#
# 计算签名
# 输入：某个集合，minHash数组
# 输出：更新后的签名集合
#
#############################################
def calcSignatures(union,min_hash,sig_list,union_num):  
    #print sig_list
    for indexsig,sig in enumerate(sig_list):
        for index,v in enumerate(union):
            if(v*min_hash[indexsig][index] < sig_list[indexsig][union_num] and v >0):
                #print "min : " +str(v*min_hash[indexsig][index])
                sig_list[indexsig][union_num]=v*min_hash[indexsig][index]
     
            

#############################################
#
# 计算相似度
# 输入：签名矩阵列表，源索引，目标索引
# 输出：源和目标的相似度
#
############################################# 
def calcSimilarity(sig_list,src_index=0,des_index=1):
    totle=float(len(sig_list))
    similar=0.0
    for sig in sig_list:
        if(sig[src_index]==sig[des_index]):
            similar=similar+1.0
    return similar/totle
    
    
    
#############################################
#
# 计算签名矩阵
# 输入：签名矩阵的个数
# 输出：签名列表集合
#
#############################################    
def calcSignatureMat(sig_num,sig_len=2):
    sig_list=[]
    for i in range(sig_num):
        sig_list.append([99999]*sig_len)
    return sig_list
    
    

#############################################
#
# 主程序 
#
#
#############################################
def calcEachSimalar(file_name_list):
    global g_hash
    global g_val
    res=[]
    for index1,v1 in enumerate(file_name_list):
        for index2,v2 in enumerate(file_name_list):
            g_hash.clear()
            g_val=0
            hash_contents=[]
            min_hashs=[]
            if(v1 != v2 and index2>index1):
                hash_contents.append(getHashInfoFromFile(v1))
                hash_contents.append(getHashInfoFromFile(v2))
                adjContentList(hash_contents)
                a=[x for x in range(len(g_hash))]
                minhash_pares=[2,3,5,7,11]
                for para in minhash_pares:
                    min_hashs.append(calcMinHash(para,len(g_hash),a))           
                sig_list=calcSignatureMat(len(min_hashs))
                for index,content in enumerate(hash_contents):
                    calcSignatures(content,min_hashs,sig_list,index)
                simalar=calcSimilarity(sig_list)
                res.append([v1,v2,simalar])
                #print v1 + " ||| " + v2 + " similarity is " +str(simalar)
    return res
                


#############################################
#
# 主程序 
#
#
#############################################


file_name_list=["/Users/wuyinghao/Documents/test1.txt",
                "/Users/wuyinghao/Documents/test2.txt",
                "/Users/wuyinghao/Documents/test3.txt"]


all_res = calcEachSimalar(file_name_list)


for res in all_res:
    print res[0] + " ||| " + res[1] + " similarity is " +str(res[2])



"""
hash_contents=[]
min_hashs=[]
hash_contents.append(getHashInfoFromFile("/Users/wuyinghao/Documents/test1.txt"))
hash_contents.append(getHashInfoFromFile("/Users/wuyinghao/Documents/test2.txt"))
hash_contents.append(getHashInfoFromFile("/Users/wuyinghao/Documents/test3.txt"))
adjContentList(hash_contents)

a=[x for x in range(len(g_hash))]
min_hashs.append(calcMinHash(2,len(g_hash),a))
min_hashs.append(calcMinHash(3,len(g_hash),a))
min_hashs.append(calcMinHash(5,len(g_hash),a))
min_hashs.append(calcMinHash(7,len(g_hash),a))
min_hashs.append(calcMinHash(11,len(g_hash),a))
sig_list=calcSignatureMat(5,3)


for index,content in enumerate(hash_contents):
    calcSignatures(content,min_hashs,sig_list,index)

"""
"""
display(a,20,"Numbers")
print ""

for i in hash_contents:
    display(i,20,"testUnion")

for i in min_hashs:
    display(i,20,"minHash")
    

for i in sig_list:
    display(i,3,"siglist")
   
    
print calcSimilarity(sig_list,0,1)
print calcSimilarity(sig_list,0,2)
print calcSimilarity(sig_list,1,2)

print len(g_hash)
""" 



"""
g_hash={1:1,2:2,3:3,4:4,5:5}
hash_contents=[]
min_hashs=[]
hash_contents.append([1,0,0,1,0])
hash_contents.append([0,0,1,0,0])
hash_contents.append([0,1,0,1,1])
hash_contents.append([1,0,1,1,0])
adjContentList(hash_contents)

a=[x for x in range(len(g_hash))]
min_hashs.append(calcMinHash(1,len(g_hash),a))
#min_hashs.append(calcMinHash(3,len(g_hash),a))
min_hashs.append(calcMinHash(3,len(g_hash),a))
#min_hashs.append(calcMinHash(7,len(g_hash),a))
#min_hashs.append(calcMinHash(11,len(g_hash),a))

sig_list=calcSignatureMat(2,4)


for index,content in enumerate(hash_contents):
    calcSignatures(content,min_hashs,sig_list,index)





display(a,5,"Numbers")
print ""

for i in hash_contents:
    display(i,5,"testUnion")

for i in min_hashs:
    display(i,5,"minHash")
    

for i in sig_list:
    display(i,4,"siglist")


print calcSimilarity(sig_list,0,3)
print calcSimilarity(sig_list,0,2)
print calcSimilarity(sig_list,0,1)
print calcSimilarity(sig_list,2,3)

print len(g_hash)

"""


