#include "Level.h"

Level::Level()
{
}
void Level::render()
{
    for(unsigned int i = 0;i < m_layers.size();i++)
    {
        m_layers[i]->render();
    }
}
void Level::update()
{
    for(unsigned int i = 0;i < m_layers.size();i++)
    {
        m_layers[i]->update(this);
    }
}
