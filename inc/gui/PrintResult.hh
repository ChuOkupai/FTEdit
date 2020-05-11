#pragma once
#include "WidgetLinker.hh"
#include "Result.hh"


class PrintResult : public QDialog
{
    Q_OBJECT

public:
    PrintResult(QWidget *parent, ResultMCS *resultMCS, ResultBoolean *resultBoolean,  QList<QString> errors);
    PrintResult(QWidget *parent, Result *result);
    void cellChanged(int y, int x);
private:
    Result *result;
    ResultMCS *resultMCS;
    ResultBoolean *resultBoolean;
    QList<QString> errors;
private slots:
    void PrintResultMCS();
    void PrintResultBoolean();
    void PrintResultErrors();
};
