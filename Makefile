
EXE = graph
TEST = test

OBJS = main.o src/graph.o
OBJS_TEST = tests/graph_test.o

main.o : main.cpp
src/graph.o : src/graph.cpp

CXX = clang++
LD = clang++

DEPFILE_FLAGS = -MMD -MP
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
CXXFLAGS += -std=c++14 -stdlib=libc++ -O2 $(WARNINGS) $(DEPFILE_FLAGS) -g -c
LDFLAGS += -std=c++14 -stdlib=libc++ -lc++abi

all: $(EXE)

$(EXE) : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

output_msg: ; $(CLANG_VERSION_MSG)

clean:
	rm -rf $(EXE) $(TEST)  *.o *.d

tidy: clean
	rm -rf doc

.PHONY: all tidy clean output_msg

