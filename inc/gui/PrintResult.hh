#pragma once
#include "WidgetLinker.hh"
#include "Result.hh"


class PrintResult : public QDialog
{
    Q_OBJECT

public:
    PrintResult(QWidget *parent, ResultMCS *resultMCS, ResultBoolean *resultBoolean);
    PrintResult(QWidget *parent, Result *result);
private:
    Result *result;
    ResultMCS *resultMCS;
    ResultBoolean *resultBoolean;
private slots:
    void PrintResultMCS();
    void PrintResultBoolean();
};
