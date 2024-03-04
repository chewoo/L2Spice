#ifndef CURRENT_CONTROL_CURRENT_SOURCE_DIALOG_H
#define CURRENT_CONTROL_CURRENT_SOURCE_DIALOG_H

#include <QDialog>
#include <node.h>

namespace Ui {
class Current_control_current_source_dialog;
}

class Current_control_current_source_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Current_control_current_source_dialog(QWidget *parent = nullptr);
    void getInput(double &,QString &);
    ~Current_control_current_source_dialog();

private:
    Ui::Current_control_current_source_dialog *ui;
    QString coefficient;
    QString branchName;

private slots:
    void buttonOK();
    void buttonCancel();
};

#endif // CURRENT_CONTROL_CURRENT_SOURCE_DIALOG_H
