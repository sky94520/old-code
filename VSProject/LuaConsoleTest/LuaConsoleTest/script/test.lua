--初始化随机数
math.randomseed(os.time());
keyBoard={};
keyBoard.up = 119;--w
keyBoard.down = 115;--s
keyBoard.left = 97;--a
keyBoard.right = 100;--d
keyBoard.exit = 48;--0
keyBoard.package = 49;--1
keyBoard.handle = 53;--5
function handleKey(key)
	if keyBoard.up == key then
		LUA_playerUp();
	elseif keyBoard.down == key then
		LUA_playerDown();
	elseif keyBoard.left == key then
		LUA_playerLeft();
	elseif keyBoard.right == key then
		LUA_playerRight();
	elseif keyBoard.exit == key then
		LUA_gameOver();
	elseif keyBoard.package == key then
		LUA_showPackageLayer();
	elseif keyBoard.handle == key then
		LUA_HandleInteractiveEvent();
	end
end
