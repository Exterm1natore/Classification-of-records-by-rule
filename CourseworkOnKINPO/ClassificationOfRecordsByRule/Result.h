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
    QString classificationRecordsByRule (const QString& textRecords, const QString& textClassificationRules);
    QString buildStringFromResult (const QList<Result>& result);
    QString getClassName();
    QList<QString> getRecordNames();
private:
    QList<Result> result;
    QList<Records> records;
    QList<ClassificationRules> rules;
    QString className;
    QList<QString> recordNames;
};

#endif // RESULT_H
