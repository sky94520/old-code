local smartMan = {};
smartMan.name = "sky";
smartMan.money = 5000;
smartMan.sayHello = function()
	print("say hello!");
end

local t1 = {};
local mt = {__index = smartMan};
mt.__newindex = function(table,key)
	print(key.."not existed!")
end
setmetatable(t1,mt);
t1.sayHello = function()
	print("en");
end
t1.sayHello();
