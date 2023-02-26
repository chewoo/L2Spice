#ifndef RLCCOMPONENT_H
#define RLCCOMPONENT_H

#include "component.h"
#include "node.h"
#include "Constant.h"

class RLCComponent:public Component
{
    private:
        QRect rect;
    public:
        RLCComponent();
        RLCComponent(const QString &s, QRect &r,QGraphicsScene *sc);
        const QPair<Node*,Node*> getNodePos();
        void setNodeindex(int,int);
        int getNodeindex1();//-
        int getNodeindex2();//+
        void setPos(int x,int y);
        void setPos(QPoint& p);
        void setNodeRotation(int rotateA);
        bool isDependant();
};

#endif // RLCCOMPONENT_H
