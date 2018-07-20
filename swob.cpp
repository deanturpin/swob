#include <algorithm>
#include <fstream>
#include <iomanip>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

struct project_info {
  std::string name;
  using rev_date = std::pair<std::string, std::string>;
  std::vector<rev_date> toolchain;
};

std::vector<project_info> get_config(const std::string &);
std::vector<project_info> get_config(const std::string &file) {

  std::ifstream in(file);
  std::vector<project_info> info;

  // Extract project name
  for (std::string name; std::getline(in, name);) {

    // Initialise a new project
    project_info p{name, {}};

    // Tool chain
    if (std::string pairs; std::getline(in, pairs)) {
      std::istringstream ss(pairs);
      std::string key, value;
      while (ss >> key >> value)
        p.toolchain.push_back({key, value});
    }

    // Look for a blank line to store it
    if (std::string blank; std::getline(in, blank))
      if (blank.empty())
        info.emplace_back(p);
  }

  return info;
}

int main() {

  const auto tools = get_config("tools.txt");
  const auto projects = get_config("projects.txt");

  std::stringstream summary;

  for (const auto & [ project_name, toolchain ] : projects) {

    std::vector<double> ages;
    for (const auto & [ tool_name, revision ] : toolchain) {

      // Try to find date for tool and version
      std::string date = "0";
      const auto tool_it = std::find_if(
          tools.cbegin(), tools.cend(), [name = tool_name](const auto &tool) {
            return tool.name == name;
          });

      if (tool_it != tools.cend()) {
        date = "-1";

        const auto &revisions = tool_it->toolchain;
        const auto revision_it =
            std::find_if(revisions.cbegin(),
                         revisions.cend(), [rev = revision](const auto &r) {
                           return r.first == rev;
                         });

        if (revision_it != revisions.cend())
          date = revision_it->second;
      }

      ages.push_back(std::strtod(date.c_str(), nullptr));
    }

    const double average_age =
        ages.empty()
            ? 0.0
            : std::accumulate(std::cbegin(ages), std::cend(ages), 0.0) /
                  ages.size();

    summary << std::quoted(project_name) << ' ' << average_age << '\n';
  }

  // Dump summary to file
  std::ofstream out("summary.csv");
  if (out.good())
    out << summary.str();
}
