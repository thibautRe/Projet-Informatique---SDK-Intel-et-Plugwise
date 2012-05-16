### Configuration.  ####################################################

# Binary and executable to build
BIN		= ../esrv_plugwise_driver.so
EXEC		= ../configurations
# C source files for the library
SOURCES		= esrv_plugwise_driver.c memory_allocation.c configuration_management.c

# Object files corresponding to source files
OBJECTS		= $(SOURCES:.c=.o)

# Root directory :
IECSDK_ROOT = $(shell find /home/ -type d -name iecsdk 2> /dev/null | grep -v iecsdk/build/windows/iecsdk | grep -v Trash)

# Include directory
INCLUDEDIRS = -I$(IECSDK_ROOT)/src/energy_server

# Computer Architecture : 
ARCHITECTURE = $(shell getconf LONG_BIT)

# Compilation flags (the -fPIC flag is because the files are compiled for a dynamic library)
CFLAGS = -g -Wall $(INCLUDEDIRS) -fPIC 

# Link flags
LDFLAGS = -g -shared

# Other information
ARCH_LINUX_GNU = $(shell find /usr/include -type d -name i386-linux-gnu 2> /dev/null | cut -d/ -f4)

### Rules.  ############################################################

.PHONY:         all clean cleanall

all: depend $(BIN) $(EXEC)
	@echo "The SDK Intel Energy Checker root : $(IECSDK_ROOT)"
	@echo "Architecture : $(ARCHITECTURE) bits"
$(BIN): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS) 

$(EXEC):configurations.o configuration_management.o memory_allocation.o
	$(CC) -Wall -o $@ $^

clean:
	rm -f *~ *.bak *.BAK

cleanall: clean
	rm -f $(OBJECTS) $(BIN) depend

depend: $(SOURCES)
	touch depend
	makedepend -- $(CFLAGS) -- $(SOURCES) 2>/dev/null

# DO NOT DELETE THIS LINE -- make depend depends on it.

esrv_plugwise_driver.o: /usr/include/stdio.h
esrv_plugwise_driver.o: /usr/include/features.h
# In some OS, 9 headers are in the i386-linux-gnu folder
ifeq ($(ARCH_LINUX_GNU),i386-linux-gnu)
esrv_plugwise_driver.o: /usr/include/i386-linux-gnu/bits/predefs.h 
esrv_plugwise_driver.o: /usr/include/i386-linux-gnu/sys/cdefs.h 
esrv_plugwise_driver.o: /usr/include/i386-linux-gnu/bits/wordsize.h
esrv_plugwise_driver.o: /usr/include/i386-linux-gnu/gnu/stubs.h 
esrv_plugwise_driver.o: /usr/include/i386-linux-gnu/gnu/stubs-$(ARCHITECTURE).h 
esrv_plugwise_driver.o: /usr/include/i386-linux-gnu/bits/types.h 
esrv_plugwise_driver.o: /usr/include/i386-linux-gnu/bits/typesizes.h
esrv_plugwise_driver.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
esrv_plugwise_driver.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
else
esrv_plugwise_driver.o: /usr/include/bits/predefs.h 
esrv_plugwise_driver.o: /usr/include/sys/cdefs.h
esrv_plugwise_driver.o: /usr/include/bits/wordsize.h
esrv_plugwise_driver.o: /usr/include/gnu/stubs.h
esrv_plugwise_driver.o: /usr/include/gnu/stubs-$(ARCHITECTURE).h
esrv_plugwise_driver.o: /usr/include/bits/types.h
esrv_plugwise_driver.o: /usr/include/bits/typesizes.h
esrv_plugwise_driver.o: /usr/include/bits/stdio_lim.h
esrv_plugwise_driver.o: /usr/include/bits/sys_errlist.h
endif
esrv_plugwise_driver.o: /usr/include/libio.h
esrv_plugwise_driver.o: /usr/include/_G_config.h
esrv_plugwise_driver.o: /usr/include/wchar.h
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