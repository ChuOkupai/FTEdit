#pragma once
#include <QtWidgets>
#include "FTEdit_Editor.hh"
#include "Distribution.hh"

class EditDistributionDialog : public QDialog
{
    Q_OBJECT
private:
    Distribution *dist;
public:
    explicit EditDistributionDialog(QWidget *parent = nullptr, Distribution *dist = 0);

signals:

};


