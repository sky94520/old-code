--关卡
Level = {};
Level.fishes = {1,3,5};
Level.getNextFishID = function()
	return getNextFishID(Level.fishes);
end
Level.restriction = {};
Level.restriction.times = 25;--出手次数
Level.restriction.needFishes = "3 4,5 2";--通关需要的鱼的数量以及种类
