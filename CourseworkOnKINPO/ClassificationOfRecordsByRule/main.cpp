#include <QCoreApplication>
#include "Records.h"
#include "ClassificationRules.h"
#include "Result.h"
#include "FileHandling.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream outStream(stdout); // переменная для вывода текста в консоль
    QTextStream inStream(stdin); // переменная для считывания текста из консоли
    outStream.setCodec(QTextCodec::codecForName("cp866")); // установка кодировки для корректной записи и считывания текста в консоли
    FileHandling textFiles; // переменная класса FileHandling для записи и считывания текста в/из файла
    Result textResult; // переменная класса Result для запуска фукнции решающей главную задачу

    QString recordFileName = "C:\\Qt\\TestRecord.txt";
    QString ruleFileName = "C:\\Qt\\TestRule.txt";
    QString resultFileName = "C:\\QtК\\result.txt";

    try
    {
        QString strRecords = textFiles.unpackTextFile(recordFileName); // получаем текст из файла с записями
        QString strRule = textFiles.unpackTextFile(ruleFileName); // получаем текст из файла с правилами классификации

        QString resultString = textResult.classificationRecordsByRule(strRecords, strRule);
        outStream << resultString << flush;

        textFiles.writeTextToFile(resultString, resultFileName);
    }

    catch (const QString& errorText)
    {
        outStream << errorText << flush;
    }

    /*QString resultString; // выходная строка, которая должна быть записана в выходной файл
    bool emptyFile = true; // флаг, означающий был ли найден входной файл по заданному пути
    QString strRecords = textFiles.unpackTextFile(recordFileName); // получаем текст из файла с записями

    // Если файл с входными данными записей не был найден
    if(strRecords == "Файл с входными данными не был найден! Возможно, файл не существует")
    {
        emptyFile = false; // установить флагу значение false
        // записать в выходную строку ошибку при задании пути к входному файлу записей
        resultString = strRecords + "\nВведённый путь: " + recordFileName;
    }

    QString strRule = textFiles.unpackTextFile(ruleFileName); // получаем текст из файла с правилами классификации

    // Если файл с входными данными правил классификации не был найден
    if(strRule == "Файл с входными данными не был найден! Возможно, файл не существует")
    {
        // Если входные данные записей так же не были найдены
        if(!emptyFile)
        {
            // дополнительно записать в выходную строку ошибку при задании пути к входному файлу правил классификации
            resultString += "\n\n" + strRule + "\nВведённый путь: " + ruleFileName;
        }

        // Иначе
        else
        {
            // записать в выходную строку ошибку при задании пути к входному файлу правил классификации
            resultString += strRule + "\nВведённый путь: " + ruleFileName;
            emptyFile = false; // установить флагу значение false
        }
    }

    // Если тексты записей и правил классификации были успешно получены
    if(emptyFile)
    {
        // запустить функцию, решающую главную задачу и записать результат в выходную строку
        resultString = textResult.classificationRecordsByRule(strRecords, strRule);
    }
    outStream << resultString << flush;

    // запустить функцию по записи выходной строки в выходной файл и вернуть флаг, указывающих на удачность записи строки в файл
    bool success = textFiles.writeStringToFile(resultString, resultFileName);

    // Если выходная строка была успешно записана в выходной файл
    if (success)
    {
        QString resultText = "\n\nЗапись в выходной файл произведена корректно";
        outStream << resultText << flush;
    }

    // Иначе
    else
    {
        QString resultText = "\n\nФайл для выходных данных указан неверно! Возможно, указанного расположения не существует";
        outStream << resultText + "\nВведённый путь: " + resultFileName << flush;
    }*/

    return  a.exec();
}
