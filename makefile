src = $(wildcard *c)
dir = $(notdir $(src))
objects = $(patsubst %c, %o, $(dir))

all: $(objects)
	@echo src = $(src)
	@echo dir = $(dir)
	@echo $(objects)

$(objects): %.o: %.c
	gcc -c $(CFLAGS) $< -o $@
