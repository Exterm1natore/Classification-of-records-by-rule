#include <QCoreApplication>
#include "Records.h"
#include "ClassificationRules.h"
#include "Result.h"
#include "FileHandling.h"

int main(int argc, char *argv[])
{
    //"Шкаф: цвет=[1, 2], размер=[10,12,15];Стол: размер=[12, 15], цвет=[1, 15], покрытие=[12].";

    /*"Запись принадлежит классу \"С покрытием\", если у нее есть свойство \"покрытие\";"
      "Запись принадлежит классу \"Объёмный\", если у нее есть свойство \"размер\", которое представлено двумя значениями;"
      "Запись принадлежит классу \"Синий\", если у нее есть свойство \"цвет\", в составе которого есть значение \"1\";"
      "Запись принадлежит классу \"Матовый\", если у нее есть свойство \"покрытие\" и значение этого свойства равно \"[44, 21]\".";*/

    QCoreApplication a(argc, argv);

    QTextStream outStream(stdout);
    QTextStream inStream(stdin);
    outStream.setCodec(QTextCodec::codecForName("cp866"));

    FileHandling textFiles;
    ClassificationRules textRule;
    Records textRecord;
    Result textResult;

    QString recordFileName = "C:\\Qt\\TestRecord.txt";
    QString ruleFileName = "C:\\Qt\\TestRule.txt";
    QString resultFileName = "C:\\Qt\\result.txt";

    QString resultString;
    bool emptyFile = false;

    QString strRecords = textFiles.unpackTextFile(recordFileName);
    if(strRecords == "Файл с входными данными не был найден! Возможно, файл не существует")
    {
        emptyFile = true;
        resultString = strRecords + "\nВведённый путь: " + recordFileName;
    }

    QString strRule = textFiles.unpackTextFile(ruleFileName);
    if(strRule == "Файл с входными данными не был найден! Возможно, файл не существует")
    {
        if(emptyFile)
            resultString += "\n\n" + strRule + "\nВведённый путь: " + ruleFileName;
        else
        {
            resultString += strRule + "\nВведённый путь: " + ruleFileName;
            emptyFile = true;
        }
    }

    if(!emptyFile)
    resultString = textResult.classificationRecordsByRule(strRecords, strRule);
    outStream << resultString << flush;

    bool success = textFiles.writeStringToFile(resultString, resultFileName);

    if (success)
    {
        QString resultText = "\n\nЗапись в выходной файл произведена корректно";
        outStream << resultText << flush;
    }
    else
    {
        QString resultText = "\n\nФайл для выходных данных указан неверно! Возможно, указанного расположения не существует";
        outStream << resultText + "\nВведённый путь: " + resultFileName << flush;
    }

    return  a.exec();
}
