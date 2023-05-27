#ifndef FILEHANDLING_H
#define FILEHANDLING_H
#include <QFile>
#include <QTextStream>

class FileHandling
{
public:
    bool writeStringToFile(const QString& content, const QString& filePath);
    QString unpackTextFile(const QString& filePath);
};

#endif // FILEHANDLING_H
