#ifndef CLASSIFICATIONRULES_H
#define CLASSIFICATIONRULES_H
#include "QMap"
#include <QRegularExpression>
#include <QStringList>

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
    void checkClassificationRules(const QString& strRule);
    void splitStringOfClassificationRules(const QString& rulesData, QList<ClassificationRules>* classificationRules);
    ConditionType getCondition();
    LimitationIntegerValues getLimitValue();
    QString getName();
    QString getConstraint();
    QList<int> getIntegerValues();
private:
    ConditionType condition;
    LimitationIntegerValues limitValue;
    QString name;
    QString constraint;
    QList<int> integerValues;
};

#endif // CLASSIFICATIONRULES_H
