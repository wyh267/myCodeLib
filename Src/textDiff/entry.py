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

file_path="/Users/wuyinghao/Desktop/test/data/sex/"
min_hash_args=[[1,1],[3,1],[5,7]]
k=5


print u"使用基本JaccardSimilarity开始计算相似度...."
start = time.time()

res=JaccardSimilarity.calcSimilarityByWords(file_path,k)
print u"显示输出...."
for i in res[:10]:
    print i
    

end = time.time()
print u"使用基本JaccardSimilarity计算相似度结束，总共用时: " + str(end-start) + u"秒"
print u"============================================================================="
print u"============================================================================="
print u"使用优化JaccardSimilarity开始计算近似相似度...."
start = time.time()

res=NewJaccardSimilarity.calcSimilarityByMiniHashSignaturesMatrix(file_path,min_hash_args,k)

print u"显示输出...."
for i in res[:10]:
    print i

end = time.time()
print u"使用优化JaccardSimilarity计算近似相似度结束，总共用时: " + str(end-start) + u"秒"


