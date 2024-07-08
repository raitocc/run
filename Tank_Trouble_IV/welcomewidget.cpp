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

void WelcomeWidget::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setOpacity(0.5);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/welcome_background.png"));
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
    configWindow->setWindowModality(Qt::ApplicationModal);
    configWindow->show();

}

