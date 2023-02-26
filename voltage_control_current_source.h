#ifndef VOLTAGE_CONTROL_CURRENT_SOURCE_H
#define VOLTAGE_CONTROL_CURRENT_SOURCE_H

#include "component.h"
#include "node.h"
#include "voltage_control_current_source_dialog.h"
#include "Constant.h"

class Voltage_control_current_source : public Component
{
private:
    double current;
    double  coefficient;
    QString nameNode1;
    QString nameNode2;
    QRect rect;
    int num;
    static QVector<bool> num_list; //1 for exist 0 for not
    Voltage_control_current_source_dialog *voltage_control_current_source_dialog;
    int mode;
    enum mode{DC,Sine,Square};
public:
    Voltage_control_current_source();
    Voltage_control_current_source(const QString &s,QRect &r,QGraphicsScene *sc);
    const QPair<Node*,Node*> getNodePos();
    int getNodeindex1();//-
    int getNodeindex2();//+
    double getCoefficient();
    QString getDependantNode1();
    QString getDependantNode2();
    double get_current(double t);
    void setPos(int x,int y);
    void setPos(QPoint& p);
    void setNodeRotation(int rotateA);
    void Delete();
    void InputValue();
    bool isDCsource();
    bool isDependant();
    ~Voltage_control_current_source();
};

#endif // VOLTAGE_CONTROL_CURRENT_SOURCE_H
