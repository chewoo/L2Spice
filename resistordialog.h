#ifndef RESISTORDIALOG_H
#define RESISTORDIALOG_H

#include <QDialog>

namespace Ui {
class Resistordialog;
}

class Resistordialog : public QDialog
{
    Q_OBJECT

public:
    explicit Resistordialog(QWidget *parent = nullptr);
    QString getInput();
    ~Resistordialog();

private:
    Ui::Resistordialog *ui;
    QString text;

private slots:
    void buttonOK();
    void buttonCancel();
};

#endif // RESISTORDIALOG_H
