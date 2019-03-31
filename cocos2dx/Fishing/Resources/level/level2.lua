--关卡
Level = {};
Level.fishes = {2,3,4};
Level.getNextFishID = function()
	return getNextFishID(Level.fishes);
end
Level.restriction = {};
Level.restriction.times = 10;--出手次数
Level.restriction.needFishes = "4 3";--通关需要的鱼的数量以及种类
