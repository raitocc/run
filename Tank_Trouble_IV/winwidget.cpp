#include "winwidget.h"
#include "ui_winwidget.h"

WinWidget::WinWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WinWidget)
{
    ui->setupUi(this);
}

WinWidget::~WinWidget()
{
    delete ui;
}
