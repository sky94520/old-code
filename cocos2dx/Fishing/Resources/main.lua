--获取出场时间，根据权值获得
function getShowSecond(all,weightMean)
	local temp = (all - weightMean)/weightMean;
	local integer = math.floor(temp);
	
	local SECOND = 3;--
	local from = 0;
	local to = 0;
	--获取下限
	from = integer - SECOND >0 and (integer - SECOND) or 0;
	--上限
	to = SECOND + integer;
	--获取随机时间
	return math.random(from,to) + temp - integer;
end
--全局函数，在各个level.lua中使用
--ret 1.鱼的id
--2.鱼的出场时间
function getNextFishID(fishes)
	--随机从fishes中选出一个
	--获取总加权数
	local weightMean = 0;
	for k,v in pairs(fishes) do
		local fish = _G["Fish"..v];
		weightMean = weightMean + fish.weightMean;
	end
	--获取随机数
	local ran = math.random(1,weightMean);
	print("the weight mean is"..weightMean);
	print("the random is"..ran);
	local temp = 0;
	for k,v in pairs(fishes)  do
		--加载对应的鱼
		local fish = _G["Fish"..v];
		temp = temp + fish.weightMean;
		if ran <= temp then
			--返回什么时候登场
			local weight = getShowSecond(weightMean,fish.weightMean);
			return v,weight;
		end
	end
end
--随机种子
function randomSeed()
	local time = tostring(os.time());
	local r = string.reverse(time);
	return string.sub(r,1,6);
end
--加载fishes.lua
dofile("fishes.lua");
--初始化随机种子
math.randomseed(randomSeed());
--关卡数目
LevelCount = 5;
