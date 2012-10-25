#include <cstdlib>
#include <cstdio>
#include <GarrysMod/Lua/Interface.h>
#define HAVE_STRUCT_TIMESPEC
#include <ruby/ruby.h>

char*
environ[] = { (char*)"GMOD=true", NULL };

static lua_State*
g_Lua;

int
gruby_func(lua_State* state)
{
    if(LUA->IsType(1, GarrysMod::Lua::Type::STRING)) {
        unsigned int len;
        const char* src = LUA->GetString(1, &len);
        VALUE retn = rb_obj_as_string(rb_eval_string(src));
        LUA->PushString(rb_string_value_cstr(&retn));
        return 1;
    } else {
        return 0;
    }
}

extern "C" __attribute__((visibility("default"))) int
gmod13_open(lua_State* state)
{
    g_Lua = state;
    
    int argc = 0;
    char** argv = NULL;
    ruby_init();
    
    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->PushString("gruby_eval");
    LUA->PushCFunction(gruby_func);
    LUA->SetTable(-3);
    
    return 0;
}

extern "C" __attribute__((visibility("default"))) int
gmod13_close(lua_State* state)
{
    return 0;
}