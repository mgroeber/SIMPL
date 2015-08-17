/* ============================================================================
* Copyright (c) 2009-2015 BlueQuartz Software, LLC
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


#include "RemoveComponentFromArray.h"

#include "DREAM3DLib/Common/Constants.h"
#include "DREAM3DLib/Common/TemplateHelpers.hpp"
#include "DREAM3DLib/FilterParameters/AbstractFilterParametersReader.h"
#include "DREAM3DLib/FilterParameters/AbstractFilterParametersWriter.h"
#include "DREAM3DLib/FilterParameters/IntFilterParameter.h"
#include "DREAM3DLib/FilterParameters/DataArraySelectionFilterParameter.h"
#include "DREAM3DLib/FilterParameters/StringFilterParameter.h"
#include "DREAM3DLib/FilterParameters/SeparatorFilterParameter.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
RemoveComponentFromArray::RemoveComponentFromArray() :
  AbstractFilter(),
  m_SelectedArrayPath("", "", ""),
  m_CompNumber(0),
  m_NewArrayArrayName(""),
  m_InArray(NULL),
  m_NewArray(NULL)
{
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
RemoveComponentFromArray::~RemoveComponentFromArray()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void RemoveComponentFromArray::setupFilterParameters()
{
  FilterParameterVector parameters;

  parameters.push_back(IntFilterParameter::New("Component Number to Extract", "CompNumber", getCompNumber(), FilterParameter::Parameter));

  parameters.push_back(DataArraySelectionFilterParameter::New("Multicomponent Attribute Array", "SelectedArrayPath", getSelectedArrayPath(), FilterParameter::RequiredArray));

  parameters.push_back(StringFilterParameter::New("Scalar Attribute Array", "NewArrayArrayName", getNewArrayArrayName(), FilterParameter::CreatedArray));

  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void RemoveComponentFromArray::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  reader->openFilterGroup(this, index);
  setNewArrayArrayName(reader->readString("NewArrayArrayName", getNewArrayArrayName() ) );
  setCompNumber(reader->readValue("CompNumber", getCompNumber() ) );
  setSelectedArrayPath( reader->readDataArrayPath( "SelectedArrayPath", getSelectedArrayPath() ) );
  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int RemoveComponentFromArray::writeFilterParameters(AbstractFilterParametersWriter* writer, int index)
{
  writer->openFilterGroup(this, index);
  DREAM3D_FILTER_WRITE_PARAMETER(FilterVersion)
  DREAM3D_FILTER_WRITE_PARAMETER(CompNumber)
  DREAM3D_FILTER_WRITE_PARAMETER(NewArrayArrayName)
  DREAM3D_FILTER_WRITE_PARAMETER(SelectedArrayPath)
  writer->closeFilterGroup();
  return ++index; // we want to return the next index that was just written to
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void RemoveComponentFromArray::dataCheck()
{
  setErrorCondition(0);

  m_InArrayPtr = getDataContainerArray()->getPrereqIDataArrayFromPath<IDataArray, AbstractFilter>(this, getSelectedArrayPath());

  if (m_NewArrayArrayName.isEmpty() == true)
  {
    setErrorCondition(-11003);
    notifyErrorMessage(getHumanLabel(), "New array name must be set.", getErrorCondition());
    return;
  }

  if(getErrorCondition() < 0) { return; }

  if (m_InArrayPtr.lock()->getNumberOfComponents() < 2)
  {
    QString ss = QObject::tr("Selected array '%1' must have more than 1 component. The number of components is %2").arg(getSelectedArrayPath().getDataArrayName()).arg(m_InArrayPtr.lock()->getNumberOfComponents());
    setErrorCondition(-11002);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
    return;
  }

  if(m_CompNumber >= m_InArrayPtr.lock()->getNumberOfComponents())
  {
    setErrorCondition(-11003);
    QString ss = QObject::tr("Component to extract (%1) is larger than the number of components (%2) for array selected: '%1'").arg(m_CompNumber).arg(m_InArrayPtr.lock()->getNumberOfComponents()).arg(getSelectedArrayPath().getDataArrayName());
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
    return;
  }

  QVector<size_t> cDims(1, 1);
  DataArrayPath tempPath(getSelectedArrayPath().getDataContainerName(), getSelectedArrayPath().getAttributeMatrixName(), getNewArrayArrayName());
  m_NewArrayPtr = TemplateHelpers::CreateNonPrereqArrayFromArrayType()(this, tempPath, cDims, m_InArrayPtr.lock());
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void RemoveComponentFromArray::preflight()
{
  setInPreflight(true);
  emit preflightAboutToExecute();
  emit updateFilterParameters(this);
  dataCheck();
  emit preflightExecuted();
  setInPreflight(false);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
template<typename T>
void extractComponent(IDataArray::Pointer inputData, IDataArray::Pointer newData, int compNumber)
{
  typename DataArray<T>::Pointer inputArrayPtr = boost::dynamic_pointer_cast<DataArray<T> >(inputData);
  typename DataArray<T>::Pointer newArrayPtr = boost::dynamic_pointer_cast<DataArray<T> >(newData);

  if (NULL == inputArrayPtr || NULL == newArrayPtr) { return; }

  T* inputArray = inputArrayPtr->getPointer(0);
  T* newArray = newArrayPtr->getPointer(0);
  size_t numPoints = inputArrayPtr->getNumberOfTuples();
  size_t numComps = inputArrayPtr->getNumberOfComponents();

  for (size_t i = 0; i < numPoints; i++)
  {
    newArray[i] = inputArray[numComps * i + compNumber];
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void RemoveComponentFromArray::execute()
{
  setErrorCondition(0);
  dataCheck();
  if(getErrorCondition() < 0) { return; }

  EXECUTE_FUNCTION_TEMPLATE(this, extractComponent, m_InArrayPtr.lock(), m_InArrayPtr.lock(), m_NewArrayPtr.lock(), m_CompNumber)

  notifyStatusMessage(getHumanLabel(), "Complete");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer RemoveComponentFromArray::newFilterInstance(bool copyFilterParameters)
{
  RemoveComponentFromArray::Pointer filter = RemoveComponentFromArray::New();
  if(true == copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString RemoveComponentFromArray::getCompiledLibraryName()
{ return Core::CoreBaseName; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString RemoveComponentFromArray::getGroupName()
{ return DREAM3D::FilterGroups::CoreFilters; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString RemoveComponentFromArray::getSubGroupName()
{ return DREAM3D::FilterSubGroups::MemoryManagementFilters; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString RemoveComponentFromArray::getHumanLabel()
{ return "Remove Component From Array"; }