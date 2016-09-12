/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
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
#include "FilterParameterWidget.h"

#include <QtCore/QTimer>
#include <QtCore/QPropertyAnimation>

#include <QtWidgets/QGraphicsOpacityEffect>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>
#include <QtWidgets/QDesktopWidget>

#include "SIMPLib/Common/AbstractFilter.h"
#include "SIMPLib/FilterParameters/FilterParameter.h"

#include "SVWidgetsLib/Core/SVWidgetsLibConstants.h"


namespace detail
{
  static const float Max = 1.0;
  static const int Duration = 400;
}



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FilterParameterWidget::FilterParameterWidget(QWidget* parent) :
  QFrame(parent),
  m_Filter(nullptr),
  m_FilterParameter(nullptr),
  m_WidgetIsExpanding(false),
  m_Timer(nullptr),
  animation(nullptr),
  effect(nullptr)
{
  fadeIn = true;
}

// Include the MOC generated file for this class
#include "moc_FilterParameterWidget.cpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FilterParameterWidget::FilterParameterWidget(FilterParameter* parameter, AbstractFilter* filter, QWidget* parent) :
  QFrame(parent),
  m_Filter(filter),
  m_FilterParameter(parameter),
  m_WidgetIsExpanding(false),
  m_Timer(nullptr),
  animation(nullptr),
  effect(nullptr)
{
  fadeIn = true;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FilterParameterWidget::~FilterParameterWidget()
{
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FilterParameterWidget::setLinkedConditionalState(int state)
{
  bool boolProp = (state == Qt::Checked);
  fadeWidget(this, boolProp);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FilterParameterWidget::setLinkedComboBoxState(int groupId)
{
  if(m_FilterParameter)
  {
    int groupIndex = m_FilterParameter->getGroupIndex();
    int state = (groupIndex == groupId) ? Qt::Checked : Qt::Unchecked;
    {
      setLinkedConditionalState(state);
    }
  }
}

#if 1
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QPointer<QtSFaderWidget> FilterParameterWidget::getFaderWidget() const
{
  return m_FaderWidget;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FilterParameterWidget::setFaderWidget(QPointer<QtSFaderWidget> faderWidget)
{
  m_FaderWidget = faderWidget;
}
#endif

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FilterParameterWidget::fadeInWidget(QWidget* widget)
{
#if 0
  if (m_FaderWidget)
  {
    m_FaderWidget->close();
  }
  m_FaderWidget = new QtSFaderWidget(widget);
  m_FaderWidget->start();
#endif
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FilterParameterWidget::setupGui()
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QPoint FilterParameterWidget::adjustedMenuPosition(QPushButton* pushButton)
{
  QSize menuSize = pushButton->menu()->sizeHint();
  QPoint point = QCursor::pos();
  point.setX(QCursor::pos().x() - menuSize.width() / 2);

  int desktopWidth = QApplication::desktop()->availableGeometry(pushButton).width();
  int desktopHeight = QApplication::desktop()->availableGeometry(pushButton).height();

  // If the menu is going to go off the screen in the X-axis, reposition it until it's completely on the screen
  while (point.x() + menuSize.width() > desktopWidth)
  {
    point.setX(point.x() - 1);
  }

  QPoint localButtonCoords = pushButton->geometry().bottomLeft();
  QPoint globalButtonCoords = mapToGlobal(localButtonCoords);
//  qDebug() << "QApplication::desktop()->geometry().width(): " << desktopWidth << "," << desktopHeight;
//  qDebug() << "localButtonCoords: " << localButtonCoords << "\tglobalButtonCoords: " << globalButtonCoords;

  point.setY(globalButtonCoords.y());

  // If the menu is going to go off the screen in the Y-axis, reposition it until it's completely on the screen
  while (point.y() + menuSize.height() > desktopHeight)
  {
    point.setY(point.y() - 1);
  }

  return point;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FilterParameterWidget::fadeWidget(QWidget* widget, bool in)
{
#if 0
  if (m_FaderWidget)
  {
    m_FaderWidget->close();
  }
  m_FaderWidget = new QtSFaderWidget(widget);
  if(in)
  {
    setVisible(true);
    m_FaderWidget->setFadeIn();
    connect(m_FaderWidget, SIGNAL(animationComplete() ),
            this, SLOT(show()));
    connect(m_FaderWidget, SIGNAL(animationComplete()),
            this, SLOT(showBorder()));

    widget->setStyleSheet("border: 2px solid MediumBlue;");
  }
  else
  {
    m_FaderWidget->setFadeOut();
    connect(m_FaderWidget, SIGNAL(animationComplete() ),
            this, SLOT(hide()));
  }

  m_FaderWidget->setStartColor(palette().color(QWidget::backgroundRole()));
  m_FaderWidget->start();
#else
  fadeIn = in;

  QString styleSheet;
  QTextStream ss (&styleSheet);
  ss << "QFrame#" << this->objectName() << " { ";
  ss << "background-color: rgb(223, 183, 175);";
  ss << "border: 0px Solid;";
  ss << "border-color: rgb(223, 183, 175);";
  ss << "border-radius: 5px;";
  ss <<  "}";

  if(!fadeIn)
  {
    startValue = detail::Max;
    endValue = 0;
  }
  else
  {
    widget->show();
    widget->setStyleSheet(styleSheet);
    //qDebug() << styleSheet();

    fadeIn = in;
    startValue = 0;
    endValue = detail::Max;
  }

  QRect rect = geometry();
  QLinearGradient alphaGradient(rect.topLeft(), rect.bottomLeft());
  alphaGradient.setColorAt(0.5, Qt::black);
  alphaGradient.setColorAt(1.0, Qt::black);

  if(!effect)
  {
    effect = new QGraphicsOpacityEffect(this);
    effect->setOpacityMask(alphaGradient);
    //this->setGraphicsEffect(effect);
  }

  if(!animation)
  {
    animation = new QPropertyAnimation(effect, "opacity", this);
    animation->setDuration(detail::Duration);
    connect(animation, SIGNAL(finished()),
            this, SLOT(animationFinished()));
    connect(animation, SIGNAL(finished()),
            this, SLOT(showBorder()));
  }

  animation->setStartValue(startValue);
  animation->setEndValue(endValue);

  animation->start();

#endif

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FilterParameterWidget::animationFinished()
{
  if(!fadeIn)
  {
    this->hide();
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FilterParameterWidget::showBorder()
{
  if (nullptr != m_Timer)
  {
    delete m_Timer;
    m_Timer = nullptr;
  }
  m_Timer = new QTimer(this);
  connect(m_Timer, SIGNAL(timeout()), this, SLOT(hideBorder()));
  m_Timer->start(2000);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FilterParameterWidget::hideBorder()
{
  setStyleSheet("");
}
