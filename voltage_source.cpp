#include "voltage_source.h"

voltage_source::voltage_source()
{
    nodes.push_back(new Node());
    nodes.push_back(new Node());
}
voltage_source::voltage_source(const QString &s,QRect &r,QGraphicsScene *sc):Component(s,r,sc)
{
    nodes.push_back(new Node());
    nodes.push_back(new Node());
    rect = r;
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

    setName(QString("VS")+QString::number(num+1));
    image->setCharacteristic(QString("VS"));
    voltagesourcedialog = new Voltagesourcedialog();
    voltagesourcedialog->setModal(true);



}
int voltage_source::get_num()
{
    return num;
}
bool voltage_source::isDCsource()
{
    if(mode == DC)
        return true;
    return false;
}
bool voltage_source::isDependant()
{
    return false;
}
void voltage_source::Delete()
{
    num_list[num] = 0;
}
double voltage_source::get_voltage(double t)
{
    switch(mode)
    {
        case DC:
            return voltagesourcedata.dcData.voltage;
            break;
        case Sine:
            return voltagesourcedata.sineData.offset+voltagesourcedata.sineData.amplitude*sin(2*M_PI*frequency*t + voltagesourcedata.sineData.phase*M_PI/180);
            break;
        case Square:
            int count = 0;
            double totalT = 0;
            while(t > totalT)
            {
                if(count % 2 == 0)
                    totalT += voltagesourcedata.squareData.Ton;
                else
                    totalT += voltagesourcedata.squareData.Tperiod - voltagesourcedata.squareData.Ton;
                count++;
            }
            if(count % 2 == 1)
                return voltagesourcedata.squareData.Von;
            else
                return voltagesourcedata.squareData.Voff;
            break;
    }
}
double voltage_source::getFrequency()
{
    return frequency;
}
void voltage_source::InputValue()
{
    voltagesourcedialog->exec();
    voltagesourcedialog->getInput(voltagesourcedata,frequency,mode);
    image->setInput(false);
    if(mode == DC){
        image->setCharacteristic(QString::number(voltagesourcedata.dcData.voltage));
    }else if(mode == Sine){
        image->setCharacteristic(QString("sin, ")+QString::number(voltagesourcedata.sineData.amplitude)+QString(", ")+QString::number(frequency)+QString(", ")+QString::number(voltagesourcedata.sineData.offset)+QString(", ")+QString::number(voltagesourcedata.sineData.phase));
        qDebug() << "sine amplitude : " << voltagesourcedata.sineData.amplitude;

    }else if(mode == Square){
        image->setCharacteristic(QString("square, ")+QString::number(voltagesourcedata.squareData.Von)+QString(", ")+QString::number(voltagesourcedata.squareData.Voff)+QString(", ")+QString::number(voltagesourcedata.squareData.Tperiod)+QString(", ")+QString::number(mode));
    }
}
voltage_source::~voltage_source()
{
    delete voltagesourcedialog;
}
const QPair<Node*,Node*> voltage_source::getNodePos()
{
    QPair<Node*,Node*> node(nodes[0],nodes[1]);
    return node;
}
int voltage_source::getNodeindex1()
{
    return nodes[0]->getNodeIndex();
}
int voltage_source::getNodeindex2()
{
    return nodes[1]->getNodeIndex();
}
void voltage_source::setPos(int x,int y)
{
    image->setPos(x,y);
    nodes[0]->setPosition(x,y+  rect.height()/2);
    nodes[1]->setPosition(x+rect.width(),y+rect.height()/2);
}
void voltage_source::setPos(QPoint& p)
{
    image->setPos(p.x(),p.y());
    nodes[0]->setPosition(p.x(),p.y() + rect.height()/2);
    nodes[1]->setPosition(p.x()+rect.width(),p.y()+rect.height()/2);
}
void voltage_source::setNodeRotation(int rotateA)
{
    if(rotateA == -90)
        return;

    switch((rotateA/90) % 4)
    {
        case 0:
            nodes[0]->setPosition(nodes[0]->getPosition().x()+resistorImageWidth/2,nodes[0]->getPosition().y()-resistorImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()-resistorImageWidth/2,nodes[1]->getPosition().y()+resistorImageWidth/2);
            break;
        case 1:
            nodes[0]->setPosition(nodes[0]->getPosition().x()+resistorImageWidth,nodes[0]->getPosition().y());
            nodes[1]->setPosition(nodes[1]->getPosition().x()-resistorImageWidth,nodes[1]->getPosition().y());
            break;
        case 2:
            nodes[0]->setPosition(nodes[0]->getPosition().x()+resistorImageWidth/2,nodes[0]->getPosition().y()+resistorImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()-resistorImageWidth/2,nodes[1]->getPosition().y()-resistorImageWidth/2);
            break;
        case 3:
            break;
        default:
            ;
    }
}
QVector<bool> voltage_source::num_list;
