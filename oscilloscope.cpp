#include "oscilloscope.h"
#include "ui_oscilloscope.h"
#include "unit_transformer.h"

Oscilloscope::Oscilloscope(Circuit* c,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Oscilloscope)
{
    ui->setupUi(this);

    circuit = c;
    chart =  new QChart();
    chartview = new QChartView(this);
    mainlayout = new QGridLayout();
    mainlayout->addWidget(chartview);
    setLayout(mainlayout);

    chart->setAnimationOptions(QChart::AllAnimations);
    chartview->setRubberBand(QChartView::RectangleRubberBand);

    xAxis = new QValueAxis();
    yAxis = new QValueAxis();

    xAxis->setMax(1000);
    xAxis->setMin(0);
    yAxis->setMax(15);
    yAxis->setMin(-15);
    chart->addAxis(xAxis,Qt::AlignBottom);
    chart->addAxis(yAxis,Qt::AlignLeft);

    chart->legend()->setAlignment(Qt::AlignTop);
    chart->legend()->show();  //<- show series name/color
    QFont font;
    font.setFamily("Times");
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(Qt::black);
    chart->setTitle("Tsai mother AOOP");


    chartview->setChart(chart);
    chartview->setGeometry(0,0,800,600);
    chartview->hide();
    y_upperBound = y_lowerBound = 0;

    timetext = new QLabel(this);
    timeline = new QLineEdit(this);
    timetext->setText("Time stop: ");
    timetext->setGeometry(200,200,130,25);
    timeline->setGeometry(350,200,130,25);

    maxtimesteptext = new QLabel(this);
    maxtimestepline = new QLineEdit(this);
    maxtimesteptext->setText("Max timestep: ");
    maxtimesteptext->setGeometry(200,240,130,25);
    maxtimestepline->setGeometry(350,240,130,25);

    warning = new QLabel(this);
    warning->setText("Time must be inputed a non-zero value");
    warning->setGeometry(200,300,200,25);
    warning->hide();

    buttonOK = new QPushButton(this);
    buttonCancel = new QPushButton(this);
    buttonOK->setText("OK");
    buttonCancel->setText("Cancel");
    buttonOK->setGeometry(400,400,93,29);
    buttonCancel->setGeometry(500,400,93,29);
    buttonFullZoom = new QPushButton(this);
    buttonFullZoom->setText("Full Zoom");
    buttonFullZoom->setGeometry(30,560,93,29);

    QObject::connect(buttonOK,SIGNAL(clicked()),this,SLOT(pushButtonOK()));
    QObject::connect(buttonCancel,SIGNAL(clicked()),this,SLOT(pushButtonCancel()));
    QObject::connect(buttonFullZoom,SIGNAL(clicked()),this,SLOT(pushButtonFullZoom()));


//    ui->objectComboBox->hide();
//    ui->MeasureComboBox->hide();
    ui->measureComboBox->addItem("max value");
    ui->measureComboBox->addItem("min value");
    ui->measureComboBox->addItem("Peak-to-peak");

    QObject::connect(ui->objectComboBox,SIGNAL(activated(int)),this,SLOT(changeObject(int)));
    QObject::connect(ui->measureComboBox,SIGNAL(activated(int)),this,SLOT(changeMeasure(int)));



    ui->widget->setInteraction(QCP::iRangeDrag,true);
    ui->widget->setInteraction(QCP::iRangeZoom,true);

    ui->widget->legend->setFont(QFont());
    buttonFullZoom->hide();
    ui->widget->hide();
}

