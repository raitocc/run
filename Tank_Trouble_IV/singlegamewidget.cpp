#include "singlegamewidget.h"
#include "ui_singlegamewidget.h"

SingleGameWidget::SingleGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleGameWidget)
{
    ui->setupUi(this);
    map.createMap();
}

SingleGameWidget::~SingleGameWidget()
{
    delete ui;
}

void SingleGameWidget::on_btnPause_clicked()
{
    emit signalPause();
}

