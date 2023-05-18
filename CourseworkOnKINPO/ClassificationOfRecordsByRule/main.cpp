#include <QCoreApplication>
#include "Records.h"
#include "ClassificationRules.h"
#include "Result.h"
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QTextCodec>
#include <QRegularExpression>

bool checkClassificationRule(const QString& strRule)
{
    QString rule = "Запись принадлежит классу \"С покрытием\", если у нее есть свойство \"покрытие\";"
                   "Запись принадлежит классу \"Объёмный\", если у нее есть свойство \"размер\", которое представлено двумя значениями;"
                   "Запись принадлежит классу \"Синий\", если у нее есть свойство \"цвет\", в составе которого есть значение \"1\";"
                   "Запись принадлежит классу \"Матовый\", если у нее есть свойство \"покрытие\" и значение этого свойства равно \"[44, 21]\".";

    // Паттерн для проверки первого типа строки
    QString pattern1 = "Запись принадлежит классу \"(.+)\", если у нее есть свойство \"(.+)\"";
    // Паттерн для проверки второго типа строки
    QString pattern2 = "Запись принадлежит классу \"(.+)\", если у нее есть свойство \"(.+)\", которое представлено ([одним|двумя|тремя|четырьмя|пятью|шестью|семью|восемью|девятью]+) значени";
    // Паттерн для проверки четвертого типа строки
    QString pattern3 = "Запись принадлежит классу \"(.+)\", если у нее есть свойство \"(.+)\", в составе которого есть значение \"(.+)\"";
    // Паттерн для проверки третьего типа строки
    QString pattern4 = "Запись принадлежит классу \"(.+)\", если у нее есть свойство \"(.+)\" и значение этого свойства равно \"\\[(.+)\\]\"";


    QRegularExpression regex1(pattern4);
    QRegularExpression regex2(pattern3);
    QRegularExpression regex3(pattern2);
    QRegularExpression regex4(pattern1);

    if (!rule.endsWith("."))
        return false; //Если заканчивается не на точку
    if (rule.count(".") > 1)
        return false; //Если больше одной точки

    QStringList strOneRule = rule.split(";", QString::SkipEmptyParts);

    for(int i = 0; i < strOneRule.count(); i++)
    {
        if(strOneRule[i][strOneRule[i].count() - 1] != "\"" && strOneRule[i][strOneRule[i].count() - 1] != "."
                && strOneRule[i][strOneRule[i].count() - 1] != "и" && strOneRule[i][strOneRule[i].count() - 1] != "м")
            return false;  //Если последний символ не " не 'и' не .

        if(strOneRule[i][0].isSpace())
            return false; //Первый символ не может быть пробелом

        for(int j = 0; j < strOneRule[i].count() - 1; j++)
            if(strOneRule[i][j].isSpace() && strOneRule[i][j + 1].isSpace())
                return false; //Нельзя больше одного пробела

        if(strOneRule[i].count("\"") != 4 && strOneRule[i].count("\"") != 6)
            return false; // символов "" должно быть либо 4 либо 6

        //---------------Провека правильности названия класса и ограничения-------------------------------------
        if(regex1.match(strOneRule[i]).hasMatch() || regex2.match(strOneRule[i]).hasMatch()
                || regex3.match(strOneRule[i]).hasMatch() || regex4.match(strOneRule[i]).hasMatch())
        {
            QStringList substrings;

            int startPos = strOneRule[i].indexOf("\"");
            while (startPos != -1)
            {
                int endPos = strOneRule[i].indexOf("\"", startPos + 1);
                if (endPos != -1)
                {
                    QString substring = strOneRule[i].mid(startPos + 1, endPos - startPos - 1);
                    substrings.append(substring);
                    startPos = strOneRule[i].indexOf("\"", endPos + 1);
                }
                else
                    break;
            }

            for(int j = 0; j < 2; j++)
            if(!substrings[j][0].isLetter() || !substrings[j][substrings[j].count() - 1].isLetter())
                return false; //нелья после " и перед " савить что-то кроме буквы

            if(substrings[0].count() < 3 || substrings[0].count() > 20)
                return false; //Название класса не может быть меньше 3 или больше 20

            if(substrings[1].count() < 3 || substrings[1].count() > 20)
                return false; // Ограничение не может быть меньше 3 или больше 20

            if(!substrings[0][0].isUpper())
                return false; //Название класса начинается с заглавной буквы

            for(int j = 1; j < substrings[0].count(); j++)
                if(!substrings[0][j].isSpace() && substrings[0][j].isUpper())
                    return false; //Все кроме заглавной буквы на названии класса должны быть в нижнем регистре

            for(int j = 0; j < substrings[0].count(); j++)
                if(!substrings[0][j].isLetter() && !substrings[0][j].isSpace())
                    return false; //Название класса может содержать только буквы и пробел

            for(int j = 0; j < substrings[1].count(); j++)
                if(!substrings[1][j].isLetter() || substrings[1][j].isSpace())
                    return false; //Ограничение может содержать только буквы без пробелов

            for(int j = 0; j < substrings[1].count(); j++)
                if(!substrings[1].isLower())
                    return false; //Ограничение может быть только в нижнем регистре

            //------------------------------------------------------------------------------------------------------

            if (regex1.match(strOneRule[i]).hasMatch())
            {

             if(strOneRule[i].count("[") != 1 && strOneRule[i].count("]") != 1)
                 return false; //[ ] должно быть по одному

             if(strOneRule[i].indexOf("]") + 2 != strOneRule[i].count() && strOneRule[i].count(".") == 0)
                 return false; //Неверный формат воода, после []" строка должна заканчиваться

             if(strOneRule[i].count(".") == 1 && strOneRule[i][strOneRule[i].indexOf("]") + 2] != ".")

                 return false; //Неверный формат воода, после []" строка должна заканчиваться
             //----------------------------------Проверка на то что в [] могут быть только определённые символы и определённое число пробелолв
             //----------------------------------и запятых и не может быть побел и запятая подряд--------------------------------------------
             int checkStart = strOneRule[i].indexOf('['); // ищем первый символ "["
             int checkEnd = strOneRule[i].indexOf(']'); // ищем первый символ "]"
             int position;

             position = checkStart + 1;

             if(checkEnd - checkStart == 1)
                 return false; //поле [..] не может быть пустым
             //Ситоит в следующих 2 if убрать условие strOneRecord[i][checkStart + 1].isSpace() т.к.

             if(strOneRule[i][checkStart + 1].isSpace() || !strOneRule[i][checkStart+ 1].isNumber())
                 return false; //если после [ идёт пробел или любой символ кроме числа

             if(strOneRule[i][checkEnd - 1].isSpace() || !strOneRule[i][checkEnd - 1].isNumber())
                 return false; //если перед ] идёт пробел или любой символ кроме числа

             while(strOneRule[i][position] != "]")
             {
                 if(!strOneRule[i][position].isNumber() && !strOneRule[i][position].isSpace() && strOneRule[i][position] != ",")
                     return false; //Не допускается использование между символами '[' и ']' всего, кроме 'пробела', ',' или цифр"


                 if(strOneRule[i][position].isSpace() && strOneRule[i][position + 1].isSpace())
                     return false; //"Ошибка! Не допускается между символами '[' и ']' использование больше одного 'пробела'"


                 if(strOneRule[i][position] == "," && strOneRule[i][position + 1] == ",")
                     return false; //"Ошибка! Не допускается между символами '[' и ']' использование больше одной запятой (',')"


                 if(strOneRule[i][position].isSpace() && strOneRule[i][position + 1] == ",")
                     return false; //"Ошибка! Не допускается между символами '[' и ']' использование после 'пробела' запятой (',')"


                 if(strOneRule[i][position + 1] != "]" && strOneRule[i][position].isNumber()
                         && !strOneRule[i][position + 1].isNumber() && strOneRule[i][position + 1] != ",")
                     return false; //"Ошибка! Между символами '[' и ']' после цифры должна стоять запятая (',')"

                 position ++;
             }
             //---------------------------------------------------------------------------------------------------------------------------------

             //------------------------------------------------------------------------------------------------------------------------------
             //-----------------------------------Проверка что в [ ] должны быть только цифры от 1 до 99
             int start = strOneRule[i].indexOf('['); // ищем первый символ "["
             int end = strOneRule[i].indexOf(']'); // ищем первый символ "]"

                 QString substring = strOneRule[i].mid(start + 1, end - start - 1); // вырезаем подстроку между скобками
                 QStringList values = substring.split(",", QString::SkipEmptyParts); // разделяем подстроку по запятой

                 //--------------

                 for (const QString& value : values)
                 {
                     bool ok;
                     int intValue = value.trimmed().toInt(&ok); // преобразуем строку в целое число
                     if (ok)
                         if(intValue < 1 || intValue > 99)
                             return false; //"Ошибка! Между символами '[' и ']' цифры должны лежать в диапазоне [1;99]"

                 }
             //-----------------------------------------------------------------------------------------------------------------------------------------
            }
            else if (regex2.match(strOneRule[i]).hasMatch())
            {
                if(strOneRule[i].lastIndexOf("\"") + 1 != strOneRule[i].count() && strOneRule[i].count(".") == 0)
                    return false; //Ошибка в написании (Больше чем шаблон)

                if(strOneRule[i].count(".") == 1 && strOneRule[i][strOneRule[i].lastIndexOf("\"") + 1] != ".")
                    return false; //Ошибка в написании (Больше чем шаблон)

                for(int j = 0; j < substrings[2].count(); j++)
                    if(!substrings[2][j].isNumber())
                        return false; //Можно использовать только цифры

                if(substrings[2].toInt() < 1 || substrings[2].toInt() > 99)
                    return false; //Нельзя чтобы число было меньше 1 и больше 99

            }
            else if (regex3.match(strOneRule[i]).hasMatch())
            {
                if(strOneRule[i].count("\"") != 4)
                    return false; //символов " должно быть 4

                if(strOneRule[i].lastIndexOf("и") + 1 != strOneRule[i].count() && strOneRule[i].lastIndexOf("м") + 1 != strOneRule[i].count()
                        && strOneRule[i].count(".") == 0)
                    return false; //Не соответствует шаблону

                if(strOneRule[i].count(".") == 1 && (strOneRule[i][strOneRule[i].lastIndexOf("и") + 1] != "."
                                                     || strOneRule[i][strOneRule[i].lastIndexOf("м") + 1] != "."))
                    return false; //Не соответсвует шаблону

                if (!strOneRule[i].contains("значением") && !strOneRule[i].contains("значениями"))
                    return false; //Нет слов значением или значениями

                //---------------------------ПОД ВОПРОСОМ НУЖНО ЛИ ЕСЛИ УЖЕ ЕСТЬ ШАБЛОН--------------------------------------
                QString value_1 = "одним";
                QString value_2 = "двумя";
                QString value_3 = "тремя";
                QString value_4 = "четырьмя";
                QString value_5 = "пятью";
                QString value_6 = "шестью";
                QString value_7 = "семью";
                QString value_8 = "восемью";
                QString value_9 = "девятью";

                if(!strOneRule[i].contains(value_1) && !strOneRule[i].contains(value_2) && !strOneRule[i].contains(value_3) &&
                        !strOneRule[i].contains(value_4) && !strOneRule[i].contains(value_5) && !strOneRule[i].contains(value_6) &&
                        !strOneRule[i].contains(value_7) && !strOneRule[i].contains(value_8) && !strOneRule[i].contains(value_9))
                return false; //Нет ни одного из доступных значений

                if(strOneRule[i].contains(value_1) && !strOneRule[i].contains("значением"))
                    return false; //одним должно быть в единственном числе

                if(!strOneRule[i].contains(value_1) && !strOneRule[i].contains("значениями"))
                    return false; //Должно быть во множественном числе

                if(strOneRule[i].count(value_1) > 1 || strOneRule[i].count(value_2) > 1 || strOneRule[i].count(value_3) > 1 ||
                        strOneRule[i].count(value_4) > 1 || strOneRule[i].count(value_5) > 1 || strOneRule[i].count(value_6) > 1 ||
                        strOneRule[i].count(value_7) > 1 || strOneRule[i].count(value_8) > 1 || strOneRule[i].count(value_9) > 1)
                    return false; //не может встречаться больше 1 из предложенных значений

                if(strOneRule[i].count("значением") > 1 || strOneRule[i].count("значениями") > 1)
                    return false; //НЕ может быть больше одного

                QStringList strLastValue = strOneRule[i].split(" ");

                if(strLastValue[strLastValue.count() - 1] != "значением" && strLastValue[strLastValue.count() - 1] != "значениями"
                        && strLastValue[strLastValue.count() - 1] != "значением." && strLastValue[strLastValue.count() - 1] != "значениями.")
                    return false; //НЕ заканчивается на значением

            }
            else if (regex4.match(strOneRule[i]).hasMatch())
            {
                if(strOneRule[i].count("\"") != 4)
                    return false; //символов " должно быть 4

                if(strOneRule[i].lastIndexOf("\"") + 1 != strOneRule[i].count() && strOneRule[i].count(".") == 0)
                    return false; //Ошибка в написании (Больше чем шаблон)

                if(strOneRule[i].count(".") == 1 && strOneRule[i][strOneRule[i].lastIndexOf("\"") + 1] != ".")
                    return false; //Ошибка в написании (Больше чем шаблон)
            }
        }
        else
            return false; // Не подошло ни по одному из шаблонов true только если проходит все проверки одного из шаблонов
    }

    return true;

}