Oscilloscope::~Oscilloscope()
{
    delete ui;
    delete chart;
    delete chartview;
    for(int i=0;i<all_series.size();i++)
        delete all_series[i];
    qDeleteAll(all_series);
    all_series.clear();
    delete xAxis;
    delete yAxis;
    delete timetext;
    delete timeline;
    delete maxtimesteptext;
    delete maxtimestepline;
    delete buttonOK;
    delete buttonCancel;
    delete buttonFullZoom;
//    delete mainlayout;
}
void Oscilloscope::calculate()
{
    clearChartViewBeforeCalculate();

    circuit->analysis_circuit_connection();
    circuit->sort_the_allcomponent();
//    circuit->analysis(time);
    if(maxtimestep!=0)
        circuit->analysis(time,maxtimestep);
    else
        circuit->analysis(time);
    solutions = circuit->get_solutions();
    //solutions = circuit->analysis_circuit_timeinterval(time);
    if(circuit->get_circuit_state()!=0){
        qDebug()<<"William ojj";
        return;
    }
    int num_of_data = solutions[0].first.get_row_num();
    for(int i=0;i<num_of_data;i++){
        all_series.push_back(new QLineSeries);
        chart->addSeries(all_series[i]);
        all_series[i]->setColor(QColor(random.bounded(1,255),random.bounded(1,255),random.bounded(1,255)));
        all_series[i]->setName(QString::number(i));
        all_series[i]->attachAxis(xAxis);
        all_series[i]->attachAxis(yAxis);
        all_series[i]->setMarkerSize(5);
        all_yboundary.push_back(qMakePair(INT_MAX,INT_MIN));
    }
    for(int i=1;i<solutions.size();i++){
        for(int j=0;j<solutions[0].first.get_row_num();j++){
            all_yboundary[j].first = std::min(all_yboundary[j].first,solutions[i].first(j,0));
            all_yboundary[j].second = std::max(all_yboundary[j].second,solutions[i].first(j,0));
        }
    }
    for(int i=0;i<all_series.size();i++)
    {
        all_series[i]->setName("");
        chart->legend()->markers()[i]->setVisible(false);
    }
}

void Oscilloscope::add_series(int node)
{
    if(node == -1)
        return;

    QList<QPointF> points;
    QList<QPointF> testpoints;
    double timeUnit=0;
    for(int i=1;i<solutions.size();i++,timeUnit += time/10000){
        points.push_back(QPointF(solutions[i].second,solutions[i].first(node,0)));
    }

    all_series[node]->clear();
    all_series[node]->setName("Node" + QString::number(node+1));
    all_series[node]->replace(points);
    chart->legend()->markers()[node]->setVisible(true);

    //setup axis range
    y_upperBound = std::max(y_upperBound,all_yboundary[node].second);
    y_lowerBound = std::min(y_lowerBound,all_yboundary[node].first);

    yAxis->setMax(y_upperBound);
    if(y_upperBound!=y_lowerBound)
        yAxis->setMin(y_lowerBound);
    else
        yAxis->setMin(y_lowerBound-10);
    xAxis->setMax(time);
    xAxis->setMin(0);
    chartview->repaint();
}

void Oscilloscope::customplot_calculate()
{
    clearCustomPlotBeforeCalculate();

    circuit->analysis_circuit_connection();
    circuit->sort_the_allcomponent();
    if(maxtimestep!=0)
        circuit->analysis(time,maxtimestep);
    else
        circuit->analysis(time);
    solutions = circuit->get_solutions();
    if(circuit->get_circuit_state()!=0){
        qDebug()<<"William ojj";
        return;
    }
    int num_of_data = solutions[0].first.get_row_num();
    for(int i=0;i<num_of_data;i++){
        ui->widget->addGraph();
        QPen pen(QColor(random.bounded(1,255),random.bounded(1,255),random.bounded(1,255)));
        pen.setWidth(3);
        ui->widget->graph(i)->setPen(pen);
        all_yboundary.push_back(qMakePair(INT_MAX,INT_MIN));
    }
    for(int i=1;i<solutions.size();i++){
        for(int j=0;j<solutions[0].first.get_row_num();j++){
            all_yboundary[j].first = std::min(all_yboundary[j].first,solutions[i].first(j,0));
            all_yboundary[j].second = std::max(all_yboundary[j].second,solutions[i].first(j,0));
        }
    }
    for(int i=0;i<ui->widget->graphCount();i++)
    {
        ui->widget->graph(i)->setName("");
        ui->widget->graph(i)->removeFromLegend();
    }
    nodesValue.resize(ui->widget->graphCount());

    ui->widget->xAxis->setRange(0,10);
    ui->widget->yAxis->setRange(0,10);
}

