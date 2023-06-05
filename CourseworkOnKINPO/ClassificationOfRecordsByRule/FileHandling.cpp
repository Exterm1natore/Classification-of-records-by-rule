#include "FileHandling.h"

bool FileHandling::writeStringToFile(const QString& content, const QString& filePath)
{
    QFile file(filePath); // открываем файл

    // Если файл не удалось открыть
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false; // в случае ошибки открытия файла, возвращаем false

    QTextStream out(&file); // переменная для записи текста в файл
    out.setCodec("UTF-8"); // установка кодировки UTF-8
    out << content; // записываем текст в файл
    file.close(); // закрываем файл
    // Текст был записан в файл, возвращаем true
    return true;
}

QString FileHandling::unpackTextFile(const QString& filePath)
{
    QFile file(filePath); // открываем файл

    // Если файл не удалось открыть
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "Файл с входными данными не был найден! Возможно, файл не существует"; // В случае ошибки открытия файла, возвращаем текст ошибки

    QTextStream in(&file); // переменная для считывания текста из файла
    in.setCodec("UTF-8"); // установка кодировки UTF-8
    QString content = in.readAll(); // считываем весь текст из файла
    content.remove('\n'); // во всём полученном тексте удаляем символ новой строки
    file.close(); // закрываем файл
    // Вернуть полученный текст из файла
    return content;
}
