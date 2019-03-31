function test_dofile(filename)
	--加载代码
	local f = assert(loadfile(filename));
	print(type(f));
	--尾调用
	return f();
end
--test
--
test_dofile("1-3.lua");


