#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QWidget>

class QPushButton;
class QLabel;
class QLineEdit;
class QRadioButton;

class CalcWidget : public QWidget
{
    Q_OBJECT

    QLabel *lblOperands;
    QLabel *lblLeftOperand;
    QLabel *lblRightOperand;
    QLineEdit *editLeftOperand;
    QLineEdit *editRightOperand;

    QLabel *lblOperators;
    QRadioButton *radioAddition;
    QRadioButton *radioSubstraction;
    QRadioButton *radioMultiplication;
    QRadioButton *radioDivision;

    QPushButton *btnCalculate;
    QPushButton *btnQuit;

    void setupLayout();

    double convertInput(const QString &s, bool *ok);

public:
    CalcWidget(QWidget *parent = nullptr);
    ~CalcWidget();
public slots:
    void calculate();
};
#endif // CALCWIDGET_H
