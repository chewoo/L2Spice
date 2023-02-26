#ifndef VOLTAGE_CONTROL_CURRENT_SOURCE_DIALOG_H
#define VOLTAGE_CONTROL_CURRENT_SOURCE_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include "node.h"

namespace Ui {
class Voltage_control_current_source_dialog;
}

class Voltage_control_current_source_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Voltage_control_current_source_dialog(QWidget *parent = nullptr);
    void getInput(double &,QString &,QString &);
    ~Voltage_control_current_source_dialog();

private:
    Ui::Voltage_control_current_source_dialog *ui;
    QString coefficient;
    QString node1name;
    QString node2name;
private slots:
    void buttonOK();
    void buttonCancel();
};

#endif // VOLTAGE_CONTROL_CURRENT_SOURCE_DIALOG_H
