#ifndef INDUCTORDIALOG_H
#define INDUCTORDIALOG_H

#include <QDialog>

namespace Ui {
class Inductordialog;
}

class Inductordialog : public QDialog
{
    Q_OBJECT

public:
    explicit Inductordialog(QWidget *parent = nullptr);
    QString getInput();
    ~Inductordialog();

private:
    Ui::Inductordialog *ui;
    QString text;

private slots:
    void buttonOK();
    void buttonCancel();
};

#endif // INDUCTORDIALOG_H
