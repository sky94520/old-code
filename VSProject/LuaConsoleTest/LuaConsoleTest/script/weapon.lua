--在c/c++中注册的函数
--id 为 英雄,damage为伤害
--LUA_Hurt(id,damage);使ID受伤
--LUA_Text(text);输出文本
--传家宝
Heirloom = {};
Heirloom.name = "传家宝";
Heirloom.description = "你离家励志要闯出一番事业时，你爸妈便传给了你，除了纪念，并没什么用处";
Heirloom.damage = 5;
Heirloom.price = 0;
Heirloom.attack = function(playerID,...)
end
--小木棍
Stick = {};
Stick.name = "小木棍";
Stick.description = "不知从哪淘来的树枝，被无聊的人捡起来当作武器，除了壮胆外，一无是处";
Stick.damage = 1;
Stick.price = 1;
Stick.attack = function(playerID,...)
end
--石斧
StoneAxe = {};
StoneAxe.name = "石斧";
StoneAxe.description = "原本普普通通，但经过无数岁月的洗礼，依然普普通通,但使用时产生反震，每次攻击血量-1";
StoneAxe.damage = 5;
StoneAxe.price = 20;
StoneAxe.attack = function(playerID,...)
	LUA_Hurt(playerID,1);
	LUA_Text(playerID.."受到反震，血量-1");
end
