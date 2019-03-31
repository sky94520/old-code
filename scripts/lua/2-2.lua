Node = {x = 0,y = 0};
function Node:new()
	local o = {};
	setmetatable(o,{__index = self});
	return o;
end
function Node:setPosition(x,y)
	self.x = x;
	self.y = y;
end
--Sprite
Sprite = Node:new();
function Sprite:setPosition(x,y)
	print "Sprite";
	--如何调用Node:sePosition
	Node:setPosition(x,y);
end

local s1 = Sprite:new();
s1:setPosition(3,5);
print(s1.x,s1.y);

local s2 = Node:new();
s2:setPosition(4,5);
print(s2.x,s2.y);
