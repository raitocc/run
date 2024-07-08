﻿#ifndef SINGLE_PLAYER_RULES_DIALOG_H
#define SINGLE_PLAYER_RULES_DIALOG_H

#include <QDialog>
#include"welcomewidget.h"

namespace Ui {
class Single_player_rules_Dialog;
}

class Single_player_rules_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Single_player_rules_Dialog(QWidget *parent = nullptr);
    ~Single_player_rules_Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Single_player_rules_Dialog *ui;
};

#endif // SINGLE_PLAYER_RULES_DIALOG_H
