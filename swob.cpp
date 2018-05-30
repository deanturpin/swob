#include <iostream>
#include <vector>

int main() {

  // A project needs a name and a list of comma separated tools
  struct project {
    std::string name {"no name"};
    std::string toolchain {"Windows 10, gcc 5, RHEL 5"};
  };

  // Create some projects with toolchains
  const std::vector<project> projects {
    {"Dean's laptop", "Ubuntu 17, gcc 6, clang 4"},
    {"Dean's Travis build", "Ubuntu 14, gcc 8, clang 6"},
  };

  // Summary
  std::cout << projects.size() << " projects\n";
}
