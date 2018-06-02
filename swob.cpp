#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

// A project needs a name and a list of attributes of the format:
// "tool-revision"
struct project {
  std::string name{"noname"};
  std::string toolchain{};
};

int main() {

  // Read project details
  std::vector<project> projects;
  std::ifstream project_file("projects.txt");
  if (project_file.good()) {
    std::string line;
    while (getline(project_file, line)) {
      std::stringstream ss(line);
      project p;
      ss >> p.name;
      std::string tool;
      while (ss >> tool)
        p.toolchain += tool + " ";
      projects.push_back(p);
    }
  }

  // A tool has a name and a list of revision/years
  struct tool {
    struct revision {
      std::string name{"noname"};
      unsigned long year;
    };

    std::string name{"noname"};
    std::vector<revision> releases{};
  };

  // Read tool details
  std::vector<tool> tools;
  std::ifstream tool_file("tools.txt");
  if (tool_file.good()) {
    std::string line;
    while (getline(tool_file, line)) {
      std::stringstream ss(line);
      tool t;
      ss >> t.name;

      std::string rev;
      while (ss >> rev) {
        unsigned long year;
        ss >> year;
        tool::revision r{rev, year};
        t.releases.emplace_back(r);
      }

      tools.push_back(t);
    }
  }

  std::stringstream summary;
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

    double mean_year = 0;
    if (!tool_years.empty())
      mean_year =
          std::accumulate(std::cbegin(tool_years), std::cend(tool_years), 0.0) /
          tool_years.size();

    summary << p.name << '\t' << mean_year - 2000 << '\n';
    // std::cout << std::string(mean_year - 2000, '-') << "| " << p.name << " ("
    //           << tool_years.size() << ") " << warnings.str() << '\n';
  }

  // Summary
  std::cout << "# Summary\n";
  std::cout << "* " << projects.size() << " projects\n";
  std::cout << "* " << tools.size() << " tools\n";
  std::cout << "\n# Projects\n";
  std::cout << "```\n";
  std::cout << summary.str();
  std::cout << "```\n";

  // Dump summary to file
  std::ofstream out("summary.csv");
  if (out.good())
    out << summary.str();
}
