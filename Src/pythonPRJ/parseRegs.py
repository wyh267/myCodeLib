# -*- coding=utf-8 -*-

import os

#
#读取文件
#
def readFiles():
    useful_lines=[]
    f=open("/Users/wuyinghao/Documents/allreg_read.txt","r")
    lines=f.readlines()
    for line in lines:
        line=line.replace(" ","")
        line=line.replace("\t","")
        line=line.replace("\r","")
        line=line.replace("\n","")
        if(len(line)>0):
            #print line
            useful_lines.append(line)
    f.close()
    return useful_lines

def writeFiles(input):
    f=open("/Users/wuyinghao/Documents/allreg_read.xml","w")
    f.write("<?xml version=\"1.0\" encoding=\"GB2312\"?>\r\n")
    for i in input:
        f.write(i)
        f.write("\r\n")
    f.close()
    
#
#格式化，分组
#
def gruopLines(lines):
    flag=0
    gruop=[]
    gruops=[]
    for line in lines:
        if(line[0]=="/"):
            if(len(gruop)>0 and flag==0):
                gruops.append(gruop)
                gruop=[]
                flag=flag+1
                #del gruop[0:]
            gruop.append(line)
        else:
            newLine=line[5:]
            if(newLine[0]!="["):
                newLine="[0:0]"+newLine
            gruop.append(newLine)
            flag=0
        
    return gruops
            

#
#分析每组，格式化成"REG"+LEN或者"ADDR"+LEN的形式
#
def parseGruop(gruop):
    gruop.reverse()
    reg_list=[]
    
    for val in gruop:
        reg_dsp=[]
        if(val[0]!="/"):
            val=val[1:-1]
            val_list=val.split("]")
            reg_len_list=val_list[0].split(":")
            reg_len=int(reg_len_list[0])-int(reg_len_list[1])+1
            #print "REG NAME : " + val_list[1] + "  REG_LEN: " + str(reg_len)
            reg_dsp.append("REG")
            reg_dsp.append(val_list[1])
            reg_dsp.append(reg_len)      
        else:
            addr_list=val.split("=")
            addr_list=addr_list[1].split(",")
            #print "REG ADDR: " + addr_list[0] + " SINGE_REG_LEN :" + addr_list[1]
            #print "====================="
            reg_dsp.append("ADDR")
            reg_dsp.append(addr_list[0])
            reg_dsp.append(int(addr_list[1]))
        reg_list.append(reg_dsp)
    return reg_list

#
#分析各组信息
#
def parseGruops(gruops):
    
    formated_gruops=[]
    for gruop in gruops:
        formated_gruop=parseGruop(gruop)
        formated_gruops.append(formated_gruop)
    
    return formated_gruops;


#
#分析格式化以后的信息，添加起始位和终止位
#
def parseFormatedGruop(gruop):
    
    start=0
    for val in gruop:
        if(val[0]=="REG"):
            val.append(start)
            end=start+val[2]-1
            start=end+1
            val.append(end)
            #print val
        else:
            pass
            #print val
    #print "====================="

def parseFormatedGruops(gruops):
    
    for gruop in gruops:
        parseFormatedGruop(gruop)
        

#
#将数据分成"REG"和"ADDR"两组
#
def parseAddr(gruop):
    reg_list=[]
    addr_list=[]
    for val in gruop:
        if(val[0]=="REG"):
            reg_list.append(val)
        else:
            addr_list.append(val)

    return reg_list, addr_list
    print "+++++++++++++"

def parseAddrs(gruops):
    reg_addr=()
    reg_addrs=[]
    for gruop in gruops:
        #reg_list,addr_list = parseAddr(gruop)
        reg_addr=parseAddr(gruop)
        reg_addrs.append(reg_addr)
        #regs.append(reg_list)
        #addrs.append(addr_list)
    
    return reg_addrs#regs,addrs


