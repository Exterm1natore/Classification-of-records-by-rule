#include <QtTest>
#include "../ClassificationOfRecordsByRule/Records.h"
// add necessary includes here

class checkRecordClassification : public QObject
{
    Q_OBJECT
    class TestRecords
    {
    public:
        QMap <QString, QList<int>> expectedRelatedIntegerValues; ///< Свойства записи и соответствующие ей целочисленные значения.
        QString expectedName;                                    ///< Название записи.
    };

public:
    checkRecordClassification();
    ~checkRecordClassification();

private slots:
    void errorRecordTest();
    void oneRecordWithOneProperty();
    void oneRecordMultipleProperties();
    void anRecordWithTwentyProperties();
    void anRecordWithNineIntegerValues();
    void oneHundredRecords();
};

checkRecordClassification::checkRecordClassification()
{

}

checkRecordClassification::~checkRecordClassification()
{

}

void checkRecordClassification::errorRecordTest()
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

void checkRecordClassification::oneRecordWithOneProperty()
{
    Records record;
    TestRecords testRecord;

    QString textRecords = "Шкаф: цвет=[1].";

    QList<Records> arrRecords;
    QList<TestRecords> arrTestRecords;

    QList<QString> strTestProperty;
    QList<QList<int>> fullIntTestRecord;

    //------------- 1 запись ----------------------------------
    QList<int> intTestRecord_1;
    testRecord.expectedName = "Шкаф";
    strTestProperty << "цвет";
    intTestRecord_1 << 1;

    fullIntTestRecord << intTestRecord_1;

    //----------------------------------------------------------

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();


    try
    {
        record.splitStringOfRecords(textRecords, &arrRecords);

        QCOMPARE(arrTestRecords.count(), arrRecords.count());


        for(int i = 0; i < arrRecords.count(); i++)
        {
            QCOMPARE(testRecord.expectedName, record.getName());

            QCOMPARE(testRecord.expectedRelatedIntegerValues.count(), record.getRelatedIntegerValues().count());

            foreach(const QString& key, testRecord.expectedRelatedIntegerValues.keys())
            {
                QVERIFY(record.getRelatedIntegerValues().contains(key));
                QCOMPARE(testRecord.expectedRelatedIntegerValues.value(key).count(),
                         record.getRelatedIntegerValues().value(key).count());

                for(int j = 0; j < testRecord.expectedRelatedIntegerValues.value(key).count(); j++)
                {
                    QCOMPARE(testRecord.expectedRelatedIntegerValues.value(key)[j], record.getRelatedIntegerValues().value(key)[j]);

                }
            }
        }
    }

    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

void checkRecordClassification::oneRecordMultipleProperties()
{
    Records record;
    TestRecords testRecord;

    QString textRecords = "Игрушка: цвет=[15,1,12], размер=[10,12,45,14], текстура=[1].";

    QList<Records> arrRecords;
    QList<TestRecords> arrTestRecords;

    QList<QString> strTestProperty;
    QList<QList<int>> fullIntTestRecord;

    //------------- 1 запись ----------------------------------
    QList<int> intTestRecord_1;
    QList<int> intTestRecord_2;
    QList<int> intTestRecord_3;
    testRecord.expectedName = "Игрушка";
    strTestProperty << "цвет" << "размер" << "текстура";
    intTestRecord_1 << 15 << 1 << 12;
    intTestRecord_2 << 10 << 12 << 45 << 14;
    intTestRecord_3 << 1;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;

    //----------------------------------------------------------

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();


    try
    {
        record.splitStringOfRecords(textRecords, &arrRecords);

        QCOMPARE(arrTestRecords.count(), arrRecords.count());


        for(int i = 0; i < arrRecords.count(); i++)
        {
            QCOMPARE(testRecord.expectedName, record.getName());

            QCOMPARE(testRecord.expectedRelatedIntegerValues.count(), record.getRelatedIntegerValues().count());

            foreach(const QString& key, testRecord.expectedRelatedIntegerValues.keys())
            {
                QVERIFY(record.getRelatedIntegerValues().contains(key));
                QCOMPARE(testRecord.expectedRelatedIntegerValues.value(key).count(),
                         record.getRelatedIntegerValues().value(key).count());

                for(int j = 0; j < testRecord.expectedRelatedIntegerValues.value(key).count(); j++)
                {
                    QCOMPARE(testRecord.expectedRelatedIntegerValues.value(key)[j], record.getRelatedIntegerValues().value(key)[j]);

                }
            }
        }
    }

    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

void checkRecordClassification::anRecordWithTwentyProperties()
{
    Records record;
    TestRecords testRecord;

    QString textRecords = "Шкаф: один=[1], два=[2], три=[3], четыре=[4], пять=[5], шесть=[6], семь=[7], весемь=[8], "
                          "девять=[9], десять=[10], одинадцать=[11], двенадцать=[12], тринадцать=[13], четырнадцать=[14], "
                          "пятнадцать=[15], шестнадцать=[16], семнадцать=[17], восемнадцать=[18], девятнадцать=[19], "
                          "двадцать=[20].";

    QList<Records> arrRecords;
    QList<TestRecords> arrTestRecords;

    QList<QString> strTestProperty;
    QList<QList<int>> fullIntTestRecord;

    //------------- 1 запись ----------------------------------
    QList<int> intTestRecord_1;
    QList<int> intTestRecord_2;
    QList<int> intTestRecord_3;
    QList<int> intTestRecord_4;
    QList<int> intTestRecord_5;
    QList<int> intTestRecord_6;
    QList<int> intTestRecord_7;
    QList<int> intTestRecord_8;
    QList<int> intTestRecord_9;
    QList<int> intTestRecord_10;
    QList<int> intTestRecord_11;
    QList<int> intTestRecord_12;
    QList<int> intTestRecord_13;
    QList<int> intTestRecord_14;
    QList<int> intTestRecord_15;
    QList<int> intTestRecord_16;
    QList<int> intTestRecord_17;
    QList<int> intTestRecord_18;
    QList<int> intTestRecord_19;
    QList<int> intTestRecord_20;
    testRecord.expectedName = "Шкаф";
    strTestProperty << "один" << "два" << "три" << "четыре" << "пять" << "шесть" << "семь" << "весемь" << "девять" << "десять" << "одинадцать" << "двенадцать" << "тринадцать" << "четырнадцать" << "пятнадцать" << "шестнадцать" << "семнадцать" << "восемнадцать" << "девятнадцать" << "двадцать";
    intTestRecord_1 << 1;
    intTestRecord_2 << 2;
    intTestRecord_3 << 3;
    intTestRecord_4 << 4;
    intTestRecord_5 << 5;
    intTestRecord_6 << 6;
    intTestRecord_7 << 7;
    intTestRecord_8 << 8;
    intTestRecord_9 << 9;
    intTestRecord_10 << 10;
    intTestRecord_11 << 11;
    intTestRecord_12 << 12;
    intTestRecord_13 << 13;
    intTestRecord_14 << 14;
    intTestRecord_15 << 15;
    intTestRecord_16 << 16;
    intTestRecord_17 << 17;
    intTestRecord_18 << 18;
    intTestRecord_19 << 19;
    intTestRecord_20 << 20;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8 << intTestRecord_9 << intTestRecord_10
                      << intTestRecord_11 << intTestRecord_12 << intTestRecord_13
                      << intTestRecord_14 << intTestRecord_15 << intTestRecord_16
                      << intTestRecord_17 << intTestRecord_18 << intTestRecord_19
                      << intTestRecord_20;

    //----------------------------------------------------------

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();


    try
    {
        record.splitStringOfRecords(textRecords, &arrRecords);

        QCOMPARE(arrTestRecords.count(), arrRecords.count());


        for(int i = 0; i < arrRecords.count(); i++)
        {
            QCOMPARE(testRecord.expectedName, record.getName());

            QCOMPARE(testRecord.expectedRelatedIntegerValues.count(), record.getRelatedIntegerValues().count());

            foreach(const QString& key, testRecord.expectedRelatedIntegerValues.keys())
            {
                QVERIFY(record.getRelatedIntegerValues().contains(key));
                QCOMPARE(testRecord.expectedRelatedIntegerValues.value(key).count(),
                         record.getRelatedIntegerValues().value(key).count());

                for(int j = 0; j < testRecord.expectedRelatedIntegerValues.value(key).count(); j++)
                {
                    QCOMPARE(testRecord.expectedRelatedIntegerValues.value(key)[j], record.getRelatedIntegerValues().value(key)[j]);

                }
            }
        }
    }

    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

void checkRecordClassification::anRecordWithNineIntegerValues()
{
    Records record;
    TestRecords testRecord;

    QString textRecords = "Шкаф: цвет=[1, 2, 3, 4, 5, 6, 7, 8, 9].";

    QList<Records> arrRecords;
    QList<TestRecords> arrTestRecords;

    QList<QString> strTestProperty;
    QList<QList<int>> fullIntTestRecord;

    //------------- 1 запись ----------------------------------
    QList<int> intTestRecord_1;
    testRecord.expectedName = "Шкаф";
    strTestProperty << "цвет";
    intTestRecord_1 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9;

    fullIntTestRecord << intTestRecord_1;

    //----------------------------------------------------------

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();


    try
    {
        record.splitStringOfRecords(textRecords, &arrRecords);

        QCOMPARE(arrTestRecords.count(), arrRecords.count());


        for(int i = 0; i < arrRecords.count(); i++)
        {
            QCOMPARE(testRecord.expectedName, record.getName());

            QCOMPARE(testRecord.expectedRelatedIntegerValues.count(), record.getRelatedIntegerValues().count());

            foreach(const QString& key, testRecord.expectedRelatedIntegerValues.keys())
            {
                QVERIFY(record.getRelatedIntegerValues().contains(key));
                QCOMPARE(testRecord.expectedRelatedIntegerValues.value(key).count(),
                         record.getRelatedIntegerValues().value(key).count());

                for(int j = 0; j < testRecord.expectedRelatedIntegerValues.value(key).count(); j++)
                {
                    QCOMPARE(testRecord.expectedRelatedIntegerValues.value(key)[j], record.getRelatedIntegerValues().value(key)[j]);

                }
            }
        }
    }

    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

void checkRecordClassification::oneHundredRecords()
{
    Records record;
    TestRecords testRecord;

    QString textRecords = "Автомобиль:регулировкавысоты=[3,9,68,40], глубина=[1,92,98, 70,60], масштабируемость=[23,98,90], времяработы=[19], масштабирующийзум=[31], шифрованиекоммуникац=[63,58,98,98], тип=[28], толщина=[22,42,56,74,58];"
                          "Банан:эластичность=[7,95], стабилизацияизображе=[8], глубина=[26,84,37,77], защитаотперегрузки=[56,72], встроенныединамики=[96,74,1,33,83], объемпамяти=[26,89,52];"
                          "Велосипед:уровеньшума=[61,15], надежность=[5,98], размер=[17,30,34,53], уровеньяркости=[75,84,59,20], максимальнаянагрузка=[8];"
                          "Гитара:прочность=[49,33], экономичность=[17,75,65,88], плотность=[39,34,85,42,64], многофункциональност=[93,53], цена=[30,66];"
                          "Дом:времяотклика=[75,82,84,84], цветоваятемпература=[79,87,4,70,79];"
                          "Ель:эффективностьработы=[79,99];"
                          "Фонарь:яркость=[76], воздухообмен=[57,75,26,33,30], эмиссия=[8], совместимость=[4,32,41,77], максимальнаянагрузка=[63,51], высота=[95,66], регулировкавысоты=[7,72,18,88], эффективностьработы=[69,49,9];"
                          "Глобус:уровеньшума=[19,75,16,9];"
                          "Холодильник:качество=[7], эргономика=[1,45,41], автоматическийвыборр=[4,46], защитаотультрафиолет=[95,71,34,72,84], масштабирующийзум=[32,32,38], съемность=[76];"
                          "Игрушка:форма=[30,19];"
                          "Йогурт:высота=[69,18,89,54,9];"
                          "Книга:странапроизводства=[48,48,33,19,54];"
                          "Лампа:разрешение=[75,72], гибкость=[82,29], ширина=[89,18,76,74];"
                          "Мяч:длина=[68];"
                          "Ноутбук:толщина=[21,10], амортизация=[6,53,62,1,98], уголобзора=[97,8,30], яркость=[56,27,41,71,63], странапроизводства=[32], расходэнергиивожидан=[4,35,22,93];"
                          "Очки:функцияавтоматическо=[14,10,51], скоростьпередачиданн=[31,54], защитаотвлаги=[98,86,68], уровеньгромкости=[25,69,87,48,9], уровеньзащиты=[4,13,28], плотностьпикселей=[51,70,30,82], защитаотультрафиолет=[71,51,27], резкость=[69], форма=[23,26,56,69];"
                          "Пианино:конфигурация=[80], системаохлаждения=[76,23,93];"
                          "Рубашка:скорость=[92,6], гибкость=[60], уровеньзащиты=[70,90], амортизация=[90,56,49], надежность=[14,87,9], функциональность=[14,17], шифрованиеданных=[33,99,63], оптическийстабилизат=[82,91,43,15,95];"
                          "Сумка:высота=[18,95,69], габариты=[92,70], защитаотпыли=[20,12], шифрованиекоммуникац=[25,68,25,13], вес=[82,2,43,14], уголобзора=[30,70,26,33];"
                          "Телефон:освещенность=[75,97], защитаотвлаги=[95,7,86];"
                          "Утюг:защитноепокрытие=[50,10,53,8];"
                          "Футболка:тип=[74,96,45];"
                          "Хлеб:напряжение=[43,99,42], максимальнаянагрузка=[49,34], скорость=[42,66,93];"
                          "Цветок:масштабируемость=[73,74];"
                          "Часы:максимальнаянагрузка=[54,14,36], объемпамяти=[9,38,4], шифрованиеданных=[32,67,19], скоростьпередачиданн=[84], материал=[47], защитаотультрафиолет=[64,84,47,76];"
                          "Шапка:времяотклика=[19,58,7], амортизация=[8,72], скоростьпередачиданн=[67,88], масштабируемость=[67,13], цвет=[26];"
                          "Щит:регулировкавысоты=[51,57], плотностьпикселей=[35,56], глубина=[41,13,99,82], расходэнергиивожидан=[6,44,11,14];"
                          "Электроника:габариты=[40,99], контрастность=[89,50,83,80,78], максимальнаянагрузка=[54,15,64,6,69], защитноепокрытие=[22,21,15], шифрованиеданных=[15,98,70,59,31];"
                          "Юбка:материал=[52,30], отзывчивость=[37], тип=[18,57];"
                          "Яблоко:масштабирующийзум=[69], функцияавтоматическо=[10], интуитивныйинтерфейс=[44,60,20,16], прочность=[71,19,6,36,40];"
                          "Апельсинчик:стабилизацияизображе=[99,77,28,63,75], эмиссия=[15,3,79], поддержкаформатов=[18,95,26,58], циклработы=[92,66,42,35,88], надежность=[72], срокслужбы=[79], цена=[95,1,23,89], освещенность=[53,32];"
                          "Браслет:гироскопическаястаби=[94,75];"
                          "Виолончель:яркость=[5,22,18], вес=[19,62], сопротивление=[72,65,25,13,18], уровеньшума=[60,89], уровеньзаряда=[77,99], поглощениезвука=[61], защитноепокрытие=[81,73], частотапроцессора=[78], амортизация=[99,20,95,20,23];"
                          "Гармоника:цветоваятемпература=[62,35,69], функциональность=[81,93], мощность=[13,87,18], нейтральность=[18,31], длина=[89], уровеньэнергопотребл=[26,92,83], ширина=[34,75], глубина=[22,57,79,14];"
                          "Дверь:резкость=[31,5,99,98,85], контрастность=[46,29,80,49,78], стабилизацияизображе=[12,5], материал=[65,7,98,78,82], нейтральность=[94,42,19,9], автоматическийвыборр=[99,65,97], защитаотвлаги=[12,57], масштабирующийзум=[40,15,79,37];"
                          "Ежик:объемпамяти=[20,82,57,41,55], количество=[24,56,31,67,71], шифрованиеданных=[90], цвет=[40,69,97,37], вес=[40,61], эффективностьработы=[78];"
                          "Флейта:высота=[37,77,95,66,79], уголобзора=[49,2,66,24,11], времяотклика=[59], энергоэффективность=[23,41,1,2,28], уровеньзащиты=[19,18];"
                          "Газета:цветоваятемпература=[85,99,47,64,99], защитаоткоррозии=[85,4,52,64], надежность=[67,46,4,32,63], расходэнергиивожидан=[87,91,3,77,27], стабильность=[59], стиль=[94,40,70,75], уровеньшума=[70], запах=[94,70];"
                          "Холст:масштабируемость=[62,55,92,30], функцияавтоматическо=[73,28,69,15], влажность=[88,39,32,72,86], разрешение=[18,80,26], прозрачность=[22], высота=[23,28,16,88], уровеньзащиты=[10,82,90,83,32], стиль=[93,64,4,73], воздухообмен=[22,84,31];"
                          "Игла:частотапроцессора=[43], скоростьчтения=[56], многофункциональност=[84], сопротивление=[64,49,20,54], контрастность=[52], скорость=[60], стабилизацияизображе=[10,17], стиль=[56];"
                          "Картина:защитаотперегрузки=[44,18,92,16,89], защитаоткоррозии=[82,23,34,77,10], времяработы=[5,93,12,30,42], цветоваятемпература=[38,12,49,74], циклработы=[39,62], энергоэффективность=[47,50,38,32,39];"
                          "Ластик:габариты=[71,48,16,97,21];"
                          "Молоток:системаохлаждения=[97,45,10], влажность=[99,20,49,91], стиль=[38,56,51,11,74], уровеньгромкости=[9,71,22], яркость=[35,10,2,84,44], воздухообмен=[90,40,6,21];"
                          "Носки:масштабируемость=[47,25,35,76,16], эластичность=[59,61,23,39];"
                          "Очиститель:цветоваятемпература=[29,20,22,17], срокслужбы=[91,47,76];"
                          "Парашют:стабильность=[73,14], совместимость=[25,30], надежность=[68], отзывчивость=[10,23,8,87,22], защитноепокрытие=[97,33,88,49,55], нейтральность=[99], температура=[10,20];"
                          "Ручка:расходэнергиивожидан=[88,56], амортизация=[42,54,61,58,80], уровеньяркости=[24], нейтральность=[57,92], уровенькомфорта=[62], магнитнаясовместимос=[89,1,75,62], антибликовоепокрытие=[33,72,7], защитаотультрафиолет=[73,60,48,53,78], уголобзора=[92,58];"
                          "Сковорода:странапроизводства=[74,4], освещенность=[42,77,60,83,42], масштабируемость=[46,25,97,81], ширина=[21], уровеньэнергопотребл=[23], поглощениезвука=[81,76,74,71];"
                          "Таблетка:сопротивление=[26,30], защитноепокрытие=[87,23,89,81,7], амортизация=[9,19,25,89], защитаотвлаги=[52,11,82,49,86], скорость=[64,50], масштабируемость=[9,66,32];"
                          "Украшение:плотностьпикселей=[88], уголобзора=[40,98,54,51];"
                          "Фотоаппарат:системаохлаждения=[35,78,1], уровеньэнергопотребл=[97,67];"
                          "Хлопушка:уровеньэнергопотребл=[16,32,31,17], функцияавтоматическо=[53,15], энергоэффективность=[34,10,95], влажность=[85,22,96], скорость=[2,33,84,85,21], надежность=[61,96,62,12], масштабируемость=[7,43,94,56,17], объемпамяти=[26,30,54,17,68];"
                          "Циркуль:оптическийстабилизат=[56,43,45,19,99], странапроизводства=[31,54,85], системаохлаждения=[50,88,69];"
                          "Чехол:воздухообмен=[7,52,60,90,90], индикация=[75,2], поддержкаформатов=[49,65,45,76,95], мощность=[95,29,25], тип=[71,73], высота=[50,28], толщина=[33,16,27];"
                          "Шарф:съемность=[38,7,64,86], прозрачность=[91,23], напряжение=[2,97,31,38], стабилизацияизображе=[28], эргономика=[72], уровеньзаряда=[67,82];"
                          "Щетка:толщина=[5,65], ширина=[5,3], частотапроцессора=[12,14,87];"
                          "Экран:антибликовоепокрытие=[74], отзывчивость=[74,17,85], регулировкавысоты=[39,61], амортизация=[13,16], вкус=[76,95,60,75,1], встроенныединамики=[45,48,94], запах=[38], защитноепокрытие=[31,85], системаохлаждения=[68,48,84];"
                          "Юмор:оптическийстабилизат=[72,23,84], длина=[25], температура=[48,74,10,32], плотностьпикселей=[99,91];"
                          "Ящик:стабильность=[47,51,42], резкость=[38], уровеньгромкости=[79], объемпамяти=[24,7];"
                          "Авокадо:сопротивление=[76,52], глубина=[91,76,26,30,95], надежность=[92,52,75,92,81], эффективностьработы=[11,54,43,3,79], разрешение=[99,45,32,21], уровеньяркости=[17], плотностьпикселей=[22,77,2,44], уровеньшума=[89,67,58];"
                          "Банк:защитаоткоррозии=[4,74,41], максимальнаянагрузка=[53,54], влажность=[95], цветоваятемпература=[29,54,34], защитаотвлаги=[17,37,18,58,36], плотность=[31,65,85,49,5], амортизация=[4,15,14,27,69], прочность=[11,43,92,61], оптическийстабилизат=[64,35];"
                          "Весы:мощность=[72,30,52], разрешение=[38], форма=[87], эргономика=[90];"
                          "Горшок:разъемыподключения=[6,59,6,88], циклработы=[90,66,96,85], скоростьпечати=[86], уровеньяркости=[57,14,36,4,69], шифрованиеданных=[10,75,48], защитноепокрытие=[82,19,89,42,74], скоростьпередачиданн=[5,17], интуитивныйинтерфейс=[18,37,61,79];"
                          "Джинсы:объемпамяти=[66,94,20,69], баланс=[52,16,92], цветоваятемпература=[45], длина=[73,27,12,44,17], прозрачность=[25,80,51,78], уровеньэнергопотребл=[65], странапроизводства=[74];"
                          "Журнал:плотностьпикселей=[97,23,18];"
                          "Зеркало:уровеньзаряда=[65,8,80,89,19], срокслужбы=[13], расходэнергиивожидан=[69], материал=[73,78], цена=[2], антибликовоепокрытие=[52,86,30,67];"
                          "Иглоушка:материал=[30,5], прозрачность=[26,56], качество=[75,44], поглощениезвука=[79,28];"
                          "Ключ:частотапроцессора=[24,66], прочность=[5,7,43,2], антибликовоепокрытие=[27,89], защитаоткоррозии=[22,84], стабилизацияизображе=[44,76], баланс=[87,87,39,76,96], интуитивныйинтерфейс=[9,26,43], разъемыподключения=[4], шифрованиеданных=[58,23,64,36];"
                          "Лейка:поглощениезвука=[50,45,71,35], антибликовоепокрытие=[28];"
                          "Музыка:разъемыподключения=[41,53,4,74], гироскопическаястаби=[22,78,58,91,31], высота=[28,59,5,70,24];"
                          "Ножницы:запах=[67,39,90], скоростьпередачиданн=[65,87,3,12,84], качество=[20,59,18,20,43], глубина=[28];"
                          "Одеяло:циклработы=[35], запах=[59,84], размер=[27], антибликовоепокрытие=[83,3,24], поглощениезвука=[85,88];"
                          "Паста:защитаотперегрузки=[3,19,43,18,17], количество=[34], уровеньэнергопотребл=[1,3], системаохлаждения=[72,82,29,66,25], шифрованиекоммуникац=[49,58,92], уголобзора=[13,11], защитаотпыли=[1,21,71], оптическийстабилизат=[47,50], тип=[6];"
                          "Ремень:баланс=[67], поглощениезвука=[72,30,94,36], защитаотультрафиолет=[55], уровеньяркости=[56,19,62,87,70], толщина=[4,35,83,29];"
                          "Серьга:освещенность=[95,8,69,77,58], срокслужбы=[26];"
                          "Торт:многофункциональност=[34,81,23,59,42], уровеньшума=[84,10,85,97,42];"
                          "Удочка:времяработы=[7,90,9,39], уровеньяркости=[34,77], функцияавтоматическо=[42,82,92,82,39], разрешение=[62,47,91], резкость=[59,86,91], отзывчивость=[10,46,55,75];"
                          "Фонарик:вкус=[55,39,60], плотностьпикселей=[72,1,12,62], эффективностьработы=[96,8,97], уровенькомфорта=[35,93,24,52,42], поглощениезвука=[96,47,16,11], съемность=[63,16,25], резкость=[52,70,34,47];"
                          "Хор:уровеньзащиты=[30,39,21,39], плотностьпикселей=[78,26,76,90], баланс=[69,81,43,82,89], стабилизацияизображе=[89], масштабируемость=[94,54,44,15,69], защитноепокрытие=[68,16,47,84], ширина=[6], толщина=[68,14,45,23,99];"
                          "Цепь:гироскопическаястаби=[96,41,22,30], функцияавтоматическо=[17,22,6,98], магнитнаясовместимос=[72,26,96,81], скоростьпечати=[78,17,17,55,9], длина=[20,50,67], воспроизведениецвето=[84];"
                          "Чайник:уголобзора=[76,15,72,65,2];"
                          "Шкаф:многофункциональност=[48], разъемыподключения=[58], вкус=[15,20,48,45,56], мощность=[12,21,77,41,4], гироскопическаястаби=[61,97,68,15,63], регулировкавысоты=[63], энергоэффективность=[50,41,86,39];"
                          "Щипцы:скоростьчтения=[84,8,5];"
                          "Эскимо:энергоэффективность=[29,15], влажность=[76,65,76,43], объемпамяти=[23,63,90,28], запах=[22,2], стиль=[95,6,91], защитаоткоррозии=[88,56,78,45];"
                          "Юрист:плотность=[58,66,40];"
                          "Ястреб:резкость=[56,87,26,39], мощность=[26,15], эмиссия=[39], амортизация=[55,26,19];"
                          "Апельсин:уровеньяркости=[5,68,7,55,81], толщина=[2,76,87], защитаотвлаги=[99,96,32,66], масштабирующийзум=[27], съемность=[15,87];"
                          "Ожерелье:тип=[54,8,23,93,97], цена=[37,44];"
                          "Контрабас:нейтральность=[46], стабилизацияизображе=[40,38,38,9], разъемыподключения=[22,78,2], плотность=[99,55,99], системаохлаждения=[33,2,73,44,87], отзывчивость=[99,2,65,83], конфигурация=[3,63];"
                          "Балалайка:тип=[61], мощность=[84,45], стабилизацияизображе=[19,78], цветоваятемпература=[68], контрастность=[7,51,60,85,16];"
                          "Ворота:размер=[82,93,22,11,76], циклработы=[26,40,8], напряжение=[3,18,11,18,57], ширина=[64,77,30], интуитивныйинтерфейс=[44,39,18,63];"
                          "Ежёнок:гироскопическаястаби=[84,83,10,81], баланс=[25], размер=[11,57], габариты=[4,38,25];"
                          "Ксилофон:магнитнаясовместимос=[79,30], уровеньшума=[4], частотапроцессора=[88,34,69], форма=[4,92,46], отзывчивость=[44,69,54], скорость=[1,45,55,36,34];"
                          "Билютень:защитаоткоррозии=[68,6,86,95,4], защитноепокрытие=[5,8,73], тип=[29,33,61,77,54], конфигурация=[74,16,89,27], масштабирующийзум=[66,10,96,84];"
                          "Палитра:времяработы=[42], освещенность=[73,85], эмиссия=[61,70,61,59];"
                          "Иголка:индикация=[90,6,88], толщина=[4,83], странапроизводства=[29,2];"
                          "Карточка:влажность=[53];"
                          "Игрушки: цвет=[15,1,12], размер=[10,12,45,14], текстура=[1];"
                          "Мячик: форма=[14], раскрас=[6,14], покрытие=[44,21];"
                          "Cтол:размер=[1,2],цвет=[99,1,3],покрытие=[12].";

    QList<Records> arrRecords;
    QList<TestRecords> arrTestRecords;

    QList<QString> strTestProperty;
    QList<QList<int>> fullIntTestRecord;


    //------------- 1 запись ----------------------------------
    QList<int> intTestRecord_1;
    QList<int> intTestRecord_2;
    QList<int> intTestRecord_3;
    QList<int> intTestRecord_4;
    QList<int> intTestRecord_5;
    QList<int> intTestRecord_6;
    QList<int> intTestRecord_7;
    QList<int> intTestRecord_8;
    QList<int> intTestRecord_9;
    QList<int> intTestRecord_10;
    QList<int> intTestRecord_11;
    QList<int> intTestRecord_12;
    QList<int> intTestRecord_13;
    QList<int> intTestRecord_14;
    QList<int> intTestRecord_15;
    QList<int> intTestRecord_16;
    QList<int> intTestRecord_17;
    QList<int> intTestRecord_18;
    QList<int> intTestRecord_19;
    QList<int> intTestRecord_20;
    testRecord.expectedName = "Автомобиль";
    strTestProperty << "регулировкавысоты" << "глубина" << "масштабируемость" << "времяработы" << "масштабирующийзум" << "шифрованиекоммуникац" << "тип" << "толщина";
    intTestRecord_1 << 3 << 9 << 68 << 40;
    intTestRecord_2 << 1 << 92 << 98 << 70 << 60;
    intTestRecord_3 << 23 << 98 << 90;
    intTestRecord_4 << 19;
    intTestRecord_5 << 31;
    intTestRecord_6 << 63 << 58 << 98 << 98;
    intTestRecord_7 << 28;
    intTestRecord_8 << 22 << 42 << 56 << 74 << 58;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 2 запись ----------------------------------

    testRecord.expectedName = "Банан";
    strTestProperty << "эластичность" << "стабилизацияизображе" << "глубина" << "защитаотперегрузки" << "встроенныединамики" << "объемпамяти";
    intTestRecord_1 << 7 << 95;
    intTestRecord_2 << 8;
    intTestRecord_3 << 26 << 84 << 37 << 77;
    intTestRecord_4 << 56 << 72;
    intTestRecord_5 << 96 << 74 << 1 << 33 << 83;
    intTestRecord_6 << 26 << 89 << 52;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 3 запись ----------------------------------

    testRecord.expectedName = "Велосипед";
    strTestProperty << "уровеньшума" << "надежность" << "размер" << "уровеньяркости" << "максимальнаянагрузка";
    intTestRecord_1 << 61 << 15;
    intTestRecord_2 << 5 << 98;
    intTestRecord_3 << 17 << 30 << 34 << 53;
    intTestRecord_4 << 75 << 84 << 59 << 20;
    intTestRecord_5 << 8;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 4 запись ----------------------------------

    testRecord.expectedName = "Гитара";
    strTestProperty << "прочность" << "экономичность" << "плотность" << "многофункциональност" << "цена";
    intTestRecord_1 << 49 << 33;
    intTestRecord_2 << 17 << 75 << 65 << 88;
    intTestRecord_3 << 39 << 34 << 85 << 42 << 64;
    intTestRecord_4 << 93 << 53;
    intTestRecord_5 << 30 << 66;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 5 запись ----------------------------------

    testRecord.expectedName = "Дом";
    strTestProperty << "времяотклика" << "цветоваятемпература";
    intTestRecord_1 << 75 << 82 << 84 << 84;
    intTestRecord_2 << 79 << 87 << 4 << 70 << 79;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2;
    intTestRecord_1.clear();
    intTestRecord_2.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 6 запись ----------------------------------

    testRecord.expectedName = "Ель";
    strTestProperty << "эффективностьработы";
    intTestRecord_1 << 79 << 99;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 7 запись ----------------------------------

    testRecord.expectedName = "Фонарь";
    strTestProperty << "яркость" << "воздухообмен" << "эмиссия" << "совместимость" << "максимальнаянагрузка" << "высота" << "регулировкавысоты" << "эффективностьработы";
    intTestRecord_1 << 76;
    intTestRecord_2 << 57 << 75 << 26 << 33 << 30;
    intTestRecord_3 << 8;
    intTestRecord_4 << 4 << 32 << 41 << 77;
    intTestRecord_5 << 63 << 51;
    intTestRecord_6 << 95 << 66;
    intTestRecord_7 << 7 << 72 << 18 << 88;
    intTestRecord_8 << 69 << 49 << 9;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 8 запись ----------------------------------

    testRecord.expectedName = "Глобус";
    strTestProperty << "уровеньшума";
    intTestRecord_1 << 19 << 75 << 16 << 9;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 9 запись ----------------------------------

    testRecord.expectedName = "Холодильник";
    strTestProperty << "качество" << "эргономика" << "автоматическийвыборр" << "защитаотультрафиолет" << "масштабирующийзум" << "съемность";
    intTestRecord_1 << 7;
    intTestRecord_2 << 1 << 45 << 41;
    intTestRecord_3 << 4 << 46;
    intTestRecord_4 << 95 << 71 << 34 << 72 << 84;
    intTestRecord_5 << 32 << 32 << 38;
    intTestRecord_6 << 76;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 10 запись ----------------------------------

    testRecord.expectedName = "Игрушка";
    strTestProperty << "форма";
    intTestRecord_1 << 30 << 19;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 11 запись ----------------------------------

    testRecord.expectedName = "Йогурт";
    strTestProperty << "высота";
    intTestRecord_1 << 69 << 18 << 89 << 54 << 9;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 12 запись ----------------------------------

    testRecord.expectedName = "Книга";
    strTestProperty << "странапроизводства";
    intTestRecord_1 << 48 << 48 << 33 << 19 << 54;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 13 запись ----------------------------------

    testRecord.expectedName = "Лампа";
    strTestProperty << "разрешение" << "гибкость" << "ширина";
    intTestRecord_1 << 75 << 72;
    intTestRecord_2 << 82 << 29;
    intTestRecord_3 << 89 << 18 << 76 << 74;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 14 запись ----------------------------------

    testRecord.expectedName = "Мяч";
    strTestProperty << "длина";
    intTestRecord_1 << 68;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 15 запись ----------------------------------

    testRecord.expectedName = "Ноутбук";
    strTestProperty << "толщина" << "амортизация" << "уголобзора" << "яркость" << "странапроизводства" << "расходэнергиивожидан";
    intTestRecord_1 << 21 << 10;
    intTestRecord_2 << 6 << 53 << 62 << 1 << 98;
    intTestRecord_3 << 97 << 8 << 30;
    intTestRecord_4 << 56 << 27 << 41 << 71 << 63;
    intTestRecord_5 << 32;
    intTestRecord_6 << 4 << 35 << 22 << 93;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 16 запись ----------------------------------

    testRecord.expectedName = "Очки";
    strTestProperty << "функцияавтоматическо" << "скоростьпередачиданн" << "защитаотвлаги" << "уровеньгромкости" << "уровеньзащиты" << "плотностьпикселей" << "защитаотультрафиолет" << "резкость" << "форма";
    intTestRecord_1 << 14 << 10 << 51;
    intTestRecord_2 << 31 << 54;
    intTestRecord_3 << 98 << 86 << 68;
    intTestRecord_4 << 25 << 69 << 87 << 48 << 9;
    intTestRecord_5 << 4 << 13 << 28;
    intTestRecord_6 << 51 << 70 << 30 << 82;
    intTestRecord_7 << 71 << 51 << 27;
    intTestRecord_8 << 69;
    intTestRecord_9 << 23 << 26 << 56 << 69;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8 << intTestRecord_9;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();
    intTestRecord_9.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 17 запись ----------------------------------

    testRecord.expectedName = "Пианино";
    strTestProperty << "конфигурация" << "системаохлаждения";
    intTestRecord_1 << 80;
    intTestRecord_2 << 76 << 23 << 93;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2;
    intTestRecord_1.clear();
    intTestRecord_2.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 18 запись ----------------------------------

    testRecord.expectedName = "Рубашка";
    strTestProperty << "скорость" << "гибкость" << "уровеньзащиты" << "амортизация" << "надежность" << "функциональность" << "шифрованиеданных" << "оптическийстабилизат";
    intTestRecord_1 << 92 << 6;
    intTestRecord_2 << 60;
    intTestRecord_3 << 70 << 90;
    intTestRecord_4 << 90 << 56 << 49;
    intTestRecord_5 << 14 << 87 << 9;
    intTestRecord_6 << 14 << 17;
    intTestRecord_7 << 33 << 99 << 63;
    intTestRecord_8 << 82 << 91 << 43 << 15 << 95;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 19 запись ----------------------------------

    testRecord.expectedName = "Сумка";
    strTestProperty << "высота" << "габариты" << "защитаотпыли" << "шифрованиекоммуникац" << "вес" << "уголобзора";
    intTestRecord_1 << 18 << 95 << 69;
    intTestRecord_2 << 92 << 70;
    intTestRecord_3 << 20 << 12;
    intTestRecord_4 << 25 << 68 << 25 << 13;
    intTestRecord_5 << 82 << 2 << 43 << 14;
    intTestRecord_6 << 30 << 70 << 26 << 33;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 20 запись ----------------------------------

    testRecord.expectedName = "Телефон";
    strTestProperty << "освещенность" << "защитаотвлаги";
    intTestRecord_1 << 75 << 97;
    intTestRecord_2 << 95 << 7 << 86;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2;
    intTestRecord_1.clear();
    intTestRecord_2.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 21 запись ----------------------------------

    testRecord.expectedName = "Утюг";
    strTestProperty << "защитноепокрытие";
    intTestRecord_1 << 50 << 10 << 53 << 8;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 22 запись ----------------------------------

    testRecord.expectedName = "Футболка";
    strTestProperty << "тип";
    intTestRecord_1 << 74 << 96 << 45;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 23 запись ----------------------------------

    testRecord.expectedName = "Хлеб";
    strTestProperty << "напряжение" << "максимальнаянагрузка" << "скорость";
    intTestRecord_1 << 43 << 99 << 42;
    intTestRecord_2 << 49 << 34;
    intTestRecord_3 << 42 << 66 << 93;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 24 запись ----------------------------------

    testRecord.expectedName = "Цветок";
    strTestProperty << "масштабируемость";
    intTestRecord_1 << 73 << 74;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 25 запись ----------------------------------

    testRecord.expectedName = "Часы";
    strTestProperty << "максимальнаянагрузка" << "объемпамяти" << "шифрованиеданных" << "скоростьпередачиданн" << "материал" << "защитаотультрафиолет";
    intTestRecord_1 << 54 << 14 << 36;
    intTestRecord_2 << 9 << 38 << 4;
    intTestRecord_3 << 32 << 67 << 19;
    intTestRecord_4 << 84;
    intTestRecord_5 << 47;
    intTestRecord_6 << 64 << 84 << 47 << 76;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 26 запись ----------------------------------

    testRecord.expectedName = "Шапка";
    strTestProperty << "времяотклика" << "амортизация" << "скоростьпередачиданн" << "масштабируемость" << "цвет";
    intTestRecord_1 << 19 << 58 << 7;
    intTestRecord_2 << 8 << 72;
    intTestRecord_3 << 67 << 88;
    intTestRecord_4 << 67 << 13;
    intTestRecord_5 << 26;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 27 запись ----------------------------------

    testRecord.expectedName = "Щит";
    strTestProperty << "регулировкавысоты" << "плотностьпикселей" << "глубина" << "расходэнергиивожидан";
    intTestRecord_1 << 51 << 57;
    intTestRecord_2 << 35 << 56;
    intTestRecord_3 << 41 << 13 << 99 << 82;
    intTestRecord_4 << 6 << 44 << 11 << 14;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 28 запись ----------------------------------

    testRecord.expectedName = "Электроника";
    strTestProperty << "габариты" << "контрастность" << "максимальнаянагрузка" << "защитноепокрытие" << "шифрованиеданных";
    intTestRecord_1 << 40 << 99;
    intTestRecord_2 << 89 << 50 << 83 << 80 << 78;
    intTestRecord_3 << 54 << 15 << 64 << 6 << 69;
    intTestRecord_4 << 22 << 21 << 15;
    intTestRecord_5 << 15 << 98 << 70 << 59 << 31;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 29 запись ----------------------------------

    testRecord.expectedName = "Юбка";
    strTestProperty << "материал" << "отзывчивость" << "тип";
    intTestRecord_1 << 52 << 30;
    intTestRecord_2 << 37;
    intTestRecord_3 << 18 << 57;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 30 запись ----------------------------------

    testRecord.expectedName = "Яблоко";
    strTestProperty << "масштабирующийзум" << "функцияавтоматическо" << "интуитивныйинтерфейс" << "прочность";
    intTestRecord_1 << 69;
    intTestRecord_2 << 10;
    intTestRecord_3 << 44 << 60 << 20 << 16;
    intTestRecord_4 << 71 << 19 << 6 << 36 << 40;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 31 запись ----------------------------------

    testRecord.expectedName = "Апельсинчик";
    strTestProperty << "стабилизацияизображе" << "эмиссия" << "поддержкаформатов" << "циклработы" << "надежность" << "срокслужбы" << "цена" << "освещенность";
    intTestRecord_1 << 99 << 77 << 28 << 63 << 75;
    intTestRecord_2 << 15 << 3 << 79;
    intTestRecord_3 << 18 << 95 << 26 << 58;
    intTestRecord_4 << 92 << 66 << 42 << 35 << 88;
    intTestRecord_5 << 72;
    intTestRecord_6 << 79;
    intTestRecord_7 << 95 << 1 << 23 << 89;
    intTestRecord_8 << 53 << 32;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 32 запись ----------------------------------

    testRecord.expectedName = "Браслет";
    strTestProperty << "гироскопическаястаби";
    intTestRecord_1 << 94 << 75;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 33 запись ----------------------------------

    testRecord.expectedName = "Виолончель";
    strTestProperty << "яркость" << "вес" << "сопротивление" << "уровеньшума" << "уровеньзаряда" << "поглощениезвука" << "защитноепокрытие" << "частотапроцессора" << "амортизация";
    intTestRecord_1 << 5 << 22 << 18;
    intTestRecord_2 << 19 << 62;
    intTestRecord_3 << 72 << 65 << 25 << 13 << 18;
    intTestRecord_4 << 60 << 89;
    intTestRecord_5 << 77 << 99;
    intTestRecord_6 << 61;
    intTestRecord_7 << 81 << 73;
    intTestRecord_8 << 78;
    intTestRecord_9 << 99 << 20 << 95 << 20 << 23;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8 << intTestRecord_9;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();
    intTestRecord_9.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 34 запись ----------------------------------

    testRecord.expectedName = "Гармоника";
    strTestProperty << "цветоваятемпература" << "функциональность" << "мощность" << "нейтральность" << "длина" << "уровеньэнергопотребл" << "ширина" << "глубина";
    intTestRecord_1 << 62 << 35 << 69;
    intTestRecord_2 << 81 << 93;
    intTestRecord_3 << 13 << 87 << 18;
    intTestRecord_4 << 18 << 31;
    intTestRecord_5 << 89;
    intTestRecord_6 << 26 << 92 << 83;
    intTestRecord_7 << 34 << 75;
    intTestRecord_8 << 22 << 57 << 79 << 14;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 35 запись ----------------------------------

    testRecord.expectedName = "Дверь";
    strTestProperty << "резкость" << "контрастность" << "стабилизацияизображе" << "материал" << "нейтральность" << "автоматическийвыборр" << "защитаотвлаги" << "масштабирующийзум";
    intTestRecord_1 << 31 << 5 << 99 << 98 << 85;
    intTestRecord_2 << 46 << 29 << 80 << 49 << 78;
    intTestRecord_3 << 12 << 5;
    intTestRecord_4 << 65 << 7 << 98 << 78 << 82;
    intTestRecord_5 << 94 << 42 << 19 << 9;
    intTestRecord_6 << 99 << 65 << 97;
    intTestRecord_7 << 12 << 57;
    intTestRecord_8 << 40 << 15 << 79 << 37;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 36 запись ----------------------------------

    testRecord.expectedName = "Ежик";
    strTestProperty << "объемпамяти" << "количество" << "шифрованиеданных" << "цвет" << "вес" << "эффективностьработы";
    intTestRecord_1 << 20 << 82 << 57 << 41 << 55;
    intTestRecord_2 << 24 << 56 << 31 << 67 << 71;
    intTestRecord_3 << 90;
    intTestRecord_4 << 40 << 69 << 97 << 37;
    intTestRecord_5 << 40 << 61;
    intTestRecord_6 << 78;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 37 запись ----------------------------------

    testRecord.expectedName = "Флейта";
    strTestProperty << "высота" << "уголобзора" << "времяотклика" << "энергоэффективность" << "уровеньзащиты";
    intTestRecord_1 << 37 << 77 << 95 << 66 << 79;
    intTestRecord_2 << 49 << 2 << 66 << 24 << 11;
    intTestRecord_3 << 59;
    intTestRecord_4 << 23 << 41 << 1 << 2 << 28;
    intTestRecord_5 << 19 << 18;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 38 запись ----------------------------------

    testRecord.expectedName = "Газета";
    strTestProperty << "цветоваятемпература" << "защитаоткоррозии" << "надежность" << "расходэнергиивожидан" << "стабильность" << "стиль" << "уровеньшума" << "запах";
    intTestRecord_1 << 85 << 99 << 47 << 64 << 99;
    intTestRecord_2 << 85 << 4 << 52 << 64;
    intTestRecord_3 << 67 << 46 << 4 << 32 << 63;
    intTestRecord_4 << 87 << 91 << 3 << 77 << 27;
    intTestRecord_5 << 59;
    intTestRecord_6 << 94 << 40 << 70 << 75;
    intTestRecord_7 << 70;
    intTestRecord_8 << 94 << 70;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 39 запись ----------------------------------

    testRecord.expectedName = "Холст";
    strTestProperty << "масштабируемость" << "функцияавтоматическо" << "влажность" << "разрешение" << "прозрачность" << "высота" << "уровеньзащиты" << "стиль" << "воздухообмен";
    intTestRecord_1 << 62 << 55 << 92 << 30;
    intTestRecord_2 << 73 << 28 << 69 << 15;
    intTestRecord_3 << 88 << 39 << 32 << 72 << 86;
    intTestRecord_4 << 18 << 80 << 26;
    intTestRecord_5 << 22;
    intTestRecord_6 << 23 << 28 << 16 << 88;
    intTestRecord_7 << 10 << 82 << 90 << 83 << 32;
    intTestRecord_8 << 93 << 64 << 4 << 73;
    intTestRecord_9 << 22 << 84 << 31;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8 << intTestRecord_9;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();
    intTestRecord_9.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 40 запись ----------------------------------

    testRecord.expectedName = "Игла";
    strTestProperty << "частотапроцессора" << "скоростьчтения" << "многофункциональност" << "сопротивление" << "контрастность" << "скорость" << "стабилизацияизображе" << "стиль";
    intTestRecord_1 << 43;
    intTestRecord_2 << 56;
    intTestRecord_3 << 84;
    intTestRecord_4 << 64 << 49 << 20 << 54;
    intTestRecord_5 << 52;
    intTestRecord_6 << 60;
    intTestRecord_7 << 10 << 17;
    intTestRecord_8 << 56;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 41 запись ----------------------------------

    testRecord.expectedName = "Картина";
    strTestProperty << "защитаотперегрузки" << "защитаоткоррозии" << "времяработы" << "цветоваятемпература" << "циклработы" << "энергоэффективность";
    intTestRecord_1 << 44 << 18 << 92 << 16 << 89;
    intTestRecord_2 << 82 << 23 << 34 << 77 << 10;
    intTestRecord_3 << 5 << 93 << 12 << 30 << 42;
    intTestRecord_4 << 38 << 12 << 49 << 74;
    intTestRecord_5 << 39 << 62;
    intTestRecord_6 << 47 << 50 << 38 << 32 << 39;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 42 запись ----------------------------------

    testRecord.expectedName = "Ластик";
    strTestProperty << "габариты";
    intTestRecord_1 << 71 << 48 << 16 << 97 << 21;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 43 запись ----------------------------------

    testRecord.expectedName = "Молоток";
    strTestProperty << "системаохлаждения" << "влажность" << "стиль" << "уровеньгромкости" << "яркость" << "воздухообмен";
    intTestRecord_1 << 97 << 45 << 10;
    intTestRecord_2 << 99 << 20 << 49 << 91;
    intTestRecord_3 << 38 << 56 << 51 << 11 << 74;
    intTestRecord_4 << 9 << 71 << 22;
    intTestRecord_5 << 35 << 10 << 2 << 84 << 44;
    intTestRecord_6 << 90 << 40 << 6 << 21;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 44 запись ----------------------------------

    testRecord.expectedName = "Носки";
    strTestProperty << "масштабируемость" << "эластичность";
    intTestRecord_1 << 47 << 25 << 35 << 76 << 16;
    intTestRecord_2 << 59 << 61 << 23 << 39;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2;
    intTestRecord_1.clear();
    intTestRecord_2.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 45 запись ----------------------------------

    testRecord.expectedName = "Очиститель";
    strTestProperty << "цветоваятемпература" << "срокслужбы";
    intTestRecord_1 << 29 << 20 << 22 << 17;
    intTestRecord_2 << 91 << 47 << 76;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2;
    intTestRecord_1.clear();
    intTestRecord_2.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 46 запись ----------------------------------

    testRecord.expectedName = "Парашют";
    strTestProperty << "стабильность" << "совместимость" << "надежность" << "отзывчивость" << "защитноепокрытие" << "нейтральность" << "температура";
    intTestRecord_1 << 73 << 14;
    intTestRecord_2 << 25 << 30;
    intTestRecord_3 << 68;
    intTestRecord_4 << 10 << 23 << 8 << 87 << 22;
    intTestRecord_5 << 97 << 33 << 88 << 49 << 55;
    intTestRecord_6 << 99;
    intTestRecord_7 << 10 << 20;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 47 запись ----------------------------------

    testRecord.expectedName = "Ручка";
    strTestProperty << "расходэнергиивожидан" << "амортизация" << "уровеньяркости" << "нейтральность" << "уровенькомфорта" << "магнитнаясовместимос" << "антибликовоепокрытие" << "защитаотультрафиолет" << "уголобзора";
    intTestRecord_1 << 88 << 56;
    intTestRecord_2 << 42 << 54 << 61 << 58 << 80;
    intTestRecord_3 << 24;
    intTestRecord_4 << 57 << 92;
    intTestRecord_5 << 62;
    intTestRecord_6 << 89 << 1 << 75 << 62;
    intTestRecord_7 << 33 << 72 << 7;
    intTestRecord_8 << 73 << 60 << 48 << 53 << 78;
    intTestRecord_9 << 92 << 58;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8 << intTestRecord_9;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();
    intTestRecord_9.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 48 запись ----------------------------------

    testRecord.expectedName = "Сковорода";
    strTestProperty << "странапроизводства" << "освещенность" << "масштабируемость" << "ширина" << "уровеньэнергопотребл" << "поглощениезвука";
    intTestRecord_1 << 74 << 4;
    intTestRecord_2 << 42 << 77 << 60 << 83 << 42;
    intTestRecord_3 << 46 << 25 << 97 << 81;
    intTestRecord_4 << 21;
    intTestRecord_5 << 23;
    intTestRecord_6 << 81 << 76 << 74 << 71;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 49 запись ----------------------------------

    testRecord.expectedName = "Таблетка";
    strTestProperty << "сопротивление" << "защитноепокрытие" << "амортизация" << "защитаотвлаги" << "скорость" << "масштабируемость";
    intTestRecord_1 << 26 << 30;
    intTestRecord_2 << 87 << 23 << 89 << 81 << 7;
    intTestRecord_3 << 9 << 19 << 25 << 89;
    intTestRecord_4 << 52 << 11 << 82 << 49 << 86;
    intTestRecord_5 << 64 << 50;
    intTestRecord_6 << 9 << 66 << 32;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 50 запись ----------------------------------

    testRecord.expectedName = "Украшение";
    strTestProperty << "плотностьпикселей" << "уголобзора";
    intTestRecord_1 << 88;
    intTestRecord_2 << 40 << 98 << 54 << 51;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2;
    intTestRecord_1.clear();
    intTestRecord_2.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 51 запись ----------------------------------

    testRecord.expectedName = "Фотоаппарат";
    strTestProperty << "системаохлаждения" << "уровеньэнергопотребл";
    intTestRecord_1 << 35 << 78 << 1;
    intTestRecord_2 << 97 << 67;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2;
    intTestRecord_1.clear();
    intTestRecord_2.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 52 запись ----------------------------------

    testRecord.expectedName = "Хлопушка";
    strTestProperty << "уровеньэнергопотребл" << "функцияавтоматическо" << "энергоэффективность" << "влажность" << "скорость" << "надежность" << "масштабируемость" << "объемпамяти";
    intTestRecord_1 << 16 << 32 << 31 << 17;
    intTestRecord_2 << 53 << 15;
    intTestRecord_3 << 34 << 10 << 95;
    intTestRecord_4 << 85 << 22 << 96;
    intTestRecord_5 << 2 << 33 << 84 << 85 << 21;
    intTestRecord_6 << 61 << 96 << 62 << 12;
    intTestRecord_7 << 7 << 43 << 94 << 56 << 17;
    intTestRecord_8 << 26 << 30 << 54 << 17 << 68;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 53 запись ----------------------------------

    testRecord.expectedName = "Циркуль";
    strTestProperty << "оптическийстабилизат" << "странапроизводства" << "системаохлаждения";
    intTestRecord_1 << 56 << 43 << 45 << 19 << 99;
    intTestRecord_2 << 31 << 54 << 85;
    intTestRecord_3 << 50 << 88 << 69;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 54 запись ----------------------------------

    testRecord.expectedName = "Чехол";
    strTestProperty << "воздухообмен" << "индикация" << "поддержкаформатов" << "мощность" << "тип" << "высота" << "толщина";
    intTestRecord_1 << 7 << 52 << 60 << 90 << 90;
    intTestRecord_2 << 75 << 2;
    intTestRecord_3 << 49 << 65 << 45 << 76 << 95;
    intTestRecord_4 << 95 << 29 << 25;
    intTestRecord_5 << 71 << 73;
    intTestRecord_6 << 50 << 28;
    intTestRecord_7 << 33 << 16 << 27;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 55 запись ----------------------------------

    testRecord.expectedName = "Шарф";
    strTestProperty << "съемность" << "прозрачность" << "напряжение" << "стабилизацияизображе" << "эргономика" << "уровеньзаряда";
    intTestRecord_1 << 38 << 7 << 64 << 86;
    intTestRecord_2 << 91 << 23;
    intTestRecord_3 << 2 << 97 << 31 << 38;
    intTestRecord_4 << 28;
    intTestRecord_5 << 72;
    intTestRecord_6 << 67 << 82;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 56 запись ----------------------------------

    testRecord.expectedName = "Щетка";
    strTestProperty << "толщина" << "ширина" << "частотапроцессора";
    intTestRecord_1 << 5 << 65;
    intTestRecord_2 << 5 << 3;
    intTestRecord_3 << 12 << 14 << 87;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 57 запись ----------------------------------

    testRecord.expectedName = "Экран";
    strTestProperty << "антибликовоепокрытие" << "отзывчивость" << "регулировкавысоты" << "амортизация" << "вкус" << "встроенныединамики" << "запах" << "защитноепокрытие" << "системаохлаждения";
    intTestRecord_1 << 74;
    intTestRecord_2 << 74 << 17 << 85;
    intTestRecord_3 << 39 << 61;
    intTestRecord_4 << 13 << 16;
    intTestRecord_5 << 76 << 95 << 60 << 75 << 1;
    intTestRecord_6 << 45 << 48 << 94;
    intTestRecord_7 << 38;
    intTestRecord_8 << 31 << 85;
    intTestRecord_9 << 68 << 48 << 84;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8 << intTestRecord_9;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();
    intTestRecord_9.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 58 запись ----------------------------------

    testRecord.expectedName = "Юмор";
    strTestProperty << "оптическийстабилизат" << "длина" << "температура" << "плотностьпикселей";
    intTestRecord_1 << 72 << 23 << 84;
    intTestRecord_2 << 25;
    intTestRecord_3 << 48 << 74 << 10 << 32;
    intTestRecord_4 << 99 << 91;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 59 запись ----------------------------------

    testRecord.expectedName = "Ящик";
    strTestProperty << "стабильность" << "резкость" << "уровеньгромкости" << "объемпамяти";
    intTestRecord_1 << 47 << 51 << 42;
    intTestRecord_2 << 38;
    intTestRecord_3 << 79;
    intTestRecord_4 << 24 << 7;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 60 запись ----------------------------------

    testRecord.expectedName = "Авокадо";
    strTestProperty << "сопротивление" << "глубина" << "надежность" << "эффективностьработы" << "разрешение" << "уровеньяркости" << "плотностьпикселей" << "уровеньшума";
    intTestRecord_1 << 76 << 52;
    intTestRecord_2 << 91 << 76 << 26 << 30 << 95;
    intTestRecord_3 << 92 << 52 << 75 << 92 << 81;
    intTestRecord_4 << 11 << 54 << 43 << 3 << 79;
    intTestRecord_5 << 99 << 45 << 32 << 21;
    intTestRecord_6 << 17;
    intTestRecord_7 << 22 << 77 << 2 << 44;
    intTestRecord_8 << 89 << 67 << 58;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 61 запись ----------------------------------

    testRecord.expectedName = "Банк";
    strTestProperty << "защитаоткоррозии" << "максимальнаянагрузка" << "влажность" << "цветоваятемпература" << "защитаотвлаги" << "плотность" << "амортизация" << "прочность" << "оптическийстабилизат";
    intTestRecord_1 << 4 << 74 << 41;
    intTestRecord_2 << 53 << 54;
    intTestRecord_3 << 95;
    intTestRecord_4 << 29 << 54 << 34;
    intTestRecord_5 << 17 << 37 << 18 << 58 << 36;
    intTestRecord_6 << 31 << 65 << 85 << 49 << 5;
    intTestRecord_7 << 4 << 15 << 14 << 27 << 69;
    intTestRecord_8 << 11 << 43 << 92 << 61;
    intTestRecord_9 << 64 << 35;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8 << intTestRecord_9;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();
    intTestRecord_9.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 62 запись ----------------------------------

    testRecord.expectedName = "Весы";
    strTestProperty << "мощность" << "разрешение" << "форма" << "эргономика";
    intTestRecord_1 << 72 << 30 << 52;
    intTestRecord_2 << 38;
    intTestRecord_3 << 87;
    intTestRecord_4 << 90;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 63 запись ----------------------------------

    testRecord.expectedName = "Горшок";
    strTestProperty << "разъемыподключения" << "циклработы" << "скоростьпечати" << "уровеньяркости" << "шифрованиеданных" << "защитноепокрытие" << "скоростьпередачиданн" << "интуитивныйинтерфейс";
    intTestRecord_1 << 6 << 59 << 6 << 88;
    intTestRecord_2 << 90 << 66 << 96 << 85;
    intTestRecord_3 << 86;
    intTestRecord_4 << 57 << 14 << 36 << 4 << 69;
    intTestRecord_5 << 10 << 75 << 48;
    intTestRecord_6 << 82 << 19 << 89 << 42 << 74;
    intTestRecord_7 << 5 << 17;
    intTestRecord_8 << 18 << 37 << 61 << 79;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 64 запись ----------------------------------

    testRecord.expectedName = "Джинсы";
    strTestProperty << "объемпамяти" << "баланс" << "цветоваятемпература" << "длина" << "прозрачность" << "уровеньэнергопотребл" << "странапроизводства";
    intTestRecord_1 << 66 << 94 << 20 << 69;
    intTestRecord_2 << 52 << 16 << 92;
    intTestRecord_3 << 45;
    intTestRecord_4 << 73 << 27 << 12 << 44 << 17;
    intTestRecord_5 << 25 << 80 << 51 << 78;
    intTestRecord_6 << 65;
    intTestRecord_7 << 74;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 65 запись ----------------------------------

    testRecord.expectedName = "Журнал";
    strTestProperty << "плотностьпикселей";
    intTestRecord_1 << 97 << 23 << 18;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 66 запись ----------------------------------

    testRecord.expectedName = "Зеркало";
    strTestProperty << "уровеньзаряда" << "срокслужбы" << "расходэнергиивожидан" << "материал" << "цена" << "антибликовоепокрытие";
    intTestRecord_1 << 65 << 8 << 80 << 89 << 19;
    intTestRecord_2 << 13;
    intTestRecord_3 << 69;
    intTestRecord_4 << 73 << 78;
    intTestRecord_5 << 2;
    intTestRecord_6 << 52 << 86 << 30 << 67;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 67 запись ----------------------------------

    testRecord.expectedName = "Иглоушка";
    strTestProperty << "материал" << "прозрачность" << "качество" << "поглощениезвука";
    intTestRecord_1 << 30 << 5;
    intTestRecord_2 << 26 << 56;
    intTestRecord_3 << 75 << 44;
    intTestRecord_4 << 79 << 28;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 68 запись ----------------------------------

    testRecord.expectedName = "Ключ";
    strTestProperty << "частотапроцессора" << "прочность" << "антибликовоепокрытие" << "защитаоткоррозии" << "стабилизацияизображе" << "баланс" << "интуитивныйинтерфейс" << "разъемыподключения" << "шифрованиеданных";
    intTestRecord_1 << 24 << 66;
    intTestRecord_2 << 5 << 7 << 43 << 2;
    intTestRecord_3 << 27 << 89;
    intTestRecord_4 << 22 << 84;
    intTestRecord_5 << 44 << 76;
    intTestRecord_6 << 87 << 87 << 39 << 76 << 96;
    intTestRecord_7 << 9 << 26 << 43;
    intTestRecord_8 << 4;
    intTestRecord_9 << 58 << 23 << 64 << 36;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8 << intTestRecord_9;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();
    intTestRecord_9.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 69 запись ----------------------------------

    testRecord.expectedName = "Лейка";
    strTestProperty << "поглощениезвука" << "антибликовоепокрытие";
    intTestRecord_1 << 50 << 45 << 71 << 35;
    intTestRecord_2 << 28;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2;
    intTestRecord_1.clear();
    intTestRecord_2.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 70 запись ----------------------------------

    testRecord.expectedName = "Музыка";
    strTestProperty << "разъемыподключения" << "гироскопическаястаби" << "высота";
    intTestRecord_1 << 41 << 53 << 4 << 74;
    intTestRecord_2 << 22 << 78 << 58 << 91 << 31;
    intTestRecord_3 << 28 << 59 << 5 << 70 << 24;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 71 запись ----------------------------------

    testRecord.expectedName = "Ножницы";
    strTestProperty << "запах" << "скоростьпередачиданн" << "качество" << "глубина";
    intTestRecord_1 << 67 << 39 << 90;
    intTestRecord_2 << 65 << 87 << 3 << 12 << 84;
    intTestRecord_3 << 20 << 59 << 18 << 20 << 43;
    intTestRecord_4 << 28;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 72 запись ----------------------------------

    testRecord.expectedName = "Одеяло";
    strTestProperty << "циклработы" << "запах" << "размер" << "антибликовоепокрытие" << "поглощениезвука";
    intTestRecord_1 << 35;
    intTestRecord_2 << 59 << 84;
    intTestRecord_3 << 27;
    intTestRecord_4 << 83 << 3 << 24;
    intTestRecord_5 << 85 << 88;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 73 запись ----------------------------------

    testRecord.expectedName = "Паста";
    strTestProperty << "защитаотперегрузки" << "количество" << "уровеньэнергопотребл" << "системаохлаждения" << "шифрованиекоммуникац" << "уголобзора" << "защитаотпыли" << "оптическийстабилизат" << "тип";
    intTestRecord_1 << 3 << 19 << 43 << 18 << 17;
    intTestRecord_2 << 34;
    intTestRecord_3 << 1 << 3;
    intTestRecord_4 << 72 << 82 << 29 << 66 << 25;
    intTestRecord_5 << 49 << 58 << 92;
    intTestRecord_6 << 13 << 11;
    intTestRecord_7 << 1 << 21 << 71;
    intTestRecord_8 << 47 << 50;
    intTestRecord_9 << 6;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8 << intTestRecord_9;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();
    intTestRecord_9.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 74 запись ----------------------------------

    testRecord.expectedName = "Ремень";
    strTestProperty << "баланс" << "поглощениезвука" << "защитаотультрафиолет" << "уровеньяркости" << "толщина";
    intTestRecord_1 << 67;
    intTestRecord_2 << 72 << 30 << 94 << 36;
    intTestRecord_3 << 55;
    intTestRecord_4 << 56 << 19 << 62 << 87 << 70;
    intTestRecord_5 << 4 << 35 << 83 << 29;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 75 запись ----------------------------------

    testRecord.expectedName = "Серьга";
    strTestProperty << "освещенность" << "срокслужбы";
    intTestRecord_1 << 95 << 8 << 69 << 77 << 58;
    intTestRecord_2 << 26;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2;
    intTestRecord_1.clear();
    intTestRecord_2.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 76 запись ----------------------------------

    testRecord.expectedName = "Торт";
    strTestProperty << "многофункциональност" << "уровеньшума";
    intTestRecord_1 << 34 << 81 << 23 << 59 << 42;
    intTestRecord_2 << 84 << 10 << 85 << 97 << 42;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2;
    intTestRecord_1.clear();
    intTestRecord_2.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 77 запись ----------------------------------

    testRecord.expectedName = "Удочка";
    strTestProperty << "времяработы" << "уровеньяркости" << "функцияавтоматическо" << "разрешение" << "резкость" << "отзывчивость";
    intTestRecord_1 << 7 << 90 << 9 << 39;
    intTestRecord_2 << 34 << 77;
    intTestRecord_3 << 42 << 82 << 92 << 82 << 39;
    intTestRecord_4 << 62 << 47 << 91;
    intTestRecord_5 << 59 << 86 << 91;
    intTestRecord_6 << 10 << 46 << 55 << 75;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 78 запись ----------------------------------

    testRecord.expectedName = "Фонарик";
    strTestProperty << "вкус" << "плотностьпикселей" << "эффективностьработы" << "уровенькомфорта" << "поглощениезвука" << "съемность" << "резкость";
    intTestRecord_1 << 55 << 39 << 60;
    intTestRecord_2 << 72 << 1 << 12 << 62;
    intTestRecord_3 << 96 << 8 << 97;
    intTestRecord_4 << 35 << 93 << 24 << 52 << 42;
    intTestRecord_5 << 96 << 47 << 16 << 11;
    intTestRecord_6 << 63 << 16 << 25;
    intTestRecord_7 << 52 << 70 << 34 << 47;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 79 запись ----------------------------------

    testRecord.expectedName = "Хор";
    strTestProperty << "уровеньзащиты" << "плотностьпикселей" << "баланс" << "стабилизацияизображе" << "масштабируемость" << "защитноепокрытие" << "ширина" << "толщина";
    intTestRecord_1 << 30 << 39 << 21 << 39;
    intTestRecord_2 << 78 << 26 << 76 << 90;
    intTestRecord_3 << 69 << 81 << 43 << 82 << 89;
    intTestRecord_4 << 89;
    intTestRecord_5 << 94 << 54 << 44 << 15 << 69;
    intTestRecord_6 << 68 << 16 << 47 << 84;
    intTestRecord_7 << 6;
    intTestRecord_8 << 68 << 14 << 45 << 23 << 99;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                      << intTestRecord_8;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();
    intTestRecord_8.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 80 запись ----------------------------------

    testRecord.expectedName = "Цепь";
    strTestProperty << "гироскопическаястаби" << "функцияавтоматическо" << "магнитнаясовместимос" << "скоростьпечати" << "длина" << "воспроизведениецвето";
    intTestRecord_1 << 96 << 41 << 22 << 30;
    intTestRecord_2 << 17 << 22 << 6 << 98;
    intTestRecord_3 << 72 << 26 << 96 << 81;
    intTestRecord_4 << 78 << 17 << 17 << 55 << 9;
    intTestRecord_5 << 20 << 50 << 67;
    intTestRecord_6 << 84;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 81 запись ----------------------------------

    testRecord.expectedName = "Чайник";
    strTestProperty << "уголобзора";
    intTestRecord_1 << 76 << 15 << 72 << 65 << 2;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 82 запись ----------------------------------

    testRecord.expectedName = "Шкаф";
    strTestProperty << "многофункциональност" << "разъемыподключения" << "вкус" << "мощность" << "гироскопическаястаби" << "регулировкавысоты" << "энергоэффективность";
    intTestRecord_1 << 48;
    intTestRecord_2 << 58;
    intTestRecord_3 << 15 << 20 << 48 << 45 << 56;
    intTestRecord_4 << 12 << 21 << 77 << 41 << 4;
    intTestRecord_5 << 61 << 97 << 68 << 15 << 63;
    intTestRecord_6 << 63;
    intTestRecord_7 << 50 << 41 << 86 << 39;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 83 запись ----------------------------------

    testRecord.expectedName = "Щипцы";
    strTestProperty << "скоростьчтения";
    intTestRecord_1 << 84 << 8 << 5;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 84 запись ----------------------------------

    testRecord.expectedName = "Эскимо";
    strTestProperty << "энергоэффективность" << "влажность" << "объемпамяти" << "запах" << "стиль" << "защитаоткоррозии";
    intTestRecord_1 << 29 << 15;
    intTestRecord_2 << 76 << 65 << 76 << 43;
    intTestRecord_3 << 23 << 63 << 90 << 28;
    intTestRecord_4 << 22 << 2;
    intTestRecord_5 << 95 << 6 << 91;
    intTestRecord_6 << 88 << 56 << 78 << 45;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 85 запись ----------------------------------

    testRecord.expectedName = "Юрист";
    strTestProperty << "плотность";
    intTestRecord_1 << 58 << 66 << 40;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 86 запись ----------------------------------

    testRecord.expectedName = "Ястреб";
    strTestProperty << "резкость" << "мощность" << "эмиссия" << "амортизация";
    intTestRecord_1 << 56 << 87 << 26 << 39;
    intTestRecord_2 << 26 << 15;
    intTestRecord_3 << 39;
    intTestRecord_4 << 55 << 26 << 19;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 87 запись ----------------------------------

    testRecord.expectedName = "Апельсин";
    strTestProperty << "уровеньяркости" << "толщина" << "защитаотвлаги" << "масштабирующийзум" << "съемность";
    intTestRecord_1 << 5 << 68 << 7 << 55 << 81;
    intTestRecord_2 << 2 << 76 << 87;
    intTestRecord_3 << 99 << 96 << 32 << 66;
    intTestRecord_4 << 27;
    intTestRecord_5 << 15 << 87;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 88 запись ----------------------------------

    testRecord.expectedName = "Ожерелье";
    strTestProperty << "тип" << "цена";
    intTestRecord_1 << 54 << 8 << 23 << 93 << 97;
    intTestRecord_2 << 37 << 44;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2;
    intTestRecord_1.clear();
    intTestRecord_2.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 89 запись ----------------------------------

    testRecord.expectedName = "Контрабас";
    strTestProperty << "нейтральность" << "стабилизацияизображе" << "разъемыподключения" << "плотность" << "системаохлаждения" << "отзывчивость" << "конфигурация";
    intTestRecord_1 << 46;
    intTestRecord_2 << 40 << 38 << 38 << 9;
    intTestRecord_3 << 22 << 78 << 2;
    intTestRecord_4 << 99 << 55 << 99;
    intTestRecord_5 << 33 << 2 << 73 << 44 << 87;
    intTestRecord_6 << 99 << 2 << 65 << 83;
    intTestRecord_7 << 3 << 63;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6 << intTestRecord_7
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();
    intTestRecord_7.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 90 запись ----------------------------------

    testRecord.expectedName = "Балалайка";
    strTestProperty << "тип" << "мощность" << "стабилизацияизображе" << "цветоваятемпература" << "контрастность";
    intTestRecord_1 << 61;
    intTestRecord_2 << 84 << 45;
    intTestRecord_3 << 19 << 78;
    intTestRecord_4 << 68;
    intTestRecord_5 << 7 << 51 << 60 << 85 << 16;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 91 запись ----------------------------------

    testRecord.expectedName = "Ворота";
    strTestProperty << "размер" << "циклработы" << "напряжение" << "ширина" << "интуитивныйинтерфейс";
    intTestRecord_1 << 82 << 93 << 22 << 11 << 76;
    intTestRecord_2 << 26 << 40 << 8;
    intTestRecord_3 << 3 << 18 << 11 << 18 << 57;
    intTestRecord_4 << 64 << 77 << 30;
    intTestRecord_5 << 44 << 39 << 18 << 63;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 92 запись ----------------------------------

    testRecord.expectedName = "Ежёнок";
    strTestProperty << "гироскопическаястаби" << "баланс" << "размер" << "габариты";
    intTestRecord_1 << 84 << 83 << 10 << 81;
    intTestRecord_2 << 25;
    intTestRecord_3 << 11 << 57;
    intTestRecord_4 << 4 << 38 << 25;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                         ;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 93 запись ----------------------------------

    testRecord.expectedName = "Ксилофон";
    strTestProperty << "магнитнаясовместимос" << "уровеньшума" << "частотапроцессора" << "форма" << "отзывчивость" << "скорость";
    intTestRecord_1 << 79 << 30;
    intTestRecord_2 << 4;
    intTestRecord_3 << 88 << 34 << 69;
    intTestRecord_4 << 4 << 92 << 46;
    intTestRecord_5 << 44 << 69 << 54;
    intTestRecord_6 << 1 << 45 << 55 << 36 << 34;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5 << intTestRecord_6;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();
    intTestRecord_6.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 94 запись ----------------------------------

    testRecord.expectedName = "Билютень";
    strTestProperty << "защитаоткоррозии" << "защитноепокрытие" << "тип" << "конфигурация" << "масштабирующийзум";
    intTestRecord_1 << 68 << 6 << 86 << 95 << 4;
    intTestRecord_2 << 5 << 8 << 73;
    intTestRecord_3 << 29 << 33 << 61 << 77 << 54;
    intTestRecord_4 << 74 << 16 << 89 << 27;
    intTestRecord_5 << 66 << 10 << 96 << 84;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3 << intTestRecord_4
                      << intTestRecord_5;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();
    intTestRecord_4.clear();
    intTestRecord_5.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 95 запись ----------------------------------

    testRecord.expectedName = "Палитра";
    strTestProperty << "времяработы" << "освещенность" << "эмиссия";
    intTestRecord_1 << 42;
    intTestRecord_2 << 73 << 85;
    intTestRecord_3 << 61 << 70 << 61 << 59;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 96 запись ----------------------------------

    testRecord.expectedName = "Иголка";
    strTestProperty << "индикация" << "толщина" << "странапроизводства";
    intTestRecord_1 << 90 << 6 << 88;
    intTestRecord_2 << 4 << 83;
    intTestRecord_3 << 29 << 2;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 97 запись ----------------------------------

    testRecord.expectedName = "Карточка";
    strTestProperty << "влажность";
    intTestRecord_1 << 53;

    fullIntTestRecord << intTestRecord_1;
    intTestRecord_1.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 98 запись ----------------------------------

    testRecord.expectedName = "Игрушки";
    strTestProperty << "цвет" << "размер" << "текстура";
    intTestRecord_1 << 15 << 1 << 12;
    intTestRecord_2 << 10 << 12 << 45 << 14;
    intTestRecord_3 << 1;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 99 запись ----------------------------------

    testRecord.expectedName = "Мячик";
    strTestProperty << "форма" << "раскрас" << "покрытие";
    intTestRecord_1 << 14;
    intTestRecord_2 << 6 << 14;
    intTestRecord_3 << 44 << 21;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    //------------- 100 запись ----------------------------------

    testRecord.expectedName = "Cтол";
    strTestProperty << "размер" << "цвет" << "покрытие";
    intTestRecord_1 << 1 << 2;
    intTestRecord_2 << 99 << 1 << 3;
    intTestRecord_3 << 12;

    fullIntTestRecord << intTestRecord_1 << intTestRecord_2 << intTestRecord_3;
    intTestRecord_1.clear();
    intTestRecord_2.clear();
    intTestRecord_3.clear();

    for(int i = 0; i < strTestProperty.count(); i++)
    {
        testRecord.expectedRelatedIntegerValues.insert(strTestProperty[i], fullIntTestRecord[i]);
    }

    arrTestRecords.append(testRecord);
    testRecord.expectedName.clear();
    testRecord.expectedRelatedIntegerValues.clear();

    //----------------------------------------------------------

    try
    {
        record.splitStringOfRecords(textRecords, &arrRecords);

        QCOMPARE(arrTestRecords.count(), arrRecords.count());


        for(int i = 0; i < arrRecords.count(); i++)
        {
            QCOMPARE(testRecord.expectedName, record.getName());

            foreach(const QString& key, testRecord.expectedRelatedIntegerValues.keys())
            {
                QVERIFY(record.getRelatedIntegerValues().contains(key));
                QCOMPARE(testRecord.expectedRelatedIntegerValues.value(key).count(),
                         record.getRelatedIntegerValues().value(key).count());

                for(int j = 0; j < testRecord.expectedRelatedIntegerValues.value(key).count(); j++)
                {
                    QCOMPARE(testRecord.expectedRelatedIntegerValues.value(key)[j], record.getRelatedIntegerValues().value(key)[j]);

                }
            }
        }
    }

    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

QTEST_APPLESS_MAIN(checkRecordClassification)

#include "tst_checkRecordClassification.moc"
