#ifndef SWOB_H
#define SWOB_H

// A project needs a name and a list of attributes of the format:
// "tool-revision"
struct project {
  const std::string name{"no name"};
  const std::string toolchain{"Windows-10 gcc-5 RHEL-5"};
};

// Create some projects with toolchains
const std::vector<project> projects{
    {"Dean's laptop",
     "Ubuntu-17 gcc-6 clang-4 C++-14 kernel-4.10 python-3.5.3"},
    {"Dean's Travis CI config", "Ubuntu-14 gcc-8 clang-6 C++-14"},
    {"Roadmap 2018", "Ubuntu-18 gcc-7 clang-5 C++-14 kernel-4.14 python-3.6.5"},
    {"Roadmap 2019", "Ubuntu-19 gcc-8 clang-6 C++-17 kernel-4.17 python-3.6.5"},
};

#endif
