#include <QCoreApplication>
#include "Records.h"
#include "ClassificationRules.h"
#include "Result.h"
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QTextCodec>

void distributesClassificationRules(const QString& rulesData, QList<ClassificationRules>* classificationRules)
{
    QStringList substringsRules = rulesData.split(";");

    for(int i = 0; i < substringsRules.count(); i++)
    {
     ClassificationRules *newRule = new ClassificationRules;

    QRegExp classRx("«([^»]+)»"); // находим слова внутри кавычек « »
    QRegExp propertyRx("свойство «([^»]+)»"); // находим слова после слова "свойство «" и до закрывающей кавычки

    int classPos = classRx.indexIn(substringsRules[i]);
    if (classPos != -1)
       newRule->setName(classRx.cap(1));

    int propertyPos = propertyRx.indexIn(substringsRules[i]);
    if (propertyPos != -1)
        newRule->setConstraint(propertyRx.cap(1));


    QString withLength = "которое представлено";
    QString singleValue = "в составе которого есть значение";
    QString severalValues = "и значение этого свойства равно";

    if(substringsRules[i].contains(withLength))
    {
        newRule->condition = propertyWithLength;

     if(substringsRules[i].contains("одним"))
         newRule->value = Single;
     else if(substringsRules[i].contains("двумя"))
         newRule->value = Two;
     else if(substringsRules[i].contains("тремя"))
         newRule->value = Three;
     else if(substringsRules[i].contains("четырьмя"))
         newRule->value = Four;
     else if(substringsRules[i].contains("пятью"))
         newRule->value = Five;
     else if(substringsRules[i].contains("шестью"))
         newRule->value = Six;
     else if(substringsRules[i].contains("семью"))
         newRule->value = Seven;
     else if(substringsRules[i].contains("восемью"))
         newRule->value = Eight;
     else if(substringsRules[i].contains("девятью"))
         newRule->value = Nine;
    }
    else if(substringsRules[i].contains(singleValue))
    {
        newRule->condition = propertySingleValue;
        newRule->value = NotQuantity;

        QRegExp rxValue("(\\d+)");
        int pos = 0;
        while ((pos = rxValue.indexIn(substringsRules[i], pos)) != -1)
        {
            newRule->setIntegerValues(rxValue.cap(1).toInt());
            pos += rxValue.matchedLength();
        }

        newRule->arrIntegerValues.append(newRule->getIntegerValues());
    }
    else if(substringsRules[i].contains(severalValues))
    {
        newRule->condition = propertyWithSeveralValues;
        newRule->value = NotQuantity;

        int start = substringsRules[i].indexOf('['); // ищем первый символ "["
        int end = substringsRules[i].indexOf(']'); // ищем первый символ "]"

        QString substring = substringsRules[i].mid(start + 1, end - start - 1); // вырезаем подстроку между скобками
        QStringList values = substring.split(",", QString::SkipEmptyParts); // разделяем подстроку по запятой
        for (const QString& value : values)
        {
            bool ok;
            int intValue = value.trimmed().toInt(&ok); // преобразуем строку в целое число
            if (ok)
            {
                newRule->setIntegerValues(intValue); // выводим полученные значения
                newRule->arrIntegerValues.append(newRule->getIntegerValues());
            }
        }
    }
    else
    {
        newRule->condition = propertyWithNoValue;
        newRule->value = NotQuantity;
    }

    classificationRules->append(*newRule);
    delete newRule;
    }
}

