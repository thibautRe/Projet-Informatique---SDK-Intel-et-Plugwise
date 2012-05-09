### Configuration.  ####################################################

# Binary to build
BIN		= esrv_plugwise_driver.so
# C source files for the library
SOURCES		= esrv_plugwise_driver.c memory_allocation.c configuration_management.c
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

esrv_plugwise_driver.o: /usr/include/stdio.h
esrv_plugwise_driver.o: /usr/include/features.h
esrv_plugwise_driver.o: /usr/include/bits/predefs.h 
esrv_plugwise_driver.o: /usr/include/sys/cdefs.h
esrv_plugwise_driver.o: /usr/include/bits/wordsize.h
esrv_plugwise_driver.o: /usr/include/gnu/stubs.h
esrv_plugwise_driver.o: /usr/include/gnu/stubs-$(ARCHITECTURE).h
esrv_plugwise_driver.o: /usr/include/bits/types.h
esrv_plugwise_driver.o: /usr/include/bits/typesizes.h
esrv_plugwise_driver.o: /usr/include/libio.h
esrv_plugwise_driver.o: /usr/include/_G_config.h
esrv_plugwise_driver.o: /usr/include/wchar.h
esrv_plugwise_driver.o: /usr/include/bits/stdio_lim.h
esrv_plugwise_driver.o: /usr/include/bits/sys_errlist.h
esrv_plugwise_driver.o: /usr/include/string.h
esrv_plugwise_driver.o: /usr/include/xlocale.h
esrv_plugwise_driver.o: /usr/include/assert.h
esrv_plugwise_driver.o: $(IECSDK_ROOT)/src/energy_server/pub_esrv.h	
esrv_plugwise_driver.o: constants.h
esrv_plugwise_driver.o: memory_allocation.h
esrv_plugwise_driver.o: configuration_management.h
esrv_plugwise_driver.o: esrv_plugwise_driver.h

memory_allocation.o: memory_allocation.h constants.h 
configuration_management.o: configuration_management.h constants.h 
