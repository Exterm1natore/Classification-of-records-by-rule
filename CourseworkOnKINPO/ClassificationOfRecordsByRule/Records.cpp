#include "Records.h"

Records::Records()
{
    name = "";
    propertes = "";
}

QString Records::getName() const
{
    return this -> name;
}

QString Records::getPropertes() const
{
    return this -> propertes;
}

unsigned int Records::getIntegerValues() const
{
    return this -> integerValues;
}

void Records::setName(QString name)
{
    this -> name = name;
}

void Records::setPropertes(QString propertes)
{
    this -> propertes = propertes;
}

void Records::setIntegerValues(unsigned int integerValues)
{
    this -> integerValues = integerValues;
}

