#ifndef MRB_SFML_HELPERS_H
#define MRB_SFML_HELPERS_H

#include <mruby.h>
#include <mruby/string.h>
#include <SFML/Config.hpp>

template <typename T> static inline mrb_value sfml_value_to_mrb(mrb_state*, T);

template <> mrb_value sfml_value_to_mrb<bool>(mrb_state* mrb, bool value) { return mrb_bool_value(value); }
template <> mrb_value sfml_value_to_mrb<sf::Int8>(mrb_state* mrb, sf::Int8 value) { return mrb_fixnum_value((mrb_int)value); }
template <> mrb_value sfml_value_to_mrb<sf::Int16>(mrb_state* mrb, sf::Int16 value) { return mrb_fixnum_value((mrb_int)value); }
template <> mrb_value sfml_value_to_mrb<sf::Int32>(mrb_state* mrb, sf::Int32 value) { return mrb_fixnum_value((mrb_int)value); }
template <> mrb_value sfml_value_to_mrb<sf::Int64>(mrb_state* mrb, sf::Int64 value) { return mrb_fixnum_value((mrb_int)value); }
template <> mrb_value sfml_value_to_mrb<sf::Uint8>(mrb_state* mrb, sf::Uint8 value) { return mrb_fixnum_value((mrb_int)value); }
template <> mrb_value sfml_value_to_mrb<sf::Uint16>(mrb_state* mrb, sf::Uint16 value) { return mrb_fixnum_value((mrb_int)value); }
template <> mrb_value sfml_value_to_mrb<sf::Uint32>(mrb_state* mrb, sf::Uint32 value) { return mrb_fixnum_value((mrb_int)value); }
template <> mrb_value sfml_value_to_mrb<sf::Uint64>(mrb_state* mrb, sf::Uint64 value) { return mrb_fixnum_value((mrb_int)value); }
template <> mrb_value sfml_value_to_mrb<float>(mrb_state* mrb, float value) { return mrb_float_value(mrb, (mrb_float)value); }
template <> mrb_value sfml_value_to_mrb<double>(mrb_state* mrb, double value) { return mrb_float_value(mrb, (mrb_float)value); }
template <> mrb_value sfml_value_to_mrb<char*>(mrb_state* mrb, char* value) { return mrb_str_new_cstr(mrb, value); }

#endif
