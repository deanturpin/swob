CXX = g++-8
CCFLAGS = -std=c++17 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -g --coverage

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

all: swob.o
	cat template.md > readme.md
	TZ=BST-1 date >> readme.md
	echo '![](summary.svg)' >> readme.md
	echo '# Tools' >> readme.md
	echo '```' >> readme.md
	cat tools.txt >> readme.md
	echo '```' >> readme.md
	echo '# Projects' >> readme.md
	echo '```' >> readme.md
	cat projects.txt >> readme.md
	echo '```' >> readme.md
	gnuplot plot.txt

clean:
	rm -f *.o *.svg
