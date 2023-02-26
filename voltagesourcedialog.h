#ifndef VOLTAGESOURCEDIALOG_H
#define VOLTAGESOURCEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>


struct voltageDCdata
{
    double voltage;
};

struct voltageSinedata
{
    double amplitude;
    double offset;
    double phase;
};

struct voltageSquaredata
{
    double Von;
    double Voff;
    double Tperiod;
    double Ton;

};

union voltageSourcedata
{
    voltageDCdata dcData;
    voltageSinedata sineData;
    voltageSquaredata squareData;
};

namespace Ui {
class Voltagesourcedialog;
}

class Voltagesourcedialog : public QDialog
{
    Q_OBJECT

public:
    explicit Voltagesourcedialog(QWidget *parent = nullptr);
    void getInput(voltageSourcedata &,double &frequency,int &mode);
    ~Voltagesourcedialog();

private:
    Ui::Voltagesourcedialog *ui;

    enum mode{DC,Sine,Square};
    int currentMode;

    //Mode DC UI
    QLineEdit *volline;
    QLabel *voltext;

    //Mode Sine UI
    QLineEdit *offline;
    QLineEdit *ampline;
    QLineEdit *freline;
    QLineEdit *phaline;
    QLabel *offtext;
    QLabel *amptext;
    QLabel *fretext;
    QLabel *phatext;


    //Mode Square UI
    QLineEdit *Vonline;
    QLineEdit *Voffline;
    QLineEdit *Tperline;
    QLineEdit *Tonline;
    QLabel *Vontext;
    QLabel *Vofftext;
    QLabel *Tpertext;
    QLabel *Tontext;

    //Mode DC parameter
    QString voltage;

    //Mode Sine parameters
    QString offset;
    QString amplitude;
    QString frequency;
    QString phase;

    //Mode Square parameters
    QString Von;
    QString Voff;
    QString Tperiod;
    QString Ton;


private slots:
    void buttonOK();
    void buttonCancel();
    void selectMode(int);
    void showDC();
    void showSine();
    void showSquare();
    void hideDC();
    void hideSine();
    void hideSquare();
    void deleteDC();
    void deleteSine();
    void deleteSquare();
};

#endif // VOLTAGESOURCEDIALOG_H
