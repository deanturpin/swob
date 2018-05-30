#include <iostream>
#include <sstream>
#include <vector>

int main() {

  // Tools
  struct tool {

    struct revision {
      const std::string name;
      const unsigned long year;
    };

    const std::string name{"no name"};
    const std::vector<revision> releases;
  };

  const std::vector<tool> tools{};

  // A project needs a name and a list of attributes, the tools are
  // comma-separated, the version and tool name is delimited by a space
  struct project {
    const std::string name{"no name"};
    const std::string toolchain{"Windows 10, gcc 5, RHEL 5"};
  };

  // Create some projects with toolchains
  const std::vector<project> projects{
      {"Dean's laptop", "Ubuntu 17, gcc 6, clang 4"},
      {"Dean's Travis build", "Ubuntu 14, gcc 8, clang 6"},
  };

  // Summary
  std::cout << projects.size() << " projects\n";
  std::cout << tools.size() << " tools\n";

  for (const auto &p : projects) {
    std::cout << p.name << ":\n";

    std::string line;
    std::stringstream toolchain(p.toolchain);
    while (std::getline(toolchain, line, ','))
      std::cout << '\t' << line << '\n';
  }

  /*
  vector<string> tokens{istream_iterator<string>{iss},
                          istream_iterator<string>{}};
                          */

  /*
   *     std::vector<std::string> elems;
   *         split(s, delim, std::back_inserter(elems));
   *         */
}
