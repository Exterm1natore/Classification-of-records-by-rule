/*!
*\file
*\brief Данный  файл содержит в себе реализацию основных функций класса Result, которые используются в программе.
*/

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

    // запускаем функцию по разделению входного текста правил классификации по типам даных
    newRule.splitStringOfClassificationRules(textClassificationRules, &rules);

    // запускаем функцию по разделению входного текста записей по типам даных
    newRecords.splitStringOfRecords(textRecords, &records);

    // Для каждого правила
    for(int i = 0; i < rules.count(); i++)
    {
        ClassificationRules rule = rules[i]; // выбираем одно правило классификации по индексу i
        Result newResult; // создаём переменную класса Result

        // записываем в результат название класса
        newResult.className = rule.getName();

        // Для каждой записи
        for(int j = 0; j < records.count(); j++)
        {
            Records record = records[j]; // выбираем одну запись по индексу j

            // Если в записи есть свойство, которое соответствует текстовому ограничению правила классификации
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
                    // записываем название записи в контейнер
                    newResult.recordNames.append(record.getName());

                    break;

                    // Правило с количеством целочисленных значений (в виде текста)
                case propertyWithLength:

                    // Если количество значений в соответствующем свойстве равно заданному дополнительному ограничению
                    if(rule.getLimitValue() == record.getRelatedIntegerValues().value(rule.getConstraint()).count())
                    {
                        // записываем название записи в контейнер
                        newResult.recordNames.append(record.getName());
                    }

                    break;

                    // Правило в виде единственного целочисленного значения (наличие хотя бы одного числа в свойстве записи)
                case propertySingleValue:

                    // Если число присутствует в свойстве записи
                    if(record.getRelatedIntegerValues().value(rule.getConstraint()).indexOf(rule.getIntegerValues().first()) != -1)
                    {
                        // записываем название записи в контейнер
                        newResult.recordNames.append(record.getName());
                    }

                    break;

                    // Правило с массивом целочисленных значений
                case propertyWithSeveralValues:

                    /* Если количество целочисленных значений соответствующего свойства записи не равно количеству
                            целочисленных значений в дополнительном ограничении правила классификации*/
                    if(rule.getIntegerValues().count() != record.getRelatedIntegerValues().value(rule.getConstraint()).count())
                    {
                        break;
                    }

                    // Для каждого целочисленного значения свойства записи и правила классификации и пока flag равен false
                    for(int z = 0;flag == false && z < rule.getIntegerValues().count(); z++)
                    {

                        // Если число в соотвестсвующем свойстве записи не равно соответствующему числу в правиле классификации
                        if(record.getRelatedIntegerValues().value(rule.getConstraint())[z] != rule.getIntegerValues()[z])
                        {
                            // присвоить флагу значение true
                            flag = true;
                        }
                    }

                    // Если флаг остался после проверки false
                    if(flag == false)
                    {
                        // записываем название записи в контейнер
                        newResult.recordNames.append(record.getName());
                    }

                    break;
                }
            }
        }
        // Если под текущее правило не нашлось ни одного свойства
        if(newResult.recordNames.count() == 0)
        {
            // записываем прочерк в контейнер
            newResult.recordNames.append("-");
        }
        // добавляем полученные в контейнер класса Result
        result.append(newResult);
    }
    //Возвращаем строку которую вернёт функция по преобразованию контейнера в строку 'buildStringFromResult'
    return buildStringFromResult(result);
}

QString Result::buildStringFromResult (const QList<Result>& result)
{
    QString resultString; // создаём строку - результат

    // Для каждого элемента контейнера класса Result
    for(int i = 0; i < result.count(); i++)
    {
        Result newResult = result[i]; // записываем данные контейнера по индексу i в переменную класса Result

        // формируем строку с названием класса записывания название и добавляя " и (: после названия)
        resultString.append("\"" + newResult.getClassName() + "\"" + ": ");

        // Для каждого названия записи которое есть в текущем классе
        for(int j = 0; j < newResult.getRecordNames().count(); j++)
        {
            // Если название записи не последнее в текущем классе
            if(j < newResult.getRecordNames().count() - 1)
            {
                // формируем строку с названиями записей ставя пробел между названиями
                resultString.append(newResult.getRecordNames()[j] + ", ");
            }

            // Иначе
            else
            {
                // добавляем последнее название записи
                resultString.append(newResult.getRecordNames()[j]);
            }
        }
        // разделяем классы новой строкой
        resultString.append("\n");
    }
    // возвращаем результат (все названия классов и соответствующие им названия записей в виде текста)
    return resultString;
}

QString Result::getClassName()
{
    // вернуть текущее название класса
    return this -> className;
}

QList<QString> Result::getRecordNames()
{
    // вернуть все названия записей, соответствующие текущему классу
    return this -> recordNames;
}
