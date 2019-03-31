#include "Player.h"
Player::Player()
	:position()
{
}
Player::~Player()
{
}
void Player::bindSprite(char sprite)
{
	this->sprite = sprite;
}
void Player::setPosition(int x,int y)
{
	position.x = x;
	position.y = y;
}
void Player::setPosition(const Point&pos)
{
	position.x = pos.x;
	position.y = pos.y;
}
Point Player::getPosition()const
{
	return position;
}
void Player::render()
{
	for(int i=0;i<position.y;i++)
	{
		printf("\n");
	}
	for(int j=0;j<position.x;j++)
	{
		printf(" ");
	}
	printf("%c",sprite);
}