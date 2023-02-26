#include "linenodeitem.h"
#include <algorithm>
LineNodeitem::LineNodeitem():node1(),node2()
{

    QGraphicsItem::setAcceptHoverEvents(true);
    deleted = false;
    node_num = -1;
}
LineNodeitem::LineNodeitem(int x1,int y1,int x2,int y2):node1(),node2()
{

    QGraphicsItem::setAcceptHoverEvents(true);
    if(x1==x2){
        verticle = true;
    }else if(y1==y2){
        verticle = false;
    }
    node_num = -1;
    node1.setPosition(QPoint(x1,y1));
    node2.setPosition(QPoint(x2,y2));

    cal_boundingRect();
    deleted = false;

    linenodeitemdialog = new Linenodeitemdialog();
    linenodeitemdialog->setModal(true);

}
LineNodeitem::LineNodeitem(const QPoint& p1,const QPoint& p2):node1(),node2()
{

    QGraphicsItem::setAcceptHoverEvents(true);

    if(p1.x()==p2.x()){
        verticle = true;
    }else if(p1.y()==p2.y()){
        verticle = false;
    }
    node1.setPosition(p1);
    node2.setPosition(p2);
    cal_boundingRect();
    deleted = false;
    node_num = -1;
}
void LineNodeitem::setLine(int x1, int y1, int x2, int y2)
{
    if(x1==x2){
        verticle = true;

    }else if(y1==y2){
        verticle = false;

    }
    node1.setPosition(QPoint(x1,y1));
    node2.setPosition(QPoint(x2,y2));
    cal_boundingRect();
}
void LineNodeitem::setLine(const QPoint& p1,const QPoint& p2)
{
    if(p1.x()==p2.x()){
        verticle = true;
    }else if(p1.y()==p2.y()){
        verticle = false;
    }
    node1.setPosition(p1);
    node2.setPosition(p2);

    cal_boundingRect();
}
void LineNodeitem::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    //node version
    QPen pen = painter->pen();
    pen.setWidth(4);
    painter->setPen(pen);
    painter->drawLine(node1.getPosition(),node2.getPosition());
}
void LineNodeitem::cal_boundingRect()
{
    //node version
    if( (node1.getPosition().x() < node2.getPosition().x()) || (node1.getPosition().y() < node2.getPosition().y()) ){
        bounding = QRect(node1.getPosition(),node2.getPosition());
    }else{
        bounding = QRect(node2.getPosition(),node1.getPosition());
    }
}
bool LineNodeitem::on_the_line(const Node& n)
{
    QPoint p = n.getPosition();
    if(verticle && p.x() == node1.getPosition().x()){
        int bound1 = node1.getPosition().y();
        int bound2 = node2.getPosition().y();
        if(bound2>bound1)
            std::swap(bound1,bound2);

        if(p.y()<=bound1&&p.y()>=bound2)
            return true;
        else
            return false;
    }else if(!verticle&& p.y() == node1.getPosition().y()){
        int bound1 = node1.getPosition().x();
        int bound2 = node2.getPosition().x();
        if(bound2>bound1)
            std::swap(bound1,bound2);
        if(p.x()<=bound1&&p.x()>=bound2)
            return true;
        else
            return false;
    }else{
        return false;
    }
}
bool LineNodeitem::on_the_line(const QPoint& p)
{
    if(verticle && p.x() == node1.getPosition().x()){
        int bound1 = node1.getPosition().y();
        int bound2 = node2.getPosition().y();
        if(bound2>bound1)
            std::swap(bound1,bound2);

        if(p.y()<=bound1&&p.y()>=bound2)
            return true;
        else
            return false;
    }else if(!verticle&& p.y() == node1.getPosition().y()){
        int bound1 = node1.getPosition().x();
        int bound2 = node2.getPosition().x();
        if(bound2>bound1)
            std::swap(bound1,bound2);
        if(p.x()<=bound1&&p.x()>=bound2)
            return true;
        else
            return false;
    }else{
        return false;
    }
}
QPair<Node,Node> LineNodeitem::getNode()const
{
    QPair<Node,Node> p(node1,node2);
    return p;
}
bool LineNodeitem::line_and_line_connect(const LineNodeitem& l)
{
    return on_the_line(l.getNode().first)||on_the_line(l.getNode().second);
}
void LineNodeitem::setNodeindex(int n)
{
    node1.setNodeIndex(n);
    node2.setNodeIndex(n);
    node_num = n;
}
void LineNodeitem::setNodeVoltage()
{
    linenodeitemdialog->exec();
    double v = linenodeitemdialog->getInput();
    node1.setNodeVoltage(v);
    node2.setNodeVoltage(v);

    qDebug() << node1.getVoltage();
    qDebug() << node2.getVoltage();
}
void LineNodeitem::resetNodeIndex()
{
    node1.setNodeIndex(-1);
    node2.setNodeIndex(-1);
    node_num = -1;
}
void LineNodeitem::Delete()
{
    deleted = true;
}
bool LineNodeitem::getDelete()
{
    return deleted;
}
QRectF LineNodeitem::boundingRect()const
{
    return bounding;
}
QRect LineNodeitem::get_bounding()
{
    return bounding;
}
int LineNodeitem::getNodeindex()
{
    return node_num;
}
LineNodeitem::~LineNodeitem()
{
    delete linenodeitemdialog;
}
