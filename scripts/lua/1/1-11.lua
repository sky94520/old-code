Object = {};
Object._bManaged = false;
Set = {};
--设计元表
local mt = {};
function Set.new(l)
	local set = {};
	for k,v in pairs(l) do
		set[v] = true;
	end
	setmetatable(set,mt);
	return set;
end
function Set.union(a,b)
	local set = {};

	for k,v in pairs(a) do
		set[k] = true;
	end
	for k,v in pairs(b) do
		set[k] = true;
	end
	return set;
end
function Set.intersection(a,b)
	local set = {};
	for k,v in pairs(a) do
		set[k] = b[k];
	end
	return set;
end
function Set.toString(l)
	local string = {};
	for k,v in pairs(l) do
		table.insert(string,k);
	end
	return table.concat(string,",");
end
mt.__add = Set.union;
mt.__mul = Set.intersection;
mt.__tostring = Set.toString;
mt.__metatable = "you don't have the power";
mt.__index = Object;
--小于等于
mt.__le = function(a,b)
	for k,v in pairs(a) do
		if a[k] ~= b[k] then
			return false;
		end
	end
end
--小于
mt.__lt = function(a,b)
	return a<=b and not (b <= a);
end
mt.__eq = function(a,b)
	return a<=b and b<=a;
end
s1 = Set.new{10,20,30,40};
s2 = Set.new{10,15};
s3 = s1 * s2;

print(s1);
print(getmetatable(s1));
print(s1._bManaged);
