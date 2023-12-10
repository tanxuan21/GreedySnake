#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include "../dataHandler/userdata.h"
namespace Ui {
class registerWidget;
}

class registerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit registerWidget(QWidget *parent = nullptr);
    ~registerWidget();

private slots:
    void on_register_back_Button_clicked();

    void on_register_confirm_Button_clicked();

private:
    Ui::registerWidget *ui;
signals:
    void backToLogin();
    void registed_and_Login(userData*);
};

#endif // REGISTERWIDGET_H
