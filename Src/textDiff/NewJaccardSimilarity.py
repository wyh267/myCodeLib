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
import time
import progressbar


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
    return file_contents
    




#############################################
#
# 计算相似度
# 输入：签名矩阵列表
# 输出：源和目标的相似度
#
############################################# 
def calcSimilarity(v1,v2):
    totle=float(len(v1))
    similar=0.0
    for i in range(len(v1)):
        if v1[i] == v2[i] :
            similar=similar+1
    return similar/totle
    



#############################################
#
# 计算签名阵列的值
# 输入：签名函数的参数 A*x + B Mod N ,词汇表
# 输出：修改词汇表每个key后面的List
#
#############################################     
def calcMiniHash(A,B,N,hash_table):
    for i in hash_table:
        hash_table[i].append((A*i+B)%N)
        
        


#############################################
#
# 获取文件列表
# 输入：目录名
# 输出：文件列表，文件名列表
#
############################################# 
def collectFileList(file_path):
    print u"获取文件列表...."
    start = time.time()
    file_name_list=[]
    file_names=[]
    for parent,dirnames,filenames in os.walk(file_path):
        #print filenames
        for file_name in filenames:
            if(file_name[-4:] == ".txt" ):
                file_name_list.append(file_path+file_name)
                file_names.append(file_name)
    end = time.time()
    print u"获取文件列表结束，用时: " + str(end-start) + u"秒"
    return file_name_list,file_names
    
    
#############################################
#
# 获取词汇表的哈希字典，遍历每一个文件，将词汇保存在哈希
# 字典中
# 输入：文件列表
# 输出：整体词汇哈希字典，每个文件的哈希字典
#
#############################################     
def getWordsHashDictionary(file_name_list,k):
    print u"读取文件,处理词汇列表...."
    start = time.time()
    hash_table={}
    union_table=[]
    all=float(len(file_name_list))
    pos=0.0
    pro = progressbar.ProgressBar().start()
    for file in file_name_list:
        pos=pos+1
        rate_num=int(pos/all*100)
        pro.update(rate_num)
        content = readFile(file)
        single_hash_table={}
        for i in range(len(content)-k):
            hash_num=hash(content[i:i+k])%2**32
            hash_table[hash_num]=[]
            #if hash_num in single_hash_table:
            #    single_hash_table[hash_num]=single_hash_table[hash_num]+1
            #else:
            #    single_hash_table[hash_num]=1
            single_hash_table[hash_num]=1
        union_table.append(single_hash_table)
    end = time.time()
    pro.finish()
    print u"读取文件,处理词汇列表结束，用时: " + str(end-start) + u"秒"
    return hash_table,union_table
    
    
#############################################
#
# 计算签名矩阵列表
# 计算以后，hash_table 变成如下结构
#  hash_table[123432] = [3,69,123]
#  ...
#  ...
#  hash_table[34522] = [64,9,3]
#
#  这种形式，后面的列表表示每个签名函数对应的值
# 输入：整体词汇哈希字典，hash函数的参数列表
# 输出：无，直接修改整体词汇哈希字典
#
#############################################     
def calcMinHashTableList(hash_table,min_hash_args):
    print u"计算签名哈希列表...."
    start = time.time()
    N=len(hash_table)
    all=float(len(min_hash_args))
    pos=0.0
    pro = progressbar.ProgressBar().start()
    for arg in min_hash_args:
        pos=pos+1
        rate_num=int(pos/all*100)
        pro.update(rate_num)
        calcMiniHash(arg[0],arg[1],N,hash_table)
    end = time.time()
    pro.finish()
    print u"计算签名哈希列表结束，用时: " + str(end-start) + u"秒"
    
    


#############################################
#
# 生成签名矩阵
# 输入：每个文件的哈希字典集合,签名集合的数量
# 输出：签名矩阵
#
############################################# 
def createSignaturesMatrix(union_table,sig_hash_len,hash_table):
    print u"生成签名矩阵...."
    start = time.time()
    sig_mat_list=[]
    all=float(len(union_table))
    pos=0.0
    pro = progressbar.ProgressBar().start()
    for union_hash in union_table:
        pos=pos+1
        rate_num=int(pos/all*100)
        pro.update(rate_num)
        #print "SINGLE HASH TABLE LEN IS ::::" + str(len(union_hash))
        sig_mat=["inf"]*sig_hash_len
        for key in union_hash:
            for index in range(sig_hash_len):
                if ( union_hash[key]*hash_table[key][index] < sig_mat[index]):
                    sig_mat[index]=union_hash[key]*hash_table[key][index]
        sig_mat_list.append(sig_mat)
    end = time.time()
    pro.finish()
    print u"生成签名矩阵结束，用时: " + str(end-start) + u"秒"
    return sig_mat_list
    
    
#############################################
#
# 计算集合中两两的相似度
# 输入：签名矩阵列表，文件名列表
# 输出：相似度列表[[相似度,文件1,文件2].....[相似度,文件k,文件n]]
#      按照相似度降序排列
#
############################################# 
def calcEachSimilarity(sig_mat_list,file_names):
    print u"计算相似度...."
    start = time.time()
    similar_res_list=[]
    for index1,v1 in enumerate(sig_mat_list):
        for index2,v2 in enumerate(sig_mat_list):
            if(index2>index1):
                similar_res_list.append([calcSimilarity(v1,v2),file_names[index1],file_names[index2]])
    similar_res_list.sort()
    similar_res_list.reverse()
    end = time.time()
    print u"计算相似度结束，用时: " + str(end-start) + u"秒"
    return similar_res_list
    
    
    

#############################################
#
# 程序入口
# 输入：目录路径，参数列表 A*x+B mod N 中的A 和 B ,k-shingle的k值
#      [[A1,B1],[A2,B2]....[An,Bn]]
# 输出：相似度列表[[相似度,文件1,文件2].....[相似度,文件k,文件n]]
#      按照相似度降序排列
#
############################################# 
def calcSimilarityByMiniHashSignaturesMatrix(file_path,min_hash_args,k=5):
    
    file_name_list,file_names=collectFileList(file_path)
    hash_table,union_table=getWordsHashDictionary(file_name_list,k) 
    calcMinHashTableList(hash_table,min_hash_args)
    sig_mat_list=createSignaturesMatrix(union_table,len(min_hash_args),hash_table)
    res=calcEachSimilarity(sig_mat_list,file_names)
    
    return res

#############################################
#
# 主程序 
#
#
#############################################

#file_path="/Users/wuyinghao/Desktop/test/data/media/"
#min_hash_args=[[1,1],[3,1],[5,7]]
#res=calcSimilarityByMiniHashSignaturesMatrix(file_path,min_hash_args)

#print u"显示输出...."
#for i in res[:10]:
#    print i


