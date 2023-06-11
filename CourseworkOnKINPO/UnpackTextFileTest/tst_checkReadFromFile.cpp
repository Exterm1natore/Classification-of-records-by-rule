#include <QtTest>
#include "../ClassificationOfRecordsByRule/FileHandling.h"
// add necessary includes here

class checkReadFromFile : public QObject
{
    Q_OBJECT

public:
    checkReadFromFile();
    ~checkReadFromFile();

private slots:
    void standardTest();
    void filePathDoesNotExist();
    void thereAreIllegalCharactersInFile();
};

checkReadFromFile::checkReadFromFile()
{

}

checkReadFromFile::~checkReadFromFile()
{

}

void checkReadFromFile::standardTest()
{
    FileHandling file;
    QString filePath = "..\\TestFiles\\UnpackTextFile\\Standard test.txt";



    QString expectedStringFromFile = "Шкаф:цвет=[1,2], размер=[10,12,15];"
                                     "Игрушка: цвет=[15,1,12], размер=[10,12,45,14], текстура=[1];"
                                     "Мяч: форма=[14], раскрас=[6,14], покрытие=[44,21];"
                                     "Cтол:размер=[1,2],цвет=[99,1,3],покрытие=[12].";

    try
    {
        QString realStringFromFile = file.unpackTextFile(filePath);
        QCOMPARE(expectedStringFromFile, realStringFromFile);
    }
    catch (const QString& errorText)
    {
        QFAIL("Fail!");
    }
}

void checkReadFromFile::filePathDoesNotExist()
{
    FileHandling file;
    QString filePath = "..\\TestFiles\\UnpackTextFile\\no File.txt";



    QString expectedStringFromFile = "Файл с входными данными не был найден! Возможно, файл не существует\n"
                                     "Введённый путь: ..\\TestFiles\\UnpackTextFile\\no File.txt";

    try
    {
        QString realStringFromFile = file.unpackTextFile(filePath);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedStringFromFile, errorText);
    }
}

void checkReadFromFile::thereAreIllegalCharactersInFile()
{
    FileHandling file;
    QString filePath = "..\\TestFiles\\UnpackTextFile\\Forbidden symbols.txt";



    QString expectedStringFromFile = "Ошибка! Входной текст из файла может содержать только буквы русского или английского алфавита, а также следующий набор символов: квадратные скобки ('[' ']'), точка с запятой (';'), двоеточие (':'), равно ('='), точку ('.'), двойные кавычки (' \" '), пробел, запятая (','), цифры [1;99] и не может быть пустым. \n"
                                     "Файл: ..\\TestFiles\\UnpackTextFile\\Forbidden symbols.txt";

    try
    {
        QString realStringFromFile = file.unpackTextFile(filePath);
        QFAIL("Fail!");
    }
    catch (const QString& errorText)
    {
        QCOMPARE(expectedStringFromFile, errorText);
    }
}

QTEST_APPLESS_MAIN(checkReadFromFile)

#include "tst_checkReadFromFile.moc"
