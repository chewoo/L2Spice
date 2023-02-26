#include "current_control_voltage_source.h"

Current_control_voltage_source::Current_control_voltage_source()
{
    nodes.push_back(new Node());
    nodes.push_back(new Node());
}

Current_control_voltage_source::Current_control_voltage_source(const QString &s,QRect &r,QGraphicsScene *sc):Component(s,r,sc)
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

    setName(QString("CCVS")+QString::number(num+1));
    image->setCharacteristic(QString("IS"));
    current_control_voltage_source_dialog = new Current_control_voltage_source_dialog();
    current_control_voltage_source_dialog->setModal(true);
}
void Current_control_voltage_source::Delete()
{
    num_list[num] = 0;
}
bool Current_control_voltage_source::isDCsource()
{
    if(mode==DC)
        return true;
    return false;
}
bool Current_control_voltage_source::isDependant()
{
    return true;
}
void Current_control_voltage_source::InputValue()
{
    current_control_voltage_source_dialog->exec();current_control_voltage_source_dialog->getInput(coefficient,branchName);
    image->setInput(false);
    image->setCharacteristic(QString::number(coefficient) + branchName);

}
Current_control_voltage_source::~Current_control_voltage_source()
{
    delete current_control_voltage_source_dialog;
}
const QPair<Node*,Node*> Current_control_voltage_source::getNodePos()
{
    QPair<Node*,Node*> node(nodes[0],nodes[1]);
    return node;
}
int Current_control_voltage_source::getNodeindex1()
{
    return nodes[0]->getNodeIndex();
}
int Current_control_voltage_source::getNodeindex2()
{
    return nodes[1]->getNodeIndex();
}
double Current_control_voltage_source::getCoefficient()
{
    return coefficient;
}
QString Current_control_voltage_source::getDependantBranchName()
{
    return branchName;
}
void Current_control_voltage_source::setPos(int x,int y)
{
    image->setPos(x,y);
    nodes[0]->setPosition(x,y+  rect.height()/2);
    nodes[1]->setPosition(x+rect.width(),y+rect.height()/2);
}
void Current_control_voltage_source::setPos(QPoint& p)
{
    image->setPos(p.x(),p.y());
    nodes[0]->setPosition(p.x(),p.y() + rect.height()/2);
    nodes[1]->setPosition(p.x()+rect.width(),p.y()+rect.height()/2);
}
double Current_control_voltage_source::get_current(double t)
{

}
void Current_control_voltage_source::setNodeRotation(int rotateA)
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
QVector<bool> Current_control_voltage_source::num_list;
