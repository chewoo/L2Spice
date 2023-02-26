#ifndef DIODE_H
#define DIODE_H

#include "component.h"
#include "node.h"
#include "diado_dialog.h"
#include "Constant.h"

class Diode : public Component
{
private:
    QRect rect;
    int num;
    static QVector<bool> num_list;
    double staturationCurrent;
    Diado_dialog *diado_dialog;
public:
    Diode();
    Diode(const QString &s,QRect &r,QGraphicsScene *sc);
    const QPair<Node*,Node*> getNodePos();
    int getNodeindex1();//-
    int getNodeindex2();//+
    double get_Isat();
    void Delete();
    void InputValue();
    bool isDependant();
    void setPos(int x,int y);
    void setPos(QPoint& p);
    void setNodeRotation(int rotateA);
    ~Diode();
};

#endif // DIODE_H
