#ifndef RECORDS_H
#define RECORDS_H
#include "QMap"
#include <QRegularExpression>
#include <QStringList>

class Records
{
public:
    Records();
    QString checkRecords (const QString& strRecords);
    QString splitStringOfRecords(const QString& recordsData, QList<Records>* record);
    QMap<QString, QList<int>> getRelatedIntegerValues();
    QString getName();
private:
    QMap <QString, QList<int>> relatedIntegerValues;
    QString name;
};

#endif // RECORDS_H