void Oscilloscope::custom_add_series(int node)
{
    if(node == -1)
        return;
/*    QString temp = "Node" + QString::number(node+1);
    for(int i=0;i<ui->objectComboBox->count();i++)
        if(ui->objectComboBox[i].accessibleName() == temp)
            return;*/

    QVector<double> x,y;

    double timeUnit=0;
    for(int i=1;i<solutions.size();i++,timeUnit += time/10000){
    //    points.push_back(QPointF(solutions[i].second,solutions[i].first(node,0)));
        x.push_back(solutions[i].second);
        y.push_back(solutions[i].first(node,0));
        nowGraphingx.push_back(solutions[i].second);
        nowGraphingy.push_back(solutions[i].first(node,0));
    }
    nodesValue[node] = y;

    y_upperBound = std::max(y_upperBound,all_yboundary[node].second);
    y_lowerBound = std::min(y_lowerBound,all_yboundary[node].first);

    ui->widget->graph(node)->setData(x,y);
    ui->widget->graph(node)->setName("Node" + QString::number(node+1));
    ui->widget->graph(node)->addToLegend();
    ui->widget->legend->setVisible(true);

    ui->objectComboBox->addItem("Node" + QString::number(node+1));

    yAxis->setMax(y_upperBound);
    if(y_upperBound!=y_lowerBound)
        yAxis->setMin(y_lowerBound);
    else
        yAxis->setMin(y_lowerBound-10);

    ui->widget->xAxis->setRange(0,time);
    ui->widget->yAxis->setRange(yAxis->min(), yAxis->max());

    ui->widget->replot();

}
void Oscilloscope::only_series(int node)
{

}
void Oscilloscope::inputTime()
{
    hideOscilloscope();
    showInput();
}

double Oscilloscope::getTime()
{
    return time;
}

void Oscilloscope::pushButtonOK()
{
//    do
//   {
        if(timeline->text() != "" && timeline->text() != "0")
        {
            time = unit_transformer::transform(timeline->text());
            if(maxtimestepline->text() != "")
            //    maxtimestep = maxtimestepline->text().toDouble();
                maxtimestep = unit_transformer::transform(maxtimestepline->text());
            else
                maxtimestep = 0;
            xAxis->setMax(time);
            hideInput();
            showOscilloscope();
            calculate();
            customplot_calculate();
            y_upperBound = INT_MIN;
            y_lowerBound = INT_MAX;
            warning->hide();
 //         break;
        }
        else
        {
            warning->show();
//            break;
        }
//    }while();
}

void Oscilloscope::pushButtonCancel()
{
    timeline->setText(QString::number(time));
    maxtimestepline->setText(QString::number(maxtimestep));
    hideInput();
    hideOscilloscope();
    hideInput();
    warning->hide();
    this->hide();
}

void Oscilloscope::pushButtonFullZoom()
{
    ui->widget->xAxis->setRange(*std::min_element(nowGraphingx.begin(),nowGraphingx.end()),*std::max_element(nowGraphingx.begin(),nowGraphingx.end()));
    ui->widget->yAxis->setRange(*std::min_element(nowGraphingy.begin(),nowGraphingy.end()),*std::max_element(nowGraphingy.begin(),nowGraphingy.end()));
    ui->widget->replot();
}

void Oscilloscope::changeObject(int a)
{
    QString index = ui->objectComboBox->currentText()[ui->objectComboBox->currentText().size()-1];
    int currentObject = index.toInt() - 1;
    double max,min;
    if(nodesValue[currentObject].size() == 0)
        return;
    max = min = nodesValue[currentObject][0];
    switch(ui->measureComboBox->currentIndex())
    {
        case Max:
            for(int i=0;i<nodesValue[currentObject].size();i++)
                if(nodesValue[currentObject][i] > max)
                    max = nodesValue[currentObject][i];
            ui->text->setText("Node" + QString::number(currentObject+1) +  " max : ");
            ui->ans->setText(QString::number(max));
            break;
        case Min:
            for(int i=0;i<nodesValue[currentObject].size();i++)
                if(nodesValue[currentObject][i] < min)
                    min = nodesValue[currentObject][i];
            ui->text->setText("Node" + QString::number(currentObject+1) + " min : ");
            ui->ans->setText(QString::number(min));
            break;
        case Peaktopeak:
            for(int i=0;i<nodesValue[currentObject].size();i++)
            {
                if(nodesValue[currentObject][i] > max)
                    max = nodesValue[currentObject][i];
                if(nodesValue[currentObject][i] < min)
                    min = nodesValue[currentObject][i];
            }
            ui->text->setText("Node" + QString::number(currentObject+1) + " Peak-to-peak : ");
            ui->ans->setText(QString::number(max - min));
            break;
    }
}

