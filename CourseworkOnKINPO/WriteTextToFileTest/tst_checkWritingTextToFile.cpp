#include <QtTest>
#include "../ClassificationOfRecordsByRule/FileHandling.h"
// add necessary includes here

class checkWritingTextToFile : public QObject
{
    Q_OBJECT

public:
    checkWritingTextToFile();
    ~checkWritingTextToFile();

private slots:
    void standartTest();
    void thereIsNoFileInThisPath();

};

checkWritingTextToFile::checkWritingTextToFile()
{

}

checkWritingTextToFile::~checkWritingTextToFile()
{

}

void checkWritingTextToFile::standartTest()
{
    FileHandling file;
    QString filePath = "..\\TestFiles\\WriteTextToFile\\Standard test.txt";

    QString inputString = "Шкаф:цвет=[1,2], размер=[10,12,15];"
                          "Игрушка: цвет=[15,1,12], размер=[10,12,45,14], текстура=[1];"
                          "Мяч: форма=[14], раскрас=[6,14], покрытие=[44,21];"
                          "Cтол:размер=[1,2],цвет=[99,1,3],покрытие=[12].";
    try
    {
        file.writeTextToFile(inputString, filePath);
        QString realString = file.unpackTextFile(filePath);
        QCOMPARE(inputString, realString);
    }
    catch (const QString& errorText)
    {
        QFAIL("FAIL!");
    }
}

void checkWritingTextToFile::thereIsNoFileInThisPath()
{
    FileHandling file;
    QString filePath = "..\\TestFiles\\WriteTextToFile\\No file.txt";

    QString inputString = "Шкаф:цвет=[1,2], размер=[10,12,15];"
                          "Игрушка: цвет=[15,1,12], размер=[10,12,45,14], текстура=[1];"
                          "Мяч: форма=[14], раскрас=[6,14], покрытие=[44,21];"
                          "Cтол:размер=[1,2],цвет=[99,1,3],покрытие=[12].";

    QString expectedString = "Файл для выходных данных указан неверно! Возможно, указанного расположения не существует или файл недоступен"
                             "\nВведённый путь: ..\\TestFiles\\WriteTextToFile\\No file.txt";
    try
    {
        file.writeTextToFile(inputString, filePath);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedString, errorText);
    }
}

QTEST_APPLESS_MAIN(checkWritingTextToFile)

#include "tst_checkWritingTextToFile.moc"
