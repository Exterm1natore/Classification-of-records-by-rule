#include "Records.h"

Records::Records()
{
    name = "";
}

void Records::splitStringOfRecords(const QString& recordsData, QList<Records>* record)
{
    Records checkRecords; // создаём переменную класса Records

    // запускаем функцию по проверке текста записей
    checkRecords.checkRecords(recordsData);

    // делим текст записей по символу точка с запятой (';')
    QStringList substringsRecords = recordsData.split(";");

    // Для каждой записи
    for(int i = 0; i < substringsRecords.count(); i++)
    {
        Records newRecord; // создаём переменную класса Records
        newRecord.name = substringsRecords[i].mid(0, substringsRecords[i].indexOf(":")); // записывваем название записи

        /* регулярное выражение которое ищет символы после символа ':' и между символами '='  и '[', исключая текст внутри
              '[' ']' и их самих (выбирает только названия свойств)*/
        QRegExp rxPropertes("([^ ,:]+)\\s*=");
        int pos = 0; // индекс символа в строке
        int start = substringsRecords[i].indexOf('['); // ищем первый символ '['
        int end = substringsRecords[i].indexOf(']'); // ищем первый символ ']'

        // Пока есть свойства у записи
        while((pos = rxPropertes.indexIn(substringsRecords[i], pos)) != -1)
        {
            QList<int> integerValues; // контейнер в который записываются целочисленные значения свойства

            // получаем название свойства
            QString propertes = rxPropertes.cap(1);

            // увеличение позиции на длину последнего совпадения регулярного выражения
            pos += rxPropertes.matchedLength();

            // вырезаем подстроку между скобками
            QString substring = substringsRecords[i].mid(start + 1, end - start - 1);

            // разделяем подстроку по запятой
            QStringList values = substring.split(",", QString::SkipEmptyParts);

            // Для каждого символа внутри '[' ']'
            for (const QString& value : values)
            {
                bool ok; // флаг удачности преобразования в целое число
                int intValue = value.trimmed().toInt(&ok); // преобразуем строку в целое число

                // Если преобразование в целое число прошло удачно
                if (ok)
                {
                    // записываем его в контейнер целочисленных значений свойства
                    integerValues.append(intValue);
                }
            }

            start = substringsRecords[i].indexOf('[', end); // ищем следующий символ '['
            end = substringsRecords[i].indexOf(']', end + 1); // ищем следующий символ ']'

            // записывает найденное свойства и соответствующие ему целочисленные значения в контейнер
            newRecord.relatedIntegerValues.insert(propertes, integerValues);
        }
        record->append(newRecord); // записываем полученные значения в контейнер класса Records
    }
}

