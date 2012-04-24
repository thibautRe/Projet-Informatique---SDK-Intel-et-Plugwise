### Configuration.  ####################################################

# Binary to build
BIN		= esrv_test_device.so
# C source files for the library
SOURCES		= esrv_test_device_dynamic_library.c allocation_memoire.c gestion_configurations.c
# Object files corresponding to source files
OBJECTS		= $(SOURCES:.c=.o)
# Root directory : TODO
IECSDK_ROOT = /home/telecom_sudparis/projet_informatique/iecsdk
# Include directory
INCLUDEDIRS = -I$(IECSDK_ROOT)/src/energy_server
# Computer Architecture : TODO 
ARCHITECTURE = 64
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

# Attention, dans la machine d'Oussama certains fichiers se trouvent
# dans i386machintruc !		

esrv_test_device_dynamic_library.o: /usr/include/stdio.h
esrv_test_device_dynamic_library.o: /usr/include/features.h
esrv_test_device_dynamic_library.o: /usr/include/bits/predefs.h 
esrv_test_device_dynamic_library.o: /usr/include/sys/cdefs.h
esrv_test_device_dynamic_library.o: /usr/include/bits/wordsize.h
esrv_test_device_dynamic_library.o: /usr/include/gnu/stubs.h
esrv_test_device_dynamic_library.o: /usr/include/gnu/stubs-$(ARCHITECTURE).h
esrv_test_device_dynamic_library.o: /usr/include/bits/types.h
esrv_test_device_dynamic_library.o: /usr/include/bits/typesizes.h
esrv_test_device_dynamic_library.o: /usr/include/libio.h
esrv_test_device_dynamic_library.o: /usr/include/_G_config.h
esrv_test_device_dynamic_library.o: /usr/include/wchar.h
esrv_test_device_dynamic_library.o: /usr/include/bits/stdio_lim.h
esrv_test_device_dynamic_library.o: /usr/include/bits/sys_errlist.h
esrv_test_device_dynamic_library.o: /usr/include/string.h
esrv_test_device_dynamic_library.o: /usr/include/xlocale.h
esrv_test_device_dynamic_library.o: /usr/include/assert.h
esrv_test_device_dynamic_library.o: $(IECSDK_ROOT)/src/energy_server/pub_esrv.h	
esrv_test_device_dynamic_library.o: constantes.h
esrv_test_device_dynamic_library.o: allocation_memoire.h
esrv_test_device_dynamic_library.o: gestion_configurations.h
esrv_test_device_dynamic_library.o: esrv_test_device_dynamic_library.h

allocation_memoire.o: allocation_memoire.h constantes.h 
gestion_configurations.o: gestion_configurations.h constantes.h 
