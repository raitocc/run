#ifndef PAUSEWIDGET_H
#define PAUSEWIDGET_H

#include <QWidget>

namespace Ui {
class PauseWidget;
}

class PauseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PauseWidget(QWidget *parent = nullptr);
    ~PauseWidget();

private:
    Ui::PauseWidget *ui;
};

#endif // PAUSEWIDGET_H
