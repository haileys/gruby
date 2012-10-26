#include <cstdlib>
#include <cstdio>
#include "gruby.hh"

char*
environ[] = { (char*)"GMOD=true", NULL };

lua_State*
gruby_L;

VALUE
cGMod;

static char*
gruby_to_s_(VALUE v)
{
    VALUE str = rb_obj_as_string(v);
    return rb_string_value_cstr(&str);
}

char*
gruby_to_s(VALUE v)
{
    int error = 0;
    char* cstr = (char*)rb_protect((VALUE(*)(VALUE))gruby_to_s_, v, &error);
    if(error) {
        lua_pushstring(gruby_L, "An exception was thrown by Ruby");
        lua_error(gruby_L);
        return NULL;
    } else {
        return cstr;
    }
}

static int
gruby_eval_(const char* src)
{
    VALUE retn = rb_obj_as_string(rb_eval_string(src));
    lua_pushstring(gruby_L, rb_string_value_cstr(&retn));
    return 1;
}

static int
gruby_eval(lua_State* state)
{
    if(LUA->IsType(1, GarrysMod::Lua::Type::STRING)) {
        unsigned int len;
        const char* src = LUA->GetString(1, &len);
        int error = 0;
        int retn = rb_protect((VALUE(*)(VALUE))gruby_eval_, (VALUE)src, &error);
        if(error) {
            lua_pushstring(state, "An exception was thrown by Ruby");
            return lua_error(state);
        } else {
            return retn;
        }
    } else {
        lua_pushstring(state, "gruby_eval() expects a string argument");
        lua_error(state);
    }
}

static VALUE
gruby_msg(int argc, VALUE* argv, VALUE self)
{
    for(int i = 0; i < argc; i++) {
        Msg(gruby_to_s(argv[i]));
        if(i + 1 < argc) {
            Msg(" ");
        }
    }
    Msg("\n");
    return Qnil;
}

extern "C" __attribute__((visibility("default"))) int
gmod13_open(lua_State* state)
{
    gruby_L = state;
    
    Msg("[gruby] Initializing...\n");
    
    int argc = 0;
    char** argv = NULL;
    ruby_init();
    
    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->PushString("gruby_eval");
    LUA->PushCFunction(gruby_eval);
    LUA->SetTable(-3);
    
    cGMod = rb_define_module("GMod");
    rb_define_singleton_method(cGMod, "msg", (VALUE(*)(...))gruby_msg, -1);
    
    Msg("[gruby] Ready to rock and roll.\n");
    
    return 0;
}

extern "C" __attribute__((visibility("default"))) int
gmod13_close(lua_State* state)
{
    return 0;
}