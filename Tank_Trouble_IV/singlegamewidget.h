#ifndef SINGLEGAMEWIDGET_H
#define SINGLEGAMEWIDGET_H

#include <QWidget>

namespace Ui {
class SingleGameWidget;
}

class SingleGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleGameWidget(QWidget *parent = nullptr);
    ~SingleGameWidget();

private slots:
    void on_btnPause_clicked();

private:
    Ui::SingleGameWidget *ui;

signals:
    void signalPause();
};

#endif // SINGLEGAMEWIDGET_H
