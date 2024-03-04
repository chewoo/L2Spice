#include "workspace.h"
#include <QApplication>
#include <QDebug>
Workspace::Workspace()
{

}

Workspace::Workspace(QWidget *parent):QGraphicsView(parent)
{
    scene = new QGraphicsScene(0,0,10000,10000);
    this->setScene(scene);

    scene->installEventFilter(this);
    this->viewport()->setEnabled(true);
    circuit = new Circuit();
    current_state = idle; // 0 for nothing
    selecting_rect.setRect(-1,-1,-1,-1);
    rotateAngle = 0;
    have_component = have_ground = false;
    cursor = new QCursor(Qt::ArrowCursor);
    setCursor(*cursor);

    oscilloscope = new Oscilloscope(circuit);
    oscilloscope->hide();

    nodeName = new QLabel(this);
    nodeName->setText("");
    nodeName->setGeometry(5,600,500,50);

    setFocus();
}


void Workspace::pushResistor()
{
    if(current_state == resistor)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = resistor;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(resistor,-100,-100);
    rotateAngle = 0;
    setFocus();
}

void Workspace::pushCapacitor()
{
    if(current_state == capacitor)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = capacitor;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(capacitor,-100,-100);
    rotateAngle = 0;
    setFocus();
}

void Workspace::pushInductor()
{
    if(current_state == inductor)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = inductor;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(inductor,-100,-100);
    rotateAngle = 0;
    setFocus();
}
void Workspace::pushDiode()
{
    if(current_state == diode)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = diode;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(diode,-100,-100);
    rotateAngle = 0;
    setFocus();
}
void Workspace::pushMove()
{
    delete_mouse_line();
    delete_current_ground();
    delete_current_component();
    current_state = move;
    rotateAngle = 0;
}

void Workspace::pushDelete()
{
    //qDebug()<<scene->items().size();
    delete_mouse_line();
    delete_current_ground();
    delete_current_component();
    current_state = del;
    rotateAngle = 0;
}

void Workspace::pushWire()
{
    //qDebug() << "123";
    delete_mouse_line();
    delete_current_ground();
    delete_current_component();
    if(current_state == wire)
        current_state = 0;
    else
        current_state = wire;
    lastPoint.setX(0);
    lastPoint.setY(0);
    rotateAngle = 0;
}
void Workspace::pushVoltageSource()
{
    if(current_state == voltageSource)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = voltageSource;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(voltageSource,-100,-100);
    rotateAngle = 0;
    setFocus();
}
void Workspace::pushCurrentSource()
{
    if(current_state == currentSource)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = currentSource;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(currentSource,-100,-100);
    rotateAngle = 0;
    setFocus();
}
/*
void Workspace::pushControlCurrentSource()
{
    if(current_state == controlCurrentSource)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = controlCurrentSource;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(controlCurrentSource,-100,-100);
    rotateAngle = 0;
    setFocus();
}

void Workspace::pushControlVoltageSource()
{
    if(current_state == controlVoltageSource)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = controlVoltageSource;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(controlVoltageSource,-100,-100);
    rotateAngle = 0;
    setFocus();
}
*/
void Workspace::pushCurrentControlCurrentSource()
{
    if(current_state == CurrentcontrolCurrentSource)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = CurrentcontrolCurrentSource;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(CurrentcontrolCurrentSource,-100,-100);
    rotateAngle = 0;
    setFocus();
}

void Workspace::pushCurrentControlVoltageSource()
{
    if(current_state == CurrentcontrolVoltageSource)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = CurrentcontrolVoltageSource;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(CurrentcontrolVoltageSource,-100,-100);
    rotateAngle = 0;
    setFocus();
}

void Workspace::pushVoltageControlCurrentSource()
{
    if(current_state == VoltagecontrolCurrentSource)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = VoltagecontrolCurrentSource;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(VoltagecontrolCurrentSource,-100,-100);
    rotateAngle = 0;
    setFocus();
}

