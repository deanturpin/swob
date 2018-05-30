A measure of software obsolescence based on toolchain age.

# References
* https://gcc.gnu.org/releases.html

# Configure and build
Edit ```swob.h``` and run ```make``` to generate new readme.

```cpp
#ifndef SWOB_H
#define SWOB_H

  // A project needs a name and a list of attributes of the format:
  // tool-revision
  struct project {
    const std::string name{"no name"};
    const std::string toolchain{"Windows-10 gcc-5 RHEL-5"};
  };

  // Create some projects with toolchains
  const std::vector<project> projects{
      {"Dean's laptop", "Ubuntu-17 gcc-6 clang-4 C++14"},
      {"Dean's Travis CI config", "Ubuntu-14 gcc-8 clang-6 C++14"},
      {"Roadmap 2018", "Ubuntu-18 gcc-7 clang-5 C++14"},
      {"Roadmap 2019", "Ubuntu-19 gcc-8 clang-6 C++17"},
  };

#endif
```
# Project summary
* 4 projects
* 4 tools

# Projects

Dean's laptop
* Ubuntu-17
* gcc-6
* clang-4
* C++14

Dean's Travis CI config
* Ubuntu-14
* gcc-8
* clang-6
* C++14

Roadmap 2018
* Ubuntu-18
* gcc-7
* clang-5
* C++14

Roadmap 2019
* Ubuntu-19
* gcc-8
* clang-6
* C++17
