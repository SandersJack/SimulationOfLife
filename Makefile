.PHONY: all clean install

BUILDDIR=build

all: $(BUILDDIR)
	+@make -C $(BUILDDIR) --no-print-directory 

install: $(BUILDDIR)
	+@make -C $(BUILDDIR) install --no-print-directory

$(BUILDDIR): 
	@cmake -H. -B$(BUILDDIR) $(CMAKE_FLAGS) ${ARGS}

clean:
	rm -rf $(BUILDDIR)
