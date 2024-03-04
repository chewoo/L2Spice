#ifndef GROUND_H
#define GROUND_H

#include "node.h"
#include <imageItem.h>
#include <QGraphicsScene>

class Ground
{
private:
    QGraphicsScene *scene;
    Node node;
    ImageItem *image;
    QRect rect;
public:
    Ground();
    Ground(const QString &s,QRect &r,QGraphicsScene *sc);
    void setImage(const QString &);
    void Delete();
    bool getDelete();
    void setRect(QRect &r);
    void setPos(int x,int y);
    void setPos(QPoint& p );
    void setNodeIndex(int);
    Node& getNode();
    int getNodeIndex();
    bool judgeSelectItem(QRect &r);
    void resetNodeIndex();
    const QPoint& getNodePos();
    int getNodeindex();
    ~Ground();
};

#endif // GROUND_H
