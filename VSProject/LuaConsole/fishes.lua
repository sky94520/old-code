--第一种鱼---
Fish1 = {};
Fish1.id = 1;
Fish1.name = "小白鱼";
Fish1.desc = "鱼中的小精灵，经常穿梭在鱼草中";
Fish1.speed = 300;
Fish1.weightMean = 20;--加权平均数，表示出现的概率
Fish1.gold = 1;
Fish1.colliableRect = {0,0,50,48};
Fish1.scaredRect = {0,0,50,48};
Fish1.walkFrame = 10;
Fish1.deadFrame = 2;
--第二种鱼
Fish2 = {};
Fish2.id = 2;
Fish2.name = "小红鱼";
Fish2.desc = "鲜艳美丽，但是并没有毒性";
Fish2.speed = 260;
Fish2.weightMean = 15;--加权平均数，表示出现的概率
Fish2.gold = 2;
Fish2.colliableRect = {0,0,55,55};
Fish2.scaredRect = {0,0,55,55};
Fish2.walkFrame = 10;
Fish2.deadFrame = 2;
--第三种鱼
Fish3 = {};
Fish3.id = 3;
Fish3.name = "草鱼";
Fish3.desc = "有人说草生鱼，反正我不信";
Fish3.speed = 200;
Fish3.weightMean = 10;--加权平均数，表示出现的概率
Fish3.gold = 5;
Fish3.colliableRect = {0,0,73,73};
Fish3.scaredRect = {0,0,73,73};
Fish3.walkFrame = 10;
Fish3.deadFrame = 2;
