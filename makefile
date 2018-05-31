CXX = clang++
CCFLAGS = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -g --coverage
%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

all: swob.o
	cat template.md > readme.md
	echo 'Generated $(shell TZ=BST-1 date)' >> readme.md
	echo '```cpp' >> readme.md
	cat swob.h >> readme.md
	echo '```' >> readme.md
	./$< >> readme.md
clean:
	rm -f *.o
