#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QValueAxis>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVector>
#include <circuit.h>
#include <algorithm>
#include <QPair>
#include <QList>
#include <QColor>
#include <QRandomGenerator>
#include <QLegendMarker>
namespace Ui {
class Oscilloscope;
}

class Oscilloscope : public QDialog
{
    Q_OBJECT

public:
    explicit Oscilloscope(Circuit* c,QWidget *parent = nullptr);
    void inputTime();
    double getTime();
    void add_series(int node);
    void custom_add_series(int mode);
    void only_series(int node);
    ~Oscilloscope();

private:
    Ui::Oscilloscope *ui;
    QChart *chart;
    QChartView *chartview;
    QVector<QLineSeries*> all_series;
    QVector<QPair<double,double>> all_yboundary;//pair(min,max)
    QVector< QPair<Matrix,double> > solutions;

    QValueAxis *xAxis;
    QValueAxis *yAxis;

    QLabel *timetext;
    QLineEdit *timeline;
    QLabel *maxtimesteptext;
    QLineEdit *maxtimestepline;
    QPushButton *buttonOK;
    QPushButton *buttonCancel;
    QPushButton *buttonFullZoom;
    QGridLayout* mainlayout;
    Circuit* circuit;
    QRandomGenerator random;
    double time;
    double maxtimestep;

    void calculate();
    void customplot_calculate();
    QVector<double> nowGraphingx;
    QVector<double> nowGraphingy;
    QVector<QVector<double>> nodesValue;
    double y_upperBound;
    double y_lowerBound;
    enum measurementType{Max,Min,Peaktopeak};

private slots:
    void pushButtonOK();
    void pushButtonCancel();
    void pushButtonFullZoom();
    void changeObject(int );
    void changeMeasure(int );
    void showInput();
    void hideInput();
    void showOscilloscope();
    void hideOscilloscope();
    void clearChartViewBeforeCalculate();
    void clearCustomPlotBeforeCalculate();
//    void testcustomplot();
};

#endif // OSCILLOSCOPE_H
