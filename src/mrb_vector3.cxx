#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/System/Vector3.hpp>
#include "mrb_vector3.hxx"
#include "mrb/sfml/system/vector3.hxx"
#include "mrb/cxx/helpers.hxx"

static struct RClass *vector3f_class;
static struct RClass *vector3i_class;

template <typename T>
static void
vector3_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::Vector3<T> *vector3 = (sf::Vector3<T>*)ptr;
    delete vector3;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_vector3f_type = { "sf::Vector3f", vector3_free<float> };
extern "C" const struct mrb_data_type mrb_sfml_vector3i_type = { "sf::Vector3i", vector3_free<int> };

template <typename T>
static inline sf::Vector3<T>*
get_vector3(mrb_state *mrb, mrb_value self)
{
  return (sf::Vector3<T>*)mrb_data_get_ptr(mrb, self, mrb_get_sfml_vector3_type<T>());
}

template <typename T>
static mrb_value
vector3_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Vector3<T> *vector3 = new sf::Vector3<T>();
  mrb_data_init(self, vector3, mrb_get_sfml_vector3_type<T>());
  return self;
}

template <typename T> static void
vector3_bind_class(mrb_state *mrb, struct RClass *cls)
{
  mrb_define_method(mrb, cls, "initialize", vector3_initialize<T>, MRB_ARGS_NONE());
}


extern "C" void
mrb_sfml_vector3_init_bind(mrb_state *mrb, struct RClass *mod)
{
  vector3f_class = mrb_define_class_under(mrb, mod, "Vector3f", mrb->object_class);
  MRB_SET_INSTANCE_TT(vector3f_class, MRB_TT_DATA);
  vector3_bind_class<float>(mrb, vector3f_class);

  vector3i_class = mrb_define_class_under(mrb, mod, "Vector3i", mrb->object_class);
  MRB_SET_INSTANCE_TT(vector3i_class, MRB_TT_DATA);
  vector3_bind_class<int>(mrb, vector3i_class);
}