void Workspace::pushVoltageControlVoltageSource()
{
    if(current_state == VoltagecontrolVoltageSource)
        return;
    delete_mouse_line();
    delete_current_ground();
    current_state = VoltagecontrolVoltageSource;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(VoltagecontrolVoltageSource,-100,-100);
    rotateAngle = 0;
    setFocus();
}

void Workspace::pushGround()
{
    if(current_state == ground)
        return;
    delete_mouse_line();
    current_state = ground;
    delete_current_component();
    setCursorShape(Qt::BlankCursor);
    new_component(ground,-100,-100);
    rotateAngle = 0;
}
void Workspace::pushRun()
{
    current_state = run;
    delete_current_ground();
    if(circuit->getAllground().size() == 0)
    {

    }
    else
    {
        oscilloscope->show();
        oscilloscope->inputTime();
    }
}
bool Workspace::eventFilter(QObject * obj, QEvent * event)
{
    //qDebug()<<event;
    return QGraphicsView::eventFilter(obj,event);
}

void Workspace::mouseMoveEvent(QMouseEvent* e)
{
    QGraphicsView::mouseMoveEvent(e);

    if(current_state >= resistor && current_state <= VoltagecontrolVoltageSource)
    {
        current_component->setPos(int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize,int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize);
        current_component->setNodeRotation(rotateAngle-90);
    }
    else if(current_state == ground)
    {
        current_ground->setPos(int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize,int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize);
    }
    else if(current_state == moving)
    {
        newPoint = QPoint(int(e->pos().x())/gridSize * gridSize,int(e->pos().y())/gridSize * gridSize);

        for(auto x:moveList)
        {
            x->setPos((x->x()+(newPoint.x()-lastPoint.x())),(x->y()+(newPoint.y()-lastPoint.y())));

        }
        lastPoint = newPoint;
    }else if(current_state == run){
        int x = int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize;
        int y = int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize;
        nodeName->setText("");
        for(int i=0;i<circuit->getAllLine().size();i++)
        {
            if(circuit->getAllLine()[i]->on_the_line(QPoint(x,y)))
            {
                QString node = "Node" + QString::number(circuit->getAllLine()[i]->getNode().first.getNodeIndex());
                nodeName->setText(node);
            }
        }
    }
    else if(current_state == idle){
        if (e->buttons() == Qt::LeftButton)
        {
            QPointF oldp = QGraphicsView::mapToScene(lastPoint);
            QPointF newP = QGraphicsView::mapToScene(e->pos());
            QPointF translation = newP - oldp;

            translate(translation.x(), translation.y());

            lastPoint.setX((e->pos()).x());
            lastPoint.setY((e->pos()).y());
        }
        else if(e->buttons() == Qt::RightButton)
        {

        }
    }
    else if(current_state == wire)
    {
        if(lastPoint.x() == 0 && lastPoint.y() == 0)
        {
            delete_mouse_line();
       //     qDebug() << "EEEEE!";
            mouseLine1 = new QGraphicsLineItem(0,int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize,10000,int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize);
            mouseLine2 = new QGraphicsLineItem(int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize,0,int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize,10000);
            scene->addItem(mouseLine1);
            scene->addItem(mouseLine2);
       //     qDebug() << "Everythings is ok!";
        }
        else
        {

            newPoint.setX(int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize);
            newPoint.setY(int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize);
            if(abs(newPoint.x()-lastPoint.x()) > abs(newPoint.y()-lastPoint.y()))
            {
                newPoint.setX(int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize);
                newPoint.setY(lastPoint.y());
            }
            else
            {
                newPoint.setX(lastPoint.x());
                newPoint.setY(int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize);
            }
            delete_mouse_line();
            mouseLine1 = new QGraphicsLineItem(0,int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize,10000,int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize);
            mouseLine2 = new QGraphicsLineItem(int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize,0,int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize,10000);
            scene->addItem(mouseLine1);
            scene->addItem(mouseLine2);
            line->setLine(lastPoint,newPoint);
            scene->update();
        }
    }
    //qDebug() << "Everythings is ok!";
}
void Workspace::mousePressEvent(QMouseEvent* e)
{
    QGraphicsView::mousePressEvent(e);
//    qDebug()<<"press!";

    if(e->button() == Qt::RightButton)
    {
        setCursorShape(Qt::ArrowCursor);
        rotateAngle = 0;
        switch(current_state)
        {
            case moving:
                if(moveListCopy.size())
                    for(int i=0;i<moveList.size();i++)
                    {
                        moveList[i]->setPos(moveListCopy[i].x(),moveListCopy[i].y());
                    }
                moveListCopy.clear();
                moveList.clear();
                current_state = idle;
                break;
            case wire:
            {
                if(lastPoint.x()!=0||lastPoint.y()!=0){
                    if(line!=nullptr){
                        scene->removeItem(line);
                        line->Delete();
                        circuit->updatedelete();
                    }
                    lastPoint.setX(0);
                    lastPoint.setY(0);
                    return;
                }
                if(line!=nullptr){
                    if(items().contains(line))
                        scene->removeItem(line);
                    line->Delete();
                    circuit->updatedelete();
                }
                delete_mouse_line();
                lastPoint.setX(0);
                lastPoint.setY(0);
                current_state = idle;
                break;
            }
            case ground:
            {
                current_state = idle;
                    delete_current_ground();
                    break;
            }
            case idle:
            {
                selecting_rect.setRect(int(e->x())/gridSize * gridSize,int(e->y())/gridSize * gridSize,0,0);
                //qDebug() << selecting_rect;
                break;
            }
            default:
                current_state = idle;
                delete_current_component();
                //circuit->getAllComponent().erase(circuit->getAllComponent().begin()+circuit->getAllComponent().size()-1);
                break;
        }
    }else if(e->button() == Qt::LeftButton)
    {
        if(current_state == wire)
            {
                if(lastPoint.x() == 0 && lastPoint.y() == 0)
                {
                    lastPoint.setX(int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize);
                    lastPoint.setY(int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize);
                    line = new LineNodeitem(lastPoint.x(),lastPoint.y(),lastPoint.x(),lastPoint.y());
                    scene->addItem(line);
                    //qDebug() << lastPoint;
                }
                else
                {
                    newPoint.setX(int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize);
                    newPoint.setY(int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize);
                    if(abs(newPoint.x()-lastPoint.x()) > abs(newPoint.y()-lastPoint.y()))
                    {
                        newPoint.setX(int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize);
                        newPoint.setY(lastPoint.y());
                    }
                    else
                    {
                        newPoint.setX(lastPoint.x());
                        newPoint.setY(int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize);
                    }
                    circuit->push_backLine(line);
                    //scene->addLine(lastPoint.x(),lastPoint.y(),newPoint.x(),newPoint.y());
                    lastPoint.setX(newPoint.x());
                    lastPoint.setY(newPoint.y());
                    line = new LineNodeitem(lastPoint.x(),lastPoint.y(),lastPoint.x(),lastPoint.y());

                    scene->addItem(line);
                }
            }

        if(current_state == moving){
            for(int i=0;i<moveList.size();i++)
            {
                moveListCopy[i].setX(moveList[i]->x());
                moveListCopy[i].setY(moveList[i]->y());
            }
            moveListCopy.clear();
            setCursorShape(Qt::ArrowCursor);
            current_state = move;
        }else if((current_state == move || current_state == del)){
            selecting_rect.setRect(int(e->x())/gridSize * gridSize,int(e->y())/gridSize * gridSize,0,0);
        }else if(current_state == idle){
            setTransformationAnchor(NoAnchor);
            lastPoint.setX((e->pos()).x());
            lastPoint.setY((e->pos()).y());
        }else if(current_state == run){
            int x = int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize;
            int y = int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize;
            for(int i=0;i<circuit->getAllLine().size();i++)
            {
                if(circuit->getAllLine()[i]->on_the_line(QPoint(x,y)))
                {
                    int series_index = circuit->getAllLine()[i]->getNodeindex();
                    if(series_index != 0)
                    {
                        //oscilloscope->add_series(circuit->getAllLine()[i]->getNodeindex() - 1);
                        oscilloscope->custom_add_series(circuit->getAllLine()[i]->getNodeindex() - 1);
                    }
                    else
                        oscilloscope->add_series(-1);
                }
            }
       /*    for(int i=0;i<circuit->getAllComponent().size()*2;i++)
            {
                int series_index;
                if(x == circuit->getAllComponent()[i]->getNodes()[0]->getPosition().x() && y == circuit->getAllComponent()[i]->getNodes()[0]->getPosition().y())
                {
                    series_index = circuit->getAllComponent()[i]->getNodes()[0]->getNodeIndex();
                }
                else if(x == circuit->getAllComponent()[i]->getNodes()[1]->getPosition().x() && y == circuit->getAllComponent()[i]->getNodes()[1]->getPosition().y())
                {
                    series_index = circuit->getAllComponent()[i]->getNodes()[1]->getNodeIndex();
                }
                if(series_index != 0)
                    oscilloscope->add_series(circuit->getAllLine()[i]->getNodeindex() - 1);
                else
                    oscilloscope->add_series(0);
            }*/
        }
        else{
            new_component(current_state,int(QGraphicsView::mapToScene(e->pos()).x())/gridSize * gridSize,int(QGraphicsView::mapToScene(e->pos()).y())/gridSize * gridSize);
            if(current_state != ground && current_state != wire)
                current_component->imageRotate90(rotateAngle-90);

            //since we don't want to rotate node at here, all we want is to make the new image continue it's rotate angle, so add a minus to the function to avoid rotating node!
            //THIS LINE CAN CAUSE BIG PROBLEM!!!!!!!!! TAKE CARE
            //maybe can be more general,but this may be fastest
        }
    }
}
void Workspace::mouseReleaseEvent(QMouseEvent* e)
{
    QGraphicsView::mouseReleaseEvent(e);
    if(current_state == del && e->button() == Qt::LeftButton&& selecting_rect.x() != -1){
        if(selecting_rect.x() == e->x() && selecting_rect.y() == e->y()){
            QList<QGraphicsItem *> list = items(QPoint(e->x(),e->y()));
            for(auto a:list){
                ImageItem* image = dynamic_cast<ImageItem*>(a);
                LineNodeitem* line = dynamic_cast<LineNodeitem*>(a);
                if(image){
                    image->Delete();
                    //scene->removeItem(a);
                }else if(line){
                    line->Delete();
                }
                //delete by index UNDONE!!!
            }
            circuit->updatedelete();
        }else{
            selecting_rect.setWidth(e->x()-selecting_rect.x());
            selecting_rect.setHeight(e->y()-selecting_rect.y());

            if(selecting_rect.width() < 0)
            {
                int x = -selecting_rect.width();
                selecting_rect.setX(selecting_rect.x()+selecting_rect.width());
                selecting_rect.setWidth(x);
            }
            if(selecting_rect.height() < 0)
            {
                int y = -selecting_rect.height();
                selecting_rect.setY(selecting_rect.y()+selecting_rect.height());
                selecting_rect.setHeight(y);
            }

            //qDebug() << selecting_rect;
            QList<QGraphicsItem*> list = items(selecting_rect);
            //qDebug()<<list;
            for(auto a:list){
                ImageItem* image = dynamic_cast<ImageItem*>(a);
                LineNodeitem* line = dynamic_cast<LineNodeitem*>(a);
                if(image){
                    //qDebug()<<a;
                    image->Delete();
                    //scene->removeItem(a);
                }else if(line){
                    line->Delete();
                }
                //delete by index UNDONE!!!
            }
            circuit->updatedelete();


        }

    }else if(current_state == move && e->button() == Qt::LeftButton && selecting_rect.x() != -1)
    {
        //qDebug() << "move e :" << e;
        //qDebug() << selecting_rect;
        lastPoint = QPoint(int(e->x())/gridSize *gridSize,e->y()/gridSize*gridSize);
        if(selecting_rect.x() == e->x() && selecting_rect.y() == e->y()){
            moveList = items(QPoint(e->x(),e->y()));
            for(auto x:moveList)
            {
                QPoint temp(x->pos().x(),x->pos().y());
                moveListCopy.push_back(temp);
            }
        }
        else
        {
            selecting_rect.setWidth(e->x()-selecting_rect.x());
            selecting_rect.setHeight(e->y()-selecting_rect.y());

            if(selecting_rect.width() < 0)
            {
                int x = -selecting_rect.width();
                selecting_rect.setX(selecting_rect.x()+selecting_rect.width());
                selecting_rect.setWidth(x);
            }
            if(selecting_rect.height() < 0)
            {
                int y = -selecting_rect.height();
                selecting_rect.setY(selecting_rect.y()+selecting_rect.height());
                selecting_rect.setHeight(y);
            }

            moveList = items(selecting_rect);
            for(auto x:moveList)
            {
                QPoint temp(x->pos().x(),x->pos().y());
                moveListCopy.push_back(temp);
            }
            //qDebug() << moveList;
            //qDebug() << moveListCopy;
        }

        if(moveList.size()){
            current_state = moving;
            setCursor(Qt::BlankCursor);
        }

    }
/*    else if(current_state == inputControlVoltageSource && e->button() == Qt::RightButton && selecting_rect.x() != -1)
    {
        selecting_rect.setWidth(e->x()-selecting_rect.x());
        selecting_rect.setHeight(e->y()-selecting_rect.y());

        if(selecting_rect.width() < 0)
        {
            int x = -selecting_rect.width();
            selecting_rect.setX(selecting_rect.x()+selecting_rect.width());
            selecting_rect.setWidth(x);
        }
        if(selecting_rect.height() < 0)
        {
            int y = -selecting_rect.height();
            selecting_rect.setY(selecting_rect.y()+selecting_rect.height());
            selecting_rect.setHeight(y);
        }
        QList<QGraphicsItem *> list = items(selecting_rect);
    //    qDebug() << "list are haha: " << list;
        for(auto a:list){
            LineNodeitem *line = dynamic_cast<LineNodeitem*>(a);
            if(line)
            {

            }
            Control_voltage_source *cvs = dynamic_cast<Control_voltage_source*>(a);
        }
    }*/
    else if(current_state == idle && e->button() == Qt::RightButton && selecting_rect.x() != -1)
    {
        if(selecting_rect.x() == e->x() && selecting_rect.y() == e->y()){
            QList<QGraphicsItem *> list = items(QPoint(e->x(),e->y()));
            for(auto a:list){
                ImageItem* image = dynamic_cast<ImageItem*>(a);
                if(image)
                {
                    image->setInput(true);
                }
            }
        }
        else
        {
            selecting_rect.setWidth(e->x()-selecting_rect.x());
            selecting_rect.setHeight(e->y()-selecting_rect.y());

            if(selecting_rect.width() < 0)
            {
                int x = -selecting_rect.width();
                selecting_rect.setX(selecting_rect.x()+selecting_rect.width());
                selecting_rect.setWidth(x);
            }
            if(selecting_rect.height() < 0)
            {
                int y = -selecting_rect.height();
                selecting_rect.setY(selecting_rect.y()+selecting_rect.height());
                selecting_rect.setHeight(y);
            }
            QList<QGraphicsItem *> list = items(selecting_rect);
        //    qDebug() << "list are haha: " << list;
            for(auto a:list){
                ImageItem* image = dynamic_cast<ImageItem*>(a);
                if(image)
                {
                    image->setInput(true);
                //    qDebug() << "You're chosen!!";
                /*    if(image->getimagePath() == QString::fromStdString("image/control_current_supply.png"))
                        current_state = inputControlCurrentSource;
                    if(image->getimagePath() == QString::fromStdString("image/control_voltage_supply.png"))
                        current_state = inputControlVoltageSource;*/
                }
                LineNodeitem *line = dynamic_cast<LineNodeitem*>(a);
                if(line)
                {
                    line->setNodeVoltage();
                }
            }
        }
        circuit->Input();
    }
        selecting_rect.setRect(-1,-1,-1,-1);
    //qDebug()<<"release!";
}

