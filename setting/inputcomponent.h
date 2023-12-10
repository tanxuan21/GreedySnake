#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <QWidget>

namespace Ui {
class InputComponent;
}

class InputComponent : public QWidget
{
    Q_OBJECT

public:
    explicit InputComponent(QWidget *parent = nullptr);
    ~InputComponent();
    int getValue();
    void setText(QString);
    void setMax(int);
    void setMin(int);
    void MysetValue(int);
private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::InputComponent *ui;
    int maxValue = 100;
    int minValue = 0;

    QString text = "属性说明";
    int value;
};

#endif // INPUTCOMPONENT_H
