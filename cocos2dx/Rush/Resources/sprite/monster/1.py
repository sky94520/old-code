#! /usr/bin/python
# -*- coding: gbk -*-

import os;
for ss in range(0,10):
             start = raw_input("�����뿪ʼ����");
             counts = raw_input("�������ж��ٸ�");
             j = raw_input("ÿ�����Ӷ���");
             prefix = raw_input("�ĺ��ǰ׺");
             after = 0;
             for i in range(0,int(counts)):
                          name1 = str(int(start)+j);
                          name2 = prefix + str(i)+'.png';
                          after += j;
                          print("name1="+name1+"\nname2="+name2);
