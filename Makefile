
EXE = graph
TEST = test

OBJS = main.o src/graph.o
CPP_TEST = $(wildcard tests/*.cpp)
CPP_TEST += catch/catchmain.cpp
CPP_TEST += src/graph.o
OBJS_TEST = $(CPP_TEST:.cpp=.o)


CXX = clang++
LD = clang++

DEPFILE_FLAGS = -MMD -MP
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
CXXFLAGS += -std=c++14 -stdlib=libc++ -O3 $(WARNINGS) $(DEPFILE_FLAGS) -g -c
LDFLAGS += -std=c++14 -stdlib=libc++ -lc++abi

all: $(EXE)

$(EXE) : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

$(TEST) : $(OBJS_TEST)
	$(LD) $(LDFLAGS) $(OBJS_TEST) -o $@


output_msg: ; $(CLANG_VERSION_MSG)

clean:
	rm -rf $(EXE) $(TEST) tests/*.o tests/*.d src/*.o src/*.d *.o *.d

clean-all: clean
	rm -rf catch/*.o catch/*.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean output_msg

