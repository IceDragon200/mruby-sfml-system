#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <SFML/System/Time.hpp>
#include "mrb_time.hxx"
#include "mrb/sfml/system/time.hxx"

static struct RClass *time_class;

static void
time_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::Time *klock = (sf::Time*)ptr;
    delete klock;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_time_type = { "sf::Time", time_free };

static inline sf::Time*
get_time(mrb_state *mrb, mrb_value self)
{
  return (sf::Time*)mrb_data_get_ptr(mrb, self, &mrb_sfml_time_type);
}

extern "C" mrb_value
mrb_sfml_time_value(mrb_state *mrb, sf::Time tme)
{
  mrb_value result = mrb_obj_new(mrb, time_class, 0, NULL);
  sf::Time *rtme = get_time(mrb, result);
  *rtme = tme;
  return result;
}

static mrb_value
time_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Time *tme = new sf::Time();
  mrb_data_init(self, tme, &mrb_sfml_time_type);
  return self;
}

static mrb_value
time_as_seconds(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, get_time(mrb, self)->asSeconds());
}

static mrb_value
time_as_milliseconds(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_time(mrb, self)->asMilliseconds());
}

static mrb_value
time_as_microseconds(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(get_time(mrb, self)->asMicroseconds());
}

static mrb_value
time_compare(mrb_state *mrb, mrb_value self)
{
  sf::Time *tme;
  sf::Time *other;
  mrb_get_args(mrb, "d", &other, &mrb_sfml_time_type);
  tme = get_time(mrb, self);
  return mrb_fixnum_value((*tme < *other) ? -1 : ((*tme > *other) ? 1 : 0));
}

static mrb_value
time_add(mrb_state *mrb, mrb_value self)
{
  sf::Time *tme;
  sf::Time *other;
  mrb_get_args(mrb, "d", &other, &mrb_sfml_time_type);
  tme = get_time(mrb, self);
  return mrb_sfml_time_value(mrb, (*tme) + (*other));
}

static mrb_value
time_sub(mrb_state *mrb, mrb_value self)
{
  sf::Time *tme;
  sf::Time *other;
  mrb_get_args(mrb, "d", &other, &mrb_sfml_time_type);
  tme = get_time(mrb, self);
  return mrb_sfml_time_value(mrb, (*tme) - (*other));
}

static mrb_value
time_mul(mrb_state *mrb, mrb_value self)
{
  sf::Time *tme;
  mrb_float other;
  mrb_get_args(mrb, "f", &other);
  tme = get_time(mrb, self);
  return mrb_sfml_time_value(mrb, (*tme) * (float)(other));
}

static mrb_value
time_div(mrb_state *mrb, mrb_value self)
{
  sf::Time *tme;
  mrb_float other;
  mrb_get_args(mrb, "f", &other);
  tme = get_time(mrb, self);
  return mrb_sfml_time_value(mrb, (*tme) / (float)(other));
}

extern "C" void
mrb_sfml_time_init_bind(mrb_state *mrb, struct RClass *mod)
{
  time_class = mrb_define_class_under(mrb, mod, "Time", mrb->object_class);
  MRB_SET_INSTANCE_TT(time_class, MRB_TT_DATA);
  mrb_include_module(mrb, time_class, mrb_module_get(mrb, "Comparable"));

  mrb_define_method(mrb, time_class, "initialize", time_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, time_class, "as_seconds", time_as_seconds, MRB_ARGS_NONE());
  mrb_define_method(mrb, time_class, "as_milliseconds", time_as_milliseconds, MRB_ARGS_NONE());
  mrb_define_method(mrb, time_class, "as_microseconds", time_as_microseconds, MRB_ARGS_NONE());

  mrb_define_method(mrb, time_class, "<=>", time_compare, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, time_class, "+", time_add, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, time_class, "-", time_sub, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, time_class, "*", time_mul, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, time_class, "/", time_div, MRB_ARGS_REQ(1));
}
