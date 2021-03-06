#include "FilterParameter.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
IFilterParameter::IFilterParameter(const std::string& humanLabel, const std::string& propertyName, IFilterParameter::Category category, int groupIndex)
: m_HumanLabel(humanLabel)
, m_PropertyName(propertyName)
, m_Category(category)
, m_GroupIndex(groupIndex)
{
}

IFilterParameter::~IFilterParameter() = default;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

Int32Parameter::Pointer Int32Parameter::New(const std::string& humanLabel, const std::string& propertyName, int defaultValue, Category category, Int32Parameter::SetterCallbackType setterCallback,
                                            Int32Parameter::GetterCallbackType getterCallback, int groupIndex)
{
  Pointer sharedPtr(new Int32Parameter(humanLabel, propertyName, defaultValue, category, setterCallback, getterCallback, groupIndex));
  return sharedPtr;
}

Int32Parameter::~Int32Parameter() = default;

Int32Parameter::SetterCallbackType Int32Parameter::getSetterCallback()
{
  return m_SetterCallback;
}
Int32Parameter::GetterCallbackType Int32Parameter::getGetterCallback()
{
  return m_GetterCallback;
}

void Int32Parameter::readJson(const QJsonObject& json)
{
  QJsonValue jsonValue = json[QString::fromStdString(getPropertyName())];
  if(!jsonValue.isUndefined())
  {
    m_SetterCallback(jsonValue.toInt(0.0));
  }
}

void Int32Parameter::writeJson(QJsonObject& json) const
{
  json[QString::fromStdString(getPropertyName())] = m_GetterCallback();
}

Int32Parameter::Int32Parameter(const std::string& humanLabel, const std::string& propertyName, int defaultValue, Category category, const SetterCallbackType& setterCallback,
                               const GetterCallbackType& getterCallback, int groupIndex)
: IFilterParameter(humanLabel, propertyName, category, groupIndex)
, m_DefaultValue(defaultValue)
, m_SetterCallback(setterCallback)
, m_GetterCallback(getterCallback)
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DoubleParameter::Pointer DoubleParameter::New(const std::string& humanLabel, const std::string& propertyName, double defaultValue, Category category,
                                              DoubleParameter::SetterCallbackType setterCallback, DoubleParameter::GetterCallbackType getterCallback, int groupIndex)
{
  Pointer sharedPtr(new DoubleParameter(humanLabel, propertyName, defaultValue, category, setterCallback, getterCallback, groupIndex));
  return sharedPtr;
}

DoubleParameter::~DoubleParameter() = default;

DoubleParameter::SetterCallbackType DoubleParameter::getSetterCallback()
{
  return m_SetterCallback;
}
DoubleParameter::GetterCallbackType DoubleParameter::getGetterCallback()
{
  return m_GetterCallback;
}

void DoubleParameter::readJson(const QJsonObject& json)
{
  QJsonValue jsonValue = json[QString::fromStdString(getPropertyName())];
  if(!jsonValue.isUndefined() && jsonValue.isDouble())
  {
    m_SetterCallback(jsonValue.toDouble(0.0));
  }
}

void DoubleParameter::writeJson(QJsonObject& json) const
{
  json[QString::fromStdString(getPropertyName())] = m_GetterCallback();
}

DoubleParameter::DoubleParameter(const std::string& humanLabel, const std::string& propertyName, double defaultValue, Category category, const SetterCallbackType& setterCallback,
                                 const GetterCallbackType& getterCallback, int groupIndex)
: IFilterParameter(humanLabel, propertyName, category, groupIndex)
, m_DefaultValue(defaultValue)
, m_SetterCallback(setterCallback)
, m_GetterCallback(getterCallback)
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataArrayPathParameter::Pointer DataArrayPathParameter::New(const std::string& humanLabel, const std::string& propertyName, const DataArrayPath& defaultValue, Category category,
                                                            SetterCallbackType setterCallback, GetterCallbackType getterCallback, int groupIndex)
{
  DataArrayPathParameter::Pointer sharedPtr(new DataArrayPathParameter(humanLabel, propertyName, defaultValue, category, setterCallback, getterCallback, groupIndex));
  return sharedPtr;
}

