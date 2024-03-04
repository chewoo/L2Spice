#include "node.h"

Node::Node()
{
    nodeIndex = -1;
    voltage = 0;
}

void Node::setVoltage(double a)
{
    voltage = a;
}

void Node::setPosition(const QPoint &p)
{
    position = p;
}

void Node::setPosition(int x, int y)
{
    position.setX(x);
    position.setY(y);
}

void Node::setNodeIndex(int a)
{
    nodeIndex = a;
}

void Node::setNodeVoltage(double a)
{
    voltage = a;
}

double Node::getVoltage()
{
    return voltage;
}

const QPoint& Node::getPosition()const
{
    return position;
}

int Node::getNodeIndex()const
{
    return nodeIndex;
}

Node::~Node()
{

}
