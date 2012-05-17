### Configuration.  ####################################################
# Compilator
CC		= gcc

# Binary and executable to build
BIN		= esrv_plugwise_driver.so
EXEC		= configurations

# Source files
SRC		= $(wildcard ./src/*)

# Object files corresponding to source files
OBJECTS		= $(subst .c,.o,$(subst ./src/,./obj/,$(SRC)))
OBJECTS_BIN 	= $(OBJECTS)
OBJECTS_EXEC 	= $(subst ./obj/esrv_plugwise_driver.o,,$(OBJECTS))

# Root and include directories :
IECSDK_ROOT 	= $(shell find /home/ -type d -name iecsdk 2> /dev/null | grep -v iecsdk/build/windows/iecsdk | grep -v Trash)
INCLUDEDIRS 	= $(IECSDK_ROOT)/src/energy_server:include

# Compilation and link flags (the -fPIC flag is because the files are compiled for a dynamic library)
CFLAGS 		= -g -Wall $(patsubst %,-I%,$(subst :, ,$(INCLUDEDIRS))) -fPIC 
LDFLAGS 	= -g -shared

### Rules.  ############################################################

.PHONY: all clean cleanall

all: information $(EXEC) $(BIN)

$(BIN): $(OBJECTS_BIN)
	$(CC) -o $@ $^ $(LDFLAGS) 

$(EXEC): $(OBJECTS_EXEC) 
	$(CC) -o $@ $^

./obj/%.o: ./src/%.c
	$(CC) -o $@ -c $^ $(CFLAGS) 

clean:
	rm -f *~ *.bak *.BAK

cleanall: clean
	rm -f $(OBJECTS) $(EXEC) $(BIN)

information:
	@echo "# iecsdk root: $(IECSDK_ROOT)"