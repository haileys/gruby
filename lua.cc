#include "gruby.hh"

VALUE cLua, cLua_Value;

VALUE
gruby_lua_object_from_stack()
{
    VALUE v = rb_obj_alloc(cLua_Value);
    DATA_PTR(v) = (void*)lua_ref(gruby_L, 1);
    return v;
}

static VALUE
Lua_eval(VALUE self, VALUE str)
{
    char* src = rb_string_value_cstr(&str);
    luaL_dostring(gruby_L, src);
    return gruby_lua_object_from_stack();
}

static void
push_lua_value(VALUE self)
{
    if(DATA_PTR(self) == (void*)0) {
        rb_raise(rb_eTypeError, "Invalid operation on uninitialized Lua::Value");
    }
    lua_getref(gruby_L, (int)DATA_PTR(self));
}

static VALUE
Lua_Value_alloc(VALUE self)
{
    DATA_PTR(self) = (void*)0;
    return self;
}

static VALUE
Lua_Value_to_s(VALUE self)
{
    push_lua_value(self);
    const char* str = lua_tostring(gruby_L, -1);
    return rb_str_new_cstr(str);
}

void
gruby_lua_init()
{
    cLua = rb_define_module("Lua");
    rb_define_module_function(cLua, "eval", (VALUE(*)(...))Lua_eval, 1);
    
    cLua_Value = rb_define_class_under(cLua, "Value", rb_cObject);
    rb_define_method(cLua_Value, "to_s", (VALUE(*)(...))Lua_Value_to_s, 0);
}