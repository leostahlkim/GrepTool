###
###
### Authors:  Leo Kim and Ilan Hamond

MAKEFLAGS += -L 

# Compilation and Linking Flags
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# This rule builds gerp
gerp: main.cpp searchDir.o wordHash.o wordSensitive.o FSTree.o \
      DirNode.o
	$(CXX) $(LDFLAGS) -o gerp $^

# This rule builds FSTreeTraversal
treeTraversal: FSTreeTraversal.cpp DirNode.o FSTree.o
	$(CXX) $(LDFLAGS) -o treeTraversal $^

# This rule builds testMain
testMain: testMain.cpp searchDir.o wordSensitive.o wordHash.o DirNode.o \
          FSTree.o
	$(CXX) $(LDFLAGS) -o testMain $^

# This rule builds searchDir.o
searchDir.o: searchDir.cpp searchDir.h wordHash.h wordSensitive.h
	$(CXX) $(CXXFLAGS) -c searchDir.cpp
# This rule builds wordSensitive.o
wordSensitive.o: wordSensitive.cpp wordSensitive.h
	$(CXX) $(CXXFLAGS) -c wordSensitive.cpp

# This rule builds wordHash.o
wordHash.o: wordHash.cpp wordHash.h wordSensitive.h
	$(CXX) $(CXXFLAGS) -c wordHash.cpp

# This rule makes the unit test
unit_test: wordSensitive.o wordHash.o FSTree.o DirNode.o \
           searchDir.o unit_test_driver.o
	$(CXX) $(CXXFLAGS) $^

# Cleaning rule
clean: 
	rm a.out