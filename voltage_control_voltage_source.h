#ifndef VOLTAGE_CONTROL_VOLTAGE_SOURCE_H
#define VOLTAGE_CONTROL_VOLTAGE_SOURCE_H

#include "component.h"
#include "node.h"
#include "voltage_control_voltage_source_dialog.h"
#include "Constant.h"

class Voltage_control_voltage_source : public Component
{
private:
    double voltage;
    double  coefficient;
    QString nameNode1;
    QString nameNode2;
    QRect rect;
    int num;
    static QVector<bool> num_list;
    enum mode{DC,Sine,Square};
    int mode;
    Voltage_control_voltage_source_dialog *voltage_control_voltage_source_dialog;
public:
    Voltage_control_voltage_source();
    Voltage_control_voltage_source(const QString &s,QRect &r,QGraphicsScene *sc);
    const QPair<Node*,Node*> getNodePos();
    int getNodeindex1();//-
    int getNodeindex2();//+
    QString getDependantNode1();
    QString getDependantNode2();
    double get_voltage(double t);
    double getCoefficient();
    void setPos(int x,int y);
    void setPos(QPoint& p);
    void setNodeRotation(int rotateA);
    void Delete();
    void InputValue();
    bool isDCsource();
    bool isDependant();
    ~Voltage_control_voltage_source();
};

#endif // VOLTAGE_CONTROL_VOLTAGE_SOURCE_H
