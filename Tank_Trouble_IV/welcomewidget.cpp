#include "welcomewidget.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}

void WelcomeWidget::on_btnBack_clicked()
{
    emit signalBackLogin();
}


void WelcomeWidget::on_btnSingle_clicked()
{
    emit signalSingleStart();
}


void WelcomeWidget::on_pushButton_clicked()
{
    Single_player_rules_Dialog *configWindow = new Single_player_rules_Dialog;
    configWindow->show();
}

