#ifndef MRB_SFML_TIME_H
#define MRB_SFML_TIME_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/System/Time.hpp>

extern "C" const struct mrb_data_type mrb_sfml_time_type;
extern "C" mrb_value mrb_sfml_time_value(mrb_state*, sf::Time);

#endif
