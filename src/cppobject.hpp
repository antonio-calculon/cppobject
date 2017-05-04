// cppobjectobject.hpp

#ifndef _CPPOBJECTOBJECT_HPP_
#define _CPPOBJECTOBJECT_HPP_

#include <cstddef>
#include <unordered_set>
#include <unordered_map>



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

#define AUTOREF(var) autoref __autoref_##var(var)



// cppobject::Object
//
namespace cppobject
{
  class Object;
  class weakref_base;
  
  typedef std::unordered_set<weakref_base *> weakref_set;
  typedef std::unordered_map<Object *, weakref_set *> weakref_map;
  
  class weakref_base
  {
    friend Object;
    
  private:
    static weakref_map weakrefs;

    static void do_notify ( Object *ref );
    
  protected:
    Object *ref;

    weakref_base();
    weakref_base ( Object *ref );
    ~weakref_base ();
    virtual void set ( Object *ref );
    virtual void notify () {}
  };

  template < class T > class weakref : public weakref_base
  {
  public:
    weakref () {}
    weakref ( T *ref ) : weakref_base((Object *) ref) {}
    void set ( T *ref ) { this->weakref_base::set((Object *) ref); }
    T *get () { return (T *) ref; }
  };
    
  class Object
  {
    friend weakref_base;
    
  private:
    unsigned int ref_count : (sizeof(unsigned int) - 1);
    unsigned int has_weakref : 1;
    
  public:
    Object ();
    virtual ~Object ();
    unsigned int get_ref_count () { return ref_count; }
    Object *ref ();
    void unref ();
  };

  class autoref
  {
  private:
    Object *ref;
    
  public:
    autoref ( Object *ref )
    {
      this->ref = (Object *) ref->ref();
    }
    ~autoref ()
    {
      this->ref->unref();
    }
  };
}

#endif
