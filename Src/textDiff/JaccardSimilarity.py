# -*- coding=utf-8 -*-


# 利用jaccard similarity 计算文本相似度

import os


#
# 读取文件，保存到一个字符串中
# 输入： 文件名完整路径
# 输出： 文件内容
#
def readFile(file_name):
    f=open(file_name,"r")
    file_contents=f.read()
    file_contents=file_contents.replace("\t","")
    file_contents=file_contents.replace("\r","")
    file_contents=file_contents.replace("\n","")
    f.close()
    return file_contents
    

    

#
# 分割字符串，使用k-shingle方式进行分割
# 输入：字符串，k值
# 输出：分割好的字符串，存入数组中
#
def splitContents(content,k=5):
    content_split=[]
    for i in range(len(content)-k):
        content_split.append(content[i:i+k])
    return content_split
    


#
# 将数据保存到hash表中，也就是某个集合
# 输入：已经分隔好的数据
# 输出：hash表
#
def hashContentsList(content_list):
    hash_content={}
    for i in content_list:
        if i in hash_content:
            hash_content[i]=hash_content[i]+1
        else:
            hash_content[i]=1
    return hash_content




#
# 从某个文本文件获取一个集合，该集合保存了文本中单词的出现频率
# 输入：文件名，k值,默认为5
# 输出：一个词频的hash表
#
def getHashInfoFromFile(file_name,k=5):
    content=readFile(file_name)
    content_list = splitContents(content,k)
    hash_content = hashContentsList(content_list)
    return hash_content
    


hash_content=getHashInfoFromFile("/Users/wuyinghao/Documents/allreg_read.txt",8)


#content = readFile("/Users/wuyinghao/Documents/allreg_read.txt")
#content_list = splitContents(content,8)
#hash_content = hashContentsList(content_list)



for key in hash_content:
    print key + " : " + str(hash_content[key])



