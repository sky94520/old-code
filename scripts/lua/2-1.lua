--从全局表中获取字段
function getField(f)
	local v = _G;
	for w in string.gmatch(f,"[%w_]+") do
		v = v[w];
	end
	return v;
end
--赋值
function setField(f,v)
	local t = _G;
	for w,d in string.gmatch(f,"([%w_]+)(%.?)") do
		if d == "." then
			t[w] = t[w] or {};
			t = t[w];
		else
			t[w] = v;
		end
	end
end
--test
local f = getField("io.read");

print(getField("my.game.x"),my.game.x);
