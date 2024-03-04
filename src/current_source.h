#ifndef CURRENT_SOURCE_H
#define CURRENT_SOURCE_H

#include "component.h"
#include "node.h"
#include "currentsourcedialog.h"
#include "Constant.h"

class current_source : public Component
{
    private:
        QRect rect;
        int num;
        static QVector<bool> num_list; //1 for exist 0 for not
        Currentsourcedialog *currentsourcedialog;
        currentSourcedata currentsourcedata;
        double frequency;
        int mode;
        enum mode{DC,Sine,Square};

    public:
        current_source();
        current_source(const QString &s,QRect &r,QGraphicsScene *sc);
        const QPair<Node*,Node*> getNodePos();
        int getNodeindex1();//-
        int getNodeindex2();//+
        double get_current(double t);
        double getFrequency();
        void Delete();
        void InputValue();
        double getValueTime(double t);
        void setPos(int x,int y);
        void setPos(QPoint& p);
        void setNodeRotation(int rotateA);
        bool isDCsource();
        bool isDependant();
        ~current_source();
};

#endif // CURRENT_SOURCE_H
