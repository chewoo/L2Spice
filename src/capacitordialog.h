#ifndef CAPACITORDIALOG_H
#define CAPACITORDIALOG_H

#include <QDialog>

namespace Ui {
class Capacitordialog;
}

class Capacitordialog : public QDialog
{
    Q_OBJECT

public:
    explicit Capacitordialog(QWidget *parent = nullptr);
    QString getInput();
    ~Capacitordialog();

private:
    Ui::Capacitordialog *ui;
    QString text;

private slots:
    void buttonOK();
    void buttonCancel();
};

#endif // CAPACITORDIALOG_H
