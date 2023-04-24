#ifndef RESULT_H
#define RESULT_H
#include "QString"
#include "QMap"

class Result
{
public:
    Result();
    //QMap<QString, QList<QString>> result;
    QList<QString> resultRecordName;

    //void arrRecordName(QList<QString> *resultRecordName);
    //void arrResult(const QList<QString> resultRecordName, QMap<QString, QList<QString>> *result);

    QString getClassName() const;
    QString getRecordName() const;

    void setClassName(QString className);
    void setRecordName(QString recordName); /*Записывать
в .cpp файле по типу: если значение пусто, то записать, если занято то перейти к следующему эементу массива*/

private:
    QString className = "";
    QString recordName = "";
};

#endif // RESULT_H
