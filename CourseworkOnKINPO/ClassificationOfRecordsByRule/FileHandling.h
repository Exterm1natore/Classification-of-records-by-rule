#ifndef FILEHANDLING_H
#define FILEHANDLING_H
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

/*!
*\file
*\brief Данный  файл содержит в себе класс FileHandling и заголовки функций, которые используются в программе.
*/

class FileHandling
{
public:

    /*!
    * \brief Записать полученный текст в файл
    * \param[in] content - текст который нужно записать в файл
    * \param[in] filePath - название файла, куда нужно записать полученный текст
    */
    void writeTextToFile(const QString& content, const QString& filePath);

    /*!
    * \brief Считать и вернуть текст из файла
    * \param[in] filePath - название файла, откуда нужно считать текст
    * \return вернуть полученный текст из файла
    */
    QString unpackTextFile(const QString& filePath);
};

#endif // FILEHANDLING_H
