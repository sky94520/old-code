#! /usr/bin/python
# -*- coding: gbk -*-

import os;

prefix = raw_input("输入要操作的文件夹");
#change the active dir
os.chdir(prefix);
#print "当前工作文件夹"+os.getcwd();

i=0;
allFile = os.listdir(os.getcwd());

for str in allFile:
             if str.find('.png') != -1:
                          #run
                          if i< 8:
                                       os.rename(str,prefix+'-horizontal'+'%d'%i+'.png');
                          elif i < 13:
                                       os.rename(str,prefix+"-up"+'%d'%(i-8)+".png");
                          elif i < 18:
                                       os.rename(str,prefix+"-down"+'%d'%(i-13)+".png");
                          elif i < 28:
                                       os.rename(str,prefix+"-attack"+'%d'%(i-18)+".png");
                          elif i < 40:
                                       os.rename(str,prefix+"-tie"+'%d'%(i-28)+".png");
                          elif i < 49:
                                       os.rename(str,prefix+"-dead"+'%d'%(i-40)+".png");
             i+=1;
print ("操作完成");
