#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "rlccomponent.h"
#include "Capacitordialog.h"
class Capacitor:public RLCComponent
{
    private:
        double capacitance;
        int num;
        static QVector<bool> num_list; //1 for exist 0 for not
        Capacitordialog *capacitordialog;
    public:
        Capacitor();
        Capacitor(const QString &s,QRect &r,QGraphicsScene *sc);
        void Delete();
        void InputValue();
        bool isDependant();
        double get_capacitance();
        ~Capacitor();
};

#endif // CAPACITOR_H
