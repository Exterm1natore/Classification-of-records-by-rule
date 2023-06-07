#ifndef RECORDS_H
#define RECORDS_H
#include "QMap"
#include <QRegularExpression>
#include <QStringList>

/*!
*\file
*\brief Данный  файл содержит в себе класс Records и заголовки функций, которые используются в программе.
*/

class Records
{
public:
    Records();

    /*!
    * \brief Проверить входной текст записей полученного из файла на предмет не соответствия заданным требованиям
    * \param[in] strRecords - входной текст записей, полученный из файла
    * \throw выбрасывает исключения в случае ошибки
    */
    void checkRecords (const QString& strRecords);

    /*!
    * \brief распределить проверенный текст записей по типам данных (название, свойство и т.д.)
    * \param[in] recordsData - проверенный текст записей
    * \param[in,out] record - контейнер класса Records в который будут записаны данные записей
    */
    void splitStringOfRecords(const QString& recordsData, QList<Records>* record);

    /*!
    * \brief Получить текущие свойства записи и соответствующие им целочисленные значения
    * \return вернуть текущие свойства записи и соответствующие им целочисленные значения
    */
    QMap<QString, QList<int>> getRelatedIntegerValues();

    /*!
    * \brief Получить текущее название записи
    * \return вернуть текущее название записи
    */
    QString getName();

private:
    QMap <QString, QList<int>> relatedIntegerValues;
    QString name;
};

#endif // RECORDS_H
