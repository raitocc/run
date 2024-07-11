#include "double_players_game_rules_dialog.h"
#include "ui_double_players_game_rules_dialog.h"

Double_players_game_rules_Dialog::Double_players_game_rules_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Double_players_game_rules_Dialog)
{
    ui->setupUi(this);
}

Double_players_game_rules_Dialog::~Double_players_game_rules_Dialog()
{
    delete ui;
}

void Double_players_game_rules_Dialog::on_pushButton_clicked()
{
    this->close();
}

