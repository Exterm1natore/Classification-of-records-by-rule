#ifndef CLASSIFICATIONRULES_H
#define CLASSIFICATIONRULES_H
#include "QMap"
#include <QRegularExpression>
#include <QStringList>

/*!
*\file
*\brief Данный  файл содержит в себе класс ClassificationRules и заголовки функций, которые используются в программе.
*/

/*!
* \brief структура, хранящая в себе информацию о дополнительном ограничении правила классификации в виде текста
* (количество целочисленных значений у правила представлено в виде текста)
* \param NotQuantity - у правила нет целочисленных значений представленных в виде текста в дополнительном ограничении
* \param Single - у правила в дополнительном ограничении написано "одним"
* \param Two - у правила в дополнительном ограничении написано "двумя"
* \param Three - у правила в дополнительном ограничении написано "тремя"
* \param Four - у правила в дополнительном ограничении написано "четырьмя"
* \param Five - у правила в дополнительном ограничении написано "пятью"
* \param Six - у правила в дополнительном ограничении написано "шестью"
* \param Seven - у правила в дополнительном ограничении написано "семью"
* \param Eight - у правила в дополнительном ограничении написано "восемью"
* \param Nine - у правила в дополнительном ограничении написано "девятью"
*/
enum LimitationIntegerValues
{
    NotQuantity,
    Single,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine
};

/*!
* \brief Структура для хранения тапа правила классификации
* \param propertyWithNoValue - правило без дополнительного ограничения
* \param propertyWithLength - правило с количеством целочисленных значений представленных в виде текста
* \param propertySingleValue - правило единстенным целочисленным значением в виде числа
* \param propertyWithSeveralValues - правило с массивом целочисленных значений
*/
enum ConditionType {
    propertyWithNoValue,
    propertyWithLength,
    propertySingleValue,
    propertyWithSeveralValues
};


class ClassificationRules
{
public:
    ClassificationRules();

    /*!
    * \brief Проверить входной текст правил классификации полученного из файла на предмет не соответствия заданным требованиям
    * \param[in] strRule - входной текст правил классификаций, полученный из файла
    * \throw выбрасывает исключения в случае ошибки
    */
    void checkClassificationRules(const QString& strRule);

    /*!
    * \brief распределить проверенный текст правил классификаии по типам данных (название, текстовое ограничение и т.д.)
    * \param[in] rulesData - проверенный текст правил классификации
    * \param[in,out] classificationRules - контейнер класса ClassificationRules в который будут записаны данные правил классификации
    */
    void splitStringOfClassificationRules(const QString& rulesData, QList<ClassificationRules>* classificationRules);

    /*!
    * \brief Получить текущий тип правила
    * \return вернуть текущий тип правила
    */
    ConditionType getCondition();

    /*!
    * \brief Получить текущее значение количества целочисленных значений в виде текста у правила в дополнительном ограничении
    * \return вернуть текущее значение количества целочисленных значений в виде текста у правила в дополнительном ограничении
    */
    LimitationIntegerValues getLimitValue();

    /*!
    * \brief Получить текущее название класса
    * \return вернуть текущее название класса
    */
    QString getName();

    /*!
    * \brief Получить текущее текстовое ограничение правила
    * \return вернуть текущее текстовое ограничение правила
    */
    QString getConstraint();

    /*!
    * \brief Получить текущие целочисленные значения правила
    * \return вернуть текущие целочисленные значения правила
    */
    QList<int> getIntegerValues();

private:
    ConditionType condition;
    LimitationIntegerValues limitValue;
    QString name;
    QString constraint;
    QList<int> integerValues;
};

#endif // CLASSIFICATIONRULES_H
