#include "bullet.h"

Bullet::Bullet() {}

int Bullet::id() const
{
    return _id;;
}

int Bullet::damage() const
{
    return _damage;
}

int Bullet::speed() const
{
    return _speed;
}

const QLineF &Bullet::direction() const
{
    return _direction;
}

Tank *Bullet::shooter() const
{

}

void Bullet::setId(int id)
{
    _id = id;
}

void Bullet::setDamage(int damage)
{
    _damage = damage;
}

void Bullet::setSpeed(int speed)
{
    _speed = speed;
}

void Bullet::setDirection(const QLineF &direction)
{
    _direction = direction;
}
