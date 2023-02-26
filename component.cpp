#include "component.h"

#define gridSize 15

#define resistorImageWidth gridSize*8
#define resistorImageHeight gridSize*4

#define inductorImageWidth gridSize*8
#define inductorImageHeight gridSize*4

#define capacitorImageWidth gridSize*8
#define capacitorImageHeight gridSize*4

#define sourceImageWidth gridSize*8
#define sourceImageHeight gridSize*4

//
#define groundImageWidth gridSize*4
#define groundImageHeight gridSize*2

Component::Component()
{

}

Component::Component(const QString &s, QRect &r,QGraphicsScene *sc)
{
    image = new ImageItem(s,r);
    scene = sc;
    sc->addItem(image);

    currentRotateAngle = 0;

    //setPos(100,100);
}

void Component::setName(const QString &s)
{
    name = s;
    image->setName(s);
    //qDebug()<<name;
}

void Component::setImage(const QString &s)
{
    image->setPixmap(s);
}
void Component::imageRotate90(int rotateA)
{
    image->rotate90(rotateA);
}
void Component::rotate90(int rotateA)
{
    //qDebug() << "you shouldn't see me Q_Q";
 //   qDebug() << "Before : " << nodes[0]->getPosition() << nodes[1]->getPosition();


    switch((rotateA/90) % 4)
    {
        case 0:
    //    qDebug() << "case0";
            nodes[0]->setPosition(nodes[0]->getPosition().x()+resistorImageWidth/2,nodes[0]->getPosition().y()-resistorImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()-resistorImageWidth/2,nodes[1]->getPosition().y()+resistorImageWidth/2);
            break;
        case 1:
    //    qDebug() << "case1";
            nodes[0]->setPosition(nodes[0]->getPosition().x()+resistorImageWidth/2,nodes[0]->getPosition().y()+resistorImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()-resistorImageWidth/2,nodes[1]->getPosition().y()-resistorImageWidth/2);
            break;
        case 2:
    //    qDebug() << "case2";
            nodes[0]->setPosition(nodes[0]->getPosition().x()-resistorImageWidth/2,nodes[0]->getPosition().y()+resistorImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()+resistorImageWidth/2,nodes[1]->getPosition().y()-resistorImageWidth/2);
            break;
        case 3:
     //   qDebug() << "case3";
            nodes[0]->setPosition(nodes[0]->getPosition().x()-resistorImageWidth/2,nodes[0]->getPosition().y()-resistorImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()+resistorImageWidth/2,nodes[1]->getPosition().y()+resistorImageWidth/2);
            break;
        default:
            ;
    }
     /*   if(rotateA % 180 != 0)
        {
            nodes[0]->setPosition(nodes[0]->getPosition().x()-resistorImageWidth/2,nodes[0]->getPosition().y()+resistorImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()+resistorImageWidth/2,nodes[1]->getPosition().y()-resistorImageWidth/2);
        }
        else
        {
            nodes[0]->setPosition(nodes[0]->getPosition().x()+resistorImageWidth/2,nodes[0]->getPosition().y()-resistorImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()-resistorImageWidth/2,nodes[1]->getPosition().y()+resistorImageWidth/2);
        }*/

//    qDebug() << "After rotate : " << nodes[0]->getPosition() << nodes[1]->getPosition();
//    scene->addRect(nodes[0]->getPosition().x()-10,nodes[0]->getPosition().y()-10,20,20);
//    scene->addRect(nodes[1]->getPosition().x()-10,nodes[1]->getPosition().y()-10,20,20);

}
bool Component::connect_the_node(Node &n)
{
    for(int i=0;i<nodes.size();i++){
        if(nodes[i]->getPosition() == n.getPosition()){
            n.setNodeIndex(nodes[i]->getNodeIndex());
            return true;
        }
    }
    return false;
}
void Component::setRect(QRect &r)
{
    image->setRect(r);
}

void Component::setCurrentRotateAngle(int RA)
{
    currentRotateAngle = RA;
}

double  Component::getReactance()
{
    return reactance;
}


void Component::setPos(int x,int y)
{
    image->setPos(x,y);

    //

}
void Component::Delete()
{

}
void Component::InputValue()
{

}
bool Component::isDependant()
{

}
const QString& Component::getname()const
{
    return name;
}
ImageItem* Component::getimage()const
{
    return image;
}
void Component::setPos(QPoint& p )
{
    image->setPos(p);
}
void Component::setNodeRotation(int rotateA)
{

}
bool Component::getDelete()
{
    return image->getDelete();
}
bool Component::getInput()
{
    return image->getInput();
}
int Component::getCurrentRotateAngle()
{
    return currentRotateAngle;
}
QVector<Node*>& Component::getNodes()
{
    return nodes;
}
void Component::resetNodeIndex()
{
    for(auto n:nodes){
        n->setNodeIndex(-1);
    }
}
Component::~Component()
{
    delete image;

}
