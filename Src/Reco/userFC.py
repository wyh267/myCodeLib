# -*- coding=utf-8 -*-

import math
import sys
from texttable import Texttable


#
#   使用 |A&B|/sqrt(|A || B |)计算余弦距离
#
#
#
def calcCosDistSpe(user1,user2):
    avg_x=0.0
    avg_y=0.0
    for key in user1:
        avg_x+=key[1]
    avg_x=avg_x/len(user1)
    
    for key in user2:
        avg_y+=key[1]
    avg_y=avg_y/len(user2)
    
    u1_u2=0.0
    for key1 in user1:
        for key2 in user2:
            if key1[1] > avg_x and key2[1]>avg_y and key1[0]==key2[0]:
                u1_u2+=1
    u1u2=len(user1)*len(user2)*1.0
    sx_sy=u1_u2/math.sqrt(u1u2)
    return sx_sy


#
#   计算余弦距离
#
#
def calcCosDist(user1,user2):
    sum_x=0.0
    sum_y=0.0
    sum_xy=0.0
    for key1 in user1:
        for key2 in user2:
            if key1[0]==key2[0] :
                sum_xy+=key1[1]*key2[1]
                sum_y+=key2[1]*key2[1]
                sum_x+=key1[1]*key1[1]
    
    if sum_xy == 0.0 :
        return 0
    sx_sy=math.sqrt(sum_x*sum_y) 
    return sum_xy/sx_sy


#
#
#   相似余弦距离
#
#
#
def calcSimlaryCosDist(user1,user2):
    sum_x=0.0
    sum_y=0.0
    sum_xy=0.0
    avg_x=0.0
    avg_y=0.0
    for key in user1:
        avg_x+=key[1]
    avg_x=avg_x/len(user1)
    
    for key in user2:
        avg_y+=key[1]
    avg_y=avg_y/len(user2)
    
    for key1 in user1:
        for key2 in user2:
            if key1[0]==key2[0] :
                sum_xy+=(key1[1]-avg_x)*(key2[1]-avg_y)
                sum_y+=(key2[1]-avg_y)*(key2[1]-avg_y)
        sum_x+=(key1[1]-avg_x)*(key1[1]-avg_x)
    
    if sum_xy == 0.0 :
        return 0
    sx_sy=math.sqrt(sum_x*sum_y) 
    return sum_xy/sx_sy
    

#
#   读取文件
#
#
def readFile(file_name):
    contents_lines=[]
    f=open(file_name,"r")
    contents_lines=f.readlines()
    f.close()
    return contents_lines



#
#   解压rating信息，格式：用户id\t硬盘id\t用户rating\t时间
#   输入：数据集合
#   输出:已经解压的排名信息
#
def getRatingInformation(ratings):
    rates=[]
    for line in ratings:
        rate=line.split("\t")
        rates.append([int(rate[0]),int(rate[1]),int(rate[2])])
    return rates


#
#   生成用户评分的数据结构
#   
#   输入:所以数据 [[2,1,5],[2,4,2]...]
#   输出:1.用户打分字典 2.电影字典
#   使用字典，key是用户id，value是用户对电影的评价，
#   rate_dic[2]=[(1,5),(4,2)].... 表示用户2对电影1的评分是5，对电影4的评分是2
#
def createUserRankDic(rates):
    user_rate_dic={}
    item_to_user={}
    for i in rates:
        user_rank=(i[1],i[2])
        if i[0] in user_rate_dic:
            user_rate_dic[i[0]].append(user_rank)
        else:
            user_rate_dic[i[0]]=[user_rank]
            
        if i[1] in item_to_user:
            item_to_user[i[1]].append(i[0])
        else:
            item_to_user[i[1]]=[i[0]]
            
    return user_rate_dic,item_to_user


#
#   计算与指定用户最相近的邻居
#   输入:指定用户ID，所以用户数据，所以物品数据
#   输出:与指定用户最相邻的邻居列表
#
def calcNearestNeighbor(userid,users_dic,item_dic):
    neighbors=[]
    #neighbors.append(userid)
    for item in users_dic[userid]:
        for neighbor in item_dic[item[0]]:
            if neighbor != userid and neighbor not in neighbors: 
                neighbors.append(neighbor)
      
    neighbors_dist=[]
    for neighbor in neighbors:
        dist=calcSimlaryCosDist(users_dic[userid],users_dic[neighbor])  #calcSimlaryCosDist  calcCosDist calcCosDistSpe
        neighbors_dist.append([dist,neighbor])
    neighbors_dist.sort(reverse=True)
    #print neighbors_dist
    return  neighbors_dist


#
#   使用UserFC进行推荐
#   输入：文件名,用户ID,邻居数量
#   输出：推荐的电影ID,输入用户的电影列表,电影对应用户的反序表，邻居列表
#
def recommendByUserFC(file_name,userid,k=5):
    
    #读取文件数据
    test_contents=readFile(file_name)
    
    #文件数据格式化成二维数组 List[[用户id,电影id,电影评分]...] 
    test_rates=getRatingInformation(test_contents)
    
    #格式化成字典数据 
    #    1.用户字典：dic[用户id]=[(电影id,电影评分)...]
    #    2.电影字典：dic[电影id]=[用户id1,用户id2...]
    test_dic,test_item_to_user=createUserRankDic(test_rates)
    
    #寻找邻居
    neighbors=calcNearestNeighbor(userid,test_dic,test_item_to_user)[:k]
        
    recommend_dic={}
    for neighbor in neighbors:
        neighbor_user_id=neighbor[1]
        movies=test_dic[neighbor_user_id]
        for movie in movies:
            #print movie
            if movie[0] not in recommend_dic:
                recommend_dic[movie[0]]=neighbor[0]
            else:
                recommend_dic[movie[0]]+=neighbor[0]
    #print len(recommend_dic)
    
    #建立推荐列表
    recommend_list=[]
    for key in recommend_dic:
        #print key
        recommend_list.append([recommend_dic[key],key])
    
    
    recommend_list.sort(reverse=True)
    #print recommend_list
    user_movies = [ i[0] for i in test_dic[userid]]

    return [i[1] for i in recommend_list],user_movies,test_item_to_user,neighbors
    
    

#
#
#   获取电影的列表
#
#
#
def getMoviesList(file_name):
    #print sys.getdefaultencoding()
    movies_contents=readFile(file_name)
    movies_info={}
    for movie in movies_contents:
        movie_info=movie.split("|")
        movies_info[int(movie_info[0])]=movie_info[1:]
    return movies_info
    
    
    
#主程序
#输入 ： 测试数据集合
if __name__ == '__main__':
    reload(sys)
    sys.setdefaultencoding('utf-8')
    movies=getMoviesList("/Users/wuyinghao/Downloads/ml-100k/u.item")
    recommend_list,user_movie,items_movie,neighbors=recommendByUserFC("/Users/wuyinghao/Downloads/ml-100k/u.data",179,80)
    neighbors_id=[ i[1] for i in neighbors]
    table = Texttable()
    table.set_deco(Texttable.HEADER)
    table.set_cols_dtype(['t',  # text 
                          't',  # float (decimal)
                          't']) # automatic
    table.set_cols_align(["l", "l", "l"])
    rows=[]
    rows.append([u"movie name",u"release", u"from userid"])
    for movie_id in recommend_list[:20]:
        from_user=[]
        for user_id in items_movie[movie_id]:
            if user_id in neighbors_id:
                from_user.append(user_id)
        rows.append([movies[movie_id][0],movies[movie_id][1],""])
    table.add_rows(rows)
    print table.draw()


    
    
    
    
    
    
    
    
    
