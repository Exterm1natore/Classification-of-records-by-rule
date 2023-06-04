#ifndef RESULT_H
#define RESULT_H
#include "ClassificationRules.h"
#include "Records.h"
#include "QList"
#include <QTextCodec>

class Result
{
public:
    Result();
    QString classificationRecordsByRule(const QString& textRecords, const QString& textClassificationRules);
    QString buildStringFromResult (const QList<Result>& result);
    QString getClassName();
    QList<QString> getRecordNames();
private:
    QString className;
    QList<QString> recordNames;
};

#endif // RESULT_H
