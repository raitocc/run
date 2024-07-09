#ifndef DOUNLE_PLAYERS_RULES_DIALOG_H
#define DOUNLE_PLAYERS_RULES_DIALOG_H

#include <QDialog>

namespace Ui {
class Dounle_players_rules_Dialog;
}

class Dounle_players_rules_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dounle_players_rules_Dialog(QWidget *parent = nullptr);
    ~Dounle_players_rules_Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dounle_players_rules_Dialog *ui;
};

#endif // DOUNLE_PLAYERS_RULES_DIALOG_H
