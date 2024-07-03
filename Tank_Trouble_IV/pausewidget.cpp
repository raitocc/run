#include "pausewidget.h"
#include "ui_pausewidget.h"

PauseWidget::PauseWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PauseWidget)
{
    ui->setupUi(this);
}

PauseWidget::~PauseWidget()
{
    delete ui;
}

void PauseWidget::on_btnBack_clicked()
{
    emit signalBackToGame();
}


void PauseWidget::on_btnExit_clicked()
{
    //再次询问确认退出
    if(QMessageBox::Yes == QMessageBox::question(0, tr("Exit"),QString(tr("Back To Menu?")),QMessageBox::Yes | QMessageBox::No))
    {
        emit signalExitToMenu();
    }
}

