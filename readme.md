[![Build
Status](https://travis-ci.org/deanturpin/swob.svg?branch=master)](https://travis-ci.org/deanturpin/swob)
[![codecov](https://codecov.io/gh/deanturpin/swob/branch/master/graph/badge.svg)](https://codecov.io/gh/deanturpin/swob)

A measure of software obsolescence based on toolchain age.

# Configure and build
Edit ```projects.txt``` and ```tools.txt``` then run ```make clean all``` to generate a new readme.

---
Sat  2 Jun 20:16:14 BST 2018
# Tools
```
gcc             4.1.2 2007 4.8.5 2015 5 2016 6 2017 7 2018 8 2018
clang           3.5 2014 4 2017 5 2017 6 2018
C++             98 1998 03 2003 0x 2008 11 2011 14 2014 17 2017 2a 2020
Ubuntu          12 2012 13 2013 14 2014 15 2015 16 2016 17 2017 18 2018 19 2019
kernel          3.10 2013 4.10 2017 4.14 2018 4.17 2018
python          3.5.3 2017 3.6.5 2018
qt              4.8.7 2011 5.6 2016 5.9 2017 5.12 2018
fw              4.1-rc8 2018 3.14.2 2013
Windows         XP 2001 7 2008 10 2010
RHEL            5 2007 6 2010 6.5 2013 7 2014 8 2019
```
# Projects
```
Dean-laptop     Ubuntu-17 gcc-6 clang-4 C++-14 kernel-4.10 python-3.5.3
Dean-Travis     Ubuntu-14 gcc-8 kernel-4.14 clang-6 C++-14
Roadmap-2018    Ubuntu-18 gcc-7 clang-5 C++-14 kernel-4.14 python-3.6.5
Roadmap-2019    Ubuntu-19 gcc-8 clang-6 C++-17 kernel-4.17 python-3.6.5
example1        gcc-4.8.5 C++-03 kernel-3.10 Windows-10 qt-4.8.7 RHEL-7 fw-4.1-rc8
example2        gcc-4.1.2 C++-03 kernel-3.10 RHEL-5 fw-3.14.2
```
# Summary
* 6 projects
* 10 tools

# Projects
```
Dean-laptop	2016.5
Dean-Travis	2016.4
Roadmap-2018	2017.17
Roadmap-2019	2018
example1	2012
example2	2008.6
```
![](summary.svg)
