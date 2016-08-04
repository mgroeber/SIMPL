/*
 * Your License or Copyright Information can go here
 */

#include "TestFilters.h"
#include "SIMPLib/FilterParameters/AbstractFilterParametersReader.h"
#include "SIMPLib/FilterParameters/IntFilterParameter.h"
#include "SIMPLib/FilterParameters/DoubleFilterParameter.h"


// Include the MOC generated file for this class
#include "moc_TestFilters.cpp"



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Filt0::Filt0() :
  AbstractFilter(),
  m_DataContainerName(SIMPL::Defaults::DataContainerName),
  m_Filt0_Float(6.6f),
  m_Filt0_Integer(15)
{
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Filt0::~Filt0()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt0::setupFilterParameters()
{
  QVector<FilterParameter::Pointer> parameters;
  /* Place all your option initialization code here */

  /*  For an Integer use this code*/
  {
    parameters.push_back(SIMPL_NEW_INTEGER_FP("Int Value", Filt0_Integer, FilterParameter::Parameter, Filt0));
  }
  /*  For a Floating point value use this code*/
  {
    parameters.push_back(SIMPL_NEW_DOUBLE_FP("Float Value", Filt0_Float, FilterParameter::Parameter, Filt0));
  }


  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt0::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  float dummyFloat = 0.0f;
  int dummyInt = 0;
  reader->openFilterGroup(this, index);
  setFilt0_Float( reader->readValue("Filt0_Float", dummyFloat) );
  setFilt0_Integer( reader->readValue("Filt0_Integer", dummyInt) );
  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt0::initialize()
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt0::dataCheck()
{
  setErrorCondition(0);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt0::preflight()
{

  dataCheck();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt0::execute()
{
  int err = 0;
  setErrorCondition(err);
  setErrorCondition(err);
  DataContainer::Pointer m = getDataContainerArray()->getDataContainer(getDataContainerName());
  if (NULL == m)
  {
    setErrorCondition(-1);
    QString ss = QObject::tr(" DataContainer was NULL");
    notifyErrorMessage(getHumanLabel(), QObject::tr("VolumeDataContainer was NULL. Returning from Execute Method for filter %1").arg(getHumanLabel()), -1);
    return;
  }
  setErrorCondition(0);

  /* Place all your code to execute your filter here. */

  /* Let the GUI know we are done with this filter */
  notifyStatusMessage(getHumanLabel(), "Complete");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Filt1::Filt1() :
  AbstractFilter(),
  m_DataContainerName(SIMPL::Defaults::DataContainerName),
  m_Filt1_Float(9.9f),
  m_Filt1_Integer(123)
{
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Filt1::~Filt1()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt1::setupFilterParameters()
{
  QVector<FilterParameter::Pointer> parameters;
  /* Place all your option initialization code here */

  /*  For an Integer use this code*/
  {
    parameters.push_back(SIMPL_NEW_INTEGER_FP("Int Value", Filt1_Integer, FilterParameter::Parameter, Filt1));
  }
  /*  For a Floating point value use this code*/
  {
    parameters.push_back(SIMPL_NEW_DOUBLE_FP("Float Value", Filt1_Float, FilterParameter::Parameter, Filt1));
  }


  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt1::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  float dummyFloat = 0.0f;
  int dummyInt = 0;
  reader->openFilterGroup(this, index);
  setFilt1_Float( reader->readValue("Filt1_Float", dummyFloat) );
  setFilt1_Integer( reader->readValue("Filt1_Integer", dummyInt) );
  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt1::initialize()
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt1::dataCheck()
{
  setErrorCondition(0);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt1::preflight()
{

  dataCheck();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Filt1::execute()
{
  int err = 0;
  setErrorCondition(err);
  DataContainer::Pointer m = getDataContainerArray()->getDataContainer(getDataContainerName());
  if (NULL == m.get())
  {
    setErrorCondition(-1);
    QString ss = QObject::tr(" DataContainer was NULL");
    notifyErrorMessage(getHumanLabel(), QObject::tr("VolumeDataContainer was NULL. Returning from Execute Method for filter %1").arg(getHumanLabel()), -1);
    return;
  }
  setErrorCondition(0);

  /* Place all your code to execute your filter here. */

  /* Let the GUI know we are done with this filter */
  notifyStatusMessage(getHumanLabel(), "Complete");
}
