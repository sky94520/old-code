#include "Arrow.h"
Arrow::Arrow()
	:m_nDamage(0),m_bAlive(false)
{
}
Arrow::~Arrow()
{
}
bool Arrow::isAlive()const
{
	return m_bAlive;
}