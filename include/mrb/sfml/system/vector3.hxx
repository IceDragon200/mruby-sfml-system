#ifndef MRB_SFML_VECTOR3_H
#define MRB_SFML_VECTOR3_H

#include <mruby.h>
#include <mruby/data.h>

extern "C" const struct mrb_data_type mrb_sfml_vector3f_type;
extern "C" const struct mrb_data_type mrb_sfml_vector3i_type;
extern "C" const struct mrb_data_type mrb_sfml_vector3u_type;

template <typename T> static inline const mrb_data_type* mrb_get_sfml_vector3_type();
template <> inline const mrb_data_type* mrb_get_sfml_vector3_type<float>() { return &mrb_sfml_vector3f_type; };
template <> inline const mrb_data_type* mrb_get_sfml_vector3_type<int>() { return &mrb_sfml_vector3i_type; };
template <> inline const mrb_data_type* mrb_get_sfml_vector3_type<unsigned int>() { return &mrb_sfml_vector3u_type; };

#endif
