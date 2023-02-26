#include "unit_transformer.h"
#include <QDebug>
unit_transformer::unit_transformer()
{

}
double unit_transformer::transform(QString s)
{
    bool ok;
    double ans = s.toDouble(&ok);
    if(ok){
        return ans;
    }else{
        QString t = s;
        char bb = t.back().toLatin1();
        t.remove(t.size()-1,1);
        double ans = t.toDouble(&ok);
        double x;
        if(ok){
            switch(bb){
                case 'f':
                    x = 1e-15;
                    break;
                case 'p':
                    x = 1e-12;
                    break;
                case 'n':
                    x = 1e-9;
                    break;
                case 'u':
                    x = 1e-6;
                    break;
                case 'm':
                    x = 1e-3;
                    break;
                case 'k':
                    x = 1e+3;
                    break;
                case 'M':
                    x = 1e+6;
                    break;
                case 'G':
                    x = 1e+9;
                    break;
                default:
                    qDebug()<<"Wrong Input";
                    return -99999;
                break;
            }
        }else{
            qDebug()<<"Wrong input";
            return -99999;
        }
        return ans*x;
    }
}
unit_transformer::~unit_transformer(){

}
