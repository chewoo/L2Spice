#ifndef RESISTOR_H
#define RESISTOR_H

#include <QObject>
#include "rlccomponent.h"
#include "resistordialog.h"

class Resistor:public RLCComponent
{
private:
    double resistance;
    int num;
    static QVector<bool> num_list; //1 for exist 0 for not
    Resistordialog *resistordialog;

public:
    Resistor();
    Resistor(const QString &s,QRect &r,QGraphicsScene *sc);
    void Delete();
    void InputValue();
    bool isDependant();
    double get_resistance();
    ~Resistor();


};

#endif // RESISTOR_H
