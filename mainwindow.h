#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "workspace.h"
#include "othercomponentsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QVector<QPixmap *> menuImage;
    QVector<QIcon *> menuButtonIcon;
    Othercomponentsdialog *othercomponentsdialog;

private slots:
    void pushResistor();
    void pushCapacitor();
    void pushInductor();
    void pushMove();
    void pushDelete();
    void pushWire();
    void pushVoltageSource();
    void pushComponents();
    void pushCurrentSource();
    void pushDiode();
    void pushGround();
    void pushRun();
    void on_action_peter_dragon_dick_triggered();
};
#endif // MAINWINDOW_H
