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
    return file_contents
    

    
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
    return float(intersection)/float(union_set)


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

hash_content1=getHashInfoFromFile("/Users/wuyinghao/Documents/test1.txt",5)
hash_content2=getHashInfoFromFile("/Users/wuyinghao/Documents/test2.txt",5)

#hash_content1={"a":1,"b":5,"c":3}
#hash_content2={"a":2,"b":4,"d":3}


intersection=calcIntersection(hash_content1,hash_content2)
union_set = calcUnionSet(hash_content1,hash_content2,intersection)
print intersection
print union_set
print "similarity is : " + str(calcSimilarity(intersection,union_set))

#print len(hash_content)
#content = readFile("/Users/wuyinghao/Documents/allreg_read.txt")
#content_list = splitContents(content,8)
#hash_content = hashContentsList(content_list)



#for key in hash_content:
#    print key + " : " + str(hash_content[key])



