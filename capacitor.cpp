#include "capacitor.h"
#include <unit_transformer.h>
Capacitor::Capacitor()
{

}

Capacitor::Capacitor(const QString &s,QRect &r,QGraphicsScene *sc):RLCComponent(s,r,sc)
{
    bool find = false;
    for(int i=0;i<num_list.size();i++){
        if(num_list[i] == 0){
            num_list[i] = 1;
            num = i;
            find = true;
            break;
        }
    }
    if(!find){
        num_list.push_back(1);
        num = num_list.size()-1;
    }

    setName(QString("C")+QString::number(num+1));
    image->setCharacteristic(QString("C"));
    capacitordialog = new Capacitordialog();
    capacitordialog->setModal(true);
}
void Capacitor::Delete()
{
    num_list[num] = 0;
}
double Capacitor::get_capacitance()
{
    return capacitance;
}
void Capacitor::InputValue()
{
    capacitordialog->exec();
    capacitance = unit_transformer::transform(capacitordialog->getInput());
    image->setCharacteristic(capacitordialog->getInput());
    image->setInput(false);
    qDebug() << capacitance;
}
bool Capacitor::isDependant()
{
    return false;
}
Capacitor::~Capacitor()
{
    delete capacitordialog;
}
QVector<bool> Capacitor::num_list;
