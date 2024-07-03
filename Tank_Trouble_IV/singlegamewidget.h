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

private:
    Ui::SingleGameWidget *ui;
};

#endif // SINGLEGAMEWIDGET_H
