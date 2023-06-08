/*!
*\file
*\brief Данный файл содержит главную управляющую функцию программы
*\mainpage Документация для программы "ClassificationOfRecordsByRule"
Программа предназначена для классификации набора записей по указанному набору правил.
Для функционирования программы необходима операционная система Windows 10 или выше.
Программа разработана на языке С++ с использованием среды разработы Qt.
Программа должна получать три параметра командной строки:
имя входного файла с записями, имя входного файла с правилами классификации, имя выходного файла.

Пример команды запуска программы:
*\code
ClassificationRecordsByRule.exe C:\\Documents\records.txt C:\\Documents\rules.txt .\out.txt
*\endcode
*\author Dorokhov Ilya
*\date Июнь 2023 года
*\version 1.0
*/

#include <QCoreApplication>
#include "Records.h"
#include "ClassificationRules.h"
#include "Result.h"
#include "FileHandling.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // установка кодировки для корректной записи и считывания текста в консоли
    setlocale(LC_ALL, "Russian");
    QTextStream outStream(stdout); // переменная для вывода текста в консоль
    QTextStream inStream(stdin); // переменная для считывания текста из консоли

    FileHandling textFiles; // переменная класса FileHandling для записи и считывания текста в/из файла
    Result textResult; // переменная класса Result для запуска фукнции решающей главную задачу

    QString recordFileName = "C:\\Qt\\record_2.txt";
    QString ruleFileName = "C:\\Qt\\rule_2.txt";
    QString resultFileName = "C:\\Qt\\result.txt";

    /*// считываем с консоли путь к файлу с записями
    QString recordFileName = inStream.readLine();

    // считываем с консоли путь к файлу к правилами классификации
    QString ruleFileName = inStream.readLine();

    // считываем с консоли путь к выходному файлу результата
    QString resultFileName = inStream.readLine();*/

    // Делать
    try
    {
        // получаем текст из файл с записями
        QString strRecords = textFiles.unpackTextFile(recordFileName);

        // получаем текст из файла с правилами классификации
        QString strRule = textFiles.unpackTextFile(ruleFileName);

        // запускаем фукнцию, решающую главную задачу по классификации записей по правилам и получаем выходную строку для записи в выходной файл
        QString resultString = textResult.classificationRecordsByRule(strRecords, strRule);
        outStream << resultString << flush;

        // записываем выходную строку в выходной файл
        textFiles.writeTextToFile(resultString, resultFileName);
    }

    // Обработка исключения
    catch (const QString& errorText)
    {
        // вывести исключение в консоль
        outStream << errorText << flush;
    }

    return  a.exec();
}
