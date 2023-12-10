#include "inputcomponent.h"
#include "ui_inputcomponent.h"

InputComponent::InputComponent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputComponent)
{
    ui->setupUi(this);
}

InputComponent::~InputComponent()
{
    delete ui;
}

int InputComponent::getValue()
{
    return this->value;
}

void InputComponent::setText(QString s)
{
    this->text = s;
    ui->label->setText(this->text);
}

void InputComponent::setMax(int v)
{
    this->maxValue = v;
    ui->spinBox->setMaximum(this->maxValue);
    ui->horizontalSlider->setMaximum(this->maxValue);
}

void InputComponent::setMin(int v)
{
    this->minValue  = v;
    ui->spinBox->setMinimum(this->minValue);
    ui->horizontalSlider->setMinimum(this->minValue);
}

void InputComponent::MysetValue(int v)
{
    ui->horizontalSlider->setValue(v);
    ui->spinBox->setValue(v);
    this->value = v;
}

void InputComponent::on_horizontalSlider_valueChanged(int value)
{
    MysetValue(value);
}


void InputComponent::on_spinBox_valueChanged(int arg1)
{
    MysetValue(arg1);
}

