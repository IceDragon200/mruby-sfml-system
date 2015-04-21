#ifndef MRB_CXX_HELPERS
#define MRB_CXX_HELPERS

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/numeric.h>

template <typename T> static inline mrb_value cxx_mrb_numeric_value(mrb_state*, T);
template <typename T> static inline T cxx_mrb_cast(mrb_state*, mrb_value);
template <typename T> static inline T cxx_mrb_get_arg(mrb_state*);

static inline void
cxx_mrb_ensure_type_data(mrb_state *mrb, mrb_value self)
{
  if (mrb_type(self) != MRB_TT_DATA) {
    mrb_check_type(mrb, self, MRB_TT_DATA);
  }
}

template <typename T>
static inline T*
cxx_mrb_data_get_ptr(mrb_state *mrb, mrb_value self)
{
  cxx_mrb_ensure_type_data(mrb, self);
  T *shape = static_cast<T*>(DATA_PTR(self));
  assert(shape);
  return shape;
}

template <> inline float
cxx_mrb_cast<float>(mrb_state *mrb, mrb_value value)
{
  return static_cast<float>(mrb_to_flo(mrb, value));
}

template <> inline int
cxx_mrb_cast<int>(mrb_state *mrb, mrb_value value)
{
  return static_cast<int>(mrb_int(mrb, value));
}

template <> inline unsigned int
cxx_mrb_cast<unsigned int>(mrb_state *mrb, mrb_value value)
{
  return static_cast<unsigned int>(mrb_int(mrb, value));
}

template <> inline mrb_value
cxx_mrb_numeric_value<float>(mrb_state *mrb, float value)
{
  return mrb_float_value(mrb, static_cast<mrb_float>(value));
}

template <> inline mrb_value
cxx_mrb_numeric_value<int>(mrb_state *mrb, int value)
{
  return mrb_fixnum_value(static_cast<mrb_int>(value));
}

template <> inline mrb_value
cxx_mrb_numeric_value<unsigned int>(mrb_state *mrb, unsigned int value)
{
  return mrb_fixnum_value(static_cast<mrb_int>(value));
}

template <> inline float
cxx_mrb_get_arg<float>(mrb_state *mrb)
{
  mrb_float value;
  mrb_get_args(mrb, "f", &value);
  return static_cast<float>(value);
}

template <> inline int
cxx_mrb_get_arg<int>(mrb_state *mrb)
{
  mrb_int value;
  mrb_get_args(mrb, "i", &value);
  return static_cast<int>(value);
}

template <> inline unsigned int
cxx_mrb_get_arg<unsigned int>(mrb_state *mrb)
{
  mrb_int value;
  mrb_get_args(mrb, "i", &value);
  return static_cast<unsigned int>(value);
}

template <> inline bool
cxx_mrb_get_arg<bool>(mrb_state *mrb)
{
  mrb_bool value;
  mrb_get_args(mrb, "b", &value);
  return static_cast<bool>(value);
}

#endif
