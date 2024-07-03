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
