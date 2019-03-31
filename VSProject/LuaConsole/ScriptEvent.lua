ScriptEvent = {};

function ScriptEvent:new(o)
	o = o or {};

	setmetatable(o,self);
	self.__index = self;

	return o;
end
--初始化
function ScriptEvent:initlize(id)
	self.id = id;
	print(self,self.id)
end
--playerId 触发的主角id
function ScriptEvent:execute(playerId)
end

function ScriptEvent:updateScript()
	-- body
end

function ScriptEvent:clean()
	self.clean = nil;
end
--test
npc01 = ScriptEvent:new();
