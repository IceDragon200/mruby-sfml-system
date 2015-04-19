#ifndef MRB_CXX_HELPERS
#define MRB_CXX_HELPERS

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>

template <typename T> static inline T cxx_mrb_cast(mrb_state*, mrb_value);
template <> inline float
cxx_mrb_cast<float>(mrb_state *mrb, mrb_value value)
{
  return (float)mrb_to_flo(mrb, value);
}

template <> inline int
cxx_mrb_cast<int>(mrb_state *mrb, mrb_value value)
{
  return (int)mrb_int(mrb, value);
}

template <typename T> static inline mrb_value cxx_mrb_numeric_value(mrb_state*, T);
template <> inline mrb_value
cxx_mrb_numeric_value<float>(mrb_state *mrb, float value)
{
  return mrb_float_value(mrb, (mrb_float)value);
}

template <> inline mrb_value
cxx_mrb_numeric_value<int>(mrb_state *mrb, int value)
{
  return mrb_fixnum_value((mrb_int)value);
}

template <typename T> static inline T cxx_mrb_get_arg(mrb_state*);
template <> inline float
cxx_mrb_get_arg<float>(mrb_state *mrb)
{
  mrb_float value;
  mrb_get_args(mrb, "f", &value);
  return (float)value;
}

template <> inline int
cxx_mrb_get_arg<int>(mrb_state *mrb)
{
  mrb_int value;
  mrb_get_args(mrb, "i", &value);
  return (int)value;
}

template <> inline bool
cxx_mrb_get_arg<bool>(mrb_state *mrb)
{
  mrb_bool value;
  mrb_get_args(mrb, "b", &value);
  return (bool)value;
}

#endif
