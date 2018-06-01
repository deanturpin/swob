[![Build
Status](https://travis-ci.org/deanturpin/swob.svg?branch=master)](https://travis-ci.org/deanturpin/swob)
[![codecov](https://codecov.io/gh/deanturpin/swob/branch/master/graph/badge.svg)](https://codecov.io/gh/deanturpin/swob)

A measure of software obsolescence based on toolchain age.

# Configure and build
Edit ```projects.txt``` and run ```make clean all``` to generate new readme.

---
Fri  1 Jun 22:10:00 BST 2018
```cpp
Dean-laptop     Ubuntu-17 gcc-6 clang-4 C++-14 kernel-4.10 python-3.5.3
Dean-Travis     Ubuntu-14 gcc-8 kernel-4.14 clang-6 C++-14
Roadmap-2018    Ubuntu-18 gcc-7 clang-5 C++-14 kernel-4.14 python-3.6.5
Roadmap-2019    Ubuntu-19 gcc-8 clang-6 C++-17 kernel-4.17 python-3.6.5
example1        gcc-4.8.5 C++-03 kernel-3.10 Windows-10 qt-4.8.7 RHEL-7 fw-4.1-rc8
```
# Project summary
* 5 projects
* 10 tools

# Projects
```
----------------| Dean-laptop (6) Dean missing, 
----------------| Dean-Travis (5) Dean missing, 
-----------------| Roadmap-2018 (6) Roadmap missing, 
------------------| Roadmap-2019 (6) Roadmap missing, 
------------| example1 (7) example1 missing, 
```
