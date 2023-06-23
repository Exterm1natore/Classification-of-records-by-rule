#include <QtTest>
#include "../ClassificationOfRecordsByRule/Records.h"
// add necessary includes here

class checkInputTextOfRecords : public QObject
{
    Q_OBJECT

public:
    checkInputTextOfRecords();
    ~checkInputTextOfRecords();

private slots:
    void recordFileIsEmpty();
    void thereIsNoFullStopAtEndOfText();
    void thereAreWwoDotsInTextOfEntries();
    void semicolonBetweenBrackets();
    void entriesAreNotSeparatedBySemicolons();
    void namesOfEntriesAreGreaterThanTheirNumber();
    void entryDoesNotStartWithTitle();
    void nameOfRecordIsNotCapitalised();
    void nameOfRecordIsThirdLetterInUppercase();
    void illegalCharactersInTitleOfRecord();
    void thereIsSpaceInEntryName();
    void betweenRecordNameAndPropertyForbiddenCharacters();
    void thereTwoSpacesBetweenRecordNameAndProperty();
    void prohibitedCharactersInPropertyName();
    void thereIsUpperCaseInProperty();
    void spaceAfterPropertyName();
    void propertyHasNoIntegerValues();
    void afterIsNotParenthesis();
    void integerValuesDoNotHavePropertyName();
    void integerValuesAreEnclosedInDoubleBrackets();
    void propertyHasNumberGreaterThanNinetyNine();
    void numberIsPrecededByZero();
    void thereForbiddenCharactersInsideBrackets();
    void thereIsNothingBetweenBrackets();
    void numberOfNumbersBetweenBracketsGreaterThanNine();
    void numbersAreNotSeparatedByComma();
    void thereTwoSpacesInsideBrackets();
    void insideBracketsAfterSpaceCcomma();
    void commaAfterLastProperty();
    void propertiesAreNotSeparatedByComma();
    void recordHasMoreThanTwentyProperties();
    void oneRecordHasRepeatedPropertyNames();
    void recordTitlesAreRepeated();
    void textOfRecordsIsCorrect();
};

checkInputTextOfRecords::checkInputTextOfRecords()
{

}

checkInputTextOfRecords::~checkInputTextOfRecords()
{

}

