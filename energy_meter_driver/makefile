### Configuration.  ####################################################

# Binary to build
BIN		= esrv_test_device.so
# C source files for the library
SOURCES		= esrv_test_device_dynamic_library.c
# Object files corresponding to source files
OBJECTS		= $(SOURCES:.c=.o)
# Include directory
INCLUDEDIRS = -I../../../../src/energy_server
# Compilation flags (the -fPIC flag is because the files are compiled for a dynamic library)
CFLAGS = -g -Wall $(INCLUDEDIRS) -fPIC 
# Link flags
LDFLAGS = -g -shared

### Rules.  ############################################################

.PHONY:         all clean cleanall

all: depend $(BIN)

$(BIN): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS) 

clean:
	rm -f *~ *.bak *.BAK 

cleanall: clean
	rm -f $(OBJECTS) $(BIN) depend

depend: $(SOURCES)
	touch depend
	makedepend -- $(CFLAGS) -- $(SOURCES) 2>/dev/null

# DO NOT DELETE THIS LINE -- make depend depends on it.

esrv_test_device_dynamic_library.o: /usr/include/stdio.h
esrv_test_device_dynamic_library.o: /usr/include/features.h
esrv_test_device_dynamic_library.o: /usr/include/i386-linux-gnu/bits/predefs.h # le chemin dépend de l'ordi :s  
esrv_test_device_dynamic_library.o: /usr/include/i386-linux-gnu/sys/cdefs.h  #idem
esrv_test_device_dynamic_library.o: /usr/include/i386-linux-gnu/bits/wordsize.h #idem
esrv_test_device_dynamic_library.o: /usr/include/i386-linux-gnu/gnu/stubs.h #
esrv_test_device_dynamic_library.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h #
esrv_test_device_dynamic_library.o: /usr/include/i386-linux-gnu/bits/types.h #idem
esrv_test_device_dynamic_library.o: /usr/include/i386-linux-gnu/bits/typesizes.h #
esrv_test_device_dynamic_library.o: /usr/include/libio.h
esrv_test_device_dynamic_library.o: /usr/include/_G_config.h
esrv_test_device_dynamic_library.o: /usr/include/wchar.h
esrv_test_device_dynamic_library.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h #
esrv_test_device_dynamic_library.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
esrv_test_device_dynamic_library.o: /usr/include/string.h
esrv_test_device_dynamic_library.o: /usr/include/xlocale.h
esrv_test_device_dynamic_library.o: /usr/include/assert.h
esrv_test_device_dynamic_library.o: ../../../../src/energy_server/pub_esrv.h
esrv_test_device_dynamic_library.o: esrv_test_device_dynamic_library.h
