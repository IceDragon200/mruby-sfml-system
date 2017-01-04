#ifndef MRB_SFML_VECTOR2_H
#define MRB_SFML_VECTOR2_H

#include <mruby.h>
#include <mruby/data.h>
#include <SFML/System/Vector2.hpp>
#include "mrb/sfml/helpers.hxx"

MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_vector2f_type;
MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_vector2i_type;
MRB_SFML_EXTERN const struct mrb_data_type mrb_sfml_vector2u_type;
MRB_SFML_EXTERN mrb_value mrb_sfml_vector2f_value(mrb_state*, sf::Vector2f);
MRB_SFML_EXTERN mrb_value mrb_sfml_vector2i_value(mrb_state*, sf::Vector2i);
MRB_SFML_EXTERN mrb_value mrb_sfml_vector2u_value(mrb_state*, sf::Vector2u);

template <typename T> static inline mrb_value mrb_sfml_vector2_value(mrb_state*, sf::Vector2<T>);
template <> inline mrb_value mrb_sfml_vector2_value<float>(mrb_state *mrb, sf::Vector2f v) { return mrb_sfml_vector2f_value(mrb, v); }
template <> inline mrb_value mrb_sfml_vector2_value<int>(mrb_state *mrb, sf::Vector2i v) { return mrb_sfml_vector2i_value(mrb, v); }
template <> inline mrb_value mrb_sfml_vector2_value<unsigned int>(mrb_state *mrb, sf::Vector2u v) { return mrb_sfml_vector2u_value(mrb, v); }

template <typename T> static inline const mrb_data_type* mrb_get_sfml_vector2_type();
template <> inline const mrb_data_type* mrb_get_sfml_vector2_type<float>() { return &mrb_sfml_vector2f_type; };
template <> inline const mrb_data_type* mrb_get_sfml_vector2_type<int>() { return &mrb_sfml_vector2i_type; };
template <> inline const mrb_data_type* mrb_get_sfml_vector2_type<unsigned int>() { return &mrb_sfml_vector2u_type; };

template <typename T>
static inline sf::Vector2<T>*
mrb_sfml_vector2_ptr(mrb_state *mrb, mrb_value self)
{
  return static_cast<sf::Vector2<T>*>(mrb_data_get_ptr(mrb, self, mrb_get_sfml_vector2_type<T>()));
}

static inline sf::Vector2f*
mrb_sfml_vector2f_ptr(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector2_ptr<float>(mrb, self);
}

static inline sf::Vector2i*
mrb_sfml_vector2i_ptr(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector2_ptr<int>(mrb, self);
}

static inline sf::Vector2u*
mrb_sfml_vector2u_ptr(mrb_state *mrb, mrb_value self)
{
  return mrb_sfml_vector2_ptr<unsigned int>(mrb, self);
}

#endif
