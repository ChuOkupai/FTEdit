#include "EditDistributionDialog.hh"

EditDistributionDialog::EditDistributionDialog(QWidget *parent, Distribution *dist)
    : QDialog(parent), dist(dist)
{
    setWindowTitle("Edit Distribution");
    setFixedSize(260,300);
    QLabel *prop = new QLabel("Model Properties :", this);
    prop->move(10,10);

    QLabel *modelName = new QLabel("Name : " ,this);
    modelName->move(10,30);
    QLineEdit *name = new QLineEdit("", this);
    name->move(60,30);

    QLabel *law = new QLabel("Law : ", this);
    law->move(10,60);
    QComboBox *combo = new QComboBox(this);
    combo->move(60,60);
    QList<QString> list = {"Constant","Exponential","Weibull"};

    combo->addItems(list);

    connect(combo,SIGNAL(currentTextChanged(const QString &text)),this,SLOT(setCurrentText(const QString &text)));

    QLabel *param = new QLabel("Model Parameters :", this);
    param->move(10,100);

    if(combo->currentText() == "Constant")
    {
        this->update();
        QLabel *nvalue = new QLabel("Value : " ,this);
        nvalue->move(10,130);
        QLineEdit *value = new QLineEdit("", this);
        value->move(60,130);
        this->show();
        this->exec();

    }else if(combo->currentText() == "Exponential"){
        this->update();
        QLabel *nvalue = new QLabel("Value : " ,this);
        nvalue->move(10,130);
        QLineEdit *value = new QLineEdit("", this);
        value->move(60,130);

        QLabel *nlambda = new QLabel("Lambda : " ,this);
        nlambda->move(10,160);
        QLineEdit *lambda = new QLineEdit("", this);
        lambda->move(60,160);
        this->show();
        this->exec();

    }else{
        this->update();
        QLabel *nvalue = new QLabel("Value : " ,this);
        nvalue->move(10,130);
        QLineEdit *value = new QLineEdit("", this);
        value->move(60,130);

        QLabel *nScale = new QLabel("Scale : " ,this);
        nScale->move(10,160);
        QLineEdit *scale = new QLineEdit("", this);
        scale->move(60,160);

        QLabel *nShape = new QLabel("Shape : " ,this);
        nShape->move(10,190);
        QLineEdit *shape = new QLineEdit("", this);
        shape->move(60,190);
        this->show();
        this->exec();
    }

    ///this->update();
    //this->show();
}