void Workspace::wheelEvent(QWheelEvent *e)
{
    setTransformationAnchor(AnchorUnderMouse);
    double scale_factor = 1.05;
    if(e->angleDelta().y()>0){
        scale(scale_factor,scale_factor);
    }else{
        scale(1/scale_factor,1/scale_factor);
    }

}

void Workspace::keyPressEvent(QKeyEvent* e)
{
    if(e->key()==Qt::Key_P){
        circuit->analysis_circuit_connection();
    }else if(e->key()==Qt::Key_O){
        oscilloscope->add_series(1);
    }
    switch(e->key())
    {
        case Qt::Key_T:
        {
            if(moveList.size())
                for(auto x:moveList)
                {
                    x->setRotation(x->rotation()+90);
                }
            else if(current_state >= resistor && current_state <= VoltagecontrolVoltageSource){
               // qDebug() << "two nodes before: " << current_component->getNodes()[0]->getPosition() << current_component->getNodes()[1]->getPosition();
                current_component->imageRotate90(rotateAngle);
                current_component->rotate90(rotateAngle);//not sure getting image's address will be better?
                rotateAngle += 90;
                //qDebug() << "two nodes after: " << current_component->getNodes()[0]->getPosition() << current_component->getNodes()[1]->getPosition();
            }
            break;
        }
        case Qt::Key_R:
        {
            pushResistor();
            break;
        }
        case Qt::Key_C:
        {
            pushCapacitor();
            break;
        }
        case Qt::Key_L:
        {
            pushInductor();
            break;
        }
        case Qt::Key_V:
        {
            pushVoltageSource();
            break;
        }
        case Qt::Key_D:
        {
            pushDiode();
            break;
        }
        case Qt::Key_A:
        {
            pushCurrentSource();
            break;
        }
        case Qt::Key_Delete:
        {
            pushDelete();
            break;
        }
        case Qt::Key_W:
        {
            pushWire();
            break;
        }
        case Qt::Key_G:
        {
            pushGround();
            break;
        }
        case Qt::Key_H:
        {
            circuit->getDependantNode("VS22R");
            break;
        }
    }
}
void Workspace::delete_current_component()
{
    if(have_component){
        current_component->getimage()->Delete();
        have_component = false;
        circuit->updatedelete();
    }
}
void Workspace::delete_current_ground()
{
    if(have_ground){
        //qDebug() << "jjj";
        current_ground->Delete();
        have_ground = false;
        circuit->updatedelete();
    }
}
void Workspace::new_component(int component,int x,int y)
{
    //qDebug()<<"";
    if(component>=resistor&&component<=VoltagecontrolVoltageSource)
        have_component = true;
    else if(component == ground)
        have_ground = true;
    switch(component){
        case resistor:
        {
            //QRect rect(0,0,80,48);
            QRect rect(0,0,resistorImageWidth,resistorImageHeight);
            //qDebug()<<resistorImageHeight<<" "<<resistorImageHeight;
            current_component = new Resistor("image/resistor.png",rect,scene);
            circuit->push_backComponent(current_component);
        //    qDebug() << "x = " << x << "y = " << y;
            current_component->setPos(x,y);
            break;
        }
        case capacitor:
        {
            //QRect rect(0,0,80,48);
            QRect rect(0,0,capacitorImageWidth,capacitorImageHeight);
            current_component = new Capacitor("image/capacitor.png",rect,scene);
            circuit->push_backComponent(current_component);
            current_component->setPos(x,y);
            break;
        }
        case inductor:
        {
            //QRect rect(0,0,80,48);
            QRect rect(0,0,inductorImageWidth,inductorImageHeight);
            current_component = new Inductor("image/inductor.png",rect,scene);
            circuit->push_backComponent(current_component);
            current_component->setPos(x,y);
            break;
        }
        case diode:
        {
            QRect rect(0,0,diodeImageWidth,diodeImageHeight);
            current_component = new Diode("image/diode.png",rect,scene);
            circuit->push_backComponent(current_component);
            current_component->setPos(x,y);
            break;
        }
        case voltageSource:
        {
            //QRect rect(0,0,80,48);
            QRect rect(0,0,sourceImageWidth,sourceImageHeight);
            current_component = new voltage_source("image/voltage_supply.png",rect,scene);
            circuit->push_backComponent(current_component);
            current_component->setPos(x,y);
            break;
        }
        case currentSource:
        {
            QRect rect(0,0,sourceImageWidth,sourceImageHeight);
            current_component = new current_source("image/current_supply.png",rect,scene);
            circuit->push_backComponent(current_component);
            current_component->setPos(x,y);
            break;
        }
        case CurrentcontrolCurrentSource:
        {
            QRect rect(0,0,sourceImageWidth,sourceImageHeight);
            current_component = new Current_control_current_source("image/control_current_supply.png",rect,scene);
            circuit->push_backComponent(current_component);
            current_component->setPos(x,y);
            break;
        }
        case CurrentcontrolVoltageSource:
        {
            QRect rect(0,0,sourceImageWidth,sourceImageHeight);
            current_component = new Current_control_voltage_source("image/control_voltage_supply.png",rect,scene);
            circuit->push_backComponent(current_component);
            current_component->setPos(x,y);
            break;
        }
        case VoltagecontrolCurrentSource:
        {
            QRect rect(0,0,sourceImageWidth,sourceImageHeight);
            current_component = new Voltage_control_current_source("image/control_current_supply.png",rect,scene);
            circuit->push_backComponent(current_component);
            current_component->setPos(x,y);
            break;
        }
        case VoltagecontrolVoltageSource:
        {
            QRect rect(0,0,sourceImageWidth,sourceImageHeight);
            current_component = new Voltage_control_voltage_source("image/control_voltage_supply.png",rect,scene);
            circuit->push_backComponent(current_component);
            current_component->setPos(x,y);
            break;
        }
        case ground:
        {
       //    QRect rect(0,0,80,48);
            QRect rect(0,0,groundImageWidth,groundImageHeight);
            current_ground = new Ground("image/ground.png",rect,scene);
            circuit->push_backGround(current_ground);
            current_ground->setPos(x,y);
            break;
        }
        default:
            break;
    }

}
void Workspace::delete_mouse_line()
{
    if(items().contains(mouseLine1)&&items().contains(mouseLine2)){
        scene->removeItem(mouseLine1);
        scene->removeItem(mouseLine2);
        delete mouseLine1;
        delete mouseLine2;
        mouseLine1 = mouseLine2 = nullptr;
    }
}
void Workspace::setCursorShape(Qt::CursorShape  shape)
{
    cursor->setShape(shape);
    setCursor(*cursor);
}
Workspace::~Workspace()
{
    circuit->deleteAllComponent();
    delete_current_component();
    delete_current_ground();
    delete_mouse_line();
    delete circuit;
    delete cursor;
    delete oscilloscope;
    delete scene;

}
