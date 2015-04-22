#ifndef MRB_SFML_CLOCK_H
#define MRB_SFML_CLOCK_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/System/Clock.hpp>

extern "C" const struct mrb_data_type mrb_sfml_clock_type;

static inline sf::Clock*
mrb_sfml_clock_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Clock*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_clock_type));
}

#endif
