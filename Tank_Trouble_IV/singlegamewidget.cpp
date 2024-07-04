#include "singlegamewidget.h"
#include "ui_singlegamewidget.h"

SingleGameWidget::SingleGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleGameWidget)
{
    ui->setupUi(this);
    map.createMap();

    scene = new QGraphicsScene(this);
    QGraphicsRectItem *rect = new QGraphicsRectItem(0, 0, 50, 50);
    scene->addItem(rect);
    QGraphicsRectItem *rect1 = new QGraphicsRectItem(50, 0, 1000, 1000);
    scene->addItem(rect1);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->centerOn(200,200);


}

SingleGameWidget::~SingleGameWidget()
{
    delete ui;

}

void SingleGameWidget::on_btnPause_clicked()
{
    emit signalPause();
}

