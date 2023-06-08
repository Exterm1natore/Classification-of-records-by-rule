#ifndef FILEHANDLING_H
#define FILEHANDLING_H
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

/*!
*\file
*\brief Данный  файл содержит в себе класс FileHandling и заголовки функций, которые используются в программе.
*/

/*!
 * \brief Класс, представляющий основные задачи работы с файлами.
 *
 * Данный класс описывает методы работы с файла по чтению и записи, а так же проверки открытия файла и
 * входных данных файла на запрещённые символы.
 *
 * Пример использования:
 * \code
 * FileHandling textFile;
 * textFile.writeTextToFile("Hello World!", "C:\\Qt\\resultText.txt")
 * QString text = textFile.unpackTextFile("C:\\Qt\\record.txt");
 *  \endcode
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
