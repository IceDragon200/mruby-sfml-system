#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/System/Vector2.hpp>
#include "mrb_vector2.hxx"
#include "mrb/sfml/system/vector2.hxx"
#include "mrb/cxx/helpers.hxx"

static struct RClass *vector2f_class;
static struct RClass *vector2i_class;
static struct RClass *vector2u_class;

template <typename T>
static void
vector2_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::Vector2<T> *vector2 = (sf::Vector2<T>*)ptr;
    delete vector2;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_vector2f_type = { "sf::Vector2f", vector2_free<float> };
extern "C" const struct mrb_data_type mrb_sfml_vector2i_type = { "sf::Vector2i", vector2_free<int> };
extern "C" const struct mrb_data_type mrb_sfml_vector2u_type = { "sf::Vector2u", vector2_free<unsigned int> };

template <typename T>
static inline sf::Vector2<T>*
get_vector2(mrb_state *mrb, mrb_value self)
{
  return (sf::Vector2<T>*)mrb_data_get_ptr(mrb, self, mrb_get_sfml_vector2_type<T>());
}

extern "C" mrb_value
mrb_sfml_vector2f_value(mrb_state *mrb, sf::Vector2f v)
{
  mrb_value result = mrb_obj_new(mrb, vector2f_class, 0, NULL);
  sf::Vector2f *target = get_vector2<float>(mrb, result);
  *target = v;
  return result;
}

extern "C" mrb_value
mrb_sfml_vector2i_value(mrb_state *mrb, sf::Vector2i v)
{
  mrb_value result = mrb_obj_new(mrb, vector2i_class, 0, NULL);
  sf::Vector2i *target = get_vector2<int>(mrb, result);
  *target = v;
  return result;
}

extern "C" mrb_value
mrb_sfml_vector2u_value(mrb_state *mrb, sf::Vector2u v)
{
  mrb_value result = mrb_obj_new(mrb, vector2u_class, 0, NULL);
  sf::Vector2u *target = get_vector2<unsigned int>(mrb, result);
  *target = v;
  return result;
}

template <typename T>
static mrb_value
vector2_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value x, y;
  mrb_int argc = mrb_get_args(mrb, "|oo", &x, &y);
  sf::Vector2<T> *vector2;
  if (argc == 0) {
    vector2 = new sf::Vector2<T>();
  } else if (argc == 2) {
    vector2 = new sf::Vector2<T>(cxx_mrb_cast<T>(mrb, x), cxx_mrb_cast<T>(mrb, y));
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 0 or 2");
    return self;
  }
  vector2_free<T>(mrb, DATA_PTR(self));
  mrb_data_init(self, vector2, mrb_get_sfml_vector2_type<T>());
  return self;
}

template <typename T>
static mrb_value
vector2_initialize_copy(mrb_state *mrb, mrb_value self)
{
  sf::Vector2<T> *other;
  mrb_get_args(mrb, "d", &other, mrb_get_sfml_vector2_type<T>());
  vector2_free<T>(mrb, DATA_PTR(self));
  mrb_data_init(self, new sf::Vector2<T>(*other), mrb_get_sfml_vector2_type<T>());
  return self;
}

template <typename T>
static mrb_value
vector2_get_x(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, get_vector2<T>(mrb, self)->x);
}

template <typename T>
static mrb_value
vector2_get_y(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, get_vector2<T>(mrb, self)->y);
}

template <typename T>
static mrb_value
vector2_set_x(mrb_state *mrb, mrb_value self)
{
  get_vector2<T>(mrb, self)->x = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T>
static mrb_value
vector2_set_y(mrb_state *mrb, mrb_value self)
{
  get_vector2<T>(mrb, self)->y = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T> static void
vector2_bind_class(mrb_state *mrb, struct RClass *cls)
{
  mrb_define_method(mrb, cls, "initialize",      vector2_initialize<T>,      MRB_ARGS_ARG(0,2));
  mrb_define_method(mrb, cls, "initialize_copy", vector2_initialize_copy<T>, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "x",               vector2_get_x<T>,           MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "y",               vector2_get_y<T>,           MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "x=",              vector2_set_x<T>,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "y=",              vector2_set_y<T>,           MRB_ARGS_REQ(1));
}

extern "C" void
mrb_sfml_vector2_init_bind(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *vector2_class = mrb_define_class_under(mrb, mod, "Vector2", mrb->object_class);

  vector2f_class = mrb_define_class_under(mrb, mod, "Vector2f", vector2_class);
  MRB_SET_INSTANCE_TT(vector2f_class, MRB_TT_DATA);
  vector2_bind_class<float>(mrb, vector2f_class);

  vector2i_class = mrb_define_class_under(mrb, mod, "Vector2i", vector2_class);
  MRB_SET_INSTANCE_TT(vector2i_class, MRB_TT_DATA);
  vector2_bind_class<int>(mrb, vector2i_class);

  vector2u_class = mrb_define_class_under(mrb, mod, "Vector2u", vector2_class);
  MRB_SET_INSTANCE_TT(vector2u_class, MRB_TT_DATA);
  vector2_bind_class<unsigned int>(mrb, vector2u_class);
}
