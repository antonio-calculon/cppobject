// cppobjectobject.hpp

#include "cppobject.hpp"

using namespace cppobject;



Object::Object ()
{
  ref_count = 1;
}



Object::~Object ()
{
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
