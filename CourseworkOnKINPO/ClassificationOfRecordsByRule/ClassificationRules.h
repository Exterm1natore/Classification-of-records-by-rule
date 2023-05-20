#ifndef CLASSIFICATIONRULES_H
#define CLASSIFICATIONRULES_H
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
    QList<int> arrIntegerValues;

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
};

#endif // CLASSIFICATIONRULES_H
