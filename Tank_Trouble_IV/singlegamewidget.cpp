#include "singlegamewidget.h"
#include "ui_singlegamewidget.h"

SingleGameWidget::SingleGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleGameWidget)
{
    ui->setupUi(this);
}

SingleGameWidget::~SingleGameWidget()
{
    delete ui;
}
