#include "rlccomponent.h"

RLCComponent::RLCComponent()
{
    nodes.push_back(new Node());
    nodes.push_back(new Node());
}

RLCComponent::RLCComponent(const QString &s, QRect &r,QGraphicsScene *sc):Component(s,r,sc)
{
    rect = r;
    nodes.push_back(new Node());
    nodes.push_back(new Node());
}
const QPair<Node*,Node*> RLCComponent::getNodePos()
{
    QPair<Node*,Node*> node(nodes[0],nodes[1]);
    return node;
}
int RLCComponent::getNodeindex1()
{
    return nodes[0]->getNodeIndex();
}
int RLCComponent::getNodeindex2()
{
    return nodes[1]->getNodeIndex();
}
int getNodeindex2();
void RLCComponent::setPos(int x,int y)
{
    image->setPos(x,y);
    nodes[0]->setPosition(x,y+  rect.height()/2);
    nodes[1]->setPosition(x+rect.width(),y+rect.height()/2);
}
void RLCComponent::setPos(QPoint& p)
{
    image->setPos(p.x(),p.y());
    nodes[0]->setPosition(p.x(),p.y() + rect.height()/2);
    nodes[1]->setPosition(p.x()+rect.width(),p.y()+rect.height()/2);
}

void RLCComponent::setNodeRotation(int rotateA)
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
bool RLCComponent::isDependant()
{
    return false;
}

