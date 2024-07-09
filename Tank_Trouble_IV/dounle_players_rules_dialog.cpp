#include "dounle_players_rules_dialog.h"
#include "ui_dounle_players_rules_dialog.h"

Dounle_players_rules_Dialog::Dounle_players_rules_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dounle_players_rules_Dialog)
{
    ui->setupUi(this);
}

Dounle_players_rules_Dialog::~Dounle_players_rules_Dialog()
{
    delete ui;
}

void Dounle_players_rules_Dialog::on_pushButton_clicked()
{
    this->close();
}

