--第一个迭代器
function values(t)
	local i = 0;
	return function()
		i = i+1;
		return t[i];
	end
end

t = {10,20,30};
iter = values(t);--iter是内部的匿名函数 此时初始化i为1
--[[while true do
	local element = iter();
	if element == nil then
		break;
	end
	print(element);
end]]--
--for在内部保存了这个迭代器
for element in values(t) do
	print(element);
end

