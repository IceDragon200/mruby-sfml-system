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
static struct RClass *vector3u_class;

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
extern "C" const struct mrb_data_type mrb_sfml_vector3u_type = { "sf::Vector3u", vector3_free<unsigned int> };

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
  mrb_value x, y, z;
  mrb_int argc = mrb_get_args(mrb, "|ooo", &x, &y, &z);
  sf::Vector3<T> *vector3;
  if (argc == 0) {
    vector3 = new sf::Vector3<T>();
  } else if (argc == 3) {
    vector3 = new sf::Vector3<T>(cxx_mrb_cast<T>(mrb, x), cxx_mrb_cast<T>(mrb, y), cxx_mrb_cast<T>(mrb, z));
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 0 or 3");
    return self;
  }
  mrb_data_init(self, vector3, mrb_get_sfml_vector3_type<T>());
  return self;
}

template <typename T>
static mrb_value
vector3_initialize_copy(mrb_state *mrb, mrb_value self)
{
  sf::Vector3<T> *other;
  mrb_get_args(mrb, "d", &other, mrb_get_sfml_vector3_type<T>());
  vector3_free<T>(mrb, DATA_PTR(self));
  mrb_data_init(self, new sf::Vector3<T>(*other), mrb_get_sfml_vector3_type<T>());
  return self;
}

template <typename T>
static mrb_value
vector3_get_x(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, get_vector3<T>(mrb, self)->x);
}

template <typename T>
static mrb_value
vector3_get_y(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, get_vector3<T>(mrb, self)->y);
}

template <typename T>
static mrb_value
vector3_get_z(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, get_vector3<T>(mrb, self)->z);
}

template <typename T>
static mrb_value
vector3_set_x(mrb_state *mrb, mrb_value self)
{
  get_vector3<T>(mrb, self)->x = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T>
static mrb_value
vector3_set_y(mrb_state *mrb, mrb_value self)
{
  get_vector3<T>(mrb, self)->y = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T>
static mrb_value
vector3_set_z(mrb_state *mrb, mrb_value self)
{
  get_vector3<T>(mrb, self)->z = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T> static void
vector3_bind_class(mrb_state *mrb, struct RClass *cls)
{
  mrb_define_method(mrb, cls, "initialize",      vector3_initialize<T>,      MRB_ARGS_ARG(0,3));
  mrb_define_method(mrb, cls, "initialize_copy", vector3_initialize_copy<T>, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "x",               vector3_get_x<T>,           MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "y",               vector3_get_y<T>,           MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "z",               vector3_get_z<T>,           MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "x=",              vector3_set_x<T>,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "y=",              vector3_set_y<T>,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "z=",              vector3_set_z<T>,           MRB_ARGS_REQ(1));
}

extern "C" void
mrb_sfml_vector3_init_bind(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *vector3_class = mrb_define_class_under(mrb, mod, "Vector3", mrb->object_class);

  vector3f_class = mrb_define_class_under(mrb, mod, "Vector3f", vector3_class);
  MRB_SET_INSTANCE_TT(vector3f_class, MRB_TT_DATA);
  vector3_bind_class<float>(mrb, vector3f_class);

  vector3i_class = mrb_define_class_under(mrb, mod, "Vector3i", vector3_class);
  MRB_SET_INSTANCE_TT(vector3i_class, MRB_TT_DATA);
  vector3_bind_class<int>(mrb, vector3i_class);

  vector3u_class = mrb_define_class_under(mrb, mod, "Vector3u", vector3_class);
  MRB_SET_INSTANCE_TT(vector3u_class, MRB_TT_DATA);
  vector3_bind_class<unsigned int>(mrb, vector3u_class);
}
