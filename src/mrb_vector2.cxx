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

template <typename T>
static inline sf::Vector2<T>*
get_vector2(mrb_state *mrb, mrb_value self)
{
  return (sf::Vector2<T>*)mrb_data_get_ptr(mrb, self, mrb_get_sfml_vector2_type<T>());
}

template <typename T>
static mrb_value
vector2_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Vector2<T> *vector2 = new sf::Vector2<T>();
  mrb_data_init(self, vector2, mrb_get_sfml_vector2_type<T>());
  return self;
}

template <typename T> static void
vector2_bind_class(mrb_state *mrb, struct RClass *cls)
{
  mrb_define_method(mrb, cls, "initialize", vector2_initialize<T>, MRB_ARGS_NONE());
}

extern "C" void
mrb_sfml_vector2_init_bind(mrb_state *mrb, struct RClass *mod)
{
  vector2f_class = mrb_define_class_under(mrb, mod, "Vector2f", mrb->object_class);
  MRB_SET_INSTANCE_TT(vector2f_class, MRB_TT_DATA);
  vector2_bind_class<float>(mrb, vector2f_class);

  vector2i_class = mrb_define_class_under(mrb, mod, "Vector2i", mrb->object_class);
  MRB_SET_INSTANCE_TT(vector2i_class, MRB_TT_DATA);
  vector2_bind_class<int>(mrb, vector2i_class);
}
