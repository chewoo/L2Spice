#ifndef DIADO_DIALOG_H
#define DIADO_DIALOG_H

#include <QDialog>

namespace Ui {
class Diado_dialog;
}

class Diado_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Diado_dialog(QWidget *parent = nullptr);
    QString getInput();
    ~Diado_dialog();

private:
    Ui::Diado_dialog *ui;
    QString text;

private slots:
    void buttonOK();
    void buttonCancel();
};

#endif // DIADO_DIALOG_H
