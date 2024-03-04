#ifndef OTHERCOMPONENTSDIALOG_H
#define OTHERCOMPONENTSDIALOG_H

#include <QDialog>

namespace Ui {
class Othercomponentsdialog;
}

class Othercomponentsdialog : public QDialog
{
    Q_OBJECT

public:
    explicit Othercomponentsdialog(QWidget *parent = nullptr);
    int getMode();
    ~Othercomponentsdialog();

private:
    Ui::Othercomponentsdialog *ui;
    enum mode{currentSource,CurrentcontrolCurrentSource,CurrentcontrolVoltageSource,VoltagecontrolCurrentSource,VoltagecontrolVoltageSource};
    int currentmode;
    bool flagOK;
    QImage *image;
    QVector<QPixmap *> menuImage;
    QVector<QIcon *> menuButtonIcon;

private slots:
    void buttonOK();
    void buttonCancel();
    void buttonCurrentSource();
    void buttonCurrentControlCurrentSource();
    void buttonCurrentControlVoltageSource();
    void buttonVoltageControlCurrentSource();
    void buttonVoltageControlVoltageSource();
};

#endif // OTHERCOMPONENTSDIALOG_H
