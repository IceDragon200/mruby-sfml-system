#ifndef MRB_SFML_VECTOR2_H
#define MRB_SFML_VECTOR2_H

#include <mruby.h>
#include <mruby/data.h>

extern "C" const struct mrb_data_type mrb_sfml_vector2i_type;
extern "C" const struct mrb_data_type mrb_sfml_vector2f_type;

template <typename T> static inline const mrb_data_type* mrb_get_sfml_vector2_type();
template <> inline const mrb_data_type* mrb_get_sfml_vector2_type<float>() { return &mrb_sfml_vector2f_type; };
template <> inline const mrb_data_type* mrb_get_sfml_vector2_type<int>() { return &mrb_sfml_vector2i_type; };

#endif
