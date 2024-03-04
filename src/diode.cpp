#include "diode.h"
#include <unit_transformer.h>
Diode::Diode()
{
    nodes.push_back(new Node());
    nodes.push_back(new Node());
}
Diode::Diode(const QString &s,QRect &r,QGraphicsScene *sc):Component(s,r,sc)
{
    rect = r;
    nodes.push_back(new Node());
    nodes.push_back(new Node());
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

    staturationCurrent = 1e-12;

    setName(QString("D")+QString::number(num+1));
    image->setCharacteristic(QString("D"));

    diado_dialog = new Diado_dialog();
    diado_dialog->setModal(true);
}
void Diode::Delete()
{
    num_list[num] = 0;
}
const QPair<Node*,Node*> Diode::getNodePos()
{
    QPair<Node*,Node*> node(nodes[0],nodes[1]);
    return node;
}
int Diode::getNodeindex1()
{
    return nodes[0]->getNodeIndex();
}
int Diode::getNodeindex2()
{
    return nodes[1]->getNodeIndex();
}
double Diode::get_Isat()
{
    return staturationCurrent;
}
void Diode::setPos(int x,int y)
{
    image->setPos(x,y);
    nodes[0]->setPosition(x,y+  rect.height()/2);
    nodes[1]->setPosition(x+rect.width(),y+rect.height()/2);
}
void Diode::setPos(QPoint& p)
{
    image->setPos(p.x(),p.y());
    nodes[0]->setPosition(p.x(),p.y() + rect.height()/2);
    nodes[1]->setPosition(p.x()+rect.width(),p.y()+rect.height()/2);
}
void Diode::setNodeRotation(int rotateA)
{
    if(rotateA == -90)
        return;

    switch((rotateA/90) % 4)
    {
        case 0:
            nodes[0]->setPosition(nodes[0]->getPosition().x()+diodeImageWidth/2,nodes[0]->getPosition().y()-diodeImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()-diodeImageWidth/2,nodes[1]->getPosition().y()+diodeImageWidth/2);
            break;
        case 1:
            nodes[0]->setPosition(nodes[0]->getPosition().x()+diodeImageWidth,nodes[0]->getPosition().y());
            nodes[1]->setPosition(nodes[1]->getPosition().x()-diodeImageWidth,nodes[1]->getPosition().y());
            break;
        case 2:
            nodes[0]->setPosition(nodes[0]->getPosition().x()+diodeImageWidth/2,nodes[0]->getPosition().y()+diodeImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()-diodeImageWidth/2,nodes[1]->getPosition().y()-diodeImageWidth/2);
            break;
        case 3:
            break;
        default:
            ;
    }
}
void Diode::InputValue()
{
    diado_dialog->exec();
    staturationCurrent = unit_transformer::transform(diado_dialog->getInput());
    image->setCharacteristic(diado_dialog->getInput());
    image->setInput(false);
    qDebug() << staturationCurrent;
}
bool Diode::isDependant()
{
    return false;
}
Diode::~Diode()
{
    delete diado_dialog;
}
QVector<bool> Diode::num_list;
