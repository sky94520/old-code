--怪物
--变异的兔子
VariantRabbit = {};
VariantRabbit.name = "变异的兔子";
VariantRabbit.description = "原本是可爱的，萌萌的小兔子，但受了魔气的熏染而变得狂躁起来";
VariantRabbit.hp = math.random(4,7);
VariantRabbit.damage = math.random(2,4);
VariantRabbit.agility = math.random(1,2);
VariantRabbit.gold = math.random(4,5);
VariantRabbit.attack = function(playerID,...)
	LUA_Hurt(playerID,VariantRabbit.damage);
	LUA_Text(playerID.."受到攻击，HP-"..VariantRabbit.damage);
end
--史莱姆
Slime = {};
Slime.name = "史莱姆";
Slime.description = "性质奇异，但没有什么特殊的能力";
Slime.hp = math.random(5,8);
Slime.damage = math.random(1,2);
Slime.gold = math.random(4,5);
Slime.agility = math.random(1,2);
Slime.attack = function(playerID,...)
	LUA_Hurt(playerID,Slime.damage);
	LUA_Text(playerID.."受到攻击，HP-"..Slime.damage);
end
--僵尸
Zombie = {}
Zombie.name = "僵尸";
Zombie.description = "一阵阵腐臭传来，但身体却刀枪不入";
Zombie.hp = math.random(12,15);
Zombie.damage = math.random(3,5);
Zombie.agility = math.random(1,2);
Zombie.gold = math.random(8,10);
Zombie.attack = function(playerID,...)
	LUA_Hurt(playerID,Zombie.damage);
	LUA_Text(playerID.."受到攻击，HP-"..Zombie.damage);
end
--平庸的哥布林
GoblinPeasant = {};
GoblinPeasant.name = "哥布林农民";
GoblinPeasant.description = "类人邪恶生物，个性贪婪又卑劣，在采矿与建筑有独特的见解,但无奈生活所迫，只能当农民";
GoblinPeasant.hp = math.random(5,8);
GoblinPeasant.damage = math.random(7,10);
GoblinPeasant.agility = math.random(3,4);
GoblinPeasant.gold = math.random(10,15);
GoblinPeasant.attack = function(playerID,...)
	LUA_Hurt(playerID,GoblinPeasant.damage);
	LUA_Text(playerID.."受到攻击，HP-"..GoblinPeasant.damage);
end
--哥布林射手
GoblinArcher = {};
GoblinArcher.name = "哥布林射手";
GoblinArcher.description = "类人邪恶生物，个性贪婪又卑劣，是哥布林中的佼佼者";
GoblinArcher.hp = math.random(3,6);
GoblinArcher.damage = math.random(10,15);
GoblinArcher.agility = math.random(5,8);
GoblinArcher.gold = math.random(13,18);
GoblinArcher.attack = function(playerID,...)
	LUA_Hurt(playerID,GoblinPeasant.damage);
	LUA_Text(playerID.."受到攻击，HP-"..GoblinPeasant.damage);
end
