#include "ClassificationRules.h"

ClassificationRules::ClassificationRules()
{
    name = "";
    constraint = "";
}

QString ClassificationRules::checkClassificationRules(const QString& strRule)
{
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

    /*if(strRule.count() < 10)
            return "Ошибка! Количество правил не может быть меньше 1. Допустимый диапазон количества правил классификации: [1;100]";*/

    if (!strRule.endsWith("."))
        return "Ошибка! В конце текста правил классификации должна стоять точка ('.')"; //Если заканчивается не на точку

    if (strRule.count(".") > 1)
        return "Ошибка! В тексте правил может быть только одна точка ('.') и должна находится после последнего правила"; //Если больше одной точки

    const QStringList& strOneRule = strRule.split(";", QString::SkipEmptyParts);

    if(strOneRule.count() > 100)
        return "Ошибка! Количество записей не должно превышать 100. Допустимый диапазон: [1;100]";

    QList<QString> numberRuleName; //Проверка на совпадения названия классов (135 - substings; )

    for(int i = 0; i < strOneRule.count(); i++)
    {
        if(strOneRule[i][strOneRule[i].count() - 1] != "\"" && strOneRule[i][strOneRule[i].count() - 1] != "."
                && strOneRule[i][strOneRule[i].count() - 1] != "и" && strOneRule[i][strOneRule[i].count() - 1] != "м")
            return "Ошибка! Неверный формат ввода. Правило должно заканчиваться на следующие символы ('\" или '.' или 'и' или 'м')"
                   " в зависимости от типа правила."
                   "\nОшибка в правиле: " + strOneRule[i];  //Если последний символ не " не 'и' не .

        if(strOneRule[i][0].isSpace())
            return "Ошибка! Правило не может начинаться с пробела"
                   "\nОшибка в правиле: " + strOneRule[i]; //Первый символ не может быть пробелом

        for(int j = 0; j < strOneRule[i].count() - 1; j++)
            if(strOneRule[i][j].isSpace() && strOneRule[i][j + 1].isSpace())
                return "Ошибка! В тексте правила не допускается использовать больше одного пробела"
                       "\nОшибка в правиле: " + strOneRule[i]; //Нельзя больше одного пробела

        if(strOneRule[i].count("\"") != 4 && strOneRule[i].count("\"") != 6)
            return "Ошибка! В правиле должно быть либо 4, либо 6 кавычек ('\"') в зависимости от типа правила"
                   "\nОшибка в правиле: " + strOneRule[i]; // символов "" должно быть либо 4 либо 6

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
                    return "Ошибка! Внутри кавычек ('\"') текст не может начинаться и заканчиваться не буквой"
                           "\nВы ввели: " + substrings[j] +
                            "\nОшибка в правиле: " + strOneRule[i]; //нелья после " и перед " савить что-то кроме буквы

            if(substrings[0].count() < 3 || substrings[0].count() > 20)
                return "Ошибка! Название класса не может быть меньше трёх или больше двадцати символов"
                       "\nВы ввели: " + substrings[0] +
                        "\nОшибка в правиле: " + strOneRule[i]; //Название класса не может быть меньше 3 или больше 20

            if(substrings[1].count() < 3 || substrings[1].count() > 20)
                return "Ошибка! Текстовое ограничение правила не может быть меньше трёх или больше двадцати символов"
                       "\nВы ввели: " + substrings[1] +
                        "\nОшибка в правиле: " + strOneRule[i]; // Ограничение не может быть меньше 3 или больше 20

            if(!substrings[0][0].isUpper())
                return "Ошибка! Название класса должно начинаться с заглавной буквы"
                       "\nВы ввели " + substrings[0] +
                        "\nОшибка в правиле: " + strOneRule[i]; //Название класса начинается с заглавной буквы

            for(int j = 1; j < substrings[0].count(); j++)
                if(!substrings[0][j].isSpace() && substrings[0][j].isUpper())
                    return "Ошибка! В названии класса все буквы, кроме заглавной, должны быть в нижнем регистре"
                           "\nВы ввели: " + substrings[0] +
                            "\nОшибка в правиле: " + strOneRule[i]; //Все кроме заглавной буквы на названии класса должны быть в нижнем регистре

            for(int j = 0; j < substrings[0].count(); j++)
                if(!substrings[0][j].isLetter() && !substrings[0][j].isSpace())
                    return "Ошибка! В названии класса допускается использование только букв русского или английского алфавита "
                           "и пробелов (не больше одного подряд)"
                           "\nВы ввели: " + substrings[0] +
                            "\nОшибка в правиле: " + strOneRule[i]; //Название класса может содержать только буквы и пробел

            for(int j = 0; j < substrings[1].count(); j++)
                if(!substrings[1][j].isLetter() /*|| substrings[1][j].isSpace()*/)
                    return "Ошибка! Текстовое ограничение может содержать только буквы русского или английского алфавита и не должно содержать пробелы"
                           "\nВы ввели: " + substrings[1] +
                            "\nОшибка в правиле: " + strOneRule[i]; //Ограничение может содержать только буквы без пробелов

            for(int j = 0; j < substrings[1].count(); j++)
                if(!substrings[1].isLower())
                    return "Ошибка! Текстовое ограничение может содержать только буквы в нижнем регистре"
                           "\nВы ввели: " + substrings[1] +
                            "\nОшибка в правиле: " + strOneRule[i]; //Ограничение может быть только в нижнем регистре

            //------------------------------------------------------------------------------------------------------

            if (regex1.match(strOneRule[i]).hasMatch())
            {

                if(strOneRule[i].count("[") != 1 && strOneRule[i].count("]") != 1)
                    return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                           "\nДанный тип правила должен содержать по одному символу '[' и ']'"
                           "\nОшибка в правиле: " + strOneRule[i]; //[ ] должно быть по одному

                if(strOneRule[i].indexOf("]") + 2 != strOneRule[i].count() && strOneRule[i].count(".") == 0)
                    return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                           "\nДанный тип правила должен заканчиваться на ']\"'"
                           "\nОшибка в правиле: " + strOneRule[i]; //Неверный формат воода, после []" строка должна заканчиваться

                if(strOneRule[i].count(".") == 1 && strOneRule[i][strOneRule[i].indexOf("]") + 2] != ".")
                    return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                           "\nДанный тип правила должен заканчиваться на ']\".'"
                           "\nОшибка в правиле: " + strOneRule[i]; //Неверный формат воода, после []" строка должна заканчиваться


                //----------------------------------Проверка на то что в [] могут быть только определённые символы и определённое число пробелолв
                //----------------------------------и запятых и не может быть побел и запятая подряд--------------------------------------------
                int checkStart = strOneRule[i].indexOf('['); // ищем первый символ "["
                int checkEnd = strOneRule[i].indexOf(']'); // ищем первый символ "]"
                int position;

                position = checkStart + 1;

                if(checkEnd - checkStart == 1)
                    return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                           "\nПоле между символами '[' и ']' не должно быть пустым"
                           "\nОшибка в правиле: " + strOneRule[i]; //поле [..] не может быть пустым
                //Ситоит в следующих 2 if убрать условие strOneRecord[i][checkStart + 1].isSpace() т.к.

                if(strOneRule[i][checkStart + 1].isSpace() || !strOneRule[i][checkStart+ 1].isNumber())
                    return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                           "\nНе допускается сразу после символа '[' использование чего-либо, кроме цифр"
                           "\nОшибка в правиле: " + strOneRule[i]; //если после [ идёт пробел или любой символ кроме числа

                if(strOneRule[i][checkEnd - 1].isSpace() || !strOneRule[i][checkEnd - 1].isNumber())
                    return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                           "\nНе допускается сразу перед символом ']' использование чего-либо, кроме цифр"
                           "\nОшибка в правиле: " + strOneRule[i]; //если перед ] идёт пробел или любой символ кроме числа

                while(strOneRule[i][position] != "]")
                {
                    if(!strOneRule[i][position].isNumber() && !strOneRule[i][position].isSpace() && strOneRule[i][position] != ",")
                        return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                               "\nНе допускается использование между символами '[' и ']' всего, кроме 'пробела', ',' или цифр"
                               "\nОшибка в правиле: " + strOneRule[i]; //Не допускается использование между символами '[' и ']' всего, кроме 'пробела', ',' или цифр"


                    if(strOneRule[i][position].isSpace() && strOneRule[i][position + 1].isSpace())
                        return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                               "\nНе допускается между символами '[' и ']' использование больше одного 'пробела'"
                               "\nОшибка в правиле: " + strOneRule[i]; //"Ошибка! Не допускается между символами '[' и ']' использование больше одного 'пробела'"


                    if(strOneRule[i][position] == "," && strOneRule[i][position + 1] == ",")
                        return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                               "\nНе допускается между символами '[' и ']' использование больше одной запятой (',') подряд"
                               "\nОшибка в правиле: " + strOneRule[i]; //"Ошибка! Не допускается между символами '[' и ']' использование больше одной запятой (',')"


                    if(strOneRule[i][position].isSpace() && strOneRule[i][position + 1] == ",")
                        return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                               "\nНе допускается между символами '[' и ']' использование после 'пробела' запятой (',')"
                               "\nОшибка в правиле: " + strOneRule[i]; //"Ошибка! Не допускается между символами '[' и ']' использование после 'пробела' запятой (',')"


                    if(strOneRule[i][position + 1] != "]" && strOneRule[i][position].isNumber()
                            && !strOneRule[i][position + 1].isNumber() && strOneRule[i][position + 1] != ",")
                        return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                               "\nМежду символами '[' и ']' после цифры должна стоять запятая (',')"
                               "\nОшибка в правиле: " + strOneRule[i]; //"Ошибка! Между символами '[' и ']' после цифры должна стоять запятая (',')"

                    position ++;
                }
                //---------------------------------------------------------------------------------------------------------------------------------

                //------------------------------------------------------------------------------------------------------------------------------
                //-----------------------------------Проверка что в [ ] должны быть только цифры от 1 до 99
                int start = strOneRule[i].indexOf('['); // ищем первый символ "["
                int end = strOneRule[i].indexOf(']'); // ищем первый символ "]"

                QString substring = strOneRule[i].mid(start + 1, end - start - 1); // вырезаем подстроку между скобками
                QStringList values = substring.split(",", QString::SkipEmptyParts); // разделяем подстроку по запятой
                int numberValues = 0;
                //--------------

                for (const QString& value : values)
                {
                    bool ok;
                    int intValue = value.trimmed().toInt(&ok); // преобразуем строку в целое число
                    if (ok)
                        if(intValue < 1 || intValue > 99)
                            return "Ошибка! Неверный формат ввода правила с несколькими целочисленными ограничениями. "
                                   "\nМежду символами '[' и ']' цифры должны лежать в диапазоне [1;99]"
                                   "\nВы ввели: " + value.trimmed() +
                                    "\nОшибка в правиле: " + strOneRule[i]; //"Ошибка! Между символами '[' и ']' цифры должны лежать в диапазоне [1;99]"

                    numberValues++;
                }
                if(numberValues > 9)
                    return "Ошибка! Количество целочисленных значений между символами '[' и ']' должно быть от 1 до 9";
                //-----------------------------------------------------------------------------------------------------------------------------------------
            }
            else if (regex2.match(strOneRule[i]).hasMatch())
            {
                if(strOneRule[i].lastIndexOf("\"") + 1 != strOneRule[i].count() && strOneRule[i].count(".") == 0)
                    return "Ошибка! Неверный формат ввода правила с одним целочисленным значением. "
                           "\nПравило должно заканчиваться на ' \" '"
                           "\nОшибка в правиле: " + strOneRule[i]; //Ошибка в написании (Больше чем шаблон)

                if(strOneRule[i].count(".") == 1 && strOneRule[i][strOneRule[i].lastIndexOf("\"") + 1] != ".")
                    return "Ошибка! Неверный формат ввода правила с одним целочисленным значением. "
                           "\nПравило должно заканчиваться на ' \". '"
                           "\nОшибка в правиле: " + strOneRule[i]; //Ошибка в написании (Больше чем шаблон)

                for(int j = 0; j < substrings[2].count(); j++)
                    if(!substrings[2][j].isNumber())
                        return "Ошибка! Неверный формат ввода правила с одним целочисленным значением. "
                               "\nМежду последними двумя символами ' \" ' должно быть целочисленное значение и только одно"
                               "\nВы ввели: " + substrings[2] +
                                "\nОшибка в правиле: " + strOneRule[i]; //Можно использовать только цифры

                if(substrings[2].toInt() < 1 || substrings[2].toInt() > 99)
                    return "Ошибка! Неверный формат ввода правила с одним целочисленным значением. "
                           "\nЦелочисленное значение должно лежать в диапазоне [1;99]"
                           "\nВы ввели: " + substrings[2] +
                            "\nОшибка в правиле: " + strOneRule[i]; //Нельзя чтобы число было меньше 1 и больше 99

            }
            else if (regex3.match(strOneRule[i]).hasMatch())
            {
                if(strOneRule[i].count("\"") != 4)
                    return "Ошибка! Неверный формат ввода правила с допустимым количеством целочисленных значений записи"
                           "\nКоличество символов ' \" ' должно быть равно четырём"
                           "\nОшибка в правиле: " + strOneRule[i]; //символов " должно быть 4

                if(strOneRule[i].lastIndexOf("и") + 1 != strOneRule[i].count() && strOneRule[i].lastIndexOf("м") + 1 != strOneRule[i].count()
                        && strOneRule[i].count(".") == 0)
                    return "Ошибка! Неверный формат ввода правила с допустимым количеством целочисленных значений записи"
                           "\nПравило должно заканичиваться на 'м' или 'и', в зависимости от указанного значения (одним) или (двумя - девятью)"
                           "\nОшибка в правиле: " + strOneRule[i]; //Не соответствует шаблону

                if(strOneRule[i].count(".") == 1 && strOneRule[i][strOneRule[i].lastIndexOf("и") + 1] != "."
                        && strOneRule[i][strOneRule[i].lastIndexOf("м") + 1] != ".")
                    return "Ошибка! Неверный формат ввода правила с допустимым количеством целочисленных значений записи"
                           "\nПравило должно заканичиваться на 'м.' или 'и.', в зависимости от указанного значения (одним) или (двумя - девятью)"
                           "\nОшибка в правиле: " + strOneRule[i]; //Не соответсвует шаблону

                if (!strOneRule[i].contains("значением") && !strOneRule[i].contains("значениями"))
                    return "Ошибка! Неверный формат ввода правила с допустимым количеством целочисленных значений записи"
                           "\nОтсутствует слово 'значением' или 'значениями', в зависимости от указанного значения (одним) или (двумя - девятью)"
                           "\nОшибка в правиле: " + strOneRule[i]; //Нет слов значением или значениями

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
                    return "Ошибка! Неверный формат ввода правила с допустимым количеством целочисленных значений записи"
                           "\nНеверно указано количество допустимых значений в записи."
                           "\nДопустимы следующие значения: " + value_1 + ", " + value_2 + ", " + value_3 + ", " + value_4 + ", " + value_5 + ", "
                            + value_6 + ", " + value_7 + ", " + value_8 + ", " + value_9 +
                            "\nОшибка в правиле: " + strOneRule[i]; //Нет ни одного из доступных значений

                if(strOneRule[i].contains(value_1) && !strOneRule[i].contains("значением"))
                    return "Ошибка! Неверный формат ввода правила с допустимым количеством целочисленных значений записи"
                           "\nЕсли было введено 'одним', то правило должно заканчиваться на 'значением'"
                           "\nОшибка в правиле: " + strOneRule[i]; //одним должно быть в единственном числе

                if(!strOneRule[i].contains(value_1) && !strOneRule[i].contains("значениями"))
                    return "Ошибка! Неверный формат ввода правила с допустимым количеством целочисленных значений записи"
                           "\nЕсли было введено ('двумя' - 'девятью'), то правило должно заканчиваться на 'значениями'"
                           "\nОшибка в правиле: " + strOneRule[i]; //Должно быть во множественном числе

                if(strOneRule[i].count(value_1) > 1 || strOneRule[i].count(value_2) > 1 || strOneRule[i].count(value_3) > 1 ||
                        strOneRule[i].count(value_4) > 1 || strOneRule[i].count(value_5) > 1 || strOneRule[i].count(value_6) > 1 ||
                        strOneRule[i].count(value_7) > 1 || strOneRule[i].count(value_8) > 1 || strOneRule[i].count(value_9) > 1)
                    return "Ошибка! Неверный формат ввода правила с допустимым количеством целочисленных значений записи"
                           "\nОграничение по количеству целочисленных значений записи должно быть представлено единственным значением"
                           "\nОшибка в правиле: " + strOneRule[i]; //не может встречаться больше 1 из предложенных значений

                if(strOneRule[i].count("значением") > 1 || strOneRule[i].count("значениями") > 1)
                    return "Ошибка! Неверный формат ввода правила с допустимым количеством целочисленных значений записи"
                           "\nПравило должно содержать одно слово 'значением' или 'значениями'"
                           "\nОшибка в правиле: " + strOneRule[i]; //НЕ может быть больше одного

                if((strOneRule[i].count("значением") == 1 && strOneRule[i].count("значениями") != 0)
                        || (strOneRule[i].count("значением") != 0 && strOneRule[i].count("значениями") == 1))
                    return "Ошибка! Неверный формат ввода правила с допустимым количеством целочисленных значений записи"
                           "\nПравило должно содержать одно слово 'значением' или 'значениями'"
                           "\nОшибка в правиле: " + strOneRule[i]; //НЕ может быть больше одного


                QStringList strLastValue = strOneRule[i].split(" ");

                if(strLastValue[strLastValue.count() - 1] != "значением" && strLastValue[strLastValue.count() - 1] != "значениями"
                        && strLastValue[strLastValue.count() - 1] != "значением." && strLastValue[strLastValue.count() - 1] != "значениями.")
                    return "Ошибка! Неверный формат ввода правила с допустимым количеством целочисленных значений записи"
                           "\nПравило должно заканчиваться на слово 'значением' или 'значениями'"
                           "\nОшибка в правиле: " + strOneRule[i]; //НЕ заканчивается на значением

            }
            else if (regex4.match(strOneRule[i]).hasMatch())
            {
                if(strOneRule[i].count("\"") != 4)
                    return "Ошибка! Неверный формат ввода правила без дополнительного целочисленного ограничения"
                           "\nКоличество символов ' \" ' должно быть равно четырём"
                           "\nОшибка в правиле: " + strOneRule[i]; //символов " должно быть 4

                if(strOneRule[i].lastIndexOf("\"") + 1 != strOneRule[i].count() && strOneRule[i].count(".") == 0)
                    return "Ошибка! Неверный формат ввода правила без дополнительного целочисленного ограничения"
                           "\nПравило должно заканчиваться на символ ' \" '"
                           "\nОшибка в правиле: " + strOneRule[i]; //Ошибка в написании (Больше чем шаблон)

                if(strOneRule[i].count(".") == 1 && strOneRule[i][strOneRule[i].lastIndexOf("\"") + 1] != ".")
                    return "Ошибка! Неверный формат ввода правила без дополнительного целочисленного ограничения"
                           "\nПравило должно заканчиваться на символ ' \". '"
                           "\nОшибка в правиле: " + strOneRule[i]; //Ошибка в написании (Больше чем шаблон)
            }



            //-------------------------------Заполнение QList названием правил (QList перед первым циклом for)---------------------------
            numberRuleName.append(substrings[0]);
            //-----------------------------------------------------------------------------------------------------------------------------


        }
        else
            return "Ошибка! Неверный формат ввода правила"
                   "\nОшибка в правиле: " + strOneRule[i] +
                    "\nДопустимые форматы: "
                    "\n1) 'Запись принадлежит классу \"<название класса>\", если у нее есть свойство \"<название свойства>\"'"
                    "\n2) 'Запись принадлежит классу \"<название класса>\", если у нее есть свойство \"<название свойства>\", которое представлено ([одним|двумя|тремя|четырьмя|пятью|шестью|семью|восемью|девятью]) значением(ями)'"
                    "\n3) 'Запись принадлежит классу \"<название класса>\", если у нее есть свойство \"<название свойства>\", в составе которого есть значение \"<одно целочисленное значение>\"'"
                    "\n4) 'Запись принадлежит классу \"<название класса>\", если у нее есть свойство \"<название свойства>\" и значение этого свойства равно \"[целочисленные значения через ',']\"'";
        // Не подошло ни по одному из шаблонов true только если проходит все проверки одного из шаблонов
    }

    //-------------------------------Проверка чтобы названия правил не совпадали---------------------------------------------------
    for (int i = 0; i < numberRuleName.count(); ++i)
    {
        const QString& currentString = numberRuleName[i];
        for (int j = i + 1; j < numberRuleName.count(); ++j)
        {
            const QString& otherString = numberRuleName[j];
            if (currentString == otherString)
            {
                return "Ошибка! Названия классов не могут повторяться"
                       "\nНазвание класса: \"" + currentString + "\""; // Найдено повторяющиеся строки
            }
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------


    //---------------------------------Проверка чтобы не было одинаковых правил---29-------------------------------------------------------
    for(int i = 0; i < strOneRule.count(); ++i)
    {
        QString currentString = strOneRule[i].mid(strOneRule[i].indexOf("\"", 29) + 1);
        currentString.remove(" ");
        if(currentString.count(".") != 0)
            currentString.remove(".");

        for(int j = i + 1; j < strOneRule.count(); ++j)
        {
            QString otherString = strOneRule[j].mid(strOneRule[j].indexOf("\"", 29) + 1);
            otherString.remove(" ");
            if(otherString.count(".") != 0)
                otherString.remove(".");

            if (currentString == otherString)
                return "Ошибка! Условия классификации не могут повторяться"
                       "\nУсловие классификации: \"" + strOneRule[i].mid(strOneRule[i].indexOf("\"", 29) + 3) + "\""; // Найдено повторяющиеся строки
        }
    }
    //----------------------------------------------------------------------------------------------------------------------------------------------

    return "Всё хорошо!";

}

QString ClassificationRules::splitStringOfClassificationRules(const QString& rulesData, QList<ClassificationRules>* classificationRules)
{

    ClassificationRules checkRules;
    QString errRule = checkRules.checkClassificationRules(rulesData);

    if(!errRule.contains("Всё хорошо!"))
        return errRule;
    else
    {
        QStringList substringsRules = rulesData.split(";");

        for(int i = 0; i < substringsRules.count(); i++)
        {
            ClassificationRules newRule;
            //ClassificationRules *newRule = new ClassificationRules;

            QRegExp classRx("\"([^\"]+)\""); // находим слова внутри кавычек \" \"
            QRegExp propertyRx("свойство \"([^\"]+)\""); // находим слова после слова "свойство \"" и до закрывающей кавычки

            int classPos = classRx.indexIn(substringsRules[i]);
            if (classPos != -1)
                newRule.name = classRx.cap(1);

            int propertyPos = propertyRx.indexIn(substringsRules[i]);
            if (propertyPos != -1)
                newRule.constraint = propertyRx.cap(1);


            QString withLength = "которое представлено";
            QString singleValue = "в составе которого есть значение";
            QString severalValues = "и значение этого свойства равно";

            if(substringsRules[i].contains(withLength))
            {
                newRule.condition = propertyWithLength;

                if(substringsRules[i].contains("одним"))
                    newRule.limitValue = Single;
                else if(substringsRules[i].contains("двумя"))
                    newRule.limitValue = Two;
                else if(substringsRules[i].contains("тремя"))
                    newRule.limitValue = Three;
                else if(substringsRules[i].contains("четырьмя"))
                    newRule.limitValue = Four;
                else if(substringsRules[i].contains("пятью"))
                    newRule.limitValue = Five;
                else if(substringsRules[i].contains("шестью"))
                    newRule.limitValue = Six;
                else if(substringsRules[i].contains("семью"))
                    newRule.limitValue = Seven;
                else if(substringsRules[i].contains("восемью"))
                    newRule.limitValue = Eight;
                else if(substringsRules[i].contains("девятью"))
                    newRule.limitValue = Nine;
            }
            else if(substringsRules[i].contains(singleValue))
            {
                newRule.condition = propertySingleValue;
                newRule.limitValue = NotQuantity;

                QRegExp rxValue("(\\d+)");
                int pos = 0;
                while ((pos = rxValue.indexIn(substringsRules[i], pos)) != -1) //НЕ НУЖЕН WHILE!!!!!!!!!!!!!!!!!!!!!!!!
                {
                    newRule.integerValues.append(rxValue.cap(1).toInt());
                    pos += rxValue.matchedLength();
                }

                //newRule->integerValues.append(newRule->getIntegerValues());
            }
            else if(substringsRules[i].contains(severalValues))
            {
                newRule.condition = propertyWithSeveralValues;
                newRule.limitValue = NotQuantity;

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
                        newRule.integerValues.append(intValue);// выводим полученные значения
                    }
                }
            }
            else
            {
                newRule.condition = propertyWithNoValue;
                newRule.limitValue = NotQuantity;
            }
            classificationRules->append(newRule);
            //delete newRule;
        }
        return errRule;
    }
}

ConditionType ClassificationRules::getCondition()
{
    return this -> condition;
}

LimitationIntegerValues ClassificationRules::getLimitValue()
{
    return this -> limitValue;
}

QString ClassificationRules::getName()
{
    return this -> name;
}

QString ClassificationRules::getConstraint()
{
    return this -> constraint;
}

QList<int> ClassificationRules::getIntegerValues()
{
    return this -> integerValues;
}
