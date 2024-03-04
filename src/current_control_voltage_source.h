#ifndef CURRENT_CONTROL_VOLTAGE_SOURCE_H
#define CURRENT_CONTROL_VOLTAGE_SOURCE_H

#include "component.h"
#include "node.h"
#include "current_control_voltage_source_dialog.h"
#include "Constant.h"

class Current_control_voltage_source : public Component
{
private:
    double current;
    double  coefficient;
    QString branchName;
    QRect rect;
    int num;
    static QVector<bool> num_list; //1 for exist 0 for not
    Current_control_voltage_source_dialog *current_control_voltage_source_dialog;
    int mode;
    enum mode{DC,Sine,Square};
public:
    Current_control_voltage_source();
    Current_control_voltage_source(const QString &s,QRect &r,QGraphicsScene *sc);
    const QPair<Node*,Node*> getNodePos();
    int getNodeindex1();//-
    int getNodeindex2();//+
    QString getDependantBranchName();
    double getCoefficient();
    double get_current(double t);
    void setPos(int x,int y);
    void setPos(QPoint& p);
    void setNodeRotation(int rotateA);
    void Delete();
    void InputValue();
    bool isDCsource();
    bool isDependant();
    ~Current_control_voltage_source();
};

#endif // CURRENT_CONTROL_VOLTAGE_SOURCE_H
