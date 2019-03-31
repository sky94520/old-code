--关卡
Level = {};
Level.fishes = {2,3,4,5};
Level.getNextFishID = function()
	return getNextFishID(Level.fishes);
end
Level.restriction = {};
Level.restriction.times = 35;--出手次数
Level.restriction.needFishes = "1 10,4 2,3 4";--通关需要的鱼的数量以及种类
