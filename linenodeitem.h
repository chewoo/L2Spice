#ifndef LINENODEITEM_H
#define LINENODEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include "node.h"
#include <QPair>
#include "component.h"
#include "linenodeitemdialog.h"
class LineNodeitem : public QGraphicsItem
{
private:
    Linenodeitemdialog *linenodeitemdialog;
    Node node1;
    Node node2;
    QRect bounding;
    int node_num;
    bool deleted;
    bool verticle;
public:
    LineNodeitem();
    LineNodeitem(int x1,int y1,int x2,int y2);
    LineNodeitem(const QPoint& p1,const QPoint& p2);
    void setLine(int x1, int y1, int x2, int y2);
    void setLine(const QPoint& p1,const QPoint& p2);
    void cal_boundingRect();
    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)override;
    QRectF boundingRect()const override;
    QRect get_bounding();
    bool on_the_line(const Node& n);
    bool on_the_line(const QPoint& p);
    bool line_and_line_connect(const LineNodeitem& l);
    QPair<Node,Node> getNode()const;
    void setNodeindex(int n);
    void setNodeVoltage();
    int getNodeindex();
    void resetNodeIndex();
    void Delete();
    bool getDelete();
    ~LineNodeitem();
};

#endif // LINENODEITEM_H
