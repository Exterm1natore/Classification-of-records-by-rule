#include "ClassificationRules.h"

ClassificationRules::ClassificationRules()
{
 name = "";
 constraint = "";
}

QString ClassificationRules::getName() const
{
    return this -> name;
}

QString ClassificationRules::getConstraint() const
{
    return this -> constraint;
}

unsigned int ClassificationRules::getIntegerValues() const
{
   return this -> integerValues;
}

void ClassificationRules::setName(QString name)
{
    this -> name = name;
}

void ClassificationRules::setConstraint(QString constraint)
{
    this -> constraint = constraint;
}

void ClassificationRules::setIntegerValues(unsigned int integerValues)
{
    this -> integerValues = integerValues;
}

/*void ClassificationRules::arrayIntegerValues(QList<int> *arrIntegerValues)
{
    arrIntegerValues->append(getIntegerValues());
}

void ClassificationRules::arrayRulesIntegerValues(const QList<int> arrIntegerValues, QMap<QString, QList<int> > *rulesIntegerValues)
{
    rulesIntegerValues->insert(getConstraint(), arrIntegerValues);
}*/
