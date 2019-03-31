--地图属性
map = {};
map.name = "矿洞";
map.description = "阴暗而又潮湿，踩在地上黏黏的，令人后怕";
map.step = math.random(8,10);
--地图等级，地图中的怪物会根据这个等级进行相应的增幅
map.level = 1;
map.monsters = "Slime,Zombie";
--传送阵
TransferMatrix1 = {x=1,y=7,mapFile="map/map2.lua"};
TransferMatrix2 = {x=39,y=7,mapFile="map/map3.lua"};
--保存传送阵数量
TransferMatrix={}
TransferMatrix.size = 2;
