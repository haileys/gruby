# How to compile Ruby for GRuby

* Grab `ruby-1.9.3-p286.tar.gz` and extract.

* Run `./configure --disable-rubygems --disable-install-doc --disable-shared --build=i686-apple-darwin11.4.0 CFLAGS=-m32 CXXFLAGS=-m32 LDFLAGS=-m32`.

    * This compiles a 32 bit Ruby without rubygems or documentation or any crap we don't care about

* Run `make`, but NOT `make install`.

    * You may get a compile error because you don't have some 32 bit libraries or something. If so, just disable that ext with `--without-PACKAGE` and try again. I had issues with Tcl/Tk, so just nuke `ext/tk`