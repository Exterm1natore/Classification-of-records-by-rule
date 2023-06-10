#include <QtTest>
#include <../ClassificationOfRecordsByRule/ClassificationRules.h>
// add necessary includes here

class checkClassificationRules : public QObject
{
    Q_OBJECT
    class TestClassificationRules
    {
    public:
        ConditionType expectedCondition;
        LimitationIntegerValues expectedlimitValue;
        QString expectedName;
        QString expectedConstraint;
        QList<int> expectedIntegerValues;
    };

public:
    checkClassificationRules();
    ~checkClassificationRules();

private slots:
    void textOfRulesisWrong();
    void oneRuleWithNoAdditionalRestriction();
    void oneRuleAsNumberOfIntegerValues();
    void oneRuleAsSingleIntegerValue();
    void oneRuleAsAnArrayOfIntegerValues();
    void fourDifferentTypesOfRules();
    void eightRulesInPairsOfSameType();
    void oneHundredRules();
};

checkClassificationRules::checkClassificationRules()
{

}

checkClassificationRules::~checkClassificationRules()
{

}

void checkClassificationRules::textOfRulesisWrong()
{
    QString textRule = "Запись в классе \"С покрытием\", если у нее есть свойство \"покрытие\".";

    QString expectedText = "Текст правил классификации:\n"
                           "Ошибка! Неверный формат ввода правила.\n"
                           "Ошибка в правиле 1: Запись в классе \"С покрытием\", если у нее есть свойство \"покрытие\"."
                           "\n\nДопустимые форматы: \n"
                           "1) 'Запись принадлежит классу \"<название класса>\", если у нее есть свойство \"<название свойства>\"'\n"
                           "2) 'Запись принадлежит классу \"<название класса>\", если у нее есть свойство \"<название свойства>\", которое представлено ([одним|двумя|тремя|четырьмя|пятью|шестью|семью|восемью|девятью]) значением(ями)'\n"
                           "3) 'Запись принадлежит классу \"<название класса>\", если у нее есть свойство \"<название свойства>\", в составе которого есть значение \"<одно целочисленное значение>\"'\n"
                           "4) 'Запись принадлежит классу \"<название класса>\", если у нее есть свойство \"<название свойства>\" и значение этого свойства равно \"[целочисленные значения через ',']\"'";

    ClassificationRules rules;

    try
    {
        rules.checkClassificationRules(textRule);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedText, errorText);
    }

}

