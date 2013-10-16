# -*- coding=utf-8 -*-

#
#
#
#
# 利用jaccard similarity 计算文本相似度
#
#
#
#

import os



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
    return file_contents#to_unicode_or_bust(file_contents)
    

    
#############################################
#
# 分割字符串，使用k-shingle方式进行分割
# 输入：字符串，k值
# 输出：分割好的字符串，存入数组中
#
#############################################
def splitContents(content,k=5):
    content_split=[]
    for i in range(len(content)-k):
        content_split.append(content[i:i+k])
    return content_split
    

#############################################
#
# 将数据保存到hash表中，也就是某个集合
# 输入：已经分隔好的数据
# 输出：hash表
#
#############################################
def hashContentsList(content_list):
    hash_content={}
    for i in content_list:
        if i in hash_content:
            hash_content[i]=hash_content[i]+1
        else:
            hash_content[i]=1
    return hash_content
    
    
#############################################   
#
# 计算交集
# 输入：两个hash表
# 输出：交集的整数
#
#############################################
def calcIntersection(hash_a,hash_b):
    intersection=0
    if(len(hash_a) <= len(hash_b)):
        hash_min=hash_a
        hash_max=hash_b
    else:
        hash_min=hash_b
        hash_max=hash_a
        
    for key in hash_min:
        if key in hash_max:
            if(hash_min[key]<=hash_max[key]):
                intersection=intersection+hash_min[key]
            else:
                intersection=intersection+hash_max[key]
        
    return intersection


#############################################
#
# 计算并集
# 输入：两个hash表
# 输出：并集的整数
#
#############################################
def calcUnionSet(hash_a,hash_b,intersection):
    union_set=0
    
    for key in hash_a:
        union_set=union_set+hash_a[key]
    for key in hash_b:
        union_set=union_set+hash_b[key]
        
    return union_set-intersection
    
    
#############################################
#
# 计算相似度
# 输入：交集和并集
# 输出：相似度
#   
#############################################
def calcSimilarity(intersection,union_set):
    if(union_set > 0):
        return float(intersection)/float(union_set)
    else:
        return 0.0


#############################################
#
# 从某个文本文件获取一个集合，该集合保存了文本中单词的出现频率
# 输入：文件名，k值,默认为5
# 输出：一个词频的hash表
#
#############################################
def getHashInfoFromFile(file_name,k=5):
    content=readFile(file_name)
    content_list = splitContents(content,k)
    hash_content = hashContentsList(content_list)
    return hash_content


#############################################
#
# 主程序
#
#
#############################################

file_name_pre="/Users/wuyinghao/Desktop/test/data/media/"
file_name_list=[]
file_names=[]
for parent,dirnames,filenames in os.walk(file_name_pre):
    for file_name in filenames:
        if(file_name[-4:] == ".txt" ):
            file_name_list.append(file_name_pre+file_name)
            file_names.append(file_name)


#print file_name_list

hash_contents=[]

#获取每个文本的词汇词频表
for index,file_name in enumerate(file_name_list):
    #print file_name
    hash_contents.append([getHashInfoFromFile(file_name,5),file_names[index]])


res=[]
for index1,v1 in enumerate(hash_contents):
    for index2,v2 in enumerate(hash_contents):
        if(v1[1] != v2[1] and index2>index1):
            intersection=calcIntersection(v1[0],v2[0]) #计算交集
            union_set=calcUnionSet(v1[0],v2[0],intersection) #计算并集
            similar=calcSimilarity(intersection,union_set)
            res.append([similar,v1[1],v2[1]])
            #print v1[1]+ "||||||" + v2[1] + " similarity is : " + str(calcSimilarity(intersection,union_set)) #计算相似度

res.sort()
res.reverse()

for i in res[:10]:
    print i




