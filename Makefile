# This makefile was created with help from the following stackoverflow answer:
# https://stackoverflow.com/a/23418196
EXE = epsilon
CC = g++
CPPFLAGS = -Wall -Wextra -fexceptions -std=c++17


ifeq ($(OS),Windows_NT)
EXE += .exe
else
LFLAGS +=  -no-pie
endif


ifeq (1, $(REL))
  CPPFLAGS += -O2 -s -DNDEBUG
  OBJ_DIR = ./obj/release
else
  CPPFLAGS += -g -O0
  OBJ_DIR = ./obj/debug
endif

SRCS = $(wildcard src/*.cpp)
df = $(OBJ_DIR)/$(*F)
AUTODEPS:=$(patsubst src/%.cpp, $(OBJ_DIR)/%.d, $(SRCS))
OBJS:=$(patsubst src/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
LIBOBJS := $(filter-out custom.o main.o, $(OBJS))


.PHONY : all clean tilde debug release remake

all: $(EXE)


$(EXE): $(OBJS)
	$(CC) $(SFLIBDIR) $(LFLAGS) -o $@ $^ $(LLIB)

$(OBJ_DIR)/%.o: src/%.cpp
	@$(CC) -MM -MP -MT $(df).o -MT $(df).d $(CPPFLAGS) $< > $(df).d
	$(CC) $(SFINCDIR) $(CPPFLAGS) -c $< -o $@

-include $(AUTODEPS)

remake: clean all

clean :
	rm -f obj/debug/*.o obj/release/*.o obj/debug/*.d obj/release/*.d ./stellar
tilde :
	rm *~
