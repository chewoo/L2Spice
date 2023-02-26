#ifndef VOLTAGE_SOURCE_H
#define VOLTAGE_SOURCE_H

#include "component.h"
#include "node.h"
#include "voltagesourcedialog.h"
#include "Constant.h"

class voltage_source : public Component
{
    private:
        QRect rect;
        int num;
        static QVector<bool> num_list; //1 for exist 0 for not
        Voltagesourcedialog *voltagesourcedialog;
        voltageSourcedata voltagesourcedata;
        double frequency;
        int mode;
        enum mode{DC,Sine,Square};
    public:
        voltage_source();
        voltage_source(const QString &s,QRect &r,QGraphicsScene *sc);
        const QPair<Node*,Node*> getNodePos();
        int getNodeindex1();//-
        int getNodeindex2();//+
        int get_num();
        double get_voltage(double t);
        double getFrequency();
        void setPos(int x,int y);
        void setPos(QPoint& p);
        void setNodeRotation(int rotateA);
        void Delete();
        void InputValue();
        bool isDCsource();
        bool isDependant();
        ~voltage_source();
};
#endif // VOLTAGE_SOURCE_H
