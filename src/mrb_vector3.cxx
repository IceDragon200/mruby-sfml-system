#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/System/Vector3.hpp>
#include "mrb/cxx/helpers.hxx"
#include "mrb/sfml/system/vector3.hxx"
#include "mrb_vector3.hxx"

static struct RClass *vector3f_class;
static struct RClass *vector3i_class;

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_vector3f_type = { "sf::Vector3f", cxx_mrb_data_free<sf::Vector3f> };
MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_vector3i_type = { "sf::Vector3i", cxx_mrb_data_free<sf::Vector3i> };

MRB_SFML_EXTERN mrb_value
mrb_sfml_vector3f_value(mrb_state *mrb, sf::Vector3f v)
{
  mrb_value result = mrb_obj_new(mrb, vector3f_class, 0, NULL);
  sf::Vector3f *target = mrb_sfml_vector3_ptr<float>(mrb, result);
  *target = v;
  return result;
}

MRB_SFML_EXTERN mrb_value
mrb_sfml_vector3i_value(mrb_state *mrb, sf::Vector3i v)
{
  mrb_value result = mrb_obj_new(mrb, vector3i_class, 0, NULL);
  sf::Vector3i *target = mrb_sfml_vector3_ptr<int>(mrb, result);
  *target = v;
  return result;
}

template <typename T>
static mrb_value
vector3_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Vector3<T> *vector3;
  mrb_value x, y, z;
  mrb_int argc = mrb_get_args(mrb, "|ooo", &x, &y, &z);
  if (argc == 0) {
    vector3 = new sf::Vector3<T>();
  } else if (argc == 1) {
    cxx_mrb_ensure_type_data(mrb, x);
    if (DATA_TYPE(x) == &mrb_sfml_vector3f_type) {
      vector3 = new sf::Vector3<T>(*mrb_sfml_vector3_ptr<float>(mrb, x));
    } else if (DATA_TYPE(x) == &mrb_sfml_vector3i_type) {
      vector3 = new sf::Vector3<T>(*mrb_sfml_vector3_ptr<int>(mrb, x));
    } else {
      mrb_raise(mrb, E_TYPE_ERROR, "Expected kind of Vector3");
      return mrb_nil_value();
    }
  } else if (argc == 3) {
    vector3 = new sf::Vector3<T>(cxx_mrb_cast<T>(mrb, x), cxx_mrb_cast<T>(mrb, y), cxx_mrb_cast<T>(mrb, z));
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 0 or 3");
    return self;
  }
  cxx_mrb_data_free<sf::Vector3<T>>(mrb, DATA_PTR(self));
  mrb_data_init(self, vector3, mrb_get_sfml_vector3_type<T>());
  return self;
}

template <typename T>
static mrb_value
vector3_initialize_copy(mrb_state *mrb, mrb_value self)
{
  sf::Vector3<T> *other;
  mrb_get_args(mrb, "d", &other, mrb_get_sfml_vector3_type<T>());
  cxx_mrb_data_free<sf::Vector3<T>>(mrb, DATA_PTR(self));
  mrb_data_init(self, new sf::Vector3<T>(*other), mrb_get_sfml_vector3_type<T>());
  return self;
}

template <typename T>
static mrb_value
vector3_get_x(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, mrb_sfml_vector3_ptr<T>(mrb, self)->x);
}

template <typename T>
static mrb_value
vector3_get_y(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, mrb_sfml_vector3_ptr<T>(mrb, self)->y);
}

template <typename T>
static mrb_value
vector3_get_z(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, mrb_sfml_vector3_ptr<T>(mrb, self)->z);
}

template <typename T>
static mrb_value
vector3_set_x(mrb_state *mrb, mrb_value self)
{
  mrb_sfml_vector3_ptr<T>(mrb, self)->x = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T>
static mrb_value
vector3_set_y(mrb_state *mrb, mrb_value self)
{
  mrb_sfml_vector3_ptr<T>(mrb, self)->y = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T>
static mrb_value
vector3_set_z(mrb_state *mrb, mrb_value self)
{
  mrb_sfml_vector3_ptr<T>(mrb, self)->z = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T>
static mrb_value
vector3_negate(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector3_value<T>(mrb, -(*mrb_sfml_vector3_ptr<T>(mrb, self)));
}

template <typename T>
static mrb_value
vector3_op_add(mrb_state *mrb, mrb_value self)
{
  sf::Vector3<T> *vec;
  mrb_get_args(mrb, "d", &vec, mrb_get_sfml_vector3_type<T>());
  return mrb_sfml_vector3_value<T>(mrb, (*mrb_sfml_vector3_ptr<T>(mrb, self)) + (*vec));
}

template <typename T>
static mrb_value
vector3_op_sub(mrb_state *mrb, mrb_value self)
{
  sf::Vector3<T> *vec;
  mrb_get_args(mrb, "d", &vec, mrb_get_sfml_vector3_type<T>());
  return mrb_sfml_vector3_value<T>(mrb, (*mrb_sfml_vector3_ptr<T>(mrb, self)) - (*vec));
}

template <typename T>
static mrb_value
vector3_op_mul(mrb_state *mrb, mrb_value self)
{
  mrb_float f;
  mrb_get_args(mrb, "f", &f);
  return mrb_sfml_vector3_value<T>(mrb, (*mrb_sfml_vector3_ptr<T>(mrb, self)) * static_cast<T>(f));
}

template <typename T>
static mrb_value
vector3_op_div(mrb_state *mrb, mrb_value self)
{
  mrb_float f;
  mrb_get_args(mrb, "f", &f);
  return mrb_sfml_vector3_value<T>(mrb, (*mrb_sfml_vector3_ptr<T>(mrb, self)) / static_cast<T>(f));
}

template <typename T>
static mrb_value
vector3_equal(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  if (mrb_type(obj) == MRB_TT_DATA) {
    if (DATA_TYPE(obj) == mrb_get_sfml_vector3_type<T>()) {
      return mrb_bool_value((*mrb_sfml_vector3_ptr<T>(mrb, obj)) == (*mrb_sfml_vector3_ptr<T>(mrb, self)));
    }
  }
  return mrb_bool_value(false);
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
  mrb_define_method(mrb, cls, "-@",              vector3_negate<T>,          MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "+",               vector3_op_add<T>,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "-",               vector3_op_sub<T>,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "*",               vector3_op_mul<T>,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "/",               vector3_op_div<T>,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "==",              vector3_equal<T>,           MRB_ARGS_REQ(1));
}

MRB_SFML_EXTERN void
mrb_sfml_vector3_init_bind(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *vector3_class = mrb_define_class_under(mrb, mod, "Vector3", mrb->object_class);

  vector3f_class = mrb_define_class_under(mrb, mod, "Vector3f", vector3_class);
  MRB_SET_INSTANCE_TT(vector3f_class, MRB_TT_DATA);
  vector3_bind_class<float>(mrb, vector3f_class);

  vector3i_class = mrb_define_class_under(mrb, mod, "Vector3i", vector3_class);
  MRB_SET_INSTANCE_TT(vector3i_class, MRB_TT_DATA);
  vector3_bind_class<int>(mrb, vector3i_class);
}
