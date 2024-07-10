#ifndef SINGLEGAMEWIDGET_H
#define SINGLEGAMEWIDGET_H

#include "gamedata.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
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

    void newGameData();

    void pauseBack();
private slots:
    void on_btnPause_clicked();

protected:
    void resizeEvent(QResizeEvent* event) override;
    //void keyPressEvent(QKeyEvent* event) override;
    //void keyReleaseEvent(QKeyEvent* event) override;

private:
    Ui::SingleGameWidget *ui;
    GameData* data;
    QGraphicsScene* scene;
    QTimer* timer;

    void initView();//初始化View
    void initTimer();//初始化Timer
    void drawMap();//绘制地图
    void drawTank();//绘制坦克

    void advance();//更新显示

signals:
    void signalPause();
};

#endif // SINGLEGAMEWIDGET_H
