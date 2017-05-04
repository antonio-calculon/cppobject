// cppobjectobject.hpp

#ifndef _CPPOBJECTOBJECT_HPP_
#define _CPPOBJECTOBJECT_HPP_



// cppobject::Object
//
namespace cppobject
{
  class Object
  {
  private:
    unsigned int ref_count;
    
  public:
    Object ();
    virtual ~Object ();
    Object *ref ();
    void unref ();
  };
}

#endif
