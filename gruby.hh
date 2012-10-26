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

extern VALUE
cLua;

extern "C" void
Msg(const char* fmt);

char*
gruby_to_s(VALUE v);

VALUE
gruby_lua_object_from_stack();

void
gruby_lua_init();

#endif