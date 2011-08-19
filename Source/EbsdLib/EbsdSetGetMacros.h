/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2010, Dr. Michael A. Groeber (US Air Force Research Laboratories
 * All rights reserved.
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
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force, 
 * BlueQuartz Software nor the names of its contributors may be used to endorse 
 * or promote products derived from this software without specific prior written
 * permission.
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
 *  This code was written under United States Air Force Contract number
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */




#ifndef _ANGSetGetMacros_h_
#define _ANGSetGetMacros_h_

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

/**
 * @file EbsdSEtGetMacros.h
 * @brief This file contains preprocessor macros that can be used to quickly
 * create instance variables, pointer types and other conveniences for a C++ class.
 */

#if defined(QT_CORE_LIB)
//-- Qt includes
#include <QtCore/QSharedPointer>
//#define RAW_PTR  data
#endif

//-- Boost Includes
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>


#define SHARED_IS_NULL(ptr)\
  (  (ptr).get() == NULL )

/**
 * @brief Creates a static method that returns a NULL pointer wrapped in a
 * boost::shared_ptr<>
 * @param thisClass The name of the class.
 */
#define EBSD_NULL_SHARED_POINTER(thisClass)\
  static Pointer NullPointer(void)\
  { \
    return Pointer(static_cast<thisClass*>(NULL));\
  }

#ifndef QT_SHARED_POINTERS
/**
 * @brief Creates some basic typedefs that can be used throughout the code to
 * reference the class.
 */
#define QT_SHARED_POINTERS(thisClass)\
  typedef thisClass                      Self;\
  typedef QSharedPointer< Self >        Pointer;\
  typedef QSharedPointer<const Self >  ConstPointer;\
  EBSD_NULL_SHARED_POINTER(thisClass)

#endif

/**
 * @brief Creates some basic typedefs that can be used throughout the code to
 * reference the class.
 */
#define EBSD_SHARED_POINTERS(thisClass)\
  typedef thisClass                      Self;\
  typedef boost::shared_ptr<Self >        Pointer;\
  typedef boost::shared_ptr<const Self >  ConstPointer;\
  typedef boost::weak_ptr<thisClass > WeakPointer;\
  typedef boost::weak_ptr<thisClass > ConstWeakPointer;\
  EBSD_NULL_SHARED_POINTER(thisClass)


#define EBSD_STATIC_NEW_SUPERCLASS(superclass, theclass)\
  static superclass::Pointer New()\
  {\
    theclass* ptr = new theclass();\
    superclass::Pointer shared_ptr (dynamic_cast<superclass*>(ptr) );\
    return shared_ptr;\
  }


/**
 * @brief Creates a typedef that points to the superclass of this class
 */
#define EBSD_SUPERCLASS_POINTER(SuperClass)\
  typedef SuperClass::Pointer SuperClass;


/**
 * @brief Creates a static "New" method that creates an instance of thisClass
 */
#define EBSD_NEW_SUPERCLASS(thisClass, SuperClass)\
  typedef SuperClass::Pointer SuperClass##Type;\
  static SuperClass##Type New##SuperClass(void) \
{ \
  SuperClass##Type sharedPtr (new thisClass); \
  return sharedPtr; \
}

/**
 * @brief Implements a Static 'New' Method for a class
 */
#define EBSD_STATIC_NEW_MACRO(thisClass) \
static Pointer New(void) \
{ \
  Pointer sharedPtr (new thisClass); \
  return sharedPtr; \
}

#define EBSD_STATIC_NEW_MACRO_WITH_ARGS(thisClass, args) \
static Pointer New args \
{ \
  Pointer sharedPtr (new thisClass); \
  return sharedPtr; \
}

/** Macro used to add standard methods to all classes, mainly type
 * information. */
#define EBSD_TYPE_MACRO(thisClass) \
    virtual const char* getNameOfClass() const \
        {return #thisClass;}

//------------------------------------------------------------------------------
// Macros for Properties
/**
* @brief Creates a std::string constant for the Property so that the property
* can be retrieved by name.
*/
#define EBSD_PROPERTY_CONSTANT(prpty) \
  const std::string prpty ( #prpty );

/**
* @brief Creates a "setter" method to set the property.
*/
#define EBSD_SET_PROPERTY(type, prpty) \
  void set##prpty(type value) { this->m_##prpty = value; }

/**
* @brief Creates a "getter" method to retrieve the value of the property.
*/
#define EBSD_GET_PROPERTY(type, prpty) \
  type get##prpty() { return m_##prpty; }



#define EBSD_VIRTUAL_INSTANCE_PROPERTY(type, prpty)\
  private:\
      type   m_##prpty;\
  public:\
    virtual EBSD_SET_PROPERTY(type, prpty)\
    virtual EBSD_GET_PROPERTY(type, prpty)


#define EBSD_INSTANCE_PROPERTY(type, prpty)\
  private:\
      type   m_##prpty;\
  public:\
    EBSD_SET_PROPERTY(type, prpty)\
    EBSD_GET_PROPERTY(type, prpty)



#define EBSD_SET_2DVECTOR_PROPERTY(type, prpty, varname)\
  void set##prpty(type value[2]) {\
      varname[0] = value[0]; varname[1] = value[1]; }\
  void set##prpty(type value_0, type value_1) {\
      varname[0] = value_0; varname[1] = value_1; }

#define EBSD_GET_2DVECTOR_PROPERTY(type, prpty, varname)\
  void get##prpty(type value[2]) {\
      value[0] = varname[0]; value[1] = varname[1]; }\
  void get##prpty(type &value_0, type &value_1) {\
      value_0 = varname[0]; value_1 = varname[1]; }


