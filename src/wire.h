#ifndef WIRE_H
#define WIRE_H
#include <QGraphicsLineItem>
#include "node.h"

class Wire:public QGraphicsLineItem
{
    private:
        Node node1;
        Node node2;
    public:
        Wire();
        Wire(QPoint &p1, QPoint &p2);
        ~Wire();
};

#endif // WIRE_H
