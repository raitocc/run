#ifndef SINGLEGAMEWIDGET_H
#define SINGLEGAMEWIDGET_H

#include <QWidget>
#include "gamemap.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QGraphicsRectItem>
//#include "testtank.h"
#include <QKeyEvent>
#include <QTimer>


namespace Ui {
class SingleGameWidget;
}

class SingleGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleGameWidget(QWidget *parent = nullptr);
    ~SingleGameWidget();

    void drawMap();
    bool eventFilter(QObject *watched, QEvent *event);
    void setViewFocus();//������ͼΪ�佹��
    void timerStart();

public slots:
    void on_btnPause_clicked();

    void advance();

    void slotFailed();//游戏失败

private:
    Ui::SingleGameWidget *ui;
    GameMap map;
    QGraphicsScene* scene;

    bool ifFailed;

    //testTank* tank;

    QTimer* timer;
    int level;//关卡
    int money;//金币数

    void centerViewOnTank();


signals:
    void signalPause();

    void signalGameFailed();
    void HP_changed();//Ѫ���ı�
private slots:
    void if_HP_changed();
    void progressBar_valueChanged();
    void change_label_level();
    void change_label_money(const QString &link);
};

#endif // SINGLEGAMEWIDGET_H
