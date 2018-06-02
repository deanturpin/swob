CXX = g++-6
CCFLAGS = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor
DEBUG = -g --coverage

%.o: %.cpp
	$(CXX) -o $@ $< $(CCFLAGS) $(DEBUG)

all: swob.o
	cat template.md > readme.md
	TZ=BST-1 date >> readme.md

	echo '# Tools' >> readme.md
	echo '```' >> readme.md
	cat tools.txt >> readme.md
	echo '```' >> readme.md

	echo '# Projects' >> readme.md
	echo '```' >> readme.md
	cat projects.txt >> readme.md
	echo '```' >> readme.md

	$(shell gnuplot <<< 'set terminal svg; set output "summary.svg"; plot "summary.csv" using 2')
	./$< >> readme.md
	echo '![](summary.svg)' >> readme.md

clean:
	rm -f *.o
