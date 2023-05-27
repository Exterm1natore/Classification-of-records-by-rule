#include "FileHandling.h"

bool FileHandling::writeStringToFile(const QString& content, const QString& filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // В случае ошибки открытия файла, возвращаем false
        return false;
    }

    QTextStream out(&file);

    out.setCodec("UTF-8"); // Установка кодировки UTF-8

    out << content;

    file.close();

    return true;
}

QString FileHandling::unpackTextFile(const QString& filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // В случае ошибки открытия файла, возвращаем пустую строку
        return "Файл с входными данными не был найден! Возможно, файл не существует";
    }

    QTextStream in(&file);

    in.setCodec("UTF-8"); // Установка кодировки UTF-8

    QString content = in.readAll();

    content.remove('\n'); //Удаление 'ENTER'

    file.close();

    return content;
}

