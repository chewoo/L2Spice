#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "rlccomponent.h"
#include "inductordialog.h"
class Inductor:public RLCComponent
{
    private:
        double inductance;
        int num;
        static QVector<bool> num_list; //1 for exist 0 for not
        Inductordialog *inductordialog;
    public:
        Inductor();
        Inductor(const QString &s,QRect &r,QGraphicsScene *sc);
        void setReactance();
        double getInductance();
        void Delete();
        void InputValue();
        bool isDependant();
        ~Inductor();
};

#endif // INDUCTOR_H
