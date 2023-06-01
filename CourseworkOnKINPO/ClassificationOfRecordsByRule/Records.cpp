#include "Records.h"

Records::Records()
{
    name = "";
    propertes = "";
}

QString Records::checkRecords (const QString& strRecords)
{
    /*if (strRecords.count() < 10)
            return "Ошибка! Количество записей не может быть меньше 1. Допустимый диапазон: [1;100]";*/

    // Проверка окончания строки на точку
    if (!strRecords.endsWith("."))
        return "Ошибка! В конце текста записей должна стоять точка ('.')";

    if (strRecords.count(".") > 1)
        return "Ошибка! Точка ('.') может стоять только после последней записи";

    //Проверка на равенство ":" и ;"
    if(strRecords.count(":") != (strRecords.count(";") + 1))
        return "Ошибка! Количество названий записи должно быть равно количеству записей (название записи находится перед символом ':',"
               "а каждая запись разделена символом ';')";

    const QStringList& strOneRecord = strRecords.split(";", QString::SkipEmptyParts);

    if(strOneRecord.count() > 100)
        return "Ошибка! Количество записей не может быть больше 100. Допустимый диапазон: [1;100]";

    //Проверка на необходимые символы ":", "=", "[", "]"
    //":" - один и < "=" и []
    for(int i = 0; i < strOneRecord.count(); i++)
    {
        //Блок сравнения количества символов, а так же их расположения

        if(strOneRecord[i].count(":") != 1)
            return "Ошибка! У записи может быть только одно название (название записи находится перед символом ':')"
                   "\nОшибка в записи: " + strOneRecord[i]; //отсутствует символ :

        if(strOneRecord[i].count("[") != strOneRecord[i].count("]"))
            return "Ошибка! У свойства записи целочисленные значения записываются между '[' и ']' (количество '[' и ']' дожно совпадать)"
                   "\nОшибка в записи: " + strOneRecord[i]; //количество скобор не равно

        if (strOneRecord[i].count("=") != strOneRecord[i].count("["))
            return "Ошибка! У записи каждому названию свойства соответствуют целочисленные значения которые соотносятся символом '=' "
                   "(количество символов '=' и '[', ']' должно совпадать)"
                   "\nОшибка в записи: " + strOneRecord[i]; //количество = не равно [

        if(strOneRecord[i].count("=") > 20)
            return "Ошибка! У записи не может быть больше 20 свойств"
                   "\nОшибка в записи: " + strOneRecord[i];  //Больше 20 свойств

        //-----------------------------ПРОверка длинны и название записи--------------------------------------------------
        int lineLength = 0; //длина какой либо строки

        //-----------------------КРАЙНЕ ВАЖННО ОШИБОЧНЫЙ ТЕКСТ РЕТЮРНА ПОПРОБОВАТЬ: Стол:;--------------------------------
        if(strOneRecord[i].lastIndexOf(":") > strOneRecord[i].indexOf("=") || strOneRecord[i].lastIndexOf(":") > strOneRecord[i].indexOf("[")
                || strOneRecord[i].lastIndexOf(":") > strOneRecord[i].indexOf("]"))
            return "Ошибка! Запись должна начинаться с названия"
                   "\nОшибка в записи: " + strOneRecord[i]; //ошибка ввода названия записи

        for(int j = 0; strOneRecord[i][j] != ":"; j++)
        {
            if(!strOneRecord[i][j].isLetter())
                return "Ошибка! В названии записи допускаются лишь буквы русского или английсского алфавита"
                       "\nВы ввели: \"" + strOneRecord[i].mid(0, strOneRecord[i].indexOf(":"))
                        + "\"\nОшибка в записи: " + strOneRecord[i]; //ошибка в названии записи

            if(!strOneRecord[i][0].isUpper())
                return "Ошибка! Название записи должно начинаться с заглавной буквы"
                       "\nВы ввели: \"" + strOneRecord[i].mid(0, strOneRecord[i].indexOf(":"))
                        + "\"\nОшибка в записи: " + strOneRecord[i];           //Название записи не с заглавной буквы


            if(j > 0 && !strOneRecord[i][j].isLower())
                return "Ошибка! В названии записи все буквы, кроме первой должны быть в нижнем регистре"
                       "\nВы ввели: \"" + strOneRecord[i].mid(0, strOneRecord[i].indexOf(":"))
                        + "\"\nОшибка в записи: " + strOneRecord[i];       //Все буквы названия записи кроме первой должны быть в нижнем регистре

            lineLength++;
        }
        if (lineLength < 3 || lineLength > 20)
            return "Ошибка! Название записи не может быть меньше трёх или больше двадцати символов"
                   "\nОшибка в записи: " + strOneRecord[i]; //Дляна названия записи



        //----------------------Проверка на то чтобы после ] стояла запятая без пробелов-----------------------------

        int lastIndex = strOneRecord[i].lastIndexOf(']');
        int commaIndex = strOneRecord[i].indexOf(',', lastIndex);
        bool isValid = true;

        if (commaIndex == -1)
        {
            // Проверка наличия символа "," после каждого символа "]"
            for (int j = 0; j < lastIndex; j++)
            {
                //if (strOneRecord[i][j] == ']' && (j + 1 >= strOneRecord[i].length() || strOneRecord[i][j + 1] != ','))
                if(strOneRecord[i][j] == "]" && strOneRecord[i][j + 1] != ',')
                {
                    //isValid = false;
                    //break;
                    return "Ошибка! После каждого символа ']', кроме последнего, должна стоять запятая (',')"
                           "\nОшибка в записи: " + strOneRecord[i];
                }
            }

            // Проверка отсутствия символа "," после последнего символа "]"
            if (lastIndex + 1 < strOneRecord[i].length() && strOneRecord[i][lastIndex + 1] == ',')
                //isValid = false;
                return "Ошибка! После последнего символа ']' может стоять только точка с запятой (';'). Или точка ('.'), если запись последняя"
                       "\nОшибка в записи: " + strOneRecord[i];
        }
        else

            // Если найден символ "," после последнего символа "]", устанавливаем isValid в false
            //isValid = false;
            return "Ошибка! После последнего символа ']' может стоять только точка с запятой (';'). Или точка ('.'), если запись последняя"
                   "\nОшибка в записи: " + strOneRecord[i];

        if (!isValid)
            return "Ошибка! После каждого символа ']' должна стоять запятая (','), кроме последнего символа ']'"
                   "\nОшибка в записи: " + strOneRecord[i];


        //-----------------------------------------------

        //-------------------------Проверка на то что = примыкает к [ и что перед равно должна быть буква а не цифра или пробел---------
        int equalSymbal = strOneRecord[i].count("=");

        for(int j = 0; j < strOneRecord[i].count(); j++)
        {
            if(strOneRecord[i][j] == "=" && strOneRecord[i][j + 1] != "[")
                return "Ошибка! После символа '=' должен стоять символ '['"
                       "\nОшибка в записи: " + strOneRecord[i];

            else if(strOneRecord[i][j] == "[" && strOneRecord[i][j - 1] != "=" && j > 0)
                return "Ошибка! Перед символом '[' должен стоять символ '='"
                       "\nОшибка в записи: " + strOneRecord[i];

            //else if(strOneRecord[i][j] == "]" && equalSymbal == strOneRecord[i].count("="))
            //return "Ошибка! Перед символом";

            else if((j + 1) >= strOneRecord[i].count() && equalSymbal != 0)
                return "Ошибка! Символ '=' должен быть перед символом '['"
                       "\nОшибка в записи: " + strOneRecord[i];

            else if(strOneRecord[i][j] == "=")
                equalSymbal--;

            //Проверка на то что перед = нет пробела или раазделителя
            if(strOneRecord[i][0] == "=")
                return "Ошибка! Строка должна начинаться с названия записи и не может начинаться с '='"
                       "\nОшибка в записи: " + strOneRecord[i];

            else if(strOneRecord[i][j] == "=" && (strOneRecord[i][j-1].isSpace() || !strOneRecord[i][j-1].isLetter()))
                return "Ошибка! Перед символом '=' должно идти название записи "
                       "(другие символы межу названием записи и символом '=' недопускаются)"
                       "\nОшибка в записи: " + strOneRecord[i];
        }
        //--------------------------------------------------------------------------------------------------------------------

        //--------------------------Проверка на названия свойств (между : и = или , и =)--------------

        QStringList entries = strOneRecord[i].split(QRegExp("[:,]")); // Разбиваем строку по символам ":" и ","

        QList<QString> listProperties;//Проверка совпадения свойств записи

        foreach (const QString& entry, entries)
        {
            QString trimmedEntry = entry.trimmed();
            int equalsIndex = trimmedEntry.indexOf("=");

            if (equalsIndex != -1)
            {
                QString substring = trimmedEntry.mid(0, equalsIndex).trimmed();
                if(substring.count() < 3 || substring.count() > 20)
                    return "Ошибка! Название свойства записи не может быть меньше трёх или больше двадцати символов"
                           "\nВы ввели: \"" + substring +
                            "\"\nОшибка в записи: " + strOneRecord[i]; //длина названия свойства меньше 3 или больше 20

                for(int j = 0; j < substring.count(); j++)
                {
                    if(!substring[j].isLetter())
                        return "Ошибка! В названии свойства записи допускаются лишь буквы русского или английсского алфавита"
                               "\nВы ввели: \"" + substring +
                                "\"\nОшибка в записи: " + strOneRecord[i];//в названии свойства есть не только буквы

                    if (!substring[j].isLower())
                        return "Ошибка! В названии свойства записи не допускается использовать верхний регистр"
                               "\nВы ввели: \"" + substring +
                                "\"\nОшибка в записи: " + strOneRecord[i];
                }

                listProperties.append(substring); //Проверка совпадения свойств записи
            }
        }

        //----------------------------------Проверка на то чтобы не было одинаковых названий свойств записи-------------------
        for (int j = 0; j < listProperties.size(); ++j)
        {
            const QString& currentString = listProperties.at(j);
            for (int k = j + 1; k < listProperties.size(); ++k)
            {
                const QString& otherString = listProperties.at(k);
                if (currentString == otherString)
                {
                    return "Ошибка! В одной записи названия свойств не могут повторяться"
                           "\nНазвание свойства: \"" + currentString +
                            "\"\nОшибка в записи: " + strOneRecord[i];; // Найдено повторяющиеся строки
                }
            }
        }
        //--------------------------------------------------------------------------------------------------------------------

        //----------------------------------Проверка на то что в [] могут быть только определённые символы и определённое число пробелолв
        //----------------------------------и запятых и не может быть побел и запятая подряд--------------------------------------------
        int checkStart = strOneRecord[i].indexOf('['); // ищем первый символ "["
        int checkEnd = strOneRecord[i].indexOf(']'); // ищем первый символ "]"
        int position;

        //Добавить проверку ЧТО ЦИФРЫ РАЗДЕЛЕНЫ ЗАПЯТОЙ и после цифр не стоит пробел
        while (checkStart != -1 && checkEnd != -1 && checkEnd > checkStart) // пока находимся внутри скобок
        {
            position = checkStart + 1;

            if(checkEnd - checkStart == 1)
                return "Ошибка! Поле между символами '[' и ']' не должно быть пустым"
                       "\nОшибка в записи: " + strOneRecord[i]; //поле [..] не может быть пустым
            //Ситоит в следующих 2 if убрать условие strOneRecord[i][checkStart + 1].isSpace() т.к.

            if(strOneRecord[i][checkStart + 1].isSpace() || !strOneRecord[i][checkStart+ 1].isNumber())
                return "Ошибка! Не допускается сразу после символа '[' использование чего-либо, кроме цифр"
                       "\nОшибка в записи: " + strOneRecord[i]; //если после [ идёт пробел или любой символ кроме числа

            if(strOneRecord[i][checkEnd - 1].isSpace() || !strOneRecord[i][checkEnd - 1].isNumber())
                return "Ошибка! Не допускается сразу перед символом ']' использование чего-либо, кроме цифр"
                       "\nОшибка в записи: " + strOneRecord[i]; //если перед ] идёт пробел или любой символ кроме числа

            while(strOneRecord[i][position] != "]")
            {
                if(!strOneRecord[i][position].isNumber() && !strOneRecord[i][position].isSpace() && strOneRecord[i][position] != ",")
                    return "Ошибка! Не допускается использование между символами '[' и ']' всего, кроме 'пробела', ',' или цифр"
                           "\nОшибка в записи: " + strOneRecord[i];

                if(strOneRecord[i][position].isSpace() && strOneRecord[i][position + 1].isSpace())
                    return "Ошибка! Не допускается между символами '[' и ']' использование больше одного 'пробела'"
                           "\nОшибка в записи: " + strOneRecord[i];

                if(strOneRecord[i][position] == "," && strOneRecord[i][position + 1] == ",")
                    return "Ошибка! Не допускается между символами '[' и ']' использование больше одной запятой (',')"
                           "\nОшибка в записи: " + strOneRecord[i];

                if(strOneRecord[i][position].isSpace() && strOneRecord[i][position + 1] == ",")
                    return "Ошибка! Не допускается между символами '[' и ']' использование после 'пробела' запятой (',')"
                           "\nОшибка в записи: " + strOneRecord[i];

                if(strOneRecord[i][position + 1] != "]" && strOneRecord[i][position].isNumber()
                        && !strOneRecord[i][position + 1].isNumber() && strOneRecord[i][position + 1] != ",")
                    return "Ошибка! Между символами '[' и ']' после цифры должна стоять запятая (',')"
                           "\nОшибка в записи: " + strOneRecord[i];

                position ++;
            }

            checkStart = strOneRecord[i].indexOf('[', checkEnd); // ищем следующий символ "["
            checkEnd = strOneRecord[i].indexOf(']', checkEnd + 1); // ищем следующий символ "]"
        }
        //------------------------------------------------------------------------------------------------------------------------------
        //-----------------------------------Проверка что в [ ] должны быть только цифры от 1 до 99
        int start = strOneRecord[i].indexOf('['); // ищем первый символ "["
        int end = strOneRecord[i].indexOf(']'); // ищем первый символ "]"

        while (start != -1 && end != -1 && end > start) // пока находимся внутри скобок
        {
            QString substring = strOneRecord[i].mid(start + 1, end - start - 1); // вырезаем подстроку между скобками
            QStringList values = substring.split(",", QString::SkipEmptyParts); // разделяем подстроку по запятой
            int numberValues = 0;
            //--------------

            for (const QString& value : values)
            {
                bool ok;
                int intValue = value.trimmed().toInt(&ok); // преобразуем строку в целое число
                if (ok)
                    if(intValue < 1 || intValue > 99)
                        return "Ошибка! Между символами '[' и ']' цифры должны лежать в диапазоне [1;99]"
                               "\nВы ввели: \"" + value.trimmed() +
                                "\"\nОшибка в записи: " + strOneRecord[i];
                numberValues++;
            }

            if(numberValues > 9)
                return "Ошибка! Количество целочисленных значений между символами '[' и ']' должно быть от 1 до 9"
                       "\"\nОшибка в записи: " + strOneRecord[i];
            start = strOneRecord[i].indexOf('[', end); // ищем следующий символ "["
            end = strOneRecord[i].indexOf(']', end + 1); // ищем следующий символ "]"
        }
        //-------------------------------------------------------------------------------------------

        //Проверка что между частями : пробел пробел "свойство" не может быть больше 1 пробела или вообще запятой
        for(int j = (strOneRecord[i].indexOf(":") + 1); !strOneRecord[i][j].isLetter(); j++)
        {
            if(strOneRecord[i][j].isNumber())
                return "Ошибка! Свойство введено неверно. Вы ввели: \""
                        + strOneRecord[i].mid(strOneRecord[i].indexOf(":") + 1, j - strOneRecord[i].indexOf(":"))
                        + "\"\nВерный формат: 'название свойства'=['целочисленные занчения']";

            if(!strOneRecord[i][j].isSpace())
                return "Ошибка! Между символом ':' и названием свойства может быть только 'пробел'"
                       "\nОшибка в записи: " + strOneRecord[i];

            if(strOneRecord[i][j].isSpace() && strOneRecord[i][j + 1].isSpace())
                return "Ошибка! Между символом ':' и названием свойства может быть только один 'пробел'"
                       "\nОшибка в записи: " + strOneRecord[i];
        }

        for(int j = strOneRecord[i].indexOf("]"); j < strOneRecord[i].lastIndexOf("["); j++)
        {
            if(strOneRecord[i][j] == "]")
            {
                j += 2;

                if(strOneRecord[i][j] == "," || strOneRecord[i][j + 1] == ",")
                    return "Ошибка! Между концом одного свойства и началом другого должна быть одна запятая и может быть только один 'пробел'"
                           "\nОшибка в записи: " + strOneRecord[i];
                else if(strOneRecord[i][j].isSpace() && strOneRecord[i][j + 1].isSpace())
                    return "Ошибка! Между концом одного свойства и началом другого должно быть не больше одного 'пробела'"
                           "\nОшибка в записи: " + strOneRecord[i];
            }
        }

        if(strOneRecord[i].lastIndexOf("]") != strOneRecord[i].count() - 1 && strOneRecord[i].count(".") == 0)
            return "Ошибка! После последнего свойства записи не должно быть никаких символов, кроме ';', которая разделяет записи"
                   "\nОшибка в записи: " + strOneRecord[i];

        if(strOneRecord[i].lastIndexOf("]") != strOneRecord[i].count() - 2 && strOneRecord[i].count(".") == 1)
            return "Ошибка! После последнего свойства записи не должно быть никаких символов, кроме '.' после последней записи"
                   "\nОшибка в записи: " + strOneRecord[i];

        //Проверка на то чтобы формат свойст был верный
        QRegularExpression rex(",(?![^\\[]*\\])");
        QStringList parts = strOneRecord[i].split(rex, QString::SkipEmptyParts);

        parts[0] = parts[0].mid(parts[0].indexOf(":") + 1, parts[0].count() - 1);

        for (int j = 0; j < parts.count(); j++)
            if(parts[j].count("=") == 0)
                return "Ошибка! Свойство введено неверно. Вы ввели: \"" + parts[j] + "\"\nВерный формат: 'название свойства'=['целочисленные занчения']";

        //Проверка на то, что после последнего символа ] должна стоять ; или .
        //if(strOneRecord[i].lastIndexOf("]") != strOneRecord[i].count() - 1)
    }

    //---------------------------------Проверка чтобы не было одинаковых названий записей----------------------------------------------------------
    for (int i = 0; i < strOneRecord.count(); ++i)
    {
        const QString& currentString = strOneRecord[i].mid(0, strOneRecord[i].indexOf(":"));
        for (int j = i + 1; j < strOneRecord.count(); ++j)
        {
            const QString& otherString = strOneRecord[j].mid(0, strOneRecord[j].indexOf(":"));
            if (currentString == otherString)
            {
                return "Ошибка! Названия записей не могут повторяться"
                       "\nНазвание записи: \"" + currentString + "\""; // Найдено повторяющиеся строки
            }
        }
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------
    return "Всё хорошо!";
}




QString Records::splitStringOfRecords(const QString& recordsData, QList<Records>* record)
{
    Records checkRecords;
    QString errRecord = checkRecords.checkRecords(recordsData);

    if(!errRecord.contains("Всё хорошо!"))
        return errRecord;
    else
    {
        QStringList substringsRecords = recordsData.split(";");

        for(int i = 0; i < substringsRecords.count(); i++)
        {
            Records newRecord;

            newRecord.name = substringsRecords[i].mid(0, substringsRecords[i].indexOf(":"));

            QRegExp rxPropertes("([^ ,:]+)\\s*=");
            int pos = 0;

            //----------------------------------------------------------------------------------------------------------------------
            int start = substringsRecords[i].indexOf('['); // ищем первый символ "["
            int end = substringsRecords[i].indexOf(']'); // ищем первый символ "]"
            //----------------------------------------------------------------------------------------------------------------------

            while((pos = rxPropertes.indexIn(substringsRecords[i], pos)) != -1)
            {
                QList<int> integerValues;
                propertes = rxPropertes.cap(1);
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
                        integerValues.append(intValue); // выводим полученные значения
                    }
                }
                start = substringsRecords[i].indexOf('[', end); // ищем следующий символ "["
                end = substringsRecords[i].indexOf(']', end + 1); // ищем следующий символ "]"
                //----------------------------------------------------------------------------------------------------------------------

                newRecord.relatedIntegerValues.insert(propertes, integerValues);
            }
            record->append(newRecord);
        }
        return errRecord;
    }
}

QMap<QString, QList<int> > Records::getRelatedIntegerValues()
{
    return this -> relatedIntegerValues;
}

QString Records::getPropertes()
{
    return this -> propertes;
}

QString Records::getName()
{
    return this -> name;
}

