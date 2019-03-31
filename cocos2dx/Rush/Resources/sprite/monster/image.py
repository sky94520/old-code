#! /usr/bin/python
# -*- coding: gbk -*-

import os;

files = os.listdir(os.getcwd());
prefix = ' ';
for fileName in files:
             if(fileName[fileName.find('.'):len(fileName)] != '.py'):
                          print(fileName);
                          #pos = fileName.find(' ');
                          #os.rename(fileName,fileName[pos+1:len(fileName)]);
                          
             