def parseAddrToXML(gruop):
    
    #print gruop[0]
    #print gruop[1]
    #print "++++++++++++++++++++++++"
    addrs=gruop[1]
    regs=gruop[0]
    addrs_lens=[]
    regs_lens=[]
    addrslen=0
    regslen=0
    for addr in  gruop[1]:
        addrs_lens.append(addr[2])
        addrslen=addrslen+addr[2]
        
    for reg in regs:
        regs_lens.append(reg[2])
        regslen=regslen+reg[2]
        #print reg
        
    regstart=0
    addrstart=0
    pos=0
    reglist=len(regs_lens)
    count=0
    
    #print addrs_lens
    #print regs_lens
    
    res=[]
    
    while(count < reglist ):
        if(regs_lens[count]-regstart < addrs_lens[pos]-addrstart):
            #print str(regs_lens[count]) + " in ADDR " + str(pos)
            #print "ADDR : [ " + str(gruop[1][pos][1]) + " : " + str(gruop[1][pos][2]) + "] ::::" + \
            #" REG: [" + str(gruop[0][count][1]) + " : " +str(gruop[0][count][2]) + " ]" + \
            #" START : " + str(addrstart) + \
            #" END : "  + str(addrstart+regs_lens[count]-regstart-1)
            res.append([gruop[1][pos][1],gruop[1][pos][2],gruop[0][count][1],gruop[0][count][2],addrstart,addrstart+regs_lens[count]-regstart-1,0])
            
            #regstart+regs_lens[count]
            addrstart=addrstart+regs_lens[count]-regstart
            regstart=0
            count=count+1
        else:
            if(regs_lens[count]-regstart > addrs_lens[pos]-addrstart):
                #print " FK " + str(regs_lens[count]) + " in ADDR " + str(pos)
                #print "ADDR : [ " + str(gruop[1][pos][1]) + " : " + str(gruop[1][pos][2]) + "] ::::" + \
                #" REG: [" + str(gruop[0][count][1]) + " : " +str(gruop[0][count][2]) + " ]" + \
                #" START : " + str(addrstart) + \
                #" END : "  + str(addrstart+addrs_lens[pos]-addrstart-1)
                res.append([gruop[1][pos][1],gruop[1][pos][2],gruop[0][count][1],gruop[0][count][2],addrstart,addrstart+regs_lens[count]-regstart-1,0])
                
                regstart=regstart+addrs_lens[pos]-addrstart
                addrstart=0
                pos=pos+1
            else :
                if (regs_lens[count]-regstart == addrs_lens[pos]-addrstart):
                    #print " ZH " + str(regs_lens[count]) + " in ADDR " + str(pos)
                    #print "ADDR : [ " + str(gruop[1][pos][1]) + " : " + str(gruop[1][pos][2]) + "] ::::" + \
                    #" REG: [" + str(gruop[0][count][1]) + " : " +str(gruop[0][count][2]) + " ]" + \
                    #" START : " + str(addrstart) + \
                    #" END : "  + str(addrstart+regs_lens[count]-regstart-1)
                    res.append([gruop[1][pos][1],gruop[1][pos][2],gruop[0][count][1],gruop[0][count][2],addrstart,addrstart+regs_lens[count]-regstart-1,0])
                    
                    addrstart=0
                    regstart=0
                    pos=pos+1
                    count=count+1
        #print "count : " + str(count)
        #print "addrstart : " + str(addrstart)
    return res
        
    
        
    
            
    
    

def parseAddrsToXML(gruops):
    res=[]
    for gruop in gruops:
        r=parseAddrToXML(gruop)
        for k in r:
            res.append(k)
    
    return res
    
    
    
def parCreateXML(input):
    head=input[0][0]
    print head
    addr=[]
    res=[]
    for val in input:
        if val[0] == head :
            addr.append(val)
        else:
            head=val[0]
            res.append(addr)
            addr=[]
            addr.append(val)
    return res
    
    
xmlres=[]
    
def createXLMNode(node):
    
    xmlres.append("\t\t<name>" + node[0][0] + "</name>")
    xmlres.append( "\t\t<addr>" + node[0][0] + "</addr>")
    xmlres.append( "\t\t<len>" + str(node[0][1]) + "</len>")
    i=1
    for val in node :
        #print val
        xmlres.append( "\t\t<part" + str(i) +">")
        xmlres.append( "\t\t\t<name>" + val[2] + "</name>")
        xmlres.append( "\t\t\t<addr>" + val[0] + "</addr>")
        xmlres.append( "\t\t\t<start>" + str(val[4]) + "</start>")
        xmlres.append( "\t\t\t<end>" + str(val[5]) + "</end>")
        xmlres.append( "\t\t\t<data>" + str(val[6]) + "</data>")
        xmlres.append( "\t\t</part" + str(i) +">")
        i=i+1
        
        
        
        
        
    
def createXML(input):
    xmlres.append( "<register>")
    for val in input:
        xmlres.append( "\t<reg>")
        createXLMNode(val)
        xmlres.append( "\t</reg>")
        xmlres.append( "")
    xmlres.append( "</register>")

lines=readFiles()
gruops=gruopLines(lines)
formatd=parseGruops(gruops)
parseFormatedGruops(formatd)
reg_addrs=parseAddrs(formatd)
res = parseAddrsToXML(reg_addrs)

res = parCreateXML(res)

createXML(res)
writeFiles(xmlres)

for i in xmlres:
    print i
