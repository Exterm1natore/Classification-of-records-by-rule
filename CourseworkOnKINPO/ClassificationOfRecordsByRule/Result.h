#ifndef RESULT_H
#define RESULT_H
#include "ClassificationRules.h"
#include "Records.h"
#include "QList"
#include <QTextCodec>

/*!
*\file
*\brief Данный  файл содержит в себе класс Result и заголовки функций, которые используются в программе.
*/

class Result
{
public:
    Result();

    /*!
    * \brief Классифицировать записи по правилам и получить выходную строку для записи в выходной файл (фукцния решающая главную задачу)
    * \param[in] textRecords - входной текст записей, полученный из файла
    * \param[in] textClassificationRules - входной текст правил классификаций, полученный из файла
    * \return выходная строка классифицированных записей
    */
    QString classificationRecordsByRule(const QString& textRecords, const QString& textClassificationRules);

    /*!
    * \brief Преобразовать данные классифицированных записей в выходную строку
    * \param[in] result - контейнер класса Result который хранит в себе данные классифицированных записей
    * \return выходная строка классифицированных записей
    */
    QString buildStringFromResult (const QList<Result>& result);

    /*!
    * \brief Получить текущее название класса
    * \return вернуть текущее название класса
    */
    QString getClassName();

    /*!
    * \brief Получить текущие названия записей
    * \return вернуть текущие названия записей
    */
    QList<QString> getRecordNames();
private:
    QString className;
    QList<QString> recordNames;
};

#endif // RESULT_H
