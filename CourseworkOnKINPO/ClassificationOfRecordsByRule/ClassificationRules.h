#ifndef CLASSIFICATIONRULES_H
#define CLASSIFICATIONRULES_H
#include "QString"
#include "QMap"

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
    LimitationIntegerValues value;
    ConditionType condition;
    //QMap<QString, QList<int>> rulesIntegerValues;
    QList<int> arrIntegerValues;

    //void arrayIntegerValues(QList<int> *arrIntegerValues);
    //void arrayRulesIntegerValues(const QList<int> arrIntegerValues, QMap<QString, QList<int>> *rulesIntegerValues);

    QString getName() const;
    QString getConstraint() const;
   unsigned int getIntegerValues() const;

    void setName(QString name);
    void setConstraint(QString constraint);
    void setIntegerValues(unsigned int integerValues);

private:
   QString name;
   QString constraint;
   unsigned int integerValues;
   //QMap<QString, int> rulesNumberValues;
};

#endif // CLASSIFICATIONRULES_H
