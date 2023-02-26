#ifndef UNIT_TRANSFORMER_H
#define UNIT_TRANSFORMER_H
#include<QString>

class unit_transformer
{
public:
    unit_transformer();
    static double transform(QString s);
    ~unit_transformer();
};

#endif // UNIT_TRANSFORMER_H
