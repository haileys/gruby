CXXFLAGS=-I inc -DNO_SDK -DGMMODULE -m32 -Iruby/ruby-1.9.3-p286/include
LDFLAGS=-dynamiclib -flat_namespace -m32 -Wl,-undefined,dynamic_lookup

STEAM_APPS=/Users/charlie/Library/Application Support/Steam/SteamApps/charlie_somerville

OBJS=gruby.o lua.o

.PHONY: install all clean

all: gruby.dylib

clean:
	rm -f gruby.dylib
	rm -f loader
	rm -f *.o

install: gruby.dylib
	cp $< "$(STEAM_APPS)/garrysmod/garrysmod/lua/bin/gmsv_gruby_osx.dll"

gruby.dylib: $(OBJS) ruby/ruby-1.9.3-p286/libruby-static.a
	$(CXX) $(LDFLAGS) -o $@ $^
