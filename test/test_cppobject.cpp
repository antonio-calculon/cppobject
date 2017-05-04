
#include "private.hpp"
#include "cppobject.hpp"

using namespace cppobject;


class Base : public Object
{
public:
  const char *name;

  Base ()
  {
    DEBUG("OUCH!");
  }
  
  Base ( const char *name )
  {
    this->name = name;
    DEBUG("new: %s (%d)", name, get_ref_count());
  }

  ~Base ()
  {
    DEBUG("delete: %s (%d)", name, get_ref_count());
  }

  Object *ref ()
  {
    DEBUG("ref: %s (%d)", name, get_ref_count());
    return this->Object::ref();
  }

  void unref ()
  {
    DEBUG("unref: %s (%d)", name, get_ref_count());
    this->Object::unref();
  }
};


class A : public Base
{
public:
  A ( const char *name ) : Base(name)
  {
  }
};


class B : public Base
{
  B ( const char *name )
  {
    // this->Base::Base(name);
  }
};


class weak_a : public weakref<A>
{
public:
  weak_a ( A *a ) : weakref<A>(a) {}
  
  virtual void notify ()
  {
    DEBUG("weak notify!");
  }
};


void foo ( A *a )
{
  DEBUG("foo!");
  AUTOREF(a);
}


int main ()
{
  A *a1 = new A((const char *) "A1");
  A *a2 = new A("A2");
  weakref<A> wa1(a1);
  weak_a wa2(a1);
  weak_a wa3(a1);
  DEBUG("wa1: %p", wa1.get());
  DEBUG("wa2: %p", wa2.get());
  foo(a1);
  a1->ref();
  DEBUG("wa1: %p", wa1.get());
  DEBUG("wa2: %p", wa2.get());
  a1->unref();
  wa3.set(NULL);
  DEBUG("wa1: %p", wa1.get());
  DEBUG("wa2: %p", wa2.get());
  a1->unref();
  DEBUG("wa1: %p", wa1.get());
  DEBUG("wa2: %p", wa2.get());
  a2->unref();
  return 0;
}
