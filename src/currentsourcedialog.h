#ifndef CURRENTSOURCEDIALOG_H
#define CURRENTSOURCEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>

struct currentDCdata
{
    double current;
};

struct currentSinedata
{
    double amplitude;
    double offset;
    double phase;
};

struct currentSquaredata
{
    double Ion;
    double Ioff;
    double Tperiod;
    double Ton;
};

union currentSourcedata
{
    currentDCdata dcData;
    currentSinedata sineData;
    currentSquaredata squareData;
};

namespace Ui {
class Currentsourcedialog;
}

class Currentsourcedialog : public QDialog
{
    Q_OBJECT

public:
    explicit Currentsourcedialog(QWidget *parent = nullptr);
//    void getInput(double &,double &,double &,double &,int &);
    void getInput(currentSourcedata &,double &frequency,int &mode);
    ~Currentsourcedialog();

private:
    Ui::Currentsourcedialog *ui;

    enum mode{DC,Sine,Square};
    int currentMode;

    //Mode DC UI
    QLineEdit *curline;
    QLabel *curtext;

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
    QLineEdit *Ionline;
    QLineEdit *Ioffline;
    QLineEdit *Tperline;
    QLineEdit *Tonline;
    QLabel *Iontext;
    QLabel *Iofftext;
    QLabel *Tpertext;
    QLabel *Tontext;

    //Mode DC parameter
    QString current;

    //Mode Sine parameters
    QString offset;
    QString amplitude;
    QString frequency;
    QString phase;

    //Mode Square parameters
    QString Ion;
    QString Ioff;
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

#endif // CURRENTSOURCEDIALOG_H
