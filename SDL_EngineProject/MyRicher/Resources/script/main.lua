function delay(duration)
	LUA_setWaitType(WaitType.Time);
	LUA_setWaitTime(duration);
	coroutine.yield();
end

function goBtnCallback(id,p)
	LUA_setGameState(GameState.Script);
	-- 获取骰子点数
	local pot = p or math.random(1,6);
	--播放骰子动画
	local duration = LUA_runAnimationOfDice(time,pot);
	delay(duration);
	--人物行走
	duration = LUA_movingOfPlayer(id,pot);
	delay(duration);

	LUA_setGameState(GameState.Normal);
end