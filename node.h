#ifndef NODE_H
#define NODE_H
#include <QPoint>

class Node
{
    private:
        double voltage;
        QPoint position;
        int nodeIndex;
    public:
        Node();
        void setVoltage(double a);
        void setPosition(const QPoint &p);
        void setPosition(int x, int y);
        void setNodeIndex(int a);
        void setNodeVoltage(double );
        double getVoltage();
        const QPoint& getPosition() const;
        int getNodeIndex()const;
        ~Node();
};

#endif // NODE_H
