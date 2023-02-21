SUBDIRS = roots test
#ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

realclean: clean
	rm -rf autom4te.cache/
	rm -f config.h config.status config.log configure~ libtool stamp-h1
	rm -rf `find . | grep -E '.deps$$'`
	rm -f `find . | grep -E 'Makefile$$'`
