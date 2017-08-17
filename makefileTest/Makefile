
srcDir?=$(shell find ./src -maxdepth 2 -type d|sort)
incDir?=$(shell find ./inc -maxdepth 2 -type d|sort)
incDir+=$(srcDir)
libDir?=$(shell find . -name lib)

vpath *.h $(incDir)
vpath *.c $(srcDir)
vpath *.cpp $(srcDir)

TARGET = god
FLAG = -g -o2 

src_c := $(wildcard $(foreach dir, $(srcDir), $(dir)/*.c))
obj_c := $(patsubst %.c, %.o, $(src_c))
src_cpp := $(wildcard $(foreach dir, $(srcDir), $(dir)/*.cpp))
obj_cpp := $(patsubst %.cpp, %.o, $(src_cpp))
OBJS = $(obj_c) $(obj_cpp)
LIB := $(patsubst %, -L%, $(wildcard $(libDir)))
INC := $(foreach dir, $(incDir), $(patsubst %,-I%,$(dir)))

.PHONY: $(TARGET) all clean show test

ifdef TARGET
$(TARGET):$(OBJS)
	@printf "\033[034m%s\033[033m %s\033[0m" "[CCLD]" "*.o --> $@"
	@gcc $(FLAG) $(INC) -o $@ $^ $(LIB)
	@printf "\r\033[75C\033[032m[ok]\033[0m\n"
endif

all:show
	@echo $(srcDir)
	@echo $(OBJS)
	@echo $(INC)

show:
	@printf "\033[034m%s\033[033m %s\033[0m\n" "[M....A....K....E]" `pwd`
	@echo $(srcDir)
	@echo $(OBJS)
	@echo $(INC)
clean:
	@rm -rf $(OBJS) $(TARGET)


%.o: %.c
	@printf "\033[034m%s\033[033m %s\033[0m" "[GCC ]" "$@"
	@gcc $(FLAG) $(INC) -o $@ -c $< $(LIB)
	@printf "\r\033[75C\033[032m[ok]\033[0m\n"
%.o: %.cpp
	@printf "\033[034m%s\033[033m %s\033[0m" "[G++ ]" "$@"
	@g++ $(FLAG) $(INC) -o $@ -c $< $(LIB)
	@printf "\r\033[75C\033[032m[ok]\033[0m\n"
