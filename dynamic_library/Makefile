BIN	= esrv_plugwise_driver.so
EXEC	= configurations 

all: $(EXEC) $(BIN)

$(EXEC) $(BIN):
	@(cd src && $(MAKE))

.PHONY: cleanall cleanall $(EXEC)

clean:
	@(cd src  && $(MAKE) $@)

cleanall: clean
	@(cd src && $(MAKE) $@)
