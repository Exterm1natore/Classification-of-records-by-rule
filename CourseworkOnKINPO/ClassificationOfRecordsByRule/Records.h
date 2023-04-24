#ifndef RECORDS_H
#define RECORDS_H
#include "QString"
#include "QMap"

class Records
{
public:
    Records();
    QMap <QString, QList<int>> recordIntegerValues;

    /*Может стоит убрать в private и сделать заполнение через метод*/
    QList<QString> recordPropertes;
    QList<int> arrIntegerValues;

   //void propertysStatus(const QList<int> arrIntegerValues, QMap <QString, QList<int>> *recordIntegerValues);
   //void arrayRecord( QList<QString> *recordPropertes);
   //void arrayIntegerValues(QList<int> *arrIntegerValues);

   QString getName() const;
   QString getPropertes() const;
   unsigned int getIntegerValues() const;

   void setName(QString name);
   void setPropertes(QString propertes);
   void setIntegerValues(unsigned int integerValues);

private:
    QString name = "";
    QString propertes = "";
    unsigned int integerValues;
};

#endif // RECORDS_H
