关于方块下落，
有以下三种情况
1.无事件发生
2.仅仅是碰撞

3.游戏结束
关于游戏结束，我是判断是否有方块在场景外，
若有设置bOutside = true
MapLayer::isGameOver()，先判断bOutside,
然后y即方块在map的位置 先加一，因为要判断下一个是否有方格
，再判断是否发生碰撞，bCollided = true
。若都为true，游戏结束

