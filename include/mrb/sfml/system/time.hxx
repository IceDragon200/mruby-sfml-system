#ifndef MRB_SFML_TIME_H
#define MRB_SFML_TIME_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/System/Time.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_time_type;
MRB_SFML_EXTERN mrb_value mrb_sfml_time_value(mrb_state*, sf::Time);

static inline sf::Time*
mrb_sfml_time_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Time*>(mrb_data_get_ptr(mrb, self, &mrb_sfml_time_type));
}

#endif
