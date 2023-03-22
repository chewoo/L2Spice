#include "voltagesourcedialog.h"
#include "ui_voltagesourcedialog.h"
#include <unit_transformer.h>
Voltagesourcedialog::Voltagesourcedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Voltagesourcedialog)
{
    ui->setupUi(this);

    QObject::connect(ui->OK,SIGNAL(clicked()),this,SLOT(buttonOK()));
    QObject::connect(ui->Cancel,SIGNAL(clicked()),this,SLOT(buttonCancel()));
    QObject::connect(ui->Mode,SIGNAL(activated(int)),this,SLOT(selectMode(int)));

    volline = new QLineEdit(this);
    voltext = new QLabel(this);

    offline = new QLineEdit(this);
    ampline = new QLineEdit(this);
    freline = new QLineEdit(this);
    phaline = new QLineEdit(this);
    offtext = new QLabel(this);
    amptext = new QLabel(this);
    fretext = new QLabel(this);
    phatext = new QLabel(this);

    Vonline = new QLineEdit(this);
    Voffline = new QLineEdit(this);
    Tperline = new QLineEdit(this);
    Tonline = new QLineEdit(this);
    Vontext = new QLabel(this);
    Vofftext = new QLabel(this);
    Tpertext = new QLabel(this);
    Tontext = new QLabel(this);

    volline->setGeometry(250,80,130,25);
    voltext->setGeometry(100,80,100,25);
    voltext->setText("DC value: ");

    offline->setGeometry(250,80,130,25);
    ampline->setGeometry(250,110,130,25);
    freline->setGeometry(250,140,130,25);
    phaline->setGeometry(250,170,130,25);
    offtext->setGeometry(100,80,100,25);
    amptext->setGeometry(100,110,100,25);
    fretext->setGeometry(100,140,100,25);
    phatext->setGeometry(100,170,100,25);

    offtext->setText("DC offset(V): ");
    amptext->setText("Amplitude(V): ");
    fretext->setText("Frequency(Hz): ");
    phatext->setText("Phase(deg): ");

    Vonline->setGeometry(250,80,130,25);
    Voffline->setGeometry(250,110,130,25);
    Tperline->setGeometry(250,140,130,25);
    Tonline->setGeometry(250,170,130,25);
    Vontext->setGeometry(100,80,100,25);
    Vofftext->setGeometry(100,110,100,25);
    Tpertext->setGeometry(100,140,100,25);
    Tontext->setGeometry(100,170,100,25);

    Vontext->setText("Von(V) :");
    Vofftext->setText("Voff(V): ");
    Tpertext->setText("Time period(s): ");
    Tontext->setText("Ton(s): ");


    showDC();
    hideSine();
    hideSquare();

    currentMode = DC;

    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

Voltagesourcedialog::~Voltagesourcedialog()
{
    delete ui;

    deleteDC();
    deleteSine();
    deleteSquare();
}

void Voltagesourcedialog::getInput(voltageSourcedata &a,double &frequency,int &mode)
{
    switch(currentMode)
    {
    case DC:
        a.dcData.voltage = unit_transformer::transform(volline->text());
        mode = DC;
        break;
    case Sine:
        a.sineData.amplitude = unit_transformer::transform(ampline->text());
        a.sineData.offset = unit_transformer::transform(offline->text());
        frequency = unit_transformer::transform(freline->text());
        a.sineData.phase = unit_transformer::transform(phaline->text());
        mode = Sine;
        break;
    case Square:
        a.squareData.Von = unit_transformer::transform(Vonline->text());
        a.squareData.Voff = unit_transformer::transform(Voffline->text());
        a.squareData.Tperiod = unit_transformer::transform(Tperline->text());
        a.squareData.Ton = unit_transformer::transform(Tonline->text());
        mode = Square;
        frequency = 1./a.squareData.Tperiod;
        break;
    }
}

void Voltagesourcedialog::buttonOK()
{
    currentMode = ui->Mode->currentIndex();
    switch(currentMode)
    {
        case DC:
            voltage = volline->text();
            break;
        case Sine:
            offset = offline->text();
            amplitude = ampline->text();
            frequency = freline->text();
            phase = phaline->text();
            break;
        case Square:
            Von = Vonline->text();
            Voff = Voffline->text();
            Tperiod = Tperline->text();
            Ton = Tonline->text();
            break;
    }
    this->hide();
}

void Voltagesourcedialog::buttonCancel()
{
    switch(currentMode)
    {
        case DC:
            volline->setText(voltage);
            break;
        case Sine:
            offline->setText(offset);
            ampline->setText(amplitude);
            freline->setText(frequency);
            phaline->setText(phase);
            break;
        case Square:
            Vonline->setText(Von);
            Voffline->setText(Voff);
            Tperline->setText(Tperiod);
            Tonline->setText(Ton);
            break;
    }
    this->hide();
}

void Voltagesourcedialog::selectMode(int m)
{
    switch(m)
    {
        case DC:
            hideSine();
            hideSquare();
            showDC();
            break;
        case Sine:
            hideDC();
            hideSquare();
            showSine();
            break;
        case Square:
            hideDC();
            hideSine();
            showSquare();
            break;
    }
}

void Voltagesourcedialog::showDC()
{
    volline->show();
    voltext->show();
}

void Voltagesourcedialog::showSine()
{
    offline->show();
    ampline->show();
    freline->show();
    phaline->show();
    offtext->show();
    amptext->show();
    fretext->show();
    phatext->show();
}

void Voltagesourcedialog::showSquare()
{
    Vonline->show();
    Voffline->show();
    Tperline->show();
    Tonline->show();
    Vontext->show();
    Vofftext->show();
    Tpertext->show();
    Tontext->show();
}

void Voltagesourcedialog::hideDC()
{
    volline->hide();
    voltext->hide();
}

void Voltagesourcedialog::hideSine()
{
    offline->hide();
    ampline->hide();
    freline->hide();
    phaline->hide();
    offtext->hide();
    amptext->hide();
    fretext->hide();
    phatext->hide();
}

void Voltagesourcedialog::hideSquare()
{
    Vonline->hide();
    Voffline->hide();
    Tperline->hide();
    Tonline->hide();
    Vontext->hide();
    Vofftext->hide();
    Tpertext->hide();
    Tontext->hide();
}

void Voltagesourcedialog::deleteDC()
{
    delete volline;
    delete voltext;
}

void Voltagesourcedialog::deleteSine()
{
    delete offline;
    delete ampline;
    delete freline;
    delete phaline;
    delete offtext;
    delete amptext;
    delete fretext;
    delete phatext;
}

void Voltagesourcedialog::deleteSquare()
{
    delete Vonline;
    delete Voffline;
    delete Tperline;
    delete Tonline;
    delete Vontext;
    delete Vofftext;
    delete Tpertext;
    delete Tontext;

}
