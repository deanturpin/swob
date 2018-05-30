#include <iostream>
#include <vector>

int main() {

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
}
