--��c/c++��ע��ĺ���
--id Ϊ Ӣ��,damageΪ�˺�
--LUA_Hurt(id,damage);ʹID����
--LUA_Text(text);����ı�
--���ұ�
Heirloom = {};
Heirloom.name = "���ұ�";
Heirloom.description = "�������־Ҫ����һ����ҵʱ�������㴫�����㣬���˼����ûʲô�ô�";
Heirloom.damage = 5;
Heirloom.price = 0;
Heirloom.attack = function(playerID,...)
end
--Сľ��
Stick = {};
Stick.name = "Сľ��";
Stick.description = "��֪������������֦�������ĵ��˼�������������������׳���⣬һ���Ǵ�";
Stick.damage = 1;
Stick.price = 1;
Stick.attack = function(playerID,...)
end
--ʯ��
StoneAxe = {};
StoneAxe.name = "ʯ��";
StoneAxe.description = "ԭ������ͨͨ���������������µ�ϴ����Ȼ����ͨͨ,��ʹ��ʱ��������ÿ�ι���Ѫ��-1";
StoneAxe.damage = 5;
StoneAxe.price = 20;
StoneAxe.attack = function(playerID,...)
	LUA_Hurt(playerID,1);
	LUA_Text(playerID.."�ܵ�����Ѫ��-1");
end
