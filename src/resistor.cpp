#include "resistor.h"
#include <unit_transformer.h>
Resistor::Resistor()
{
    resistordialog = nullptr;
}

Resistor::Resistor(const QString &s, QRect &r,QGraphicsScene *sc):RLCComponent(s,r,sc)
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

    setName(QString("R")+QString::number(num+1));
    image->setCharacteristic(QString("R"));
    resistordialog = new Resistordialog();
    resistordialog->setModal(true);
}
void Resistor::Delete()
{
    num_list[num] = 0;
}
void Resistor::InputValue()
{
    resistordialog->exec();
    resistance = unit_transformer::transform(resistordialog->getInput());
    image->setCharacteristic(resistordialog->getInput());
    image->setInput(false);
    qDebug() << resistance;
}
bool Resistor::isDependant()
{
    return false;
}
double Resistor::get_resistance()
{
    return resistance;
}
Resistor::~Resistor()
{
    delete resistordialog;
}
QVector<bool> Resistor::num_list;
