#include "ground.h"

Ground::Ground():node()
{

}

Ground::Ground(const QString &s,QRect &r,QGraphicsScene *sc):node()
{
    image = new ImageItem(s,r);
    scene = sc;
    sc->addItem(image);
    rect = r;
    node.setVoltage(0);
}

void Ground::setImage(const QString &s)
{
    image->setPixmap(s);
}

void Ground::setRect(QRect &r)
{
    image->setRect(r);
}

void Ground::setPos(int x,int y)
{
    image->setPos(x,y);
    node.setPosition(x+rect.width()/2,y);
}
void Ground::setNodeIndex(int n)
{
    node.setNodeIndex(n);
}
int Ground::getNodeIndex()
{
    return node.getNodeIndex();
}
Node& Ground::getNode()
{
    return node;
}
void Ground::Delete()
{
    image->Delete();
}
bool Ground::getDelete()
{
    return image->getDelete();
}
int Ground::getNodeindex()
{
    return node.getNodeIndex();
}
void Ground::resetNodeIndex()
{
    node.setNodeIndex(-1);
}
const QPoint& Ground::getNodePos()
{
    return node.getPosition();
}
void Ground::setPos(QPoint& p )
{
    image->setPos(p);
    node.setPosition(p.x()+rect.width()/2,p.y());
}

Ground::~Ground()
{
    delete image;
}
