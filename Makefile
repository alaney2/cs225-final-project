#
#EXE = graph
#TEST = test
#
#EXE_OBJ = main.o
#OBJS = main.o Graph.o
#
#CXX = clang++
#LD = clang++
#OBJS_DIR = .objs
#
#DEPFILE_FLAGS = -MMD -MP
#
#WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
#
#CXXFLAGS += $(CS225) -std=c++14 -stdlib=libc++ -O0 $(WARNINGS) $(DEPFILE_FLAGS) -g -c
#
#LDFLAGS += $(CS225) -std=c++14 -stdlib=libc++ -lc++abi
#
#$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
#	$(CXX) $(CXXFLAGS) $< -o $@
#
#all: $(EXE)
#
#$(TEST): output_msg $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_TEST))
#	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@
#
#-include $(OBJS_DIR)/*.d
#-include $(OBJS_DIR)/src/*.d
#-include $(OBJS_DIR)/catch/*.d
#-include $(OBJS_DIR)/tests/*.d
##
### Rule for linking the final executable:
### - $(EXE) depends on all object files in $(OBJS)
### - `patsubst` function adds the directory name $(OBJS_DIR) before every object file
#$(EXE): output_msg $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS))
#	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@
#
#output_msg: ; $(CLANG_VERSION_MSG)
#
#clean:
#	rm -rf $(EXE) $(TEST) $(OBJS_DIR)  *.o *.d
#
#tidy: clean
#	rm -rf doc
#
#.PHONY: all tidy clean output_msg
g++ -c -std=c++0x -o main.o  main.cpp
g++ -c -std=c++0x -o src/graph.o  src/graph.cpp
g++ -o main main.o src/graph.o
