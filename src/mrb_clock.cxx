#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <SFML/System/Clock.hpp>
#include "mrb_clock.hxx"
#include "mrb/sfml/system/clock.hxx"
#include "mrb/sfml/system/time.hxx"

static struct RClass *clock_class;

static void
clock_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    sf::Clock *klock = (sf::Clock*)ptr;
    delete klock;
  }
}

extern "C" const struct mrb_data_type mrb_sfml_clock_type = { "sf::Clock", clock_free };

static inline sf::Clock*
get_clock(mrb_state *mrb, mrb_value self)
{
  return (sf::Clock*)mrb_data_get_ptr(mrb, self, &mrb_sfml_clock_type);
}

static mrb_value
clock_initialize(mrb_state *mrb, mrb_value self)
{
  sf::Clock *klock = new sf::Clock();
  clock_free(mrb, DATA_PTR(self));
  mrb_data_init(self, klock, &mrb_sfml_clock_type);
  return self;
}

static mrb_value
clock_get_elapsed_time(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_time_value(mrb, get_clock(mrb, self)->getElapsedTime());
}

static mrb_value
clock_restart(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_time_value(mrb, get_clock(mrb, self)->restart());
}

extern "C" void
mrb_sfml_clock_init_bind(mrb_state *mrb, struct RClass *mod)
{
  clock_class = mrb_define_class_under(mrb, mod, "Clock", mrb->object_class);
  MRB_SET_INSTANCE_TT(clock_class, MRB_TT_DATA);

  mrb_define_method(mrb, clock_class, "initialize", clock_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, clock_class, "elapsed_time", clock_get_elapsed_time, MRB_ARGS_NONE());
  mrb_define_method(mrb, clock_class, "restart", clock_restart, MRB_ARGS_NONE());
}
