#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int main() {

  // Tool definition
  struct tool {

    struct revision {
      const std::string name{};
      const unsigned long year{};
    };

    const std::string name{"no name"};
    const std::vector<revision> releases{};
  };

  // Tools we know about
  const std::vector<tool> tools{
      {
          "gcc",
          {
              {"3", 2003}, {"4", 2010}, {"5", 2015}, {"6", 2016},
          },
      },
      {
          "clang",
          {
              {"4", 2010}, {"5", 2015}, {"6", 2016},
          },
      },
      {
          "C++",
          {
              {"98", 1998},
              {"03", 2003},
              {"0x", 2008},
              {"11", 2011},
              {"14", 2014},
              {"17", 2017},
              {"2a", 2020},
          },
      },
  };

  // A project needs a name and a list of attributes
  struct project {
    const std::string name{"no name"};
    const std::string toolchain{"Windows-10, gcc-5, RHEL-5"};
  };

  // Create some projects with toolchains
  const std::vector<project> projects{
      {"Dean's laptop", "Ubuntu-17 gcc-6 clang-4 C++14"},
      {"Dean's Travis CI config", "Ubuntu-14 gcc-8 clang-6 C++14"},
      {"Roadmap 2018", "Ubuntu-18 gcc-7 clang-5 C++14"},
      {"Roadmap 2019", "Ubuntu-19 gcc-8 clang-6 C++17"},
  };

  // Summary
  std::cout << "# Project summary\n";
  std::cout << "* " << projects.size() << " projects\n";
  std::cout << "* " << tools.size() << " tools\n";

  // Print project info
  std::cout << "\n# Projects\n";
  for (const auto &p : projects) {

    std::cout << '\n' << p.name << ":\n";
    std::istringstream iss(p.toolchain);

    // Tokenise the toolchain
    for (const auto &t :
         std::vector<std::string>{std::istream_iterator<std::string>{iss},
                                  std::istream_iterator<std::string>{}}) {
      std::cout << "* " << t << '\n';

      // Split token into tool and revision
    }
  }
}