void distributesRecords(const QString& recordsData, QList<Records>* record)
{
    QStringList substringsRecords = recordsData.split(";");

    for(int i = 0; i < substringsRecords.count(); i++)
    {
        Records *newRecord = new Records;

        newRecord->setName(substringsRecords[i].mid(0, substringsRecords[i].indexOf(":")));

        QRegExp rxPropertes("([^ ,:]+)\\s*=");
        int pos = 0;

        //----------------------------------------------------------------------------------------------------------------------
        int start = substringsRecords[i].indexOf('['); // ищем первый символ "["
        int end = substringsRecords[i].indexOf(']'); // ищем первый символ "]"
        //----------------------------------------------------------------------------------------------------------------------

        while((pos = rxPropertes.indexIn(substringsRecords[i], pos)) != -1)
        {
            newRecord->setPropertes(rxPropertes.cap(1));
            newRecord->recordPropertes.append(newRecord->getPropertes());
            pos += rxPropertes.matchedLength();

            //-------------------------------------------------------------------------------------------------------------------
                QString substring = substringsRecords[i].mid(start + 1, end - start - 1); // вырезаем подстроку между скобками
                QStringList values = substring.split(",", QString::SkipEmptyParts); // разделяем подстроку по запятой
                for (const QString& value : values)
                {
                    bool ok;
                    int intValue = value.trimmed().toInt(&ok); // преобразуем строку в целое число
                    if (ok)
                    {
                       newRecord->setIntegerValues(intValue); // выводим полученные значения
                       newRecord->arrIntegerValues.append(newRecord->getIntegerValues());
                    }
                }
                start = substringsRecords[i].indexOf('[', end); // ищем следующий символ "["
                end = substringsRecords[i].indexOf(']', end + 1); // ищем следующий символ "]"
            //----------------------------------------------------------------------------------------------------------------------

           newRecord->recordIntegerValues.insert(newRecord->getPropertes(), newRecord->arrIntegerValues);
           newRecord->arrIntegerValues.clear();
        }
        record->append(*newRecord);
        delete newRecord;
    }
}

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

        QString strRecords = "Шкаф: цвет=[1, 2], размер=[10,12,15];Стол: размер=[12, 15], цвет=[1, 15], покрытие=[12].";
        QString strRule = "Запись принадлежит классу «С покрытием», если у нее есть свойство «покрытие»;"
                              "Запись принадлежит классу «Объёмный», если у нее есть свойство «размер», которое представлено тремя значениями;"
                              "Запись принадлежит классу «Синий», если у нее есть свойство «цвет», в составе которого есть значение «1»;"
                              "Запись принадлежит классу «Матовый», если у нее есть свойство «покрытие» и значение этого свойства равно «[44, 21]».";

        /*Records *rec = new Records;
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
            qDebug() << result[1].resultRecordName[i];*/


        //-----------------------------------------------------------------------------------

            /*distributesRecords(strRecords, &records);

            QTextStream outStream(stdout);
             outStream.setCodec(QTextCodec::codecForName("cp866"));

             for(int i = 0; i < records.count(); i++)
             {
                outStream <<"Name: " << records[i].getName() << flush;
                for(int j = 0; j < records[i].recordPropertes.count(); j++)
                {
                    outStream << "\n" << flush;
                    outStream <<"Properties: " << records[i].recordPropertes[j] << flush << "\n" << "Value: ";
                    for(int k = 0; k < records[i].recordIntegerValues[records[i].recordPropertes[j]].count(); k++)
                        outStream << records[i].recordIntegerValues[records[i].recordPropertes[j]][k] << ", " << flush;
                }
                outStream << "\n\n" << flush;
             }*/

        //-----------------------------------------------------------------------------------

            distributesClassificationRules(strRule, &rules);

            QTextStream outStream(stdout);
             outStream.setCodec(QTextCodec::codecForName("cp866"));

             for(int i = 0; i < rules.count(); i++)
             {
                 outStream << "Class: " << rules[i].getName() << flush << "\n";
                 outStream << "Constraint: " << rules[i].getConstraint() << flush << "\n";

                 switch (rules[i].condition)
                 {
                 case propertyWithLength:
                     outStream << "Value: " << rules[i].value << flush << "\n";
                     break;

                 case propertySingleValue:
                     outStream << "Value: " << rules[i].arrIntegerValues.first() << flush << "\n";
                     break;

                 case propertyWithSeveralValues:
                     outStream << "Value: " << flush;
                     for(int j = 0; j < rules[i].arrIntegerValues.count(); j++)
                        outStream << rules[i].arrIntegerValues[j] << ", " << flush;
                     break;

                 default:
                     outStream << "ERROR" << flush << "\n";
                     break;
                 }
                 outStream << "\n\n" << flush;
             }

    return a.exec();
}
