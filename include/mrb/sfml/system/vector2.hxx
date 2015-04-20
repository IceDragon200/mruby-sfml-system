#ifndef MRB_SFML_VECTOR2_H
#define MRB_SFML_VECTOR2_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/System/Vector2.hpp>

extern "C" const struct mrb_data_type mrb_sfml_vector2f_type;
extern "C" const struct mrb_data_type mrb_sfml_vector2i_type;
extern "C" const struct mrb_data_type mrb_sfml_vector2u_type;
extern "C" mrb_value mrb_sfml_vector2f_value(mrb_state*, sf::Vector2f);
extern "C" mrb_value mrb_sfml_vector2i_value(mrb_state*, sf::Vector2i);
extern "C" mrb_value mrb_sfml_vector2u_value(mrb_state*, sf::Vector2u);

template <typename T> static inline const mrb_data_type* mrb_get_sfml_vector2_type();
template <> inline const mrb_data_type* mrb_get_sfml_vector2_type<float>() { return &mrb_sfml_vector2f_type; };
template <> inline const mrb_data_type* mrb_get_sfml_vector2_type<int>() { return &mrb_sfml_vector2i_type; };
template <> inline const mrb_data_type* mrb_get_sfml_vector2_type<unsigned int>() { return &mrb_sfml_vector2u_type; };

#endif