#define EBSD_INSTANCE_2DVECTOR_PROPERTY(type, prpty)\
  private:\
    type   m_##prpty[2];\
  public:\
    EBSD_SET_2DVECTOR_PROPERTY(type, prpty, m_##prpty)\
    EBSD_GET_2DVECTOR_PROPERTY(type, prpty, m_##prpty)

/**
* @brief Creates a "setter" method to set the property.
*/
#define EBSD_SET_STRING_PROPERTY( prpty, varname) \
  void set##prpty(const std::string &value) { this->varname = value; }

/**
* @brief Creates a "getter" method to retrieve the value of the property.
*/
#define EBSD_GET_STRING_PROPERTY( prpty, varname) \
  std::string get##prpty() { return varname; }

/**
 * @brief Creates setters and getters in the form of 'setXXX()' and 'getXXX()' methods
 */
#define EBSD_INSTANCE_STRING_PROPERTY(prpty)\
  private:\
  std::string      m_##prpty;\
  public:\
  EBSD_SET_STRING_PROPERTY(prpty,  m_##prpty)\
  EBSD_GET_STRING_PROPERTY(prpty,  m_##prpty)


#define EBSD_VIRTUAL_INSTANCE_STRING_PROPERTY(prpty)\
  private:\
  std::string      m_##prpty;\
  public:\
    virtual EBSD_SET_STRING_PROPERTY(prpty,  m_##prpty)\
    virtual EBSD_GET_STRING_PROPERTY(prpty,  m_##prpty)

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
/**
 * @brief Creates a "setter" method to set the property.
 */
#define EbsdHeader_SET_PROPERTY( HeaderType, type, prpty, key) \
  void set##prpty(type value) { \
    HeaderType* p = dynamic_cast<HeaderType*>(m_Headermap[key].get()); \
    if (NULL != p) { p->setValue(value); } else {\
      std::cout << "Value for Key: " << key << " was null." << std::endl;} }

/**
 * @brief Creates a "getter" method to retrieve the value of the property.
 */
#define EbsdHeader_GET_PROPERTY(HeaderType, type, prpty, key) \
  type get##prpty() { \
    HeaderType* p = dynamic_cast<HeaderType*>(m_Headermap[key].get());\
    if (NULL != p) { return p->getValue(); } else {\
      std::cout << "Value for Key: " << key << " was null." << std::endl; return 0;} }


#define EbsdHeader_INSTANCE_PROPERTY(HeaderType, type, prpty, key)\
  public:\
    EbsdHeader_SET_PROPERTY(HeaderType, type, prpty, key)\
    EbsdHeader_GET_PROPERTY(HeaderType, type, prpty, key)


#define EBSD_POINTER_PROPERTY(name, var, type)\
private:\
  type* m_##var;\
public:\
type* get##name##Pointer() { return m_##var; }\
void set##name##Pointer(type* f)\
  {\
    if (m_##var != NULL && m_##var != f)\
    {\
      deallocateArrayData(m_##var);\
      m_##var = NULL;\
    }\
    m_##var = f;\
  }


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

// These are simple over-rides from the boost distribution because we don't want the entire boost distribution just
// for a few boost headers
namespace Ang
{
  class bad_lexical_cast : public std::runtime_error {
  public:
    bad_lexical_cast(const std::string& s)
      : std::runtime_error(s)
    { }
  };

  class bad_any_cast : public std::runtime_error {
  public:
    bad_any_cast(const std::string& s)
      : std::runtime_error(s)
    { }
  };

  template<typename T>
  T lexical_cast(const std::string &s)
  {
    std::istringstream i(s);
    T x;
    if (!(i >> x))
      throw bad_lexical_cast("convertToDouble(\"" + s + "\")");

    return x;
  }
}


#if 0
/**
* @brief Creates an if conditional where the key is tested against the values constant
* and if a match found then the property value is set
* @param name_space The Namespace for the constants
* @param type The primitive type of the variable
* @param prpty the name of the property, usually with CamelCase spelling
* @param key The Key used for the property
* @param value The value of the property
*/
#define SET_PROPERTY_BODY(name_space, type, prpty, key, value) \
  if (name_space::prpty.compare(key) == 0) { \
    try { \
      this->set##prpty(Ang::lexical_cast<type>(value)); return 1; \
    }  catch(Ang::bad_lexical_cast &excp) { \
      std::cout << excp.what() << std::endl; \
      std::cout << "Could not convert value '" << value << "' to type '" << #type << "' for property '" << #prpty << "'" << std::endl; \
    } \
  }

#define SET_STRING_PROPERTY_BODY(name_space, type, prpty, key, value) \
  if (name_space::prpty.compare(key) == 0) { \
  try { \
  this->set##prpty(value); return 1; \
}  catch(Ang::bad_lexical_cast &excp) { \
  std::cout << excp.what() << std::endl; \
  std::cout << "Could not convert value '" << value << "' to type '" << #type << "' for property '" << #prpty << "'" << std::endl; \
} \
  }

/**
* @brief Creates an if condition where the key is tested against the values constant
* and if a match found the the property is returned using the 'value' argument
* @param name_space The Namespace for the constants
* @param type The primitive type of the variable
* @param prpty the name of the property, usually with CamelCase spelling
* @param varname The internal variable name used to store the property
* @param key The Key used for the property
* @param value The value of the property
*/

#define GET_PROPERTY_BODY(name_space, type, prpty, key, value)\
    if (name_space::prpty.compare(key) == 0) {  \
      try { value = *(reinterpret_cast<T*>( &(m_##prpty))); return 1;} \
  catch(Ang::bad_any_cast &) { std::cout << "Could not cast value '" << value << "' to type '" << #type << "' for property '" << #prpty << "'" << std::endl; } }

#define GET_STRING_PROPERTY_BODY2(name_space, type, prpty, key, value)\
  if (name_space::prpty.compare(key) == 0) {  \
    try { value = m_##prpty; return 1;} \
  catch(Ang::bad_any_cast &) { std::cout << "Could not cast value '" << value << "' to type '" << #type << "' for property '" << #prpty << "'" << std::endl; } }


//
/

#endif


#endif /* _ANGSetGetMacros_h_  */
