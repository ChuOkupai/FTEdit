#pragma once
#include "WidgetLinker.hh"
#include "Result.hh"


class PrintResultat : public QDialog
{
    Q_OBJECT

public:
    PrintResultat(QWidget *parent, ResultMCS *resultMCS, ResultBoolean *resultBoolean);
private:
    ResultMCS *resultMCS;
    ResultBoolean *resultBoolean;
private slots:
    void PrintResultMCS();
    void PrintResultBoolean();
};
