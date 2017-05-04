// cppobjectobject.hpp

#include "private.hpp"
#include "cppobject.hpp"

using namespace cppobject;



weakref_map weakref_base::weakrefs;



weakref_base::weakref_base()
{
  this->ref = NULL;
}



weakref_base::weakref_base ( Object *ref )
{
  this->ref = NULL;
  set(ref);
}



weakref_base::~weakref_base ()
{
  set(NULL);
}



void weakref_base::set ( Object *ref )
{
  if (this->ref == ref)
    return;
  if (this->ref)
    {
      auto list = weakrefs[this->ref];
      if (list)
        {
          list->erase(this);
          if (list->empty())
            {
              weakrefs.erase(this->ref);
              ref->has_weakref = 0;
            }
        }
      else
        {
          ERROR("no list found!");
        }
    }
  if (!(this->ref = ref))
    return;
  auto list = weakrefs[ref];
  if (!list)
    {
      list = new weakref_set;
      weakrefs[ref] = list;
    }
  list->insert(this);
  ref->has_weakref = 1;
}



void weakref_base::do_notify ( Object *ref )
{
  auto list = weakrefs[ref];
  if (!list)
    {
      ERROR("no weakref found!");
      return;
    }
  auto end = list->end();
  for (auto it = list->begin(); it != end; it++)
    {
      (*it)->ref = NULL;
      (*it)->notify();
    }
  delete list;
  weakrefs.erase(ref);
}



Object::Object ()
{
  ref_count = 1;
  has_weakref = 0;
}



Object::~Object ()
{
  if (this->has_weakref)
    weakref_base::do_notify(this);
}



Object *Object::ref ()
{
  ref_count++;
  return this;
}



void Object::unref ()
{
  if (!(--ref_count))
    delete this;
}
