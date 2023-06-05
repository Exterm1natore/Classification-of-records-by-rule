#include "Result.h"

Result::Result()
{
    className = "";
}

QString Result::classificationRecordsByRule(const QString& textRecords, const QString& textClassificationRules)
{
    QList<Result> result; // создаём контейнер класса Result для хранения всех результатов классификации
    QList<Records> records; // создаём контейнер класса Records для хранения всех записей
    QList<ClassificationRules> rules; // создаём контейнер класса ClassificationRules для хранения всех правил классификации
    ClassificationRules newRule; // создаём переменную класса ClessificationRules
    Records newRecords; // создаём переменную класса Records
    QString errRule = "Текст правил классификации:"; // строка для хранения текста которое вернёт функция 'splitStringOfClassificationRules'
    // добваляем текст который вернула функция 'splitStringOfClassificationRules'
    errRule += "\n" + newRule.splitStringOfClassificationRules(textClassificationRules, &rules);
    QString errRecord = "Текст записей:";// строка для хранения текста которое вернёт функция 'splitStringOfRecords'
    // добваляем текст который вернула функция 'splitStringOfRecords'
    errRecord +="\n" + newRecords.splitStringOfRecords(textRecords, &records);

    // Если обе функции 'splitStringOfClassificationRules' и 'splitStringOfRecords' вернули не "Всё хорошо!"
    if(!errRule.contains("Всё хорошо!") && !errRecord.contains("Всё хорошо!"))
        return errRule + "\n\n" + errRecord;

    // Иначе если только функция 'splitStringOfClassificationRules' вернула не "Всё хорошо!"
    else if(!errRule.contains("Всё хорошо!") && errRecord.contains("Всё хорошо!"))
        return errRule;

    // Иначе если только функция splitStringOfRecords' вернула не "Всё хорошо!"
    else if(errRule.contains("Всё хорошо!") && !errRecord.contains("Всё хорошо!"))
        return errRecord;

    // Иначе
    else
    {
        // Для каждого правила
        for(int i = 0; i < rules.count(); i++)
        {
            ClassificationRules rule = rules[i]; // выбираем одно правило классификации по индексу i
            Result newResult; // создаём переменную класса Result
            newResult.className = rule.getName(); // записываем в результат название класса

            // Для каждой записи
            for(int j = 0; j < records.count(); j++)
            {
                Records record = records[j]; // выбираем одну запись по индексу j

                // Если в записи есть свойство которое соответсвует текстовому ограничению правила классификации
                if(record.getRelatedIntegerValues().contains(rule.getConstraint()))
                {
                    /* флаг который при сравнении целочисленных значений возвращает true если какое-либо число не совпало с дополнительным
                        огарничением правила классификации*/
                    bool flag = false;

                    // Выбираем проверку по типу текущего правила
                    switch (rule.getCondition())
                    {
                        // Правило без дополнительного ограничения
                    case propertyWithNoValue:
                        newResult.recordNames.append(record.getName()); // записываем название записи в контейнер
                        break;

                        // Правило с количеством целочисленных значений (в виде текста)
                    case propertyWithLength:

                        // Если количество значений в соответствующем свойстве равно заданному дополнительному ограничению
                        if(rule.getLimitValue() == record.getRelatedIntegerValues().value(rule.getConstraint()).count())
                            newResult.recordNames.append(record.getName()); // записываем название записи в контейнер
                        break;

                        // Правило в виде единственного целочисленного значения (наличие хотя бы одного числа в свойстве записи)
                    case propertySingleValue:

                        // Если число присутствует в свойстве записи
                        if(record.getRelatedIntegerValues().value(rule.getConstraint()).indexOf(rule.getIntegerValues().first()) != -1)
                            newResult.recordNames.append(record.getName()); // записываем название записи в контейнер
                        break;

                        // Правило с массивом целочисленных значений
                    case propertyWithSeveralValues:

                        /* Если количество целочисленных значений соответствующего свойства записи не равно количеству
                            целочисленных значений в дополнительном ограничении правила классификации*/
                        if(rule.getIntegerValues().count() != record.getRelatedIntegerValues().value(rule.getConstraint()).count())
                            break;

                        // Для каждого целочисленного значения свойства записи и правила классификации и пока flag равен false
                        for(int z = 0;flag == false && z < rule.getIntegerValues().count(); z++)

                            // Если число в соотвестсвующем свойстве записи не равно соответствующему числу в правиле классификации
                            if(record.getRelatedIntegerValues().value(rule.getConstraint())[z] != rule.getIntegerValues()[z])
                                flag = true; // присвоить флагу значение true

                        // Если флаг остался после проверки false
                        if(flag == false)
                            newResult.recordNames.append(record.getName()); // записываем название записи в контейнер
                        break;
                    }
                }
            }
            // Если под текущее правило не нашлось ни одного свойства
            if(newResult.recordNames.count() == 0)
                newResult.recordNames.append("-"); // записываем прочерк в контейнер

            result.append(newResult); // добавляем полученные в контейнер класса Result
        }
        //Возвращаем строку которую вернёт функция по преобразованию контейнера в строку 'buildStringFromResult'
        return buildStringFromResult(result);
    }
}

QString Result::buildStringFromResult (const QList<Result>& result)
{
    QString resultString; // создаём строку - результат

    // Для каждого элемента контейнера класса Result
    for(int i = 0; i < result.count(); i++)
    {
        Result newResult = result[i]; // записываем данные контейнера по индексу i в переменную класса Result
        resultString.append("\"" + newResult.getClassName() + "\"" + ": "); // формируем строку с названием класса

        // Для каждого названия записи которое есть в текущем классе
        for(int j = 0; j < newResult.getRecordNames().count(); j++)
        {
            // Если название записи не последнее в текущем классе
            if(j < newResult.getRecordNames().count() - 1)
                resultString.append(newResult.getRecordNames()[j] + ", "); // формируем строку с названиями записей

            // Иначе
            else
                resultString.append(newResult.getRecordNames()[j]); // добавляем последнее название записи
        }
        resultString.append("\n"); // разделяем классы новой строкой
    }
    return resultString; // возвращаем результат (все названия классов и соответствующие им названия записей в виде текста)
}

QString Result::getClassName()
{
    return this -> className; // вернуть текущее название класса
}

QList<QString> Result::getRecordNames()
{
    return this -> recordNames; // вернуть все названия записей, соответствующие текущему классу
}