DataArrayPathParameter::~DataArrayPathParameter() = default;

DataArrayPathParameter::SetterCallbackType DataArrayPathParameter::getSetterCallback()
{
  return m_SetterCallback;
}
DataArrayPathParameter::GetterCallbackType DataArrayPathParameter::getGetterCallback()
{
  return m_GetterCallback;
}

void DataArrayPathParameter::readJson(const QJsonObject& json)
{
  QJsonValue jsonValue = json[QString::fromStdString(getPropertyName())];
  if(!jsonValue.isUndefined() && jsonValue.isObject() && m_SetterCallback)
  {
    DataArrayPath dap;
    QJsonObject obj = jsonValue.toObject();
    dap.readJson(obj);
    if(m_SetterCallback)
    {
      m_SetterCallback(dap);
    }
  }
}

void DataArrayPathParameter::writeJson(QJsonObject& json) const
{
  if(m_GetterCallback)
  {
    json[QString::fromStdString(getPropertyName())] = m_GetterCallback().toJsonObject();
  }
}

DataArrayPathParameter::DataArrayPathParameter(const std::string& humanLabel, const std::string& propertyName, const DataArrayPath& defaultValue, Category category,
                                               const SetterCallbackType& setterCallback, const GetterCallbackType& getterCallback, int groupIndex)
: IFilterParameter(humanLabel, propertyName, category, groupIndex)
, m_DefaultValue(defaultValue)
, m_SetterCallback(setterCallback)
, m_GetterCallback(getterCallback)
{
}

// -----------------------------------------------------------------------------
FilterParameter::Pointer FilterParameter::NullPointer()
{
  return Pointer(static_cast<Self*>(nullptr));
}

// -----------------------------------------------------------------------------
void FilterParameter::setHumanLabel(const std::string& value)
{
  m_HumanLabel = value;
}

// -----------------------------------------------------------------------------
std::string FilterParameter::getHumanLabel() const
{
  return m_HumanLabel;
}

// -----------------------------------------------------------------------------
void FilterParameter::setPropertyName(const std::string& value)
{
  m_PropertyName = value;
}

// -----------------------------------------------------------------------------
std::string FilterParameter::getPropertyName() const
{
  return m_PropertyName;
}

// -----------------------------------------------------------------------------
void FilterParameter::setCategory(const Category& value)
{
  m_Category = value;
}

// -----------------------------------------------------------------------------
Category FilterParameter::getCategory() const
{
  return m_Category;
}

// -----------------------------------------------------------------------------
void FilterParameter::setGroupIndex(int value)
{
  m_GroupIndex = value;
}

// -----------------------------------------------------------------------------
int FilterParameter::getGroupIndex() const
{
  return m_GroupIndex;
}

// -----------------------------------------------------------------------------
FilterParameter::Pointer FilterParameter::NullPointer()
{
  return Pointer(static_cast<Self*>(nullptr));
}

// -----------------------------------------------------------------------------
void FilterParameter::setDefaultValue(int value)
{
  m_DefaultValue = value;
}

// -----------------------------------------------------------------------------
int FilterParameter::getDefaultValue() const
{
  return m_DefaultValue;
}

// -----------------------------------------------------------------------------
FilterParameter::Pointer FilterParameter::NullPointer()
{
  return Pointer(static_cast<Self*>(nullptr));
}

// -----------------------------------------------------------------------------
void FilterParameter::setDefaultValue(double value)
{
  m_DefaultValue = value;
}

// -----------------------------------------------------------------------------
double FilterParameter::getDefaultValue() const
{
  return m_DefaultValue;
}

// -----------------------------------------------------------------------------
FilterParameter::Pointer FilterParameter::NullPointer()
{
  return Pointer(static_cast<Self*>(nullptr));
}

// -----------------------------------------------------------------------------
void FilterParameter::setDefaultValue(const DataArrayPath& value)
{
  m_DefaultValue = value;
}

// -----------------------------------------------------------------------------
DataArrayPath FilterParameter::getDefaultValue() const
{
  return m_DefaultValue;
}
