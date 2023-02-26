#include "current_source.h"

current_source::current_source()
{
    nodes.push_back(new Node());
    nodes.push_back(new Node());
}
current_source::current_source(const QString &s,QRect &r,QGraphicsScene *sc):Component(s,r,sc)
{
    nodes.push_back(new Node());
    nodes.push_back(new Node());
    rect = r;
    bool find = false;
    for(int i=0;i<num_list.size();i++){
        if(num_list[i] == 0){
            num_list[i] = 1;
            num = i;
            find = true;
            break;
        }
    }
    if(!find){
        num_list.push_back(1);
        num = num_list.size()-1;
    }

    setName(QString("IS")+QString::number(num+1));
    image->setCharacteristic(QString("IS"));
    currentsourcedialog = new Currentsourcedialog();
    currentsourcedialog->setModal(true);
}
void current_source::Delete()
{
    num_list[num] = 0;
}
bool current_source::isDCsource()
{
    if(mode==DC)
        return true;
    return false;
}
bool current_source::isDependant()
{
    return false;
}
void current_source::InputValue()
{
    currentsourcedialog->exec();
    //currentsourcedialog->getInput(curDCorAmporIon,offsetDCorIoff,frequencyorTperiod,phaseorTon,mode);
    currentsourcedialog->getInput(currentsourcedata,frequency,mode);
    image->setInput(false);
    if(mode == DC){
        image->setCharacteristic(QString::number(currentsourcedata.dcData.current));
    }else if(mode == Sine){
        image->setCharacteristic(QString("sin, ")+QString::number(currentsourcedata.sineData.amplitude)+QString(", ")+QString::number(frequency)+QString(", ")+QString::number(currentsourcedata.sineData.offset)+QString(", ")+QString::number(currentsourcedata.sineData.phase));
    }else if(mode == Square){
        image->setCharacteristic(QString("square, ")+QString::number(currentsourcedata.squareData.Ion)+QString(", ")+QString::number(currentsourcedata.squareData.Ioff)+QString(", ")+QString::number(currentsourcedata.squareData.Tperiod)+QString(", ")+QString::number(mode));
    }
}
current_source::~current_source()
{
    delete currentsourcedialog;
}
const QPair<Node*,Node*> current_source::getNodePos()
{
    QPair<Node*,Node*> node(nodes[0],nodes[1]);
    return node;
}
int current_source::getNodeindex1()
{
    return nodes[0]->getNodeIndex();
}
int current_source::getNodeindex2()
{
    return nodes[1]->getNodeIndex();
}
void current_source::setPos(int x,int y)
{
    image->setPos(x,y);
    nodes[0]->setPosition(x,y+  rect.height()/2);
    nodes[1]->setPosition(x+rect.width(),y+rect.height()/2);

    //scene->addRect(x-10,y+rect.height()/2-10,20,20);
    //scene->addRect(x+rect.width(),y+rect.height()/2,20,20);

}
void current_source::setPos(QPoint& p)
{
    image->setPos(p.x(),p.y());
    nodes[0]->setPosition(p.x(),p.y() + rect.height()/2);
    nodes[1]->setPosition(p.x()+rect.width(),p.y()+rect.height()/2);

    //scene->addRect(p.x()-10,p.y()+rect.height()/2-10,20,20);
    //scene->addRect(p.x()+rect.width(),p.y()+rect.height()/2,20,20);
}
double current_source::get_current(double t)
{
    switch(mode)
    {
        case DC:
            return currentsourcedata.dcData.current;
            break;
        case Sine:
            return currentsourcedata.sineData.offset+currentsourcedata.sineData.amplitude*sin(2*M_PI*frequency*t + currentsourcedata.sineData.phase*M_PI/180);
        break;
        case Square:
            int count = 0;
            double totalT = 0;
            while(t > totalT)
            {
                if(count % 2 == 0)
                    totalT += currentsourcedata.squareData.Ton;
                else
                    totalT += currentsourcedata.squareData.Tperiod - currentsourcedata.squareData.Ton;
                count++;
            }
            if(count % 2 == 1)
                return currentsourcedata.squareData.Ion;
            else
                return currentsourcedata.squareData.Ioff;
            break;
    }
}
double current_source::getFrequency()
{
    return frequency;
}
void current_source::setNodeRotation(int rotateA)
{
    if(rotateA == -90)
        return;
//    rotateA -= 90;
//    qDebug() << "rotatA = " << rotateA;
    switch((rotateA/90) % 4)
    {
        case 0:
    //    qDebug() << "case0";
            nodes[0]->setPosition(nodes[0]->getPosition().x()+resistorImageWidth/2,nodes[0]->getPosition().y()-resistorImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()-resistorImageWidth/2,nodes[1]->getPosition().y()+resistorImageWidth/2);
            break;
        case 1:
    //    qDebug() << "case1";
            nodes[0]->setPosition(nodes[0]->getPosition().x()+resistorImageWidth,nodes[0]->getPosition().y());
            nodes[1]->setPosition(nodes[1]->getPosition().x()-resistorImageWidth,nodes[1]->getPosition().y());
            break;
        case 2:
    //    qDebug() << "case2";
            nodes[0]->setPosition(nodes[0]->getPosition().x()+resistorImageWidth/2,nodes[0]->getPosition().y()+resistorImageWidth/2);
            nodes[1]->setPosition(nodes[1]->getPosition().x()-resistorImageWidth/2,nodes[1]->getPosition().y()-resistorImageWidth/2);
            break;
        case 3:
    //    qDebug() << "case3";
    //        nodes[0]->setPosition(nodes[0]->getPosition().x()-resistorImageWidth/2,nodes[0]->getPosition().y()-resistorImageWidth/2);
    //        nodes[1]->setPosition(nodes[1]->getPosition().x()+resistorImageWidth/2,nodes[1]->getPosition().y()+resistorImageWidth/2);
            break;
        default:
            ;
    }
//    scene->addRect(nodes[0]->getPosition().x()-10,nodes[0]->getPosition().y()-10,20,20);
//    scene->addRect(nodes[1]->getPosition().x()-10,nodes[1]->getPosition().y()-10,20,20);



}
QVector<bool> current_source::num_list;
