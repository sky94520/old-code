--[[
--print("enter your expression:");
local l = io.read();
local func = assert(load("return "..l));
print("the result is"..func());]]--

--[[print("enter your expression:");
local l = io.read();
local func = assert(load("local x = ...;return "..l));
for i=1,20 do
	print(string.rep("*",func(i)));
end]]--
local file,msg;
repeat
	print "open a file name:";
	local name = io.read();
	if not name then
		return 
	end
	file,msg = io.open(name,"r");
	if not file then
		print(msg);
	end
until file
--打开文件知道成功
function func()
	error({code=121;});
end
local status,err = pcall(func);
print(status);
