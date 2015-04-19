#ifndef MRB_SFML_TIME_PRIV_H
#define MRB_SFML_TIME_PRIV_H

#include <mruby.h>
#include <mruby/class.h>

extern "C" void mrb_sfml_time_init_bind(mrb_state *mrb, struct RClass *mod);

#endif