void checkInputTextOfRecords::recordFileIsEmpty()
{
    QString textRecord = "   ";
    QString expectedText = "Текст записей:\n"
                           "Ошибка! Файл с входными данными записей является пустым.";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::thereIsNoFullStopAtEndOfText()
{
    QString textRecord = "Шкаф:цвет=[1,2], размер=[10,12,15];"
                         "Игрушка: цвет=[15,1,12], размер=[10,12,45,14], текстура=[1];"
                         "Мяч: форма=[14], раскрас=[6,14], покрытие=[44,21];"
                         "Cтол:размер=[1,2],цвет=[99,1,3],покрытие=[12]";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! В конце текста записей должна стоять точка ('.').";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::thereAreWwoDotsInTextOfEntries()
{
    QString textRecord = "Шкаф:цвет=[1,2], размер=[10,12,15];"
                         "Игрушка: цвет=[15,1,12], размер=[10,12,45,14], текстура=[1]."
                         "Мяч: форма=[14], раскрас=[6,14], покрытие=[44,21];"
                         "Cтол:размер=[1,2],цвет=[99,1,3],покрытие=[12].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! В тексте записей может быть только одна точка ('.'), которая должна находится после последней записи\n"
                           "Номер ошибочного символа в тексте с записями: 95";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::semicolonBetweenBrackets()
{
    QString textRecord = "Шкаф:цвет=[1,2], размер=[10,12,15];"
                         "Игрушка: цвет=[15,1,12], размер=[10,12,45,14], текстура=[1];"
                         "Мяч: форма=[14], раскрас=[6,14], покрытие=[44;21];"
                         "Cтол:размер=[1,2],цвет=[99,1,3],покрытие=[12].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Между символами '[ ]' цифры не могут раздиляться точкой с запятой ';'.\n"
                           "Номер ошибочного символа в тексте с записями: 141";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::entriesAreNotSeparatedBySemicolons()
{
    QString textRecord = "Шкаф:цвет=[1,2], размер=[10,12,15];"
                         "Игрушка: цвет=[15,1,12], размер=[10,12,45,14], текстура=[1]"
                         "Мяч: форма=[14], раскрас=[6,14], покрытие=[44,21];"
                         "Cтол:размер=[1,2],цвет=[99,1,3],покрытие=[12].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Количество названий записи должно быть равно количеству записей. \n"
                           "У записи должно быть название и притом только одно(название записи находится перед символом ':', а каждая запись разделена символом ';', после последней ставится точка ('.').";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::namesOfEntriesAreGreaterThanTheirNumber()
{
    QString textRecord = "Шкаф:цвет=[1,2], размер=[10,12,15];"
                         "Игрушка: цвет=[15,1,12], размер:=[10,12,45,14], текстура=[1];"
                         "Мяч: форма=[14], раскрас=[6,14], покрытие=[44,21];"
                         "Cтол:размер=[1,2],цвет=[99,1,3],покрытие=[12].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Количество названий записи должно быть равно количеству записей. \n"
                           "У записи должно быть название и притом только одно(название записи находится перед символом ':', а каждая запись разделена символом ';', после последней ставится точка ('.').";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::entryDoesNotStartWithTitle()
{
    QString textRecord = "цвет=[1,2], Шкаф: размер=[10,12,15].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Запись должна начинаться с названия.\n"
                           "Название записи состоит только из букв русского или английского алфавита (иные символы недопустимы).\n"
                           "Ошибка в записи 1: цвет=[1,2], Шкаф: размер=[10,12,15].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::nameOfRecordIsNotCapitalised()
{
    QString textRecord = "шкаф: цвет=[1,2], размер=[10,12,15].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Название записи должно начинаться с заглавной буквы.\n"
                           "Вы ввели: \"шкаф\"\n"
                           "Ошибка в записи 1: шкаф: цвет=[1,2], размер=[10,12,15].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::nameOfRecordIsThirdLetterInUppercase()
{
    QString textRecord = "ШкАф: цвет=[1,2], размер=[10,12,15].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! В названии записи все буквы, кроме первой должны быть в нижнем регистре.\n"
                           "Вы ввели: \"ШкАф\"\n"
                           "Ошибка в записи 1: ШкАф: цвет=[1,2], размер=[10,12,15].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::illegalCharactersInTitleOfRecord()
{
    QString textRecord = "Шкаф1: цвет=[1,2], размер=[10,12,15].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! В названии записи допускаются лишь буквы русского или английского алфавита.\n"
                           "Вы ввели: \"Шкаф1\"\n"
                           "Ошибка в записи 1: Шкаф1: цвет=[1,2], размер=[10,12,15].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::thereIsSpaceInEntryName()
{
    QString textRecord = "Шк аф: цвет=[1,2], размер=[10,12,15].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! В названии записи допускаются лишь буквы русского или английского алфавита.\n"
                           "Вы ввели: \"Шк аф\"\n"
                           "Ошибка в записи 1: Шк аф: цвет=[1,2], размер=[10,12,15].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::betweenRecordNameAndPropertyForbiddenCharacters()
{
    QString textRecord = "Шкаф: , цвет=[1,2], размер=[10,12,15].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Между символом ':' и названием свойства может быть только один 'пробел'.\n"
                           "Ошибка в записи 1: Шкаф: , цвет=[1,2], размер=[10,12,15].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::thereTwoSpacesBetweenRecordNameAndProperty()
{
    QString textRecord = "Шкаф:  цвет=[1,2], размер=[10,12,15].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Между символом ':' и названием свойства может быть только один 'пробел'.\n"
                           "Ошибка в записи 1: Шкаф:  цвет=[1,2], размер=[10,12,15].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::prohibitedCharactersInPropertyName()
{
    QString textRecord = "Шкаф: цвет=[1,2], разме1р=[10,12,15].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! В названии свойства записи допускаются лишь буквы русского или английского алфавита.\n"
                           "Вы ввели: \"разме1р\"\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1,2], разме1р=[10,12,15].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::thereIsUpperCaseInProperty()
{
    QString textRecord = "Шкаф: цвет=[1,2], раЗмер=[10,12,15].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! В названии свойства записи не допускается использовать верхний регистр.\n"
                           "Вы ввели: \"раЗмер\"\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1,2], раЗмер=[10,12,15].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::spaceAfterPropertyName()
{
    QString textRecord = "Шкаф: цвет=[1,2], размер =[10,12,15].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Перед символом '=' должно идти название свойства записи.\n"
                           "Название состоит только из букв русского или английского алфавита (другие символы межу названием записи и символом '=' недопускаются).\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1,2], размер =[10,12,15].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::propertyHasNoIntegerValues()
{
    QString textRecord = "Шкаф: цвет, размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Свойство введено неверно. Вы ввели: \" цвет\"\n"
                           "Верный формат: 'название свойства'=['целочисленные занчения']";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::afterIsNotParenthesis()
{
    QString textRecord = "Шкаф: цвет= [1, 2], размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! После символа '=' должен стоять символ '['.\n"
                           "Ошибка в записи 1: Шкаф: цвет= [1, 2], размер=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::integerValuesDoNotHavePropertyName()
{
    QString textRecord = "Шкаф: цвет=[1, 2],[15,15], размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! У записи каждому названию свойства соответствуют целочисленные значения которые соотносятся символом '=' (количество символов '=' и '[', ']' должно совпадать).\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1, 2],[15,15], размер=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::integerValuesAreEnclosedInDoubleBrackets()
{
    QString textRecord = "Шкаф: цвет=[[1, 2]],размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! У записи каждому названию свойства соответствуют целочисленные значения которые соотносятся символом '=' (количество символов '=' и '[', ']' должно совпадать).\n"
                           "Ошибка в записи 1: Шкаф: цвет=[[1, 2]],размер=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::propertyHasNumberGreaterThanNinetyNine()
{
    QString textRecord = "Шкаф: цвет=[1, 2],размер=[99,100].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Между символами '[' и ']' числа должны лежать в диапазоне [1;99].\n"
                           "Вы ввели: \"100\"\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1, 2],размер=[99,100].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::numberIsPrecededByZero()
{
    QString textRecord = "Шкаф: цвет=[1, 02],размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Целочисленные значения должны лежать в диапазоне [1;99] (0 перед числом писать нельзя). \n"
                           "Вы ввели: \"02\"\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1, 02],размер=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::thereForbiddenCharactersInsideBrackets()
{
    QString textRecord = "Шкаф: цвет=[1, три,2],размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Не допускается использование между символами '[' и ']' всего, кроме 'пробела', ',' или цифр.\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1, три,2],размер=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::thereIsNothingBetweenBrackets()
{
    QString textRecord = "Шкаф: цвет=[],размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Поле между символами '[' и ']' не должно быть пустым (должно содеражть от 1 до 9 чисел, разделённых запятой ',').\n"
                           "Ошибка в записи 1: Шкаф: цвет=[],размер=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::numberOfNumbersBetweenBracketsGreaterThanNine()
{
    QString textRecord = "Шкаф: цвет=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10],размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Количество целочисленных значений между символами '[' и ']' должно быть от 1 до 9.\n"
                           "Вы ввели 10 значений.\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10],размер=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::numbersAreNotSeparatedByComma()
{
    QString textRecord = "Шкаф: цвет=[1 2],размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Между символами '[' и ']', после числа, должна стоять запятая (',').\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1 2],размер=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::thereTwoSpacesInsideBrackets()
{
    QString textRecord = "Шкаф: цвет=[1,  2],размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Не допускается между символами '[' и ']' использование больше одного 'пробела' подряд.\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1,  2],размер=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::insideBracketsAfterSpaceCcomma()
{
    QString textRecord = "Шкаф: цвет=[1 ,2],размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Между символами '[' и ']', после числа, должна стоять запятая (',').\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1 ,2],размер=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::commaAfterLastProperty()
{
    QString textRecord = "Шкаф: цвет=[1, 2],размер=[99,99],.";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! После последнего свойства записи не должно быть никаких символов, кроме '.' после последней записи.\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1, 2],размер=[99,99],.";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::propertiesAreNotSeparatedByComma()
{
    QString textRecord = "Шкаф: цвет=[1, 2] размер=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! После каждого символа ']', кроме последнего, должна стоять запятая ','.\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1, 2] размер=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::recordHasMoreThanTwentyProperties()
{
    QString textRecord = "Шкаф: один=[1], два=[2], три=[3], четыре=[4], пять=[5], шесть=[6], семь=[7], весемь=[8], девять=[9], "
                         "десять=[10], одинадцать=[11], двенадцать=[12], тринадцать=[13], четырнадцать=[14], пятнадцать=[15], "
                         "шестнадцать=[16], семнадцать=[17], восемнадцать=[18], девятнадцать=[19], двадцать=[20], двадцатьодин=[21].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! У записи не может быть больше 20 свойств (каждое свойство соотносится символом равно '=').\n"
                           "Ошибка в записи 1: Шкаф: один=[1], два=[2], три=[3], четыре=[4], пять=[5], шесть=[6], семь=[7], "
                           "весемь=[8], девять=[9], десять=[10], одинадцать=[11], двенадцать=[12], тринадцать=[13], "
                           "четырнадцать=[14], пятнадцать=[15], шестнадцать=[16], семнадцать=[17], восемнадцать=[18], "
                           "девятнадцать=[19], двадцать=[20], двадцатьодин=[21].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::oneRecordHasRepeatedPropertyNames()
{
    QString textRecord = "Шкаф: цвет=[1, 2], размер=[2], цвет=[99,99].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! В одной записи названия свойств не могут повторяться.\n"
                           "Название свойства: \"цвет\"\n"
                           "Ошибка в записи 1: Шкаф: цвет=[1, 2], размер=[2], цвет=[99,99].";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::recordTitlesAreRepeated()
{
    QString textRecord = "Шкаф:цвет=[1,2], размер=[10,12,15];"
                         "Игрушка: цвет=[15,1,12], размер=[10,12,45,14], текстура=[1];"
                         "Шкаф: форма=[14], раскрас=[6,14], покрытие=[44,21];"
                         "Cтол:размер=[1,2],цвет=[99,1,3],покрытие=[12].";

    QString expectedText = "Текст записей:\n"
                           "Ошибка! Названия записей не могут повторяться.\n"
                           "Название записи: \"Шкаф\"\n"
                           "Повторение в записях: 1 и 3";
    Records record;

    try
    {
        record.checkRecords(textRecord);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }
}

void checkInputTextOfRecords::textOfRecordsIsCorrect()
{
    QString textRecords = "Шкаф:цвет=[1,2], размер=[10,12,15];"
                          "Игрушка: цвет=[15,1,12], размер=[10,12,45,14], текстура=[1];"
                          "Мяч: форма=[14], раскрас=[6,14], покрытие=[44,21];"
                          "Cтол:размер=[1,2],цвет=[99,1,3],покрытие=[12].";

    Records record;

    try
    {
        record.checkRecords(textRecords);
        QVERIFY(true);
    }
    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

QTEST_APPLESS_MAIN(checkInputTextOfRecords)

#include "tst_checkInputTextOfRecords.moc"
