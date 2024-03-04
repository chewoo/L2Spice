#include "inductor.h"
#include <unit_transformer.h>
Inductor::Inductor()
{

}

Inductor::Inductor(const QString &s,QRect &r,QGraphicsScene *sc):RLCComponent(s,r,sc)
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

    setName(QString("L")+QString::number(num+1));
    image->setCharacteristic(QString("L"));
    inductordialog = new Inductordialog();
    inductordialog->setModal(true);
}
void setReactance()
{

}
double Inductor::getInductance()
{
    return inductance;
}
void Inductor::Delete()
{
    num_list[num] = 0;
}
void Inductor::InputValue()
{
    inductordialog->exec();
    inductance = unit_transformer::transform(inductordialog->getInput());
    image->setCharacteristic(inductordialog->getInput());
    image->setInput(false);
    qDebug() << inductance;
}
bool Inductor::isDependant()
{
    return false;
}
Inductor::~Inductor()
{
    delete inductordialog;
}
QVector<bool> Inductor::num_list;
