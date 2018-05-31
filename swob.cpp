#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

#include "swob.h"

int main() {

  // Tool definition
  struct tool {

    struct revision {
      const std::string name;
      const unsigned long year;
    };

    const std::string name{"no name"};
    const std::vector<revision> releases{};
  };

  // Tools we know about
  const std::vector<tool> tools{
      {
          "gcc",
          {
              {"4.1.2", 2007},
              {"4.8.5", 2015},
              {"5", 2016},
              {"6", 2017},
              {"7", 2018},
              {"8", 2018},
          },
      },
      {
          "clang",
          {
              {"3.5", 2014}, {"4", 2017}, {"5", 2017}, {"6", 2018},
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
      {
          "Ubuntu",
          {
              {"12", 2012},
              {"13", 2013},
              {"14", 2014},
              {"15", 2015},
              {"16", 2016},
              {"17", 2017},
              {"18", 2018},
              {"19", 2019},
          },
      },
      {
          "kernel",
          {
              {"4.10", 2017}, {"4.14", 2018}, {"4.17", 2018},
          },
      },
      {
          "python",
          {
              {"3.5.3", 2017}, {"3.6.5", 2018},
          },
      },
  };

  // Summary
  std::cout << "# Project summary\n";
  std::cout << "* " << projects.size() << " projects\n";
  std::cout << "* " << tools.size() << " tools\n";
  std::cout << "\n# Projects\n";

  // Print project info
  std::cout << "```\n";
  for (const auto &p : projects) {

    std::istringstream iss(p.toolchain);
    std::stringstream warnings;

    std::vector<unsigned long> tool_years;

    // Tokenise the toolchain and extract the years
    for (const auto &t :
         std::vector<std::string>{std::istream_iterator<std::string>{iss},
                                  std::istream_iterator<std::string>{}}) {

      // Split token into tool name and revision
      std::istringstream token(t);
      std::string name, revision;
      std::getline(token, name, '-');
      token >> revision;

      // Look up the provenance of the tool
      const auto tool_iterator =
          std::find_if(std::cbegin(tools), std::cend(tools),
                       [&name](const auto &a) { return a.name == name; });

      // If we've found the tool then look for the revision
      if (tool_iterator != std::cend(tools)) {
        const auto revision_iterator = std::find_if(
            std::cbegin(tool_iterator->releases),
            std::cend(tool_iterator->releases),
            [&revision](const auto &b) { return b.name == revision; });

        if (revision_iterator != std::cend(tool_iterator->releases))
          tool_years.push_back(revision_iterator->year);
        else
          warnings << revision << " missing, ";

      } else
        warnings << name << " missing, ";
    }

    unsigned long mean_year = 0;
    if (!tool_years.empty())
      mean_year =
          std::accumulate(std::cbegin(tool_years), std::cend(tool_years), 0) /
          tool_years.size();

    std::cout << std::string(mean_year - 2000, '-') << "| " << p.name << " ("
              << tool_years.size() << ") " << warnings.str() << '\n';
  }
  std::cout << "```\n";
}
