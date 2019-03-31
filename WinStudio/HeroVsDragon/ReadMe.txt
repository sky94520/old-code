如何决定攻击者和被攻击者？
1.在Skill类中写函数 setOwner() setAtk() 来设置
当Button的mouseLBDown()被调用并且有效时，再回调
Skill::attack()函数。这时产生的log放到一个单例类FightingLog中

2.使用lua，技能为技能描述文件，并且有相应的attack函数，
这样就不再分怪物和人的技能，只要注册了，就都能使用，关键是在
Skill.lua中
--需要获取
--1.人物的当前等级，mp 或 hp的多少 攻击力 等内容
NoramlSkill.attack = function()
end
目前的解决方案是使用lua++，但我几乎没有用过。。。
