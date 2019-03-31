network = {
	{name="grauna",ip="210.26.30.34"},
	{name="lua",ip="210.26.30.23"},
	{name="derain",ip="210.26.23.20"}
};
table.sort(network,function(a,b)return a.name>b.name; end);
for k,v in ipairs(network) do
	print(v.name,v.ip);
end

function derivative(f,delta)
	delta = delta or 1e-4;
	return function(x)
		print(x,delta);
		return (f(x+delta) - f(x))/delta;
	end
end

c = derivative(math.sin);
print(math.cos(10),c(10));
--闭包函数
function newCounter()
	local i=0;
	return function()
		i = i+1;
		return i;
	end
end
c1 = newCounter();
c2 = newCounter();
print(c1());
print(c2());
print(c1());
print(c1());
print(newCounter());
print(newCounter());
