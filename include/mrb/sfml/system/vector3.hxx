#ifndef MRB_SFML_VECTOR3_H
#define MRB_SFML_VECTOR3_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/System/Vector3.hpp>

extern "C" const struct mrb_data_type mrb_sfml_vector3f_type;
extern "C" const struct mrb_data_type mrb_sfml_vector3i_type;
extern "C" mrb_value mrb_sfml_vector3f_value(mrb_state*, sf::Vector3f);
extern "C" mrb_value mrb_sfml_vector3i_value(mrb_state*, sf::Vector3i);

template <typename T> static inline mrb_value mrb_sfml_vector3_value(mrb_state*, sf::Vector3<T>);
template <> inline mrb_value mrb_sfml_vector3_value<float>(mrb_state *mrb, sf::Vector3f v) { return mrb_sfml_vector3f_value(mrb, v); }
template <> inline mrb_value mrb_sfml_vector3_value<int>(mrb_state *mrb, sf::Vector3i v) { return mrb_sfml_vector3i_value(mrb, v); }

template <typename T> static inline const mrb_data_type* mrb_get_sfml_vector3_type();
template <> inline const mrb_data_type* mrb_get_sfml_vector3_type<float>() { return &mrb_sfml_vector3f_type; };
template <> inline const mrb_data_type* mrb_get_sfml_vector3_type<int>() { return &mrb_sfml_vector3i_type; };

template <typename T>
static inline sf::Vector3<T>*
mrb_sfml_vector3_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Vector3<T>*>(mrb_data_get_ptr(mrb, self, mrb_get_sfml_vector3_type<T>()));
}

static inline sf::Vector3f*
mrb_sfml_vector3f_ptr(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector3_ptr<float>(mrb, self);
}

static inline sf::Vector3i*
mrb_sfml_vector3i_ptr(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector3_ptr<int>(mrb, self);
}

#endif
