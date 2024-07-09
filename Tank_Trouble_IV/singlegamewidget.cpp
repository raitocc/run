#include "singlegamewidget.h"
#include "ui_singlegamewidget.h"


//调用newGame函数，传入关卡数作为参数进行初始化工作
SingleGameWidget::SingleGameWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleGameWidget)
{
    ui->setupUi(this);
    newGame();
}

SingleGameWidget::~SingleGameWidget()
{
    delete ui;
}

void SingleGameWidget::newGame()
{
    data = new GameData;
}

void SingleGameWidget::on_btnPause_clicked()
{
    emit signalPause();
}

