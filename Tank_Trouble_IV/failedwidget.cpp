#include "failedwidget.h"
#include "ui_failedwidget.h"

FailedWidget::FailedWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FailedWidget)
{
    ui->setupUi(this);
}

FailedWidget::~FailedWidget()
{
    delete ui;
}

void FailedWidget::on_btnRestart_clicked()
{
    emit signalRestart();
}


void FailedWidget::on_btnBackToMenu_clicked()
{
    emit signalBack();
}