void Records::checkRecords (const QString& strRecords)
{
    QString emptyStr = strRecords.trimmed(); // удаляем лишние пробелы в начале и конце текста записей

    // Если текст записей пуст
    if(emptyStr.isEmpty())
    {
        throw QString ("Текст записей:\nОшибка! Файл с входными данными записей является пустым.");
    }

    // Если входной текст записей не заканчивается на точку
    if (!strRecords.endsWith("."))
    {
        throw QString ("Текст записей:\nОшибка! В конце текста записей должна стоять точка ('.').");
    }

    // Если во входном тексте записей больше одной точки
    if (strRecords.count(".") > 1)
    {
        throw QString ("Текст записей:\nОшибка! В тексте записей может быть только одна точка ('.'), которая должна находится после последней записи"
                       "\nНомер ошибочного символа в тексте с записями: " + QString::number(strRecords.indexOf(".") + 1));
    }

    //--------------------------Блок проверки что во входном тексте записей внутри '[' ']' не стоит ';' (конкретизация вероятной ошибки)----
    int checkStart = strRecords.indexOf('['); // ищем первый символ '['
    int checkEnd = strRecords.indexOf(']'); // ищем первый символ ']'

    // Пока есть символы '[' и ']'
    while (checkStart != -1 && checkEnd != -1 && checkEnd > checkStart && strRecords.count("[") == strRecords.count("]"))
    {
        int position = checkStart + 1; // переменная следующего индекса в тексте после '['

        // Пока не внутри '[' ']'
        while(strRecords[position] != "]")
        {

            // Если встретилась точка с запятой вернуть ошибку
            if(strRecords[position] == ";")
            {
                throw QString ("Текст записей:\nОшибка! Между символами \'[ ]\' цифры не могут раздиляться точкой с запятой \';\'."
                               "\nНомер ошибочного символа в тексте с записями: " + QString::number(position + 1));
            }

            position ++; // перейти к следующему символу
        }
        checkStart = strRecords.indexOf('[', checkEnd); // ищем следующий символ '['
        checkEnd = strRecords.indexOf(']', checkEnd + 1); // ищем следующий символ ']'
    }
    //--------------------------------------------------------------------------------------------------------------------------------------

    // Если в тексте количество символов ':' не равно количеству символов (';' + 1) (количество названий записей = количеству записей)
    if(strRecords.count(":") != (strRecords.count(";") + 1))
    {
        throw QString ("Текст записей:\nОшибка! Количество названий записи должно быть равно количеству записей. "
                       "\nУ записи должно быть название и притом только одно"
                       "(название записи находится перед символом ':', а каждая запись разделена символом ';', после последней ставится точка '.').");
    }

    const QStringList& strOneRecord = strRecords.split(";", QString::SkipEmptyParts); // разделить текст записей по символу ';'

    // Если записей больше 100
    if(strOneRecord.count() > 100)
    {
        throw QString ("Текст записей:\nОшибка! Количество записей не может быть больше 100. Допустимый диапазон: [1;100].");
    }

    // Для каждой записи (записи разделены символом ';')
    for(int i = 0; i < strOneRecord.count(); i++)
    {
        // Если количество символов ':' не равно одному
        if(strOneRecord[i].count(":") != 1)
        {
            throw QString ("Текст записей:\nОшибка! У записи может быть только одно название (название записи находится перед символом ':')."
                           "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
        }

        // Если количество '[' не равно количеству ']'
        if(strOneRecord[i].count("[") != strOneRecord[i].count("]"))
        {
            throw QString ("Текст записей:\nОшибка! У свойства записи целочисленные значения записываются между '[' и ']' (количество '[' и ']' дожно совпадать)."
                           "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
        }

        // Если количество символов '=' не равно количеству '['
        if (strOneRecord[i].count("=") != strOneRecord[i].count("["))
        {
            throw QString ("Текст записей:\nОшибка! У записи каждому названию свойства соответствуют целочисленные значения которые соотносятся символом '=' "
                           "(количество символов '=' и '[', ']' должно совпадать)."
                           "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
        }

        // Если количество свойств больше 20
        if(strOneRecord[i].count("=") > 20)
        {
            throw QString ("Текст записей:\nОшибка! У записи не может быть больше 20 свойств (каждое свойство соотносится символом равно '=')."
                           "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
        }

        // Если в записи нет ни одного свойства (количество '=' = 0, перед ':' есть символы и строка не начинается с пробела)
        if(strOneRecord[i].count("=") == 0 && strOneRecord[i].indexOf(":") > 2 && !strOneRecord[i][0].isSpace())
        {
            throw QString ("Текст записей:\nОшибка! Запись должна имень хотя бы одно свойство."
                           "\n<название записи>: <название свойства>=[<целочисленные значения>], ... , <название свойства>=[<целочисленные значения>];"
                           "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
        }

        // Если запись не начинается с названия
        if(strOneRecord[i].lastIndexOf(":") > strOneRecord[i].indexOf("=") || strOneRecord[i].lastIndexOf(":") > strOneRecord[i].indexOf("[")
                || strOneRecord[i].lastIndexOf(":") > strOneRecord[i].indexOf("]"))
        {
            throw QString ("Текст записей:\nОшибка! Запись должна начинаться с названия."
                           "\nНазвание записи состоит только из букв русского или ангийского алфавита (иные символы недопустимы)."
                           "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
        }

        int lineLength = 0; // длина названия записи

        // Для каждого символа названия записи (с начала строки и до символа ':')
        for(int j = 0; strOneRecord[i][j] != ":"; j++)
        {
            // Если в названии записи встретилась не буква
            if(!strOneRecord[i][j].isLetter())
            {
                throw QString ("Текст записей:\nОшибка! В названии записи допускаются лишь буквы русского или английсского алфавита."
                               "\nВы ввели: \"" + strOneRecord[i].mid(0, strOneRecord[i].indexOf(":"))
                               + "\"\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }

            // Если первая буква названия записи не заглавная
            if(!strOneRecord[i][0].isUpper())
            {
                throw QString ("Текст записей:\nОшибка! Название записи должно начинаться с заглавной буквы."
                               "\nВы ввели: \"" + strOneRecord[i].mid(0, strOneRecord[i].indexOf(":"))
                               + "\"\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }

            // Если последующие после первой буквы в названии записи не в нижнем регистре
            if(j > 0 && !strOneRecord[i][j].isLower())
            {
                throw QString ("Текст записей:\nОшибка! В названии записи все буквы, кроме первой должны быть в нижнем регистре."
                               "\nВы ввели: \"" + strOneRecord[i].mid(0, strOneRecord[i].indexOf(":"))
                               + "\"\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }

            lineLength++; // инкрементируем длину название записи
        }

        // Если название записи меньше 3 или больше 20 символов
        if (lineLength < 3 || lineLength > 20)
        {
            throw QString ("Текст записей:\nОшибка! Название записи не может быть меньше трёх или больше двадцати символов."
                           "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
        }

        int lastIndex = strOneRecord[i].lastIndexOf(']'); // индекс последнего символа ']'

        // Для каждого символа строки до последнего символа ']'
        for (int j = 0; j < lastIndex; j++)
        {
            // Если после символа ']' не стоит запятая
            if(strOneRecord[i][j] == "]" && strOneRecord[i][j + 1] != ',')
            {
                throw QString ("Текст записей:\nОшибка! После каждого символа ']', кроме последнего, должна стоять запятая ','."
                               "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }
        }

        // Для каждого символа записи кроме последнего
        for(int j = 0; j < strOneRecord[i].count() - 1; j++)
        {
            // Если после символа '=' не стоит '['
            if(strOneRecord[i][j] == "=" && strOneRecord[i][j + 1] != "[")
            {
                throw QString ("Текст записей:\nОшибка! После символа '=' должен стоять символ '['."
                               "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }

            // Если перед символом '[' не стоит '='
            else if(strOneRecord[i][j] == "[" && strOneRecord[i][j - 1] != "=" && j > 0)
            {
                throw QString ("Текст записей:\nОшибка! Перед символом '[' должен стоять символ '='."
                               "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }

            // Если название записи начинается с символа '='
            if(strOneRecord[i][0] == "=")
            {
                throw QString ("Текст записей:\nОшибка! Строка должна начинаться с названия записи и не может начинаться с '='."
                               "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }

            // Иначе если перед символом '=' стоит не буква
            else if(strOneRecord[i][j] == "=" && !strOneRecord[i][j-1].isLetter())
            {
                throw QString ("Текст записей:\nОшибка! Перед символом '=' должно идти название свойства записи."
                               "\nНазвание состоит только из букв русского или английского алфавита "
                               "(другие символы межу названием записи и символом '=' недопускаются)."
                               "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }
        }

        //----------------------------Блок проверки названий свойств записи---------------------------------------------------------------
        QStringList entries = strOneRecord[i].split(QRegExp("[:,]")); // Разбиваем строку по символам ":" и ","
        QList<QString> listProperties; // контейнер, хранящий названия свойств одной записи для проверки на совпадение

        // Для каждого элемента массива entries
        foreach (const QString& entry, entries)
        {
            QString trimmedEntry = entry.trimmed(); // удаляем лишние пробелы по краям
            int equalsIndex = trimmedEntry.indexOf("="); // индекс первого символа '='

            // Если в элементе массива присутствует символ '=' (то это название свойства)
            if (equalsIndex != -1)
            {
                QString substring = trimmedEntry.mid(0, equalsIndex).trimmed(); // получаем подстроку состоящую только из названия свойства

                // Если длина подстроки меньше 3 или больше 20
                if(substring.count() < 3 || substring.count() > 20)
                {
                    throw QString ("Текст записей:\nОшибка! Название свойства записи не может быть меньше трёх или больше двадцати символов."
                                   "\nВы ввели: \"" + substring +
                                   "\"\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                }

                // Для каждого символа подстроки
                for(int j = 0; j < substring.count(); j++)
                {
                    // Если в названии свойства присутствуют не только буквы
                    if(!substring[j].isLetter())
                    {
                        throw QString ("Текст записей:\nОшибка! В названии свойства записи допускаются лишь буквы русского или английсского алфавита."
                                       "\nВы ввели: \"" + substring +
                                       "\"\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                    }

                    // Если в названии свойства присутствуют буквы в верхнем регистре
                    if (!substring[j].isLower())
                    {
                        throw QString ("Текст записей:\nОшибка! В названии свойства записи не допускается использовать верхний регистр."
                                       "\nВы ввели: \"" + substring +
                                       "\"\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                    }
                }
                listProperties.append(substring); // добавляем название свойства в контейнер для проверки на совпадения
            }
        }
        //--------------------------------------------------------------------------------------------------------------------------------
        //--------------------------------Блок проверки совпадений свойств одной записи---------------------------------------------------
        // Для каждого названия свойства записи
        for (int j = 0; j < listProperties.size(); ++j)
        {
            const QString& currentString = listProperties.at(j); // получаем название свойства записи по индексу j

            // Для каждого названия свойства записи следующего после текущего
            for (int k = j + 1; k < listProperties.size(); ++k)
            {
                const QString& otherString = listProperties.at(k); // получаем название свойства записи по индексу k

                // Если названия свойств совпали
                if (currentString == otherString)
                {
                    throw QString ("Текст записей:\nОшибка! В одной записи названия свойств не могут повторяться."
                                   "\nНазвание свойства: \"" + currentString +
                                   "\"\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                }
            }
        }
        //--------------------------------------------------------------------------------------------------------------------------------
        //--------------------------------Блок проверки символов внутри '[' ']'-----------------------------------------------------------
        int checkStart = strOneRecord[i].indexOf('['); // ищем первый символ '['
        int checkEnd = strOneRecord[i].indexOf(']'); // ищем первый символ ']'
        int position; // индекс символа в строке

        // Пока есть скобки ('[' ']') в строке
        while (checkStart != -1 && checkEnd != -1 && checkEnd > checkStart)
        {
            position = checkStart + 1; // индекс равен следующему символу после '['

            // Если между '[' ']' ничего нет (стоят рядом)
            if(checkEnd - checkStart == 1)
            {
                throw QString ("Текст записей:\nОшибка! Поле между символами '[' и ']' не должно быть пустым "
                               "(должно содеражть от 1 до 9 чисел, разделённых запятой \',\')."
                               "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }

            // Если следующий символ после ']' не цифра
            if(!strOneRecord[i][checkStart + 1].isNumber())
            {
                throw QString ("Текст записей:\nОшибка! Не допускается сразу после символа '[' использование чего-либо, кроме цифр."
                               "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }

            // Если предыдущий символ перед '[' не цифра
            if(!strOneRecord[i][checkEnd - 1].isNumber())
            {
                throw QString ("Текст записей:\nОшибка! Не допускается сразу перед символом ']' использование чего-либо, кроме цифр."
                               "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }

            // Пока символ строки не будет равен ']'
            while(strOneRecord[i][position] != "]")
            {
                // Если между '[' ']' есть что-то кроме цифр, пробела и запятой
                if(!strOneRecord[i][position].isNumber() && !strOneRecord[i][position].isSpace() && strOneRecord[i][position] != ",")
                {
                    throw QString ("Текст записей:\nОшибка! Не допускается использование между символами '[' и ']' всего, кроме 'пробела', ',' или цифр."
                                   "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                }

                // Если между '[' ']' стоит больше 1 пробела
                if(strOneRecord[i][position].isSpace() && strOneRecord[i][position + 1].isSpace())
                {
                    throw QString ("Текст записей:\nОшибка! Не допускается между символами '[' и ']' использование больше одного 'пробела' подряд."
                                   "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                }

                // Если между '[' ']' стоит боьлше 1 запятой подряд
                if(strOneRecord[i][position] == "," && strOneRecord[i][position + 1] == ",")
                {
                    throw QString ("Текст записей:\nОшибка! Не допускается между символами '[' и ']' использование больше одной запятой (',') подряд."
                                   "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                }

                // Если после пробела идёт запятая (',')
                if(strOneRecord[i][position].isSpace() && strOneRecord[i][position + 1] == ",")
                {
                    throw QString ("Текст записей:\nОшибка! Не допускается между символами '[' и ']' использование после 'пробела' запятой (',')."
                                   "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                }

                // Если числа между '[' ']' разделены не запятой а другим символом
                if(strOneRecord[i][position + 1] != "]" && strOneRecord[i][position].isNumber()
                        && !strOneRecord[i][position + 1].isNumber() && strOneRecord[i][position + 1] != ",")
                {
                    throw QString ("Текст записей:\nОшибка! Между символами '[' и ']', после числа, должна стоять запятая (',')."
                                   "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                }

                position ++; // инкрементируем позицию в строке
            }
            checkStart = strOneRecord[i].indexOf('[', checkEnd); // ищем следующий символ '['
            checkEnd = strOneRecord[i].indexOf(']', checkEnd + 1); // ищем следующий символ ']'
        }

        int start = strOneRecord[i].indexOf('['); // ищем первый символ '['
        int end = strOneRecord[i].indexOf(']'); // ищем первый символ ']'

        // Пока есть скобки ('[' ']') в строке
        while (start != -1 && end != -1 && end > start)
        {
            QString substring = strOneRecord[i].mid(start + 1, end - start - 1); // вырезаем подстроку между скобками
            QStringList values = substring.split(",", QString::SkipEmptyParts); // разделяем подстроку по запятой
            int numberValues = 0; // количество целочисленных значений внутри одной пары '[' ']'

            // Для каждого элемента массива values
            for (const QString& value : values)
            {
                bool ok; // флаг удачности преобразования в целое число
                int intValue = value.trimmed().toInt(&ok); // преобразуем строку в целое число

                // Если успешно преобразовали в целое число
                if (ok)
                {
                    // Если число между '[' ']' меньше 1 или больше 99
                    if(intValue < 1 || intValue > 99)
                    {
                        throw QString ("Текст записей:\nОшибка! Между символами '[' и ']' числа должны лежать в диапазоне [1;99]."
                                       "\nВы ввели: \"" + value.trimmed() +
                                       "\"\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                    }

                    numberValues++; // инкрементируем количество целочисленных значений
                }
            }

            // Для каждого элемента массива values
            for(const QString& value : values)
            {
                QString valInt = value.trimmed(); // удаляем начальные пробелы из подстроки

                // Если длина числа (почимвольно) больше 2 или в ней присутствует 0
                if(valInt.count() > 2 || valInt[0] == '0')
                {
                    throw QString ("Текст записей:\nОшибка! Целочисленные значения должны лежать в диапазоне [1;99] (0 перед числом писать нельзя). "
                                   "\nВы ввели: " + valInt +
                                   "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                }
            }

            // Если количество целочисленных значений внутри '[' ']' больше 9
            if(numberValues > 9)
            {
                throw QString ("Текст записей:\nОшибка! Количество целочисленных значений между символами '[' и ']' должно быть от 1 до 9."
                               "\nВы ввели " + QString::number(numberValues) +
                               " значений.\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }

            start = strOneRecord[i].indexOf('[', end); // ищем следующий символ '['
            end = strOneRecord[i].indexOf(']', end + 1); // ищем следующий символ ']'
        }
        //--------------------------------------------------------------------------------------------------------------------------------

        // Для каждого элемента до первой буквы (не больше длины строки - 1), начиная с следующего символа после ':'
        for(int j = (strOneRecord[i].indexOf(":") + 1); j < (strOneRecord[i].count() - 1) && !strOneRecord[i][j].isLetter(); j++)
        {
            // Если встретился символ - число
            if(strOneRecord[i][j].isNumber())
            {
                throw QString ("Текст записей:\nОшибка! Свойство введено неверно. \nВы ввели: \""
                               + strOneRecord[i].mid(strOneRecord[i].indexOf(":") + 1, j - strOneRecord[i].indexOf(":"))
                               + "\"\nВерный формат: 'название свойства'=['целочисленные занчения']");
            }

            // Если встретился любой символ кроме пробела
            if(!strOneRecord[i][j].isSpace())
            {
                throw QString ("Текст записей:\nОшибка! Между символом ':' и названием свойства может быть только один 'пробел'."
                               "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }

            // Если встретилось 2 пробела подряд
            if(strOneRecord[i][j].isSpace() && strOneRecord[i][j + 1].isSpace())
            {
                throw QString ("Текст записей:\nОшибка! Между символом ':' и названием свойства может быть только один 'пробел'."
                               "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
            }
        }

        // Для каждого элемента строки начиная с первого символа '[' и до последнего символа '['
        for(int j = strOneRecord[i].indexOf("]"); j < strOneRecord[i].lastIndexOf("["); j++)
        {
            // Если встретился символ ']'
            if(strOneRecord[i][j] == "]")
            {
                j += 2; // переходим на 2 элемента вперёд

                // Если встретилось 2 запятые (',') подряд
                if(strOneRecord[i][j] == "," || strOneRecord[i][j + 1] == ",")
                {
                    throw QString ("Текст записей:\nОшибка! Между концом одного свойства и началом другого должна быть одна запятая и может быть только один 'пробел'."
                                   "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
                }

                // Иначе если встретилось 2 пробела подряд
                else if(strOneRecord[i][j].isSpace() && strOneRecord[i][j + 1].isSpace())
                {
                    QString errTXT = strOneRecord[i]; // создать изменяемую строку и присвоить текущую строку
                    errTXT.replace(" ", "*", Qt::CaseInsensitive); // поменять в этой строке все пробелы на символ '*'
                    throw QString ("Текст записей:\nОшибка! Между концом одного свойства и началом другого должно быть не больше одного 'пробела' подряд."
                                   "\nОшибка в записи " + QString::number(i + 1) + ": " + errTXT);
                }
            }
        }

        // Если после последнего символа ']' есть символы кроме единственного символа ';' и запись не последняя
        if(strOneRecord[i].lastIndexOf("]") != strOneRecord[i].count() - 1 && strOneRecord[i].count(".") == 0)
        {
            throw QString ("Текст записей:\nОшибка! После последнего свойства записи не должно быть никаких символов, кроме ';', которая разделяет записи."
                           "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i] + ";");
        }

        // Если после последнего символа ']' есть символы кроме единственного символа ';' и запись последняя
        if(strOneRecord[i].lastIndexOf("]") != strOneRecord[i].count() - 2 && strOneRecord[i].count(".") == 1)
        {
            throw QString ("Текст записей:\nОшибка! После последнего свойства записи не должно быть никаких символов, кроме '.' после последней записи."
                           "\nОшибка в записи " + QString::number(i + 1) + ": " + strOneRecord[i]);
        }

        QRegularExpression rex(",(?![^\\[]*\\])"); // регулярное выражение которое разбивает строку по запятой, исключая запятые между '[' ']'
        QStringList parts = strOneRecord[i].split(rex, QString::SkipEmptyParts); // разбиваем строку по регулярному выражению

        // удаляем из первого элемента массива parts название записи
        parts[0] = parts[0].mid(parts[0].indexOf(":") + 1, parts[0].count() - 1);

        // Для каждого элемента массива parts
        for (int j = 0; j < parts.count(); j++)
        {
            // Если в тексте массива (свойстве полностью) отсутствует символ '='
            if(parts[j].count("=") == 0)
            {
                throw QString ("Текст записей:\nОшибка! Свойство введено неверно. Вы ввели: \"" + parts[j] + "\"\nВерный формат: 'название свойства'=['целочисленные занчения']");
            }
        }
    }

    //--------------------------------- Блок проверки названий записей на совпадение----------------------------------------------
    // Для каждого названия записи
    for (int i = 0; i < strOneRecord.count(); ++i)
    {
        const QString& currentString = strOneRecord[i].mid(0, strOneRecord[i].indexOf(":")); // получить текст названия записи по индексу i

        // Для каждого названия записи идущего после текущего
        for (int j = i + 1; j < strOneRecord.count(); ++j)
        {
            const QString& otherString = strOneRecord[j].mid(0, strOneRecord[j].indexOf(":")); // получить текст названия записи по индексу j

            // Если названия записей совпали
            if (currentString == otherString)
            {
                throw QString ("Текст записей:\nОшибка! Названия записей не могут повторяться."
                               "\nНазвание записи: \"" + currentString +
                               "\"\nПовторение в записях: " + QString::number(i + 1) + " и " + QString::number(j + 1));
            }
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
}

QMap<QString, QList<int> > Records::getRelatedIntegerValues()
{
    // вернуть текущий контейнер с названиями свойств и соответствующими им целочисленными значениями для текущей записи
    return this -> relatedIntegerValues;
}

QString Records::getName()
{
    // вернуть текущее название записи
    return this -> name;
}
