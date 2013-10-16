# -*- coding=utf-8 -*-

#
#
#
#
# 整体文件
#
#
#
#

import NewJaccardSimilarity
import JaccardSimilarity
import time

file_path="/Users/wuyinghao/Desktop/test/data/media/"
min_hash_args=[[1,1],[3,1],[5,7]]
k=5


print u"使用基本JaccardSimilarity开始计算相似度...."
start = time.time()

res=JaccardSimilarity.calcSimilarityByWords(file_path,k)
res1=res[:20]

    

end = time.time()
print u"使用基本JaccardSimilarity计算相似度结束，总共用时: " + str(end-start) + u"秒"
print u"============================================================================="
print u"============================================================================="
print u"使用优化JaccardSimilarity开始计算近似相似度...."
start = time.time()

res=NewJaccardSimilarity.calcSimilarityByMiniHashSignaturesMatrix(file_path,min_hash_args,k)
res2=res[:20]

end = time.time()
print u"使用优化JaccardSimilarity计算近似相似度结束，总共用时: " + str(end-start) + u"秒"
print ""
print ""
print u"============================================================================="
print u"============================================================================="
print ""
print ""

print u"使用基本JaccardSimilarity计算结果，显示输出...."
for i in res1:
    print i


print u"使用优化JaccardSimilarity计算近似相似度结果，显示输出...."
for i in res2:
    print i
    
catch=0.0
for v in res2:
    for k in res1:
        if(v[1]==k[1] and v[2]==k[2]):
            catch=catch+1

print u"前20名命中率:::" + str(catch/20)



