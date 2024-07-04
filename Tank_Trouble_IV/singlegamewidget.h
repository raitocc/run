#ifndef SINGLEGAMEWIDGET_H
#define SINGLEGAMEWIDGET_H

#include <QWidget>
#include "gamemap.h"
#include <QGraphicsScene>

#include <QGraphicsRectItem>

namespace Ui {
class SingleGameWidget;
}

class SingleGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleGameWidget(QWidget *parent = nullptr);
    ~SingleGameWidget();

private slots:
    void on_btnPause_clicked();

private:
    Ui::SingleGameWidget *ui;
    GameMap map;
    QGraphicsScene* scene;

signals:
    void signalPause();
};

#endif // SINGLEGAMEWIDGET_H
