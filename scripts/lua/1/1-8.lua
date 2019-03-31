--链表
List = {};
function List.new()
	return {first=0,next=-1};
end
--在队列头插入元素
function List.pustfirst(value)
	local first = self.first - 1;
	self.first = first;
	list.first[first] = value;
end
--队尾插入元素
function List.pushlast(value)
	local last = self.last + 1;
	self.last = last;
	self[last] = value;
end
function List.popfirst()
	local first = self.first;
	if first > self.last then
		error("the list is empty");
	end
	local value = self[first];
	self[first] = nil;
	self.first = first + 1;
	return value;
end
function List.poplast()
	local last = self.last;
	if self.first > last then
		error("the list is empty");
	end
	local value = self[last];
	self.last = last - 1;
	return value;
end
--test
list = List.new();
list:pushlast(4);
list:pushlast("sky");


