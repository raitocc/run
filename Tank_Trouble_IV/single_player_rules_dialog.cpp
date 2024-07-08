#include "single_player_rules_dialog.h"
#include "ui_single_player_rules_dialog.h"

Single_player_rules_Dialog::Single_player_rules_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Single_player_rules_Dialog)
{
    ui->setupUi(this);
}

Single_player_rules_Dialog::~Single_player_rules_Dialog()
{
    delete ui;
}

void Single_player_rules_Dialog::on_pushButton_clicked()
{
    this->close();
}



