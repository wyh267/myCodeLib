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
    return useful_lines


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
    
    print gruop[0]
    print gruop[1]
    print "++++++++++++++++++++++++"
    start_reg=0;
    start_addr=0;
    addr=0
    addr_and_regs=[]
    addr_and_regs.append(gruop[1][addr])
    for reg in gruop[0]:
        if(reg[4]<gruop[1][addr][2]):
            #print str(reg)+"++++"
            addr_and_regs.append(reg)
            start_addr=start_addr+reg[2]
        else:
            addr_and_regs.append(reg)
            addr=addr+1
            addr_and_regs.append(gruop[1][addr])
            addr_and_regs.append(reg)
    print addr_and_regs
    print "========================="
            
    
    

def parseAddrsToXML(gruops):
    for gruop in gruops:
        parseAddrToXML(gruop)


lines=readFiles()
gruops=gruopLines(lines)
formatd=parseGruops(gruops)
parseFormatedGruops(formatd)
reg_addrs=parseAddrs(formatd)
parseAddrsToXML(reg_addrs)
"""
for gruop in reg_addrs:
    print gruop[0]
    print "+++++++++"
    print gruop[1]
    print "========="
"""
