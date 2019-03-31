keyBoard={};
keyBoard.up = 119;--w
keyBoard.down = 115;--s
keyBoard.left = 97;--a
keyBoard.right = 100;--d

function handleKey(key)
	if keyBoard.up == key then
		LUA_playerUp();
	elseif keyBoard.down == key then
		LUA_playerDown();
	elseif keyBoard.left == key then
		LUA_playerLeft();
	elseif keyBoard.right == key then
		LUA_playerRight();
	end
end
