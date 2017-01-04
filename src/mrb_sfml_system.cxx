#include <mruby.h>
#include <mruby/class.h>
#include <SFML/System.hpp>
#include "mrb/sfml/system/time.hxx"
#include "mrb_clock.hxx"
#include "mrb_time.hxx"
#include "mrb_vector2.hxx"
#include "mrb_vector3.hxx"

static struct RClass *sfml_module;

static mrb_value
sfml_sleep(mrb_state *mrb, mrb_value klass)
{
  sf::Time *tme;
  mrb_get_args(mrb, "d", &tme, &mrb_sfml_time_type);
  sf::sleep(*tme);
  return klass;
}

static mrb_value
sfml_seconds(mrb_state *mrb, mrb_value klass)
{
  mrb_float amount;
  mrb_get_args(mrb, "f", &amount);
  return mrb_sfml_time_value(mrb, sf::seconds(amount));
}

static mrb_value
sfml_milliseconds(mrb_state *mrb, mrb_value klass)
{
  mrb_int amount;
  mrb_get_args(mrb, "i", &amount);
  return mrb_sfml_time_value(mrb, sf::milliseconds(amount));
}

static mrb_value
sfml_microseconds(mrb_state *mrb, mrb_value klass)
{
  mrb_int amount;
  mrb_get_args(mrb, "i", &amount);
  return mrb_sfml_time_value(mrb, sf::microseconds(amount));
}

MRB_SFML_EXTERN void
mrb_mruby_sfml_system_gem_init(mrb_state *mrb)
{
  sfml_module = mrb_define_module(mrb, "SFML");
  /* Sleep */
  mrb_define_class_method(mrb, sfml_module, "sleep", sfml_sleep, MRB_ARGS_REQ(1));
  /* Time */
  mrb_define_class_method(mrb, sfml_module, "seconds",      sfml_seconds, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, sfml_module, "milliseconds", sfml_milliseconds, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, sfml_module, "microseconds", sfml_microseconds, MRB_ARGS_REQ(1));

  mrb_sfml_clock_init_bind(mrb, sfml_module);
  mrb_sfml_time_init_bind(mrb, sfml_module);
  mrb_sfml_vector2_init_bind(mrb, sfml_module);
  mrb_sfml_vector3_init_bind(mrb, sfml_module);
}

MRB_SFML_EXTERN void
mrb_mruby_sfml_system_gem_final(mrb_state *mrb)
{

}