void checkClassificationRules::oneRuleWithNoAdditionalRestriction()
{
    ClassificationRules rules;
    TestClassificationRules testRules;
    QString textRule = "Запись принадлежит классу \"С покрытием\", если у нее есть свойство \"покрытие\".";

    testRules.expectedName = "С покрытием";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "покрытие";
    testRules.expectedlimitValue = NotQuantity;

    QList<ClassificationRules> arrRules;
    QList<TestClassificationRules> arrTestRules;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();

    try
    {
        rules.splitStringOfClassificationRules(textRule, &arrRules);

        if(arrRules.count() != arrTestRules.count())
        {
            QFAIL("Fail");
        }

        for(int i = 0; i < arrRules.count(); i++)
        {
            QCOMPARE(arrTestRules[i].expectedName, arrRules[i].getName());
            QCOMPARE(arrTestRules[i].expectedCondition, arrRules[i].getCondition());
            QCOMPARE(arrTestRules[i].expectedConstraint, arrRules[i].getConstraint());
            QCOMPARE(arrTestRules[i].expectedlimitValue, arrRules[i].getLimitValue());

            if(arrTestRules[i].expectedIntegerValues.count() != arrRules[i].getIntegerValues().count())
            {
                QFAIL("Fail");
            }
            else
            {
                for(int j = 0; j < arrRules[i].getIntegerValues().count(); j++)
                {
                    QCOMPARE(arrTestRules[i].expectedIntegerValues[j], arrRules[i].getIntegerValues()[j]);
                }

            }
        }
    }
    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

void checkClassificationRules::oneRuleAsNumberOfIntegerValues()
{
    ClassificationRules rules;
    TestClassificationRules testRules;
    QString textRule = "Запись принадлежит классу \"П л о с к и й\", если у нее есть свойство \"размер\", которое представлено девятью значениями.";

    testRules.expectedName = "П л о с к и й";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "размер";
    testRules.expectedlimitValue = Nine;

    QList<ClassificationRules> arrRules;
    QList<TestClassificationRules> arrTestRules;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();

    try
    {
        rules.splitStringOfClassificationRules(textRule, &arrRules);

        if(arrRules.count() != arrTestRules.count())
        {
            QFAIL("Fail");
        }

        for(int i = 0; i < arrRules.count(); i++)
        {
            QCOMPARE(arrTestRules[i].expectedName, arrRules[i].getName());
            QCOMPARE(arrTestRules[i].expectedCondition, arrRules[i].getCondition());
            QCOMPARE(arrTestRules[i].expectedConstraint, arrRules[i].getConstraint());
            QCOMPARE(arrTestRules[i].expectedlimitValue, arrRules[i].getLimitValue());

            if(arrTestRules[i].expectedIntegerValues.count() != arrRules[i].getIntegerValues().count())
            {
                QFAIL("Fail");
            }
            else
            {
                for(int j = 0; j < arrRules[i].getIntegerValues().count(); j++)
                {
                    QCOMPARE(arrTestRules[i].expectedIntegerValues[j], arrRules[i].getIntegerValues()[j]);
                }

            }
        }
    }
    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

void checkClassificationRules::oneRuleAsSingleIntegerValue()
{
    ClassificationRules rules;
    TestClassificationRules testRules;
    QString textRule = "Запись принадлежит классу \"Синий\", если у нее есть свойство \"цвет\", в составе которого есть значение \"1\".";

    testRules.expectedName = "Синий";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "цвет";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues.append(1);

    QList<ClassificationRules> arrRules;
    QList<TestClassificationRules> arrTestRules;

    arrTestRules.append(testRules);
    try
    {
        rules.splitStringOfClassificationRules(textRule, &arrRules);

        if(arrRules.count() != arrTestRules.count())
        {
            QFAIL("Fail");
        }

        for(int i = 0; i < arrRules.count(); i++)
        {
            QCOMPARE(arrTestRules[i].expectedName, arrRules[i].getName());
            QCOMPARE(arrTestRules[i].expectedCondition, arrRules[i].getCondition());
            QCOMPARE(arrTestRules[i].expectedConstraint, arrRules[i].getConstraint());
            QCOMPARE(arrTestRules[i].expectedlimitValue, arrRules[i].getLimitValue());

            if(arrTestRules[i].expectedIntegerValues.count() != arrRules[i].getIntegerValues().count())
            {
                QFAIL("Fail");
            }
            else
            {
                for(int j = 0; j < arrRules[i].getIntegerValues().count(); j++)
                {
                    QCOMPARE(arrTestRules[i].expectedIntegerValues[j], arrRules[i].getIntegerValues()[j]);
                }

            }
        }
    }
    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

void checkClassificationRules::oneRuleAsAnArrayOfIntegerValues()
{
    ClassificationRules rules;
    TestClassificationRules testRules;
    QString textRule = "Запись принадлежит классу \"Матовый\", если у нее есть свойство \"покрытие\" и значение этого свойства равно \"[1, 99]\".";

    testRules.expectedName = "Матовый";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "покрытие";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 1 << 99;

    QList<ClassificationRules> arrRules;
    QList<TestClassificationRules> arrTestRules;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();

    try
    {
        rules.splitStringOfClassificationRules(textRule, &arrRules);

        if(arrRules.count() != arrTestRules.count())
        {
            QFAIL("Fail");
        }

        for(int i = 0; i < arrRules.count(); i++)
        {
            QCOMPARE(arrTestRules[i].expectedName, arrRules[i].getName());
            QCOMPARE(arrTestRules[i].expectedCondition, arrRules[i].getCondition());
            QCOMPARE(arrTestRules[i].expectedConstraint, arrRules[i].getConstraint());
            QCOMPARE(arrTestRules[i].expectedlimitValue, arrRules[i].getLimitValue());

            if(arrTestRules[i].expectedIntegerValues.count() != arrRules[i].getIntegerValues().count())
            {
                QFAIL("Fail");
            }
            else
            {
                for(int j = 0; j < arrRules[i].getIntegerValues().count(); j++)
                {
                    QCOMPARE(arrTestRules[i].expectedIntegerValues[j], arrRules[i].getIntegerValues()[j]);
                }

            }
        }
    }
    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

void checkClassificationRules::fourDifferentTypesOfRules()
{
    ClassificationRules rules;
    TestClassificationRules testRules;
    QList<ClassificationRules> arrRules;
    QList<TestClassificationRules> arrTestRules;

    QString textRule = "Запись принадлежит классу \"С покрытием\", если у нее есть свойство \"покрытие\";"
                       "Запись принадлежит классу \"П л о с к и й\", если у нее есть свойство \"размер\", которое представлено двумя значениями;"
                       "Запись принадлежит классу \"Синий\", если у нее есть свойство \"цвет\", в составе которого есть значение \"1\";"
                       "Запись принадлежит классу \"Матовый\", если у нее есть свойство \"покрытие\" и значение этого свойства равно \"[44, 21]\".";

    //------------- 1 правило-----------------------------------
    testRules.expectedName = "С покрытием";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "покрытие";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 2 правило-----------------------------------
    testRules.expectedName = "П л о с к и й";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "размер";
    testRules.expectedlimitValue = Two;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 3 правило-----------------------------------
    testRules.expectedName = "Синий";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "цвет";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 1;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 4 правило-----------------------------------
    testRules.expectedName = "Матовый";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "покрытие";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 44 << 21;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    try
    {
        rules.splitStringOfClassificationRules(textRule, &arrRules);

        if(arrRules.count() != arrTestRules.count())
        {
            QFAIL("Fail");
        }

        for(int i = 0; i < arrRules.count(); i++)
        {
            QCOMPARE(arrTestRules[i].expectedName, arrRules[i].getName());
            QCOMPARE(arrTestRules[i].expectedCondition, arrRules[i].getCondition());
            QCOMPARE(arrTestRules[i].expectedConstraint, arrRules[i].getConstraint());
            QCOMPARE(arrTestRules[i].expectedlimitValue, arrRules[i].getLimitValue());

            if(arrTestRules[i].expectedIntegerValues.count() != arrRules[i].getIntegerValues().count())
            {
                QFAIL("Fail");
            }
            else
            {
                for(int j = 0; j < arrRules[i].getIntegerValues().count(); j++)
                {
                    QCOMPARE(arrTestRules[i].expectedIntegerValues[j], arrRules[i].getIntegerValues()[j]);
                }

            }
        }
    }
    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

void checkClassificationRules::eightRulesInPairsOfSameType()
{
    ClassificationRules rules;
    TestClassificationRules testRules;
    QList<ClassificationRules> arrRules;
    QList<TestClassificationRules> arrTestRules;

    QString textRule = "Запись принадлежит классу \"С покрытием\", если у нее есть свойство \"покрытие\";"
                       "Запись принадлежит классу \"П л о с к и й\", если у нее есть свойство \"размер\", которое представлено двумя значениями;"
                       "Запись принадлежит классу \"Синий\", если у нее есть свойство \"цвет\", в составе которого есть значение \"1\";"
                       "Запись принадлежит классу \"Матовый\", если у нее есть свойство \"покрытие\" и значение этого свойства равно \"[44, 21]\";"
                       "Запись принадлежит классу \"Красный\", если у нее есть свойство \"красный\";"
                       "Запись принадлежит классу \"Большой\", если у нее есть свойство \"объём\", которое представлено двумя значениями;"
                       "Запись принадлежит классу \"Мягкий\", если у нее есть свойство \"материал\", в составе которого есть значение \"1\";"
                       "Запись принадлежит классу \"Тонированный\", если у нее есть свойство \"тонер\" и значение этого свойства равно \"[44, 21]\".";

    //------------- 1 правило-----------------------------------
    testRules.expectedName = "С покрытием";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "покрытие";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 2 правило-----------------------------------
    testRules.expectedName = "П л о с к и й";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "размер";
    testRules.expectedlimitValue = Two;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 3 правило-----------------------------------
    testRules.expectedName = "Синий";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "цвет";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 1;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 4 правило-----------------------------------
    testRules.expectedName = "Матовый";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "покрытие";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 44 << 21;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 5 правило-----------------------------------
    testRules.expectedName = "Красный";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "красный";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 6 правило-----------------------------------
    testRules.expectedName = "Большой";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "объём";
    testRules.expectedlimitValue = Two;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 7 правило-----------------------------------
    testRules.expectedName = "Мягкий";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "материал";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 1;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 8 правило-----------------------------------
    testRules.expectedName = "Тонированный";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "тонер";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 44 << 21;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    try
    {
        rules.splitStringOfClassificationRules(textRule, &arrRules);

        if(arrRules.count() != arrTestRules.count())
        {
            QFAIL("Fail");
        }

        for(int i = 0; i < arrRules.count(); i++)
        {
            QCOMPARE(arrTestRules[i].expectedName, arrRules[i].getName());
            QCOMPARE(arrTestRules[i].expectedCondition, arrRules[i].getCondition());
            QCOMPARE(arrTestRules[i].expectedConstraint, arrRules[i].getConstraint());
            QCOMPARE(arrTestRules[i].expectedlimitValue, arrRules[i].getLimitValue());

            if(arrTestRules[i].expectedIntegerValues.count() != arrRules[i].getIntegerValues().count())
            {
                QFAIL("Fail");
            }
            else
            {
                for(int j = 0; j < arrRules[i].getIntegerValues().count(); j++)
                {
                    QCOMPARE(arrTestRules[i].expectedIntegerValues[j], arrRules[i].getIntegerValues()[j]);
                }

            }
        }
    }
    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

void checkClassificationRules::oneHundredRules()
{
    ClassificationRules rules;
    TestClassificationRules testRules;
    QList<ClassificationRules> arrRules;
    QList<TestClassificationRules> arrTestRules;

    QString textRule = "Запись принадлежит классу \"Автомобиль\", если у нее есть свойство \"встроенныединамики\";"
                       "Запись принадлежит классу \"Балерина\", если у нее есть свойство \"времяотклика\", которое представлено одним значением;"
                       "Запись принадлежит классу \"Велосипед\", если у нее есть свойство \"скоростьпередачиданн\" и значение этого свойства равно \"[15]\";"
                       "Запись принадлежит классу \"Гитара\", если у нее есть свойство \"скоростьпечати\" и значение этого свойства равно \"[2]\";"
                       "Запись принадлежит классу \"Дом\", если у нее есть свойство \"температура\" и значение этого свойства равно \"[37,89]\";"
                       "Запись принадлежит классу \"Единорог\", если у нее есть свойство \"материал\";"
                       "Запись принадлежит классу \"Фонарь\", если у нее есть свойство \"ширина\";"
                       "Запись принадлежит классу \"Глобус\", если у нее есть свойство \"съемность\" и значение этого свойства равно \"[30]\";"
                       "Запись принадлежит классу \"Холодильник\", если у нее есть свойство \"цвет\", которое представлено одним значением;"
                       "Запись принадлежит классу \"Игрушка\", если у нее есть свойство \"прозрачность\", которое представлено тремя значениями;"
                       "Запись принадлежит классу \"Йога\", если у нее есть свойство \"плотность\";"
                       "Запись принадлежит классу \"Кот\", если у нее есть свойство \"нейтральность\";"
                       "Запись принадлежит классу \"Луна\", если у нее есть свойство \"материал\", в составе которого есть значение \"86\";"
                       "Запись принадлежит классу \"Машина\", если у нее есть свойство \"многофункциональност\";"
                       "Запись принадлежит классу \"Небо\", если у нее есть свойство \"отзывчивость\", которое представлено четырьмя значениями;"
                       "Запись принадлежит классу \"Океан\", если у нее есть свойство \"тип\", которое представлено восемью значениями;"
                       "Запись принадлежит классу \"Парашют\", если у нее есть свойство \"оптическийстабилизат\", которое представлено восемью значениями;"
                       "Запись принадлежит классу \"Радуга\", если у нее есть свойство \"влажность\" и значение этого свойства равно \"[68,62]\";"
                       "Запись принадлежит классу \"Солнце\", если у нее есть свойство \"цвет\", в составе которого есть значение \"90\";"
                       "Запись принадлежит классу \"Танцор\", если у нее есть свойство \"функциональность\";"
                       "Запись принадлежит классу \"Утка\", если у нее есть свойство \"уровеньзаряда\", которое представлено четырьмя значениями;"
                       "Запись принадлежит классу \"Фламинго\", если у нее есть свойство \"автоматическийвыборр\", в составе которого есть значение \"39\";"
                       "Запись принадлежит классу \"Холм\", если у нее есть свойство \"качество\";"
                       "Запись принадлежит классу \"Цветок\", если у нее есть свойство \"времяотклика\", которое представлено четырьмя значениями;"
                       "Запись принадлежит классу \"Чайник\", если у нее есть свойство \"длина\" и значение этого свойства равно \"[88,33,51]\";"
                       "Запись принадлежит классу \"Шар\", если у нее есть свойство \"циклработы\" и значение этого свойства равно \"[36,56,56,99,10]\";"
                       "Запись принадлежит классу \"Щука\", если у нее есть свойство \"расходэнергиивожидан\", в составе которого есть значение \"29\";"
                       "Запись принадлежит классу \"Экран\", если у нее есть свойство \"длина\" и значение этого свойства равно \"[96,44,9,98]\";"
                       "Запись принадлежит классу \"Юмор\", если у нее есть свойство \"скоростьпередачиданн\", в составе которого есть значение \"16\";"
                       "Запись принадлежит классу \"Яхта\", если у нее есть свойство \"шифрованиеданных\", в составе которого есть значение \"31\";"
                       "Запись принадлежит классу \"Апельсин\", если у нее есть свойство \"оптическийстабилизат\", которое представлено одним значением;"
                       "Запись принадлежит классу \"Бабочка\", если у нее есть свойство \"максимальнаянагрузка\", которое представлено четырьмя значениями;"
                       "Запись принадлежит классу \"Виолончель\", если у нее есть свойство \"циклработы\", в составе которого есть значение \"82\";"
                       "Запись принадлежит классу \"Галактика\", если у нее есть свойство \"циклработы\", в составе которого есть значение \"9\";"
                       "Запись принадлежит классу \"Дракон\", если у нее есть свойство \"эффективностьработы\", которое представлено пятью значениями;"
                       "Запись принадлежит классу \"Ель\", если у нее есть свойство \"цвет\", которое представлено четырьмя значениями;"
                       "Запись принадлежит классу \"Ферма\", если у нее есть свойство \"толщина\", которое представлено девятью значениями;"
                       "Запись принадлежит классу \"Газель\", если у нее есть свойство \"количество\", которое представлено тремя значениями;"
                       "Запись принадлежит классу \"Хор\", если у нее есть свойство \"размер\", которое представлено девятью значениями;"
                       "Запись принадлежит классу \"Иглу\", если у нее есть свойство \"уровеньшума\", в составе которого есть значение \"3\";"
                       "Запись принадлежит классу \"Картина\", если у нее есть свойство \"интуитивныйинтерфейс\", которое представлено пятью значениями;"
                       "Запись принадлежит классу \"Лампа\", если у нее есть свойство \"конфигурация\", которое представлено шестью значениями;"
                       "Запись принадлежит классу \"Море\", если у нее есть свойство \"времяработы\" и значение этого свойства равно \"[21,67,55,84,52]\";"
                       "Запись принадлежит классу \"Носки\", если у нее есть свойство \"эргономика\", которое представлено тремя значениями;"
                       "Запись принадлежит классу \"Орел\", если у нее есть свойство \"защитаотпыли\" и значение этого свойства равно \"[37,14,38,98]\";"
                       "Запись принадлежит классу \"Птица\", если у нее есть свойство \"материал\" и значение этого свойства равно \"[94,30,76]\";"
                       "Запись принадлежит классу \"Ракета\", если у нее есть свойство \"напряжение\", в составе которого есть значение \"70\";"
                       "Запись принадлежит классу \"Солнечный луч\", если у нее есть свойство \"магнитнаясовместимос\", которое представлено девятью значениями;"
                       "Запись принадлежит классу \"Тигр\", если у нее есть свойство \"оптическийстабилизат\";"
                       "Запись принадлежит классу \"Узор\", если у нее есть свойство \"гироскопическаястаби\";"
                       "Запись принадлежит классу \"Фонарик\", если у нее есть свойство \"автоматическийвыборр\", в составе которого есть значение \"48\";"
                       "Запись принадлежит классу \"Хомяк\", если у нее есть свойство \"амортизация\";"
                       "Запись принадлежит классу \"Цирк\", если у нее есть свойство \"эмиссия\", в составе которого есть значение \"64\";"
                       "Запись принадлежит классу \"Чехол\", если у нее есть свойство \"уровенькомфорта\";"
                       "Запись принадлежит классу \"Шоколад\", если у нее есть свойство \"срокслужбы\" и значение этого свойства равно \"[60,15,56]\";"
                       "Запись принадлежит классу \"Щенок\", если у нее есть свойство \"стабилизацияизображе\" и значение этого свойства равно \"[69,89,65,86,46]\";"
                       "Запись принадлежит классу \"Эксперимент\", если у нее есть свойство \"цветоваятемпература\" и значение этого свойства равно \"[50,4,54]\";"
                       "Запись принадлежит классу \"Юрист\", если у нее есть свойство \"эмиссия\", которое представлено восемью значениями;"
                       "Запись принадлежит классу \"Ягода\", если у нее есть свойство \"размер\", в составе которого есть значение \"82\";"
                       "Запись принадлежит классу \"Аптека\", если у нее есть свойство \"стабилизацияизображе\" и значение этого свойства равно \"[71,49,10,26,87]\";"
                       "Запись принадлежит классу \"Банк\", если у нее есть свойство \"скоростьпередачиданн\", которое представлено четырьмя значениями;"
                       "Запись принадлежит классу \"Весна\", если у нее есть свойство \"уровенькомфорта\", которое представлено семью значениями;"
                       "Запись принадлежит классу \"Гора\", если у нее есть свойство \"уровеньзаряда\", которое представлено шестью значениями;"
                       "Запись принадлежит классу \"Деньги\", если у нее есть свойство \"странапроизводства\" и значение этого свойства равно \"[98,8,29,77,62]\";"
                       "Запись принадлежит классу \"Жемчуг\", если у нее есть свойство \"напряжение\" и значение этого свойства равно \"[92]\";"
                       "Запись принадлежит классу \"Змея\", если у нее есть свойство \"длина\", которое представлено тремя значениями;"
                       "Запись принадлежит классу \"Игла\", если у нее есть свойство \"системаохлаждения\";"
                       "Запись принадлежит классу \"Карта\", если у нее есть свойство \"цена\" и значение этого свойства равно \"[54,31]\";"
                       "Запись принадлежит классу \"Полнолуние\", если у нее есть свойство \"конфигурация\", в составе которого есть значение \"77\";"
                       "Запись принадлежит классу \"Маска\", если у нее есть свойство \"регулировкавысоты\", в составе которого есть значение \"69\";"
                       "Запись принадлежит классу \"Нож\", если у нее есть свойство \"стабилизацияизображе\";"
                       "Запись принадлежит классу \"Речка\", если у нее есть свойство \"мощность\" и значение этого свойства равно \"[95,8,67]\";"
                       "Запись принадлежит классу \"Палец\", если у нее есть свойство \"скоростьпечати\" и значение этого свойства равно \"[43]\";"
                       "Запись принадлежит классу \"Робот\", если у нее есть свойство \"сопротивление\", в составе которого есть значение \"26\";"
                       "Запись принадлежит классу \"Сок\", если у нее есть свойство \"максимальнаянагрузка\", в составе которого есть значение \"77\";"
                       "Запись принадлежит классу \"Телефон\", если у нее есть свойство \"материал\" и значение этого свойства равно \"[9,91,15,44,77]\";"
                       "Запись принадлежит классу \"Ухо\", если у нее есть свойство \"уровеньяркости\", в составе которого есть значение \"72\";"
                       "Запись принадлежит классу \"Фишка\", если у нее есть свойство \"уровеньзаряда\";"
                       "Запись принадлежит классу \"Художник\", если у нее есть свойство \"индикация\", которое представлено девятью значениями;"
                       "Запись принадлежит классу \"Цвет\", если у нее есть свойство \"скоростьпередачиданн\", которое представлено двумя значениями;"
                       "Запись принадлежит классу \"Чемодан\", если у нее есть свойство \"индикация\";"
                       "Запись принадлежит классу \"Школа\", если у нее есть свойство \"влажность\", которое представлено одним значением;"
                       "Запись принадлежит классу \"Щит\", если у нее есть свойство \"защитаотпыли\", в составе которого есть значение \"4\";"
                       "Запись принадлежит классу \"Электричество\", если у нее есть свойство \"вес\", которое представлено двумя значениями;"
                       "Запись принадлежит классу \"Клерк\", если у нее есть свойство \"интуитивныйинтерфейс\";"
                       "Запись принадлежит классу \"Ястреб\", если у нее есть свойство \"объемпамяти\", которое представлено шестью значениями;"
                       "Запись принадлежит классу \"Спорткар\", если у нее есть свойство \"стиль\", в составе которого есть значение \"2\";"
                       "Запись принадлежит классу \"Гнилой банан\", если у нее есть свойство \"эргономика\" и значение этого свойства равно \"[74,39,11,30]\";"
                       "Запись принадлежит классу \"Крутой велик\", если у нее есть свойство \"съемность\" и значение этого свойства равно \"[56,66,73,43,2]\";"
                       "Запись принадлежит классу \"Бас гитара\", если у нее есть свойство \"гибкость\" и значение этого свойства равно \"[25]\";"
                       "Запись принадлежит классу \"Котедж\", если у нее есть свойство \"времяработы\" и значение этого свойства равно \"[89]\";"
                       "Запись принадлежит классу \"С мандаринками\", если у нее есть свойство \"энергоэффективность\", которое представлено шестью значениями;"
                       "Запись принадлежит классу \"Плато\", если у нее есть свойство \"защитаотультрафиолет\" и значение этого свойства равно \"[24]\";"
                       "Запись принадлежит классу \"Невыносимый\", если у нее есть свойство \"разрешение\" и значение этого свойства равно \"[98,70,78]\";"
                       "Запись принадлежит классу \"Большой\", если у нее есть свойство \"магнитнаясовместимос\";"
                       "Запись принадлежит классу \"Сложный\", если у нее есть свойство \"эластичность\", в составе которого есть значение \"66\";"
                       "Запись принадлежит классу \"С покрытием\", если у нее есть свойство \"покрытие\";"
                       "Запись принадлежит классу \"П л о с к и й\", если у нее есть свойство \"размер\", которое представлено двумя значениями;"
                       "Запись принадлежит классу \"Синий\", если у нее есть свойство \"цвет\", в составе которого есть значение \"1\";"
                       "Запись принадлежит классу \"Матовый\", если у нее есть свойство \"покрытие\" и значение этого свойства равно \"[44, 99]\".";

    //------------- 1 правило-----------------------------------
    testRules.expectedName = "Автомобиль";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "встроенныединамики";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 2 правило-----------------------------------
    testRules.expectedName = "Балерина";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "времяотклика";
    testRules.expectedlimitValue = Single;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 3 правило-----------------------------------
    testRules.expectedName = "Велосипед";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "скоростьпередачиданн";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 15;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 4 правило-----------------------------------
    testRules.expectedName = "Гитара";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "скоростьпечати";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 2;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 5 правило-----------------------------------
    testRules.expectedName = "Дом";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "температура";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 37 << 89;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 6 правило-----------------------------------
    testRules.expectedName = "Единорог";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "материал";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 7 правило-----------------------------------
    testRules.expectedName = "Фонарь";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "ширина";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 8 правило-----------------------------------
    testRules.expectedName = "Глобус";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "съемность";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 30;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 9 правило-----------------------------------
    testRules.expectedName = "Холодильник";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "цвет";
    testRules.expectedlimitValue = Single;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 10 правило-----------------------------------
    testRules.expectedName = "Игрушка";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "прозрачность";
    testRules.expectedlimitValue = Three;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 11 правило-----------------------------------
    testRules.expectedName = "Йога";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "плотность";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 12 правило-----------------------------------
    testRules.expectedName = "Кот";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "нейтральность";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 13 правило-----------------------------------
    testRules.expectedName = "Луна";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "материал";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 86;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 14 правило-----------------------------------
    testRules.expectedName = "Машина";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "многофункциональност";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 15 правило-----------------------------------
    testRules.expectedName = "Небо";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "отзывчивость";
    testRules.expectedlimitValue = Four;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 16 правило-----------------------------------
    testRules.expectedName = "Океан";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "тип";
    testRules.expectedlimitValue = Seven;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 17 правило-----------------------------------
    testRules.expectedName = "Парашют";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "оптическийстабилизат";
    testRules.expectedlimitValue = Seven;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 18 правило-----------------------------------
    testRules.expectedName = "Радуга";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "влажность";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 68 << 62;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 19 правило-----------------------------------
    testRules.expectedName = "Солнце";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "цвет";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 90;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 20 правило-----------------------------------
    testRules.expectedName = "Танцор";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "функциональность";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 21 правило-----------------------------------
    testRules.expectedName = "Утка";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "уровеньзаряда";
    testRules.expectedlimitValue = Four;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 22 правило-----------------------------------
    testRules.expectedName = "Фламинго";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "автоматическийвыборр";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 39;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 23 правило-----------------------------------
    testRules.expectedName = "Холм";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "качество";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 24 правило-----------------------------------
    testRules.expectedName = "Цветок";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "времяотклика";
    testRules.expectedlimitValue = Four;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 25 правило-----------------------------------
    testRules.expectedName = "Чайник";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "длина";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 88 << 33 << 51;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 26 правило-----------------------------------
    testRules.expectedName = "Шар";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "циклработы";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 36 << 56 << 56 << 99 << 10;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 27 правило-----------------------------------
    testRules.expectedName = "Щука";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "расходэнергиивожидан";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 29;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 28 правило-----------------------------------
    testRules.expectedName = "Экран";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "длина";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 96 << 44 << 9 << 98;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 29 правило-----------------------------------
    testRules.expectedName = "Юмор";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "скоростьпередачиданн";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 16;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 30 правило-----------------------------------
    testRules.expectedName = "Яхта";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "шифрованиеданных";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 31;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 31 правило-----------------------------------
    testRules.expectedName = "Апельсин";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "оптическийстабилизат";
    testRules.expectedlimitValue = Single;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 32 правило-----------------------------------
    testRules.expectedName = "Бабочка";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "максимальнаянагрузка";
    testRules.expectedlimitValue = Four;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 33 правило-----------------------------------
    testRules.expectedName = "Виолончель";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "циклработы";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 82;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 34 правило-----------------------------------
    testRules.expectedName = "Галактика";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "циклработы";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 9;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 35 правило-----------------------------------
    testRules.expectedName = "Дракон";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "эффективностьработы";
    testRules.expectedlimitValue = Five;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 36 правило-----------------------------------
    testRules.expectedName = "Ель";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "цвет";
    testRules.expectedlimitValue = Four;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 37 правило-----------------------------------
    testRules.expectedName = "Ферма";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "толщина";
    testRules.expectedlimitValue = Nine;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 38 правило-----------------------------------
    testRules.expectedName = "Газель";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "количество";
    testRules.expectedlimitValue = Three;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 39 правило-----------------------------------
    testRules.expectedName = "Хор";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "размер";
    testRules.expectedlimitValue = Nine;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 40 правило-----------------------------------
    testRules.expectedName = "Иглу";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "уровеньшума";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 3;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 41 правило-----------------------------------
    testRules.expectedName = "Картина";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "интуитивныйинтерфейс";
    testRules.expectedlimitValue = Five;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 42 правило-----------------------------------
    testRules.expectedName = "Лампа";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "конфигурация";
    testRules.expectedlimitValue = Six;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 43 правило-----------------------------------
    testRules.expectedName = "Море";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "времяработы";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 21 << 67 << 55 << 84 << 52;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 44 правило-----------------------------------
    testRules.expectedName = "Носки";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "эргономика";
    testRules.expectedlimitValue = Three;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 45 правило-----------------------------------
    testRules.expectedName = "Орел";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "защитаотпыли";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 37 << 14 << 38 << 98;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 46 правило-----------------------------------
    testRules.expectedName = "Птица";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "материал";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 94 << 30 << 76;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 47 правило-----------------------------------
    testRules.expectedName = "Ракета";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "напряжение";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 70;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 48 правило-----------------------------------
    testRules.expectedName = "Солнечный луч";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "магнитнаясовместимос";
    testRules.expectedlimitValue = Nine;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 49 правило-----------------------------------
    testRules.expectedName = "Тигр";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "оптическийстабилизат";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 50 правило-----------------------------------
    testRules.expectedName = "Узор";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "гироскопическаястаби";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 51 правило-----------------------------------
    testRules.expectedName = "Фонарик";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "автоматическийвыборр";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 48;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 52 правило-----------------------------------
    testRules.expectedName = "Хомяк";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "амортизация";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 53 правило-----------------------------------
    testRules.expectedName = "Цирк";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "эмиссия";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 64;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 54 правило-----------------------------------
    testRules.expectedName = "Чехол";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "уровенькомфорта";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 55 правило-----------------------------------
    testRules.expectedName = "Шоколад";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "срокслужбы";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 60 << 15 << 56;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 56 правило-----------------------------------
    testRules.expectedName = "Щенок";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "стабилизацияизображе";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 69 << 89 << 65 << 86 << 46;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 57 правило-----------------------------------
    testRules.expectedName = "Эксперимент";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "цветоваятемпература";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 50 << 4 << 54;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 58 правило-----------------------------------
    testRules.expectedName = "Юрист";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "эмиссия";
    testRules.expectedlimitValue = Seven;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 59 правило-----------------------------------
    testRules.expectedName = "Ягода";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "размер";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 82;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 60 правило-----------------------------------
    testRules.expectedName = "Аптека";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "стабилизацияизображе";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 71 << 49 << 10 << 26 << 87;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 61 правило-----------------------------------
    testRules.expectedName = "Банк";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "скоростьпередачиданн";
    testRules.expectedlimitValue = Four;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 62 правило-----------------------------------
    testRules.expectedName = "Весна";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "уровенькомфорта";
    testRules.expectedlimitValue = Seven;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 63 правило-----------------------------------
    testRules.expectedName = "Гора";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "уровеньзаряда";
    testRules.expectedlimitValue = Six;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 64 правило-----------------------------------
    testRules.expectedName = "Деньги";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "странапроизводства";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 98 << 8 << 29 << 77 << 62;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 65 правило-----------------------------------
    testRules.expectedName = "Жемчуг";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "напряжение";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 92;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 66 правило-----------------------------------
    testRules.expectedName = "Змея";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "длина";
    testRules.expectedlimitValue = Three;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 67 правило-----------------------------------
    testRules.expectedName = "Игла";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "системаохлаждения";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 68 правило-----------------------------------
    testRules.expectedName = "Карта";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "цена";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 54 << 31;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 69 правило-----------------------------------
    testRules.expectedName = "Полнолуние";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "конфигурация";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 77;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 70 правило-----------------------------------
    testRules.expectedName = "Маска";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "регулировкавысоты";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 69;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 71 правило-----------------------------------
    testRules.expectedName = "Нож";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "стабилизацияизображе";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 72 правило-----------------------------------
    testRules.expectedName = "Речка";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "мощность";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 95 << 8 << 67;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 73 правило-----------------------------------
    testRules.expectedName = "Палец";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "скоростьпечати";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 43;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 74 правило-----------------------------------
    testRules.expectedName = "Робот";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "сопротивление";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 26;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 75 правило-----------------------------------
    testRules.expectedName = "Сок";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "максимальнаянагрузка";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 77;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 76 правило-----------------------------------
    testRules.expectedName = "Телефон";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "материал";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 9 << 91 << 15 << 44 << 77;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 77 правило-----------------------------------
    testRules.expectedName = "Ухо";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "уровеньяркости";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 72;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 78 правило-----------------------------------
    testRules.expectedName = "Фишка";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "уровеньзаряда";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 79 правило-----------------------------------
    testRules.expectedName = "Художник";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "индикация";
    testRules.expectedlimitValue = Nine;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 80 правило-----------------------------------
    testRules.expectedName = "Цвет";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "скоростьпередачиданн";
    testRules.expectedlimitValue = Two;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 81 правило-----------------------------------
    testRules.expectedName = "Чемодан";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "индикация";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 82 правило-----------------------------------
    testRules.expectedName = "Школа";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "влажность";
    testRules.expectedlimitValue = Single;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 83 правило-----------------------------------
    testRules.expectedName = "Щит";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "защитаотпыли";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 4;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 84 правило-----------------------------------
    testRules.expectedName = "Электричество";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "вес";
    testRules.expectedlimitValue = Two;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 85 правило-----------------------------------
    testRules.expectedName = "Клерк";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "интуитивныйинтерфейс";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 86 правило-----------------------------------
    testRules.expectedName = "Ястреб";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "объемпамяти";
    testRules.expectedlimitValue = Six;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 87 правило-----------------------------------
    testRules.expectedName = "Спорткар";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "стиль";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 2;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 88 правило-----------------------------------
    testRules.expectedName = "Гнилой банан";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "эргономика";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 74 << 39 << 11 << 30;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 89 правило-----------------------------------
    testRules.expectedName = "Крутой велик";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "съемность";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 56 << 66 << 73 << 43 << 2;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 90 правило-----------------------------------
    testRules.expectedName = "Бас гитара";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "гибкость";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 25;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 91 правило-----------------------------------
    testRules.expectedName = "Котедж";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "времяработы";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 89;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 92 правило-----------------------------------
    testRules.expectedName = "С мандаринками";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "энергоэффективность";
    testRules.expectedlimitValue = Six;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 93 правило-----------------------------------
    testRules.expectedName = "Плато";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "защитаотультрафиолет";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 24;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 94 правило-----------------------------------
    testRules.expectedName = "Невыносимый";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "разрешение";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 98 << 70 << 78;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 95 правило-----------------------------------
    testRules.expectedName = "Большой";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "магнитнаясовместимос";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 96 правило-----------------------------------
    testRules.expectedName = "Сложный";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "эластичность";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 66;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 97 правило-----------------------------------
    testRules.expectedName = "С покрытием";
    testRules.expectedCondition = propertyWithNoValue;
    testRules.expectedConstraint = "покрытие";
    testRules.expectedlimitValue = NotQuantity;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 98 правило-----------------------------------
    testRules.expectedName = "П л о с к и й";
    testRules.expectedCondition = propertyWithLength;
    testRules.expectedConstraint = "размер";
    testRules.expectedlimitValue = Two;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 99 правило-----------------------------------
    testRules.expectedName = "Синий";
    testRules.expectedCondition = propertySingleValue;
    testRules.expectedConstraint = "цвет";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 1;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    //------------- 100 правило-----------------------------------
    testRules.expectedName = "Матовый";
    testRules.expectedCondition = propertyWithSeveralValues;
    testRules.expectedConstraint = "покрытие";
    testRules.expectedlimitValue = NotQuantity;
    testRules.expectedIntegerValues << 44 << 99;

    arrTestRules.append(testRules);
    testRules.expectedIntegerValues.clear();
    //-----------------------------------------------------------

    try
    {
        rules.splitStringOfClassificationRules(textRule, &arrRules);

        if(arrRules.count() != arrTestRules.count())
        {
            QFAIL("Fail");
        }

        for(int i = 0; i < arrRules.count(); i++)
        {
            QCOMPARE(arrTestRules[i].expectedName, arrRules[i].getName());
            QCOMPARE(arrTestRules[i].expectedCondition, arrRules[i].getCondition());
            QCOMPARE(arrTestRules[i].expectedConstraint, arrRules[i].getConstraint());
            QCOMPARE(arrTestRules[i].expectedlimitValue, arrRules[i].getLimitValue());

            if(arrTestRules[i].expectedIntegerValues.count() != arrRules[i].getIntegerValues().count())
            {
                QFAIL("Fail");
            }
            else
            {
                for(int j = 0; j < arrRules[i].getIntegerValues().count(); j++)
                {
                    QCOMPARE(arrTestRules[i].expectedIntegerValues[j], arrRules[i].getIntegerValues()[j]);
                }

            }
        }
    }
    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

QTEST_APPLESS_MAIN(checkClassificationRules)

#include "tst_checkThatClassificationRulesIsCorrect.moc"
