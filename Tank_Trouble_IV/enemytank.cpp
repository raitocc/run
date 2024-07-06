// enemytank.cpp
#include "enemytank.h"

EnemyTank::EnemyTank(QObject *parent) : QObject(parent)
{
    health = 100;
}

EnemyTank::EnemyTank(int x, int y, int health, QObject *parent) : QObject(parent)
{
    rect = QRect(x, y, 50, 50); // Example size and position
    this->health = health;
}

QRect EnemyTank::getRect() const
{
    return rect;
}

void EnemyTank::setRect(const QRect &value)
{
    rect = value;
}

int EnemyTank::getHealth() const
{
    return health;
}

void EnemyTank::setHealth(int value)
{
    health = value;
}

bool EnemyTank::isAlive() const
{
    return health > 0;
}

void EnemyTank::takeDamage(int damage)
{
    health -= damage;
    if (health <= 0)
    {
        emit tankDestroyed();
    }
}
