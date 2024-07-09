#ifndef SINGLEGAMEWIDGET_H
#define SINGLEGAMEWIDGET_H

#include <QWidget>
#include "gamedata.h"
#include "qgraphicsscene.h"
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

    void newGameData();
private slots:
    void on_btnPause_clicked();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::SingleGameWidget *ui;
    GameData* data;
    QGraphicsScene* scene;

    void initView();
    void drawMap();

signals:
    void signalPause();
};

#endif // SINGLEGAMEWIDGET_H