void Oscilloscope::changeMeasure(int a)
{
    if(ui->objectComboBox->count() == 0)
        return;
    QString index = ui->objectComboBox->currentText()[ui->objectComboBox->currentText().size()-1];
    int currentObject = index.toInt() - 1;
    double max,min;
    if(nodesValue[currentObject].size() == 0)
        return;
    max = min = nodesValue[currentObject][0];
    switch(a)
    {
        case Max:
            for(int i=0;i<nodesValue[currentObject].size();i++)
                if(nodesValue[currentObject][i] > max)
                    max = nodesValue[currentObject][i];
            ui->text->setText("Node" + QString::number(currentObject+1) +  " max : ");
            ui->ans->setText(QString::number(max));
            break;
        case Min:
            for(int i=0;i<nodesValue[currentObject].size();i++)
                if(nodesValue[currentObject][i] < min)
                    min = nodesValue[currentObject][i];
            if(min < 1e-10)
                min = 0;
            ui->text->setText("Node" + QString::number(currentObject+1) + " min : ");
            ui->ans->setText(QString::number(min));
            break;
        case Peaktopeak:
            for(int i=0;i<nodesValue[currentObject].size();i++)
            {
                if(nodesValue[currentObject][i] > max)
                    max = nodesValue[currentObject][i];
                if(nodesValue[currentObject][i] < min)
                    min = nodesValue[currentObject][i];
            }
            ui->text->setText("Node" + QString::number(currentObject+1) + " Peak-to-peak : ");
            ui->ans->setText(QString::number(max - min));
            break;
    }
}

void Oscilloscope::showInput()
{
    this->resize(800,600);
    timetext->show();
    timeline->show();
    maxtimesteptext->show();
    maxtimestepline->show();
    buttonOK->show();
    buttonCancel->show();
}

void Oscilloscope::hideInput()
{
    timetext->hide();
    timeline->hide();
    maxtimesteptext->hide();
    maxtimestepline->hide();
    buttonOK->hide();
    buttonCancel->hide();
}

void Oscilloscope::showOscilloscope()
{
    //chartview->show();
    this->resize(1160,600);
    ui->widget->show();
    buttonFullZoom->show();
}

void Oscilloscope::hideOscilloscope()
{
    chartview->hide();
    ui->widget->hide();
    buttonFullZoom->hide();
}

void Oscilloscope::clearChartViewBeforeCalculate()
{
    chart->removeAllSeries();
    all_yboundary.clear();
    all_series.clear();
}

void Oscilloscope::clearCustomPlotBeforeCalculate()
{
    all_yboundary.clear();
    ui->widget->clearGraphs();
    ui->widget->replot();
    nowGraphingx.clear();
    nowGraphingy.clear();
    nodesValue.clear();
    ui->objectComboBox->clear();
    ui->text->clear();
    ui->ans->clear();
}

