--集合
function Set(list)
	local set = {};
	for k,v in ipairs(list) do
		set[v] = true;
	end
	return set;
end
--插入元素，值为插入了多少个
function insert(bag,element)
	bag[element] = bag[element] or 0 + 1;
end
function remove(bag,element)
	local count = bag[element];
	bag[element] = (count and count > 1) and count -1 or nil;
end
--test
reversed = Set{"while","end","function","local"};

for key,value in pairs(reversed) do
	print(key,value);
end
