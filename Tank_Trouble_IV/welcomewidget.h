﻿#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include "single_player_game_rules_dialog.h"
#include "double_players_game_rules_dialog.h"

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = nullptr);
    ~WelcomeWidget();
    void paintEvent(QPaintEvent * event);

private slots:

    void on_btnBack_clicked();

    void on_btnSingle_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void signalBackLogin();

    void signalSingleStart();

private:
    Ui::WelcomeWidget *ui;
};

#endif // WELCOMEWIDGET_H
