#ifndef LINENODEITEMDIALOG_H
#define LINENODEITEMDIALOG_H

#include <QDialog>

namespace Ui {
class Linenodeitemdialog;
}

class Linenodeitemdialog : public QDialog
{
    Q_OBJECT

public:
    explicit Linenodeitemdialog(QWidget *parent = nullptr);
    double getInput();
    ~Linenodeitemdialog();

private slots:
    void on_OK_clicked();
    void on_Cancel_clicked();

private:
    Ui::Linenodeitemdialog *ui;
    QString voltage;
};

#endif // LINENODEITEMDIALOG_H
