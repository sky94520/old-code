--全局函数，在各个level.lua中使用
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
			return v;
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

