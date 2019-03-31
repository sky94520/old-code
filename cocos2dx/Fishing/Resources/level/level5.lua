--关卡
Level = {};
Level.fishes = {1,2,3,4,5};
Level.getNextFishID = function()
	return getNextFishID(Level.fishes);
end
Level.restriction = {};
Level.restriction.times = 32;--出手次数
Level.restriction.needFishes = "1 5,2 4,3 3,4 2,5 1";--通关需要的鱼的数量以及种类
