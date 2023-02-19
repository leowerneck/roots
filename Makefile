.PHONY: roots test
prefix=None

all: roots

roots:
	meson compile -vC build

test:
	meson test -C build

test-verbose:
	meson test -vC build

install: roots
	meson install -C build

clean:
	@echo "Cleaning object files"
	@rm -f `find build | grep -E "\.[s]?o$$"`

realclean:
	@echo "Removing build and Makefile. Run configure again before building."
	@rm -rf build lib include
	@rm -f Makefile

uninstall:
	@echo "Removing header files from $(prefix)/include"
	@rm -f `find $(prefix)/include | grep roots.h`
	@echo "Removing library files from $(prefix)/lib"
	@rm -f `find $(prefix)/lib | grep libroots`
	@echo "All done"