QString checkRecords (const QString& strRecords)
{

    //QString strRecords = "Шкаф: цвет=[1,2], размер=[10,12,15];Стол:размер=[12, 15],цвет=[1,2,3],покрытие=[12].";

    // Проверка окончания строки на точку
    if (!strRecords.endsWith("."))
        return "Ошибка! Последняя запись должна оканчиваться на точку ('.')";

    if (strRecords.count(".") > 1)
        return "Ошибка! Точка ('.') может стоять только после последней записи";

    if (strRecords.count() < 10)
        return "Ошибка! Количество записей не может быть меньше 1. Допустимый диапазон: [1;100]";

    //Проверка на равенство ":" и ;"
    if(strRecords.count(":") != (strRecords.count(";") + 1))
        return "Ошибка! Количество названий записи должно быть равно количеству записей (название записи находится перед символом ':',"
               "а каждая запись разделена символом ';')";

    QStringList strOneRecord = strRecords.split(";", QString::SkipEmptyParts);

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

        //-----------------------------ПРОверка длинны и название записи--------------------------------------------------
        int lineLength = 0; //длина какой либо строки
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
            lineLength++;
        }
        if (lineLength < 3 || lineLength > 20)
            return "Ошибка! Название записи не может быть меньше трёх или больше двадцати символов"
                   "\nОшибка в записи: " + strOneRecord[i]; //Дляна названия записи

        lineLength = 0;



        //----------------------Проверка на то чтобы после ] стояла запятая без пробелов-----------------------------

        int lastIndex = strOneRecord[i].lastIndexOf(']');
        int commaIndex = strOneRecord[i].indexOf(',', lastIndex);
        bool isValid = true;

        if (commaIndex == -1)
        {
            // Проверка наличия символа "," после каждого символа "]"
            for (int j = 0; j < lastIndex; j++)
            {
                if (strOneRecord[i][j] == ']' && (i + 1 >= strOneRecord[i].length() || strOneRecord[i][j + 1] != ','))
                {
                    //isValid = false;
                    //break;
                    return "Ошибка! После каждого символа ']' должна стоять запятая (',')"
                           "\nОшибка в записи: " + strOneRecord[i];
                }
            }

            // Проверка отсутствия символа "," после последнего символа "]"
            if (lastIndex + 1 < strOneRecord[i].length() && strOneRecord[i][lastIndex + 1] == ',')
                //isValid = false;
                return "Ошибка! После последнего символа ']' может стоять только точка с запятой (';') или точка ('.')"
                       "\nОшибка в записи: " + strOneRecord[i];
        }
        else

            // Если найден символ "," после последнего символа "]", устанавливаем isValid в false
            //isValid = false;
            return "Ошибка! После последнего символа ']' может стоять только точка с запятой (';') или точка ('.')"
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
        foreach (const QString& entry, entries)
        {
            QString trimmedEntry = entry.trimmed();
            int equalsIndex = trimmedEntry.indexOf("=");

            if (equalsIndex != -1)
            {
                QString substring = trimmedEntry.mid(0, equalsIndex).trimmed();
                if(substring.count() < 3 || substring.count() > 20)
                    return "Ошибка! Название свойства записи не может быть меньше трёх или больше двадцати"
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
            }
        }

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
            }

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

        if(strOneRecord[i].lastIndexOf("]") < (strOneRecord[i].count() - 1) &&
                (strOneRecord[i][strOneRecord[i].lastIndexOf("]") + 1].isSpace() || strOneRecord[i][strOneRecord[i].lastIndexOf("]") + 1] == ","))
            return "Ошибка! после последнего свойства не может стоять 'пробел' или запятая (',')"
                   "\nОшибка в записи: " + strOneRecord[i];


        //Проверка на то чтобы формат свойст был верный
        QRegularExpression rex(",(?![^\\[]*\\])");
        QStringList parts = strOneRecord[i].split(rex, QString::SkipEmptyParts);

        parts[0] = parts[0].mid(parts[0].indexOf(":") + 1, parts[0].count() - 1);

        for (int j = 0; j < parts.count(); j++)
            if(parts[j].count("=") == 0)
                return "Ошибка! Свойство введено неверно. Вы ввели: \"" + parts[j] + "\"\nВерный формат: 'название свойства'=['целочисленные занчения']";
    }

    return "Всё хорошо!";
}

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

    QTextStream outStream(stdout);
         outStream.setCodec(QTextCodec::codecForName("cp866"));

        QList<Records> records;
        QList<ClassificationRules> rules;
        QList<Result> result;

        QString strRecords = "Шкаф: цвет=[1, 2], размер=[10,12,15];Стол: размер=[12, 15], цвет=[1, 15], покрытие=[12].";

        QString strRule = "Запись принадлежит классу «С покрытием», если у нее есть свойство «покрытие»;"
                          "Запись принадлежит классу «Объёмный», если у нее есть свойство «размер», которое представлено тремя значениями;"
                          "Запись принадлежит классу «Синий», если у нее есть свойство «цвет», в составе которого есть значение «1»;"
                          "Запись принадлежит классу «Матовый», если у нее есть свойство «покрытие» и значение этого свойства равно «[44, 21]».";

        //outStream << checkRecords(strRecords) << flush;

        qDebug() << checkClassificationRule(strRule);

        /*distributesRecords(strRecords, &records);
        distributesClassificationRules(strRule, &rules);
        classificationRecordsByRule(records, rules, &result);

        for(int i = 0; i < result.count(); i++)
        {
            outStream << result[i].getClassName() << ": " << flush;
            for(int j = 0; j < result[i].resultRecordName.count(); j++)
                outStream << result[i].resultRecordName[j] << ", " << flush;
            outStream << "\n\n" << flush;
        }*/

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

            /*distributesClassificationRules(strRule, &rules);

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
             }*/

    return a.exec();
}
