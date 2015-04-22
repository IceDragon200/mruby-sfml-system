#ifndef MRB_SFML_TIME_H
#define MRB_SFML_TIME_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/System/Time.hpp>

extern "C" const struct mrb_data_type mrb_sfml_time_type;
extern "C" mrb_value mrb_sfml_time_value(mrb_state*, sf::Time);

static inline sf::Time*
mrb_sfml_time_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Time*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_time_type));
}

#endif
