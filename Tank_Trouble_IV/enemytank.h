// enemytank.h
#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include <QObject>
#include <QRect>

class EnemyTank : public QObject
{
    Q_OBJECT
public:
    explicit EnemyTank(QObject *parent = nullptr);
    EnemyTank(int x, int y, int health, QObject *parent = nullptr);

    QRect getRect() const;
    void setRect(const QRect &value);

    int getHealth() const;
    void setHealth(int value);

    bool isAlive() const;

signals:
    void tankDestroyed();

public slots:
    void takeDamage(int damage);

private:
    QRect rect;
    int health;
};

#endif // ENEMYTANK_H
