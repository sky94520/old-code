--地图属性
map = {};
map.name = "荒芜小径";
map.description = "茂密的树林把阳光几乎全都遮住了，只有细细簌簌的声音";
map.step = math.random(10,20);
--地图等级，地图中的怪物会根据这个等级进行相应的增幅
map.level = 1;
map.monsters = "Slime,VariantRabbit";
--传送阵
TransferMatrix1 = {x=39,y=7,mapFile="map/map1.lua"};
--TransferMatrix2 = {x=4,y=10,mapFile="map/map3.lua"};
--保存传送阵数量
TransferMatrix={}
TransferMatrix.size = 1;
