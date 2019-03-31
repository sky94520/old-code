--严格控制局部变量的作用域
do
	local a2 = 2;
end
print(a2);
--repeat until
repeat
	print(line);
	local line = io.read();
	print(line);
until line == ""
