#include "main.hpp"

GameCamera::GameCamera(int x, int y)
{
    posX = x;
    posY = y;
}

GameCamera::~GameCamera()
{
}

void GameCamera::refreshPosition(int x, int y)
{
    posX = x;
    posY = y;
}

GameObject::GameObject(int x, int y)
{
    posX = x;
    posY = y;
    character = '@';
    color = TCODColor::white;
    ai = NULL;
    name = "@Game object";
}

GameObject::~GameObject()
{
}

void GameObject::move(int dx, int dy)
{
    posX += dx;
    posY += dy;
}

PlayerObject::~PlayerObject()
{
}
