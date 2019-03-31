#include "HandleKey.h"
/**
针对电脑用户，这里说明一下，按键响应有 字符2 4 6 8 ，w a s d和方向键
这里稍微偷了一个懒，键盘的方向键 不是单字节，也就是说 getch接收的只是前8位。

*/
HandleKey::HandleKey()
{
    this->key = 0;
}
HandleKey::~HandleKey()
{

}
void HandleKey::getKey()
{
    this->key = _getch();
    //判断是否是方向键
    if(this->key < 0)
    {
        //cout<<"in"<<endl;
        this->key = _getch();
        //printf("%d",key);
        if(this->key == 72)//up
          this->key = '2';
        else if(this->key == 75)//left
		  this->key = '4';
	    else if(this->key == 77)//right
		  this->key = '6';
	    else if(this->key == 80)//down
		  this->key = '8';
    }
    else return;

   /* printf("%d",this->key);
    getch();*/
}
KEY HandleKey::judgeKey()
{
    switch(this->key)
    {
        case '0':
        return PLAYER_PROPERTY;
        break;
        case '2':
        case 'w':
        case 'W':
        return UP;
        break;
        case '4':
        case 'a':
        case 'A':
        return LEFT;
        break;
        case '6':
        case 'd':
        case 'D':
        return RIGHT;
        break;
        case '8':
        case 's':
        case 'S':
        return DOWN;
        break;
    }
}
