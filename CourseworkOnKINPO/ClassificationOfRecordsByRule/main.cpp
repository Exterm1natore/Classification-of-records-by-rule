#include <QCoreApplication>
#include "Records.h"
#include "ClassificationRules.h"
#include "Result.h"
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QTextCodec>

void classificationRecordsByRule (const QList<Records>& records, const QList<ClassificationRules>& classificationRules, QList<Result>* result)
{

    int numberSorts = classificationRules.count();

    for(int i = 0; i < numberSorts; i++)
    {
        ClassificationRules rule =  classificationRules[i];
        Result *newResult = new Result;

        newResult->setClassName(rule.getName());

        for(int j = 0; j < records.count(); j++)
        {
            Records record = records[j];
            int numberRecordProperty = record.recordPropertes.count();

            for(int k = 0; k < numberRecordProperty /*!!!ИСПРАВИТЬ!!! и добавить && boll при добавлении записи, чтобы дальше не проверяло*/; k++)
            {
                if(rule.getConstraint() == record.recordPropertes[k])
                {
                    bool flag = false;

                    switch (rule.condition)
                    {
                    case propertyWithNoValue:
                        newResult->setRecordName(record.getName());
                        break;

                    case propertyWithLength:
                        if(rule.value == record.recordIntegerValues[record.recordPropertes[k]].count())
                            newResult->setRecordName(record.getName());
                        break;

                    case propertySingleValue:
                        /*if(rule.arrIntegerValues.first() == record.recordIntegerValues[record.recordPropertes[k]].first())
                 newResult->setRecordName(record.getName());
                 break;*/
                        if(record.recordIntegerValues[record.recordPropertes[k]].indexOf(rule.arrIntegerValues.first()) != -1)
                            newResult->setRecordName(record.getName());
                        break;


                    case propertyWithSeveralValues:
                        //Стоит уточнить на счёт порядка для нескольких значений. Подходит или нет
                        for(int z = 0; z < rule.arrIntegerValues.count() && flag == false; z++)
                            if(record.recordIntegerValues[record.recordPropertes[k]][z] != rule.arrIntegerValues[z])
                                flag = true;

                        if(flag == false)
                            newResult->setRecordName(record.getName());
                        break;
                    }
                }
            }
            /*ПОД ОВПРОСОМ*/
            if(newResult->getRecordName() != "")
            {
                newResult->resultRecordName.append(newResult->getRecordName());
                newResult->setRecordName("");
            }

        }
        /*ПОД ВОПРОСОМ*/
        if(newResult->resultRecordName.count() == 0)
            newResult->resultRecordName.append("-");

        result->append(*newResult); //Исправить, будет добавлять в следующий элемент такое же название класса что и было в предыдущем! лучше сделать QMap
        delete newResult;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

        QList<Records> records;
        QList<ClassificationRules> rules;
        QList<Result> result;

        Records *rec = new Records;
        rec->setName("stol");

        rec->recordPropertes.append("cvet");
        rec->recordPropertes.append("razmer");
        rec->recordPropertes.append("material");

        rec->arrIntegerValues << 1 << 5 << 3 << 4;
        rec->recordIntegerValues.insert("cvet", rec->arrIntegerValues);
        rec->arrIntegerValues.clear();

        rec->arrIntegerValues << 12 << 25 << 8;
        rec->recordIntegerValues.insert("razmer", rec->arrIntegerValues);
        rec->arrIntegerValues.clear();

        rec->arrIntegerValues << 3 << 4 << 1;
        rec->recordIntegerValues.insert("material", rec->arrIntegerValues);


        Records *rec2 = new Records;
        rec2->setName("kover");

        rec2->recordPropertes.append("cvet");
        rec2->recordPropertes.append("razmer");
        rec2->recordPropertes.append("yzor");

        rec2->arrIntegerValues << 12 << 10 << 14;
        rec2->recordIntegerValues.insert("cvet", rec2->arrIntegerValues);
        rec2->arrIntegerValues.clear();

        rec2->arrIntegerValues << 10 << 5 << 8;
        rec2->recordIntegerValues.insert("razmer", rec2->arrIntegerValues);
        rec2->arrIntegerValues.clear();

        rec2->arrIntegerValues << 1 << 2 << 3;
        rec2->recordIntegerValues.insert("yzor", rec2->arrIntegerValues);



        ClassificationRules *rul = new ClassificationRules;
        rul->setName("s cvetom");
        rul->setConstraint("cvet");
        rul->condition = propertyWithLength;
        rul->value = Three;



        ClassificationRules *rul2 = new ClassificationRules;
        rul2->setName("s razmerom");
        rul2->setConstraint("razmer");
        rul2->condition = propertySingleValue;
        rul2->value = NotQuantity;

        rul2->arrIntegerValues << 8;

        records << *rec << *rec2;
        rules << *rul << *rul2;

        delete rec;
        delete rec2;
        delete rul;
        delete rul2;

        classificationRecordsByRule(records, rules, &result);

        qDebug() << result[0].getClassName();
        for(int i = 0; i < result[0].resultRecordName.count(); i++)
            qDebug() << result[0].resultRecordName[i];

        qDebug() << "-------------------------------------------------------";

        qDebug() << result[1].getClassName();
        for(int i = 0; i < result[1].resultRecordName.count(); i++)
            qDebug() << result[1].resultRecordName[i];


        //-----------------------------------------------------------------------------------

    return a.exec();
}
