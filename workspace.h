#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QGraphicsView>
#include <QObject>
#include <QMouseEvent>
#include <QVector>
#include <QKeyEvent>
#include <QHoverEvent>
#include <QPushButton>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <linenodeitem.h>
#include "circuit.h"
#include "resistor.h"
#include "capacitor.h"
#include "inductor.h"
#include "ground.h"
#include "voltage_source.h"
#include "current_source.h"
#include "current_control_current_source.h"
#include "current_control_voltage_source.h"
#include "voltage_control_current_source.h"
#include "voltage_control_voltage_source.h"
#include "diode.h"
#include <matrix.h>
#include "oscilloscope.h"




namespace Ui { class MainWindow; }


class Workspace : public QGraphicsView
{
    Q_OBJECT

    private:
        enum state{idle,resistor,
                   capacitor,inductor,diode,
                   voltageSource,currentSource,
                   CurrentcontrolCurrentSource,CurrentcontrolVoltageSource,
                   VoltagecontrolCurrentSource,VoltagecontrolVoltageSource,
                   ground,move,moving,
                   del,wire,run};
        int current_state;
        bool have_component;
        int rotateAngle;

        Circuit *circuit;
        Component* current_component;
        QGraphicsScene *scene;
        QCursor* cursor;

        QRect selecting_rect;
        QPoint lastPoint,newPoint;
        QList<QGraphicsItem *> moveList;
        QVector<QPoint> moveListCopy;
        LineNodeitem *line;

        void delete_current_component();
        void new_component(int component,int x,int y);
        void setCursorShape(Qt::CursorShape );
        void delete_mouse_line();

        bool have_ground;
        Ground *current_ground;
        void delete_current_ground();

        QGraphicsLineItem *mouseLine1,*mouseLine2;
        //QMouseEvent *mouse;

        Oscilloscope *oscilloscope;
        QLabel *nodeName;

    public:
        Workspace();
        explicit Workspace(QWidget *parent);

        ~Workspace();
    protected:
        bool eventFilter(QObject *obj, QEvent *ev) override;
        void keyPressEvent(QKeyEvent*) override;
        void mouseMoveEvent(QMouseEvent*)override;
        void mousePressEvent(QMouseEvent*)override;
        void mouseReleaseEvent(QMouseEvent*)override;
        void wheelEvent(QWheelEvent*)override;
    public slots:
        void pushResistor();
        void pushCapacitor();
        void pushInductor();
        void pushVoltageSource();
        void pushCurrentSource();
  //      void pushControlCurrentSource();
  //      void pushControlVoltageSource();
        void pushCurrentControlCurrentSource();
        void pushCurrentControlVoltageSource();
        void pushVoltageControlCurrentSource();
        void pushVoltageControlVoltageSource();
        void pushDiode();
        void pushMove();
        void pushDelete();
        void pushWire();
        void pushRun();
        void pushGround();
    private slots:


};

#endif // WORKSPACE_H
