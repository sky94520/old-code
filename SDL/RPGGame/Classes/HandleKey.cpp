#include "HandleKey.h"
/**
��Ե����û�������˵��һ�£�������Ӧ�� �ַ�2 4 6 8 ��w a s d�ͷ����
������΢͵��һ���������̵ķ���� ���ǵ��ֽڣ�Ҳ����˵ getch���յ�ֻ��ǰ8λ��

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
    //�ж��Ƿ��Ƿ����
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
