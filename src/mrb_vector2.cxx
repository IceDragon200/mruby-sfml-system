#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <SFML/System/Vector2.hpp>
#include "mrb/sfml/system/vector2.hxx"
#include "mrb/cxx/helpers.hxx"
#include "mrb_vector2.hxx"

static struct RClass *vector2f_class;
static struct RClass *vector2i_class;
static struct RClass *vector2u_class;

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_vector2f_type = { "sf::Vector2f", cxx_mrb_data_free<sf::Vector2f> };
MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_vector2i_type = { "sf::Vector2i", cxx_mrb_data_free<sf::Vector2i> };
MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_vector2u_type = { "sf::Vector2u", cxx_mrb_data_free<sf::Vector2u> };

MRB_SFML_EXTERN mrb_value
mrb_sfml_vector2f_value(mrb_state *mrb, sf::Vector2f v)
{
  mrb_value result = mrb_obj_new(mrb, vector2f_class, 0, NULL);
  sf::Vector2f *target = mrb_sfml_vector2_ptr<float>(mrb, result);
  *target = v;
  return result;
}

MRB_SFML_EXTERN mrb_value
mrb_sfml_vector2i_value(mrb_state *mrb, sf::Vector2i v)
{
  mrb_value result = mrb_obj_new(mrb, vector2i_class, 0, NULL);
  sf::Vector2i *target = mrb_sfml_vector2_ptr<int>(mrb, result);
  *target = v;
  return result;
}

MRB_SFML_EXTERN mrb_value
mrb_sfml_vector2u_value(mrb_state *mrb, sf::Vector2u v)
{
  mrb_value result = mrb_obj_new(mrb, vector2u_class, 0, NULL);
  sf::Vector2u *target = mrb_sfml_vector2_ptr<unsigned int>(mrb, result);
  *target = v;
  return result;
}

template <typename T>
static mrb_value
vector2_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Vector2<T> *vector2;
  mrb_value x, y;
  mrb_int argc = mrb_get_args(mrb, "|oo", &x, &y);
  if (argc == 0) {
    vector2 = new sf::Vector2<T>();
  } else if (argc == 1) {
    cxx_mrb_ensure_type_data(mrb, x);
    if (DATA_TYPE(x) == &mrb_sfml_vector2f_type) {
      vector2 = new sf::Vector2<T>(*mrb_sfml_vector2_ptr<float>(mrb, x));
    } else if (DATA_TYPE(x) == &mrb_sfml_vector2i_type) {
      vector2 = new sf::Vector2<T>(*mrb_sfml_vector2_ptr<int>(mrb, x));
    } else if (DATA_TYPE(x) == &mrb_sfml_vector2u_type) {
      vector2 = new sf::Vector2<T>(*mrb_sfml_vector2_ptr<unsigned int>(mrb, x));
    } else {
      mrb_raise(mrb, E_TYPE_ERROR, "Expected kind of Vector2");
      return mrb_nil_value();
    }
  } else if (argc == 2) {
    vector2 = new sf::Vector2<T>(cxx_mrb_cast<T>(mrb, x), cxx_mrb_cast<T>(mrb, y));
  } else {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "expected 0 or 2");
    return mrb_nil_value();
  }
  cxx_mrb_data_free<sf::Vector2<T>>(mrb, DATA_PTR(self));
  mrb_data_init(self, vector2, mrb_get_sfml_vector2_type<T>());
  return self;
}

template <typename T>
static mrb_value
vector2_initialize_copy(mrb_state *mrb, mrb_value self)
{
  sf::Vector2<T> *other;
  mrb_get_args(mrb, "d", &other, mrb_get_sfml_vector2_type<T>());
  cxx_mrb_data_free<sf::Vector2<T>>(mrb, DATA_PTR(self));
  mrb_data_init(self, new sf::Vector2<T>(*other), mrb_get_sfml_vector2_type<T>());
  return self;
}

template <typename T>
static mrb_value
vector2_get_x(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, mrb_sfml_vector2_ptr<T>(mrb, self)->x);
}

template <typename T>
static mrb_value
vector2_get_y(mrb_state *mrb, mrb_value self)
{
  return cxx_mrb_numeric_value<T>(mrb, mrb_sfml_vector2_ptr<T>(mrb, self)->y);
}

template <typename T>
static mrb_value
vector2_set_x(mrb_state *mrb, mrb_value self)
{
  mrb_sfml_vector2_ptr<T>(mrb, self)->x = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T>
static mrb_value
vector2_set_y(mrb_state *mrb, mrb_value self)
{
  mrb_sfml_vector2_ptr<T>(mrb, self)->y = cxx_mrb_get_arg<T>(mrb);
  return self;
}

template <typename T>
static mrb_value
vector2_negate(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector2_value<T>(mrb, -(*mrb_sfml_vector2_ptr<T>(mrb, self)));
}

template <typename T>
static mrb_value
vector2_op_add(mrb_state *mrb, mrb_value self)
{
  sf::Vector2<T> *vec;
  mrb_get_args(mrb, "d", &vec, mrb_get_sfml_vector2_type<T>());
  return mrb_sfml_vector2_value<T>(mrb, (*mrb_sfml_vector2_ptr<T>(mrb, self)) + (*vec));
}

template <typename T>
static mrb_value
vector2_op_sub(mrb_state *mrb, mrb_value self)
{
  sf::Vector2<T> *vec;
  mrb_get_args(mrb, "d", &vec, mrb_get_sfml_vector2_type<T>());
  return mrb_sfml_vector2_value<T>(mrb, (*mrb_sfml_vector2_ptr<T>(mrb, self)) - (*vec));
}

template <typename T>
static mrb_value
vector2_op_mul(mrb_state *mrb, mrb_value self)
{
  mrb_float f;
  mrb_get_args(mrb, "f", &f);
  return mrb_sfml_vector2_value<T>(mrb, (*mrb_sfml_vector2_ptr<T>(mrb, self)) * static_cast<T>(f));
}

template <typename T>
static mrb_value
vector2_op_div(mrb_state *mrb, mrb_value self)
{
  mrb_float f;
  mrb_get_args(mrb, "f", &f);
  return mrb_sfml_vector2_value<T>(mrb, (*mrb_sfml_vector2_ptr<T>(mrb, self)) / static_cast<T>(f));
}

template <typename T>
static mrb_value
vector2_equal(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  if (mrb_type(obj) == MRB_TT_DATA) {
    if (DATA_TYPE(obj) == mrb_get_sfml_vector2_type<T>()) {
      return mrb_bool_value((*mrb_sfml_vector2_ptr<T>(mrb, obj)) == (*mrb_sfml_vector2_ptr<T>(mrb, self)));
    }
  }
  return mrb_bool_value(false);
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
  mrb_define_method(mrb, cls, "-@",              vector2_negate<T>,          MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "+",               vector2_op_add<T>,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "-",               vector2_op_sub<T>,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "*",               vector2_op_mul<T>,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "/",               vector2_op_div<T>,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "==",              vector2_equal<T>,           MRB_ARGS_REQ(1));
}

MRB_SFML_EXTERN void
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
