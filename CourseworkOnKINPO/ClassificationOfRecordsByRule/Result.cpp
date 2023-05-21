#include "Result.h"

Result::Result()
{
    className = "";
    recordName = "";
}

QString Result::getClassName() const
{
    return this -> className;
}

QString Result::getRecordName() const
{
    return this -> recordName;
}

void Result::setClassName(QString className)
{
    this -> className = className;
}

void Result::setRecordName(QString recordName)
{
    this -> recordName = recordName;
}
