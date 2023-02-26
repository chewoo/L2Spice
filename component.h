#ifndef COMPONENT_H
#define COMPONENT_H
#include <QString>
#include <QGraphicsScene>
#include "imageItem.h"
#include "node.h"
class Component
{
    private:
        QString name;
    protected:
        ImageItem *image;
        QGraphicsScene* scene;
        QVector<Node*> nodes;
        int currentRotateAngle;
        double reactance;           //Z
    public:
        Component();
        Component(const QString &s, QRect &r,QGraphicsScene *sc);
        void setName(const QString &);
        void setImage(const QString &);
        void setRect(QRect &r);
        void setCurrentRotateAngle(int);
        double  getReactance();
        void imageRotate90(int rotateA);
        void rotate90(int rotateA);
        bool getDelete();
        bool getInput();
        int getCurrentRotateAngle();
        bool connect_the_node(Node &n);
        const QString& getname()const;
        ImageItem* getimage()const;
        QVector<Node*>& getNodes();
        void resetNodeIndex();     
        virtual void setPos(int x,int y);
        virtual void setPos(QPoint& p);
        virtual void setNodeRotation(int rotateA);
        virtual void Delete();
        virtual void InputValue();
        virtual bool isDependant();
        bool judgeSelectItem(QRect &r);
        ~Component();
};

#endif // COMPONENT_H
