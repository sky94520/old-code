#! /usr/bin/python
# -*- coding: gbk -*-

import os;
for ss in range(0,10):
             start = raw_input("请输入开始名称");
             counts = raw_input("请输入有多少个");
             j = raw_input("每次增加多少");
             prefix = raw_input("改后的前缀");
             after = 0;
             for i in range(0,int(counts)):
                          name1 = str(int(start)+j);
                          name2 = prefix + str(i)+'.png';
                          after += j;
                          print("name1="+name1+"\nname2="+name2);
