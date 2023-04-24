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

/*void Result::arrRecordName(QList<QString> *resultRecordName)
{
    resultRecordName->append(getRecordName());
}

void Result::arrResult(const QList<QString> resultRecordName, QMap<QString, QList<QString>> *result)
{
    result->insert(getClassName(), resultRecordName);
}*/
