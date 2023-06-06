#include "FileHandling.h"

void FileHandling::writeTextToFile(const QString& content, const QString& filePath)
{
    QFile file(filePath); // открываем файл

    // Если файл не удалось открыть
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // в случае ошибки открытия файла, вызываем исключение
        throw QString ("Файл для выходных данных указан неверно! Возможно, указанного расположения не существует\nВведённый путь: " + filePath);
    }

    QTextStream out(&file); // переменная для записи текста в файл

    // установка кодировки UTF-8
    out.setCodec("UTF-8");

    // записываем текст в файл
    out << content;

    // закрываем файл
    file.close();
}

QString FileHandling::unpackTextFile(const QString& filePath)
{
    QFile file(filePath); // открываем файл

    // Если файл не удалось открыть
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // в случае ошибки открытия файла, вызываем исключение
        throw QString ("Файл с входными данными не был найден! Возможно, файл не существует\nВведённый путь: " + filePath);
    }

    QTextStream in(&file); // переменная для считывания текста из файла

    // установка кодировки UTF-8
    in.setCodec("UTF-8");

    // считываем весь текст из файла
    QString content = in.readAll();

    // во всём полученном тексте удаляем символ новой строки
    content.remove('\n');

    // закрываем файл
    file.close();

    // возвращаем полученный текст
    return content;
}