//This if for QCustomPlot testing
/*
void Oscilloscope::testcustomplot()
{

    ui->widget->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
    ui->widget->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    ui->widget->legend->setFont(legendFont);
    ui->widget->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    ui->widget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);

    // setup for graph 0: key axis left, value axis bottom
    // will contain left maxwell-like function
    ui->widget->addGraph(ui->widget->yAxis, ui->widget->xAxis);
    ui->widget->graph(0)->setPen(QPen(QColor(255, 100, 0)));
    ui->widget->graph(0)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // fill with texture of specified image
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    ui->widget->graph(0)->setName("Left maxwell function");

    // setup for graph 1: key axis bottom, value axis left (those are the default axes)
    // will contain bottom maxwell-like function with error bars
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::red));
    ui->widget->graph(1)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // same fill as we used for graph 0
    ui->widget->graph(1)->setLineStyle(QCPGraph::lsStepCenter);
    ui->widget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 7));
    ui->widget->graph(1)->setName("Bottom maxwell function");
    QCPErrorBars *errorBars = new QCPErrorBars(ui->widget->xAxis, ui->widget->yAxis);
    errorBars->removeFromLegend();
    errorBars->setDataPlottable(ui->widget->graph(1));

    // setup for graph 2: key axis top, value axis right
    // will contain high frequency sine with low frequency beating:
    ui->widget->addGraph(ui->widget->xAxis2, ui->widget->yAxis2);
    ui->widget->graph(2)->setPen(QPen(Qt::blue));
    ui->widget->graph(2)->setName("High frequency sine");

    // setup for graph 3: same axes as graph 2
    // will contain low frequency beating envelope of graph 2
    ui->widget->addGraph(ui->widget->xAxis2, ui->widget->yAxis2);
    QPen blueDotPen;
    blueDotPen.setColor(QColor(30, 40, 255, 150));
    blueDotPen.setStyle(Qt::DotLine);
    blueDotPen.setWidthF(4);
    ui->widget->graph(3)->setPen(blueDotPen);
    ui->widget->graph(3)->setName("Sine envelope");

    // setup for graph 4: key axis right, value axis top
    // will contain parabolically distributed data points with some random perturbance
    ui->widget->addGraph(ui->widget->yAxis2, ui->widget->xAxis2);
    ui->widget->graph(4)->setPen(QColor(50, 50, 50, 255));
    ui->widget->graph(4)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    ui->widget->graph(4)->setName("Some random data around\na quadratic function");

    // generate data, just playing with numbers, not much to learn here:
    QVector<double> x0(25), y0(25);
    QVector<double> x1(15), y1(15), y1err(15);
    QVector<double> x2(250), y2(250);
    QVector<double> x3(250), y3(250);
    QVector<double> x4(250), y4(250);
    for (int i=0; i<25; ++i) // data for graph 0
    {
      x0[i] = 3*i/25.0;
      y0[i] = qExp(-x0[i]*x0[i]*0.8)*(x0[i]*x0[i]+x0[i]);
    }
    for (int i=0; i<15; ++i) // data for graph 1
    {
      x1[i] = 3*i/15.0;;
      y1[i] = qExp(-x1[i]*x1[i])*(x1[i]*x1[i])*2.6;
      y1err[i] = y1[i]*0.25;
    }
    for (int i=0; i<250; ++i) // data for graphs 2, 3 and 4
    {
      x2[i] = i/250.0*3*M_PI;
      x3[i] = x2[i];
      x4[i] = i/250.0*100-50;
      y2[i] = qSin(x2[i]*12)*qCos(x2[i])*10;
      y3[i] = qCos(x3[i])*10;
      y4[i] = 0.01*x4[i]*x4[i] + 1.5*(rand()/(double)RAND_MAX-0.5) + 1.5*M_PI;
    }

    // pass data points to graphs:
    ui->widget->graph(0)->setData(x0, y0);
    ui->widget->graph(1)->setData(x1, y1);
    errorBars->setData(y1err);
    ui->widget->graph(2)->setData(x2, y2);
    ui->widget->graph(3)->setData(x3, y3);
    ui->widget->graph(4)->setData(x4, y4);
    // activate top and right axes, which are invisible by default:
    ui->widget->xAxis2->setVisible(true);
    ui->widget->yAxis2->setVisible(true);
    // set ranges appropriate to show data:
    ui->widget->xAxis->setRange(0, 2.7);
    ui->widget->yAxis->setRange(0, 2.6);
    ui->widget->xAxis2->setRange(0, 3.0*M_PI);
    ui->widget->yAxis2->setRange(-70, 35);
    // set pi ticks on top axis:
    ui->widget->xAxis2->setTicker(QSharedPointer<QCPAxisTickerPi>(new QCPAxisTickerPi));
    // add title layout element:
    ui->widget->plotLayout()->insertRow(0);
    ui->widget->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widget, "Way too many graphs in one plot", QFont("sans", 12, QFont::Bold)));
    // set labels:
    ui->widget->xAxis->setLabel("Bottom axis with outward ticks");
    ui->widget->yAxis->setLabel("Left axis label");
    ui->widget->xAxis2->setLabel("Top axis label");
    ui->widget->yAxis2->setLabel("Right axis label");
    // make ticks on bottom axis go outward:
    ui->widget->xAxis->setTickLength(0, 5);
    ui->widget->xAxis->setSubTickLength(0, 3);
    // make ticks on right axis go inward and outward:
    ui->widget->yAxis2->setTickLength(3, 3);
    ui->widget->yAxis2->setSubTickLength(1, 1);
    ui->widget->replot();

/*    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(-1, 1);
    ui->widget->yAxis->setRange(0, 1);
    ui->widget->replot();
    ui->widget->show();

}
*/
