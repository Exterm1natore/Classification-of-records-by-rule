#include "Result.h"

Result::Result()
{
    className = "";
}

void Result::classificationRecordsByRule (const QList<Records>& records, const QList<ClassificationRules>& classificationRules, QList<Result>* result)
{
    for(int i = 0; i < classificationRules.count(); i++)
    {
        ClassificationRules rule = classificationRules[i];
        Result newResult;

        newResult.className = rule.getName();

        for(int j = 0; j < records.count(); j++)
        {
            Records record = records[j];
            /*for(int k = 0; k < record.getRelatedIntegerValues().count(); k++)
            {*/
                if(record.getRelatedIntegerValues().contains(rule.getConstraint()))
                {
                    bool flag = false;

                    switch (rule.getCondition())
                    {
                    case propertyWithNoValue:
                        newResult.recordNames.append(record.getName());
                        break;

                    case propertyWithLength:
                        if(rule.getLimitValue() == record.getRelatedIntegerValues().value(rule.getConstraint()).count())
                            newResult.recordNames.append(record.getName());
                        break;

                    case propertySingleValue:
                        if(record.getRelatedIntegerValues().value(rule.getConstraint()).indexOf(rule.getIntegerValues().first()) != -1)
                            newResult.recordNames.append(record.getName());
                        break;

                    case propertyWithSeveralValues:
                        //Стоит уточнить на счёт порядка для нескольких значений. Подходит или нет
                        for(int z = 0;flag == false && (z < rule.getIntegerValues().count() || record.getRelatedIntegerValues().value(rule.getConstraint()).count()); z++)
                            if(record.getRelatedIntegerValues().value(rule.getConstraint())[z] != rule.getIntegerValues()[z])
                                flag = true;

                        if(flag == false)
                            newResult.recordNames.append(record.getName());
                        break;
                    }
                }
            //}
            /*ПОД ОВПРОСОМ*/
            /*if(newResult->getRecordName() != "")
            {
                newResult->resultRecordName.append(newResult->getRecordName());
                newResult->setRecordName("");
            }*/

        }
        /*ПОД ВОПРОСОМ*/
        if(newResult.recordNames.count() == 0)
            newResult.recordNames.append("-");

        result->append(newResult); //Исправить, будет добавлять в следующий элемент такое же название класса что и было в предыдущем! лучше сделать QMap
        //delete newResult;
    }
}

QString Result::buildStringFromResult (const QList<Result>& result)
{
    QString resultString;

    for(int i = 0; i < result.count(); i++)
    {
        Result newResult = result[i];
        resultString.append("\"" + newResult.getClassName() + "\"" + ": ");

        for(int j = 0; j < newResult.getRecordNames().count(); j++)
        {
            if(j < newResult.getRecordNames().count() - 1)
                resultString.append(newResult.getRecordNames()[j] + ", ");
            else
                resultString.append(newResult.getRecordNames()[j]);
        }
        resultString.append("\n");
    }

    return resultString;
}

QString Result::getClassName()
{
    return this -> className;
}

QList<QString> Result::getRecordNames()
{
    return this -> recordNames;
}
