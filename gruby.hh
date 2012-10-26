#ifndef GRUBY_HH
#define GRUBY_HH

#include <GarrysMod/Lua/Interface.h>

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#define HAVE_STRUCT_TIMESPEC
#include <ruby/ruby.h>

extern lua_State*
gruby_L;

extern VALUE
cGMod;

extern "C" void
Msg(const char* fmt);

char*
gruby_to_s(VALUE v);

#endif