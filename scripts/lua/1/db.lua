entry = {};
entry.title = "小牛牛sky的主页";
entry.org = "Computer Graphics Technology Group,PUC-Rio";
entry.url = "http://www.baidu.com";
entry.contact = "Waldemar Celes";
entry.description = [[
pcall (f [, arg1, ···])
Calls function f with the given arguments in protected mode.
This means that any error inside f is not propagated;
instead, pcall catches the error and returns a status code. 
Its first result is the status code (a boolean), which is 
true if the call succeeds without errors. In such case, 
pcall also returns all results from the call, after this 
first result. In case of any error, pcall returns false
plus the error message.
]];
