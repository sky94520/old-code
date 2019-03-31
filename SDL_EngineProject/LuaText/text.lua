require "love"

function test(a)
	print("hello world",a);
	love();

	sky("sky");
	local x,y = coroutine.yield(1,2);

	print("the func end",x,y);

	return 1,2,3;
end