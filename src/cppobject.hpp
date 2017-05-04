// cppobjectobject.hpp

#ifndef _CPPOBJECTOBJECT_HPP_
#define _CPPOBJECTOBJECT_HPP_



#define REF(obj) ((typeof(obj)) (obj)->ref())

#define CLEAR(obj) do {                         \
    cppobject::Object *__tmp_obj_clear =        \
      (cppobject::Object *) (obj);              \
    (obj) = NULL;                               \
    __tmp_obj_clear->unref();                   \
  } while (0)

#define XCLEAR(obj) do {                        \
    if (obj)                                    \
      CLEAR(obj);                               \
  } while (0)



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
