#include "calcwidget.h"
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

CalcWidget::CalcWidget(QWidget *parent)
    : QWidget(parent)
{
    setupLayout();
}

void CalcWidget::setupLayout()
{
    QVBoxLayout *lMain = new QVBoxLayout;
    QHBoxLayout *lTop = new QHBoxLayout;

    QVBoxLayout *lOperands = new QVBoxLayout;

    lblOperands = new QLabel(tr("operands: "));

    lblLeftOperand = new QLabel(tr("&left operand: "));
    editLeftOperand = new QLineEdit;
    lblLeftOperand->setBuddy(editLeftOperand); // ?

    lblRightOperand = new QLabel(tr("&right operand: "));
    editRightOperand = new QLineEdit;
    lblRightOperand->setBuddy(editRightOperand); // ?

    lOperands->addWidget(lblOperands);
    lOperands->addWidget(lblLeftOperand);
    lOperands->addWidget(editLeftOperand);
    lOperands->addWidget(lblRightOperand);
    lOperands->addWidget(editRightOperand);

    lOperands->addStretch();

    QVBoxLayout *lOperators = new QVBoxLayout;

    lblOperators = new QLabel(tr("operator: "));

    radioAddition = new QRadioButton(tr("&+"));
    radioSubstraction = new QRadioButton(tr("&-"));
    radioMultiplication = new QRadioButton(tr("&*"));
    radioDivision = new QRadioButton(tr("&/"));

    lOperators->addWidget(lblOperators);
    lOperators->addWidget(radioAddition);
    lOperators->addWidget(radioSubstraction);
    lOperators->addWidget(radioMultiplication);
    lOperators->addWidget(radioDivision);

    radioAddition->setChecked(true);

    lOperators->addStretch();

    QHBoxLayout *lButtons = new QHBoxLayout;

    btnCalculate = new QPushButton(tr("&calculate"));
    btnQuit = new QPushButton(tr("&quite"));

    lButtons->addWidget(btnCalculate);
    lButtons->addStretch();
    lButtons->addWidget(btnQuit);

    lTop->addLayout(lOperands);
    lTop->addLayout(lOperators);

    lMain->addLayout(lTop);
    lMain->addLayout(lButtons);

    setLayout(lMain);
    setWindowTitle(tr("simple calculator"));
    connect(btnQuit, SIGNAL(clicked()), this, SLOT(close()));
    connect(btnCalculate, SIGNAL(clicked()), this, SLOT(calculate()));
}

CalcWidget::~CalcWidget()
{
}

double CalcWidget::convertInput(const QString &s, bool *ok)
{
    double x = s.toDouble(ok);
    if (!ok)
    {
        QMessageBox::critical(this, tr("wrong input"), tr("operands must be a number"));
    }
    return x;
}

void CalcWidget::calculate()
{
    double x, y, result;
    bool ok;

    x = convertInput(editLeftOperand->text(), &ok);
    if (!ok) return;
    y = convertInput(editRightOperand->text(), &ok);
    if (!ok) return;

    if (radioAddition->isChecked())
    {
        result = x + y;
    }
    else if (radioSubstraction->isChecked())
    {
        result = x - y;
    }
    else if (radioMultiplication->isChecked())
    {
        result = x * y;
    }
    else
    {
        if (y == 0)
        {
            QMessageBox::warning(this, tr("invalid arguments"), tr("division by zero"));
        }
        result = x / y;
    }

    QMessageBox::information(this, tr("result"), tr("the result is %1").arg(result));
}
