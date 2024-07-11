#ifndef DOUBLE_PLAYERS_GAME_RULES_DIALOG_H
#define DOUBLE_PLAYERS_GAME_RULES_DIALOG_H

#include <QDialog>

namespace Ui {
class Double_players_game_rules_Dialog;
}

class Double_players_game_rules_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Double_players_game_rules_Dialog(QWidget *parent = nullptr);
    ~Double_players_game_rules_Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Double_players_game_rules_Dialog *ui;
};

#endif // DOUBLE_PLAYERS_GAME_RULES_DIALOG_H
