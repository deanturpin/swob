#include <algorithm>
#include <fstream>
#include <iomanip>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

// A project has a name and a toolchain of tool/revision pairs
struct project_info {
  std::string name;

  struct rev_date {
    std::string revision;
    std::string date;
  };

  std::vector<rev_date> toolchain;
};

// Open a project configuration and populate a container of revision information
std::vector<project_info> get_config(const std::string &);
std::vector<project_info> get_config(const std::string &file) {

  std::ifstream in(file);
  std::vector<project_info> info;

  // Read project name
  for (std::string name; std::getline(in, name);) {

    // Read the toolchain
    if (std::string pairs; std::getline(in, pairs)) {

      // Populate a local copy of toolchain
      std::vector<project_info::rev_date> toolchain;

      // Read the revision/date pairs
      std::istringstream ss(pairs);
      std::string key, value;
      while (ss >> key >> value)
        toolchain.push_back({key, value});

      // Store the project if there's a blank line delimiter
      if (std::string blank; std::getline(in, blank))
        if (blank.empty())
          info.push_back({name, toolchain});
    }
  }

  return info;
}

int main() {

  // Read tools and projects
  const auto &tools = get_config("tools.txt");
  const auto &projects = get_config("projects.txt");

  std::stringstream summary;

  for (const auto & [ project_name, toolchain ] : projects) {

    // Try to find date for tool and revision
    std::vector<double> ages;
    for (const auto & [ tool_name, revision ] : toolchain)
      if (const auto tool_it = std::find_if(
              tools.cbegin(),
              tools.cend(), [name = tool_name](
                                const auto
                                    &tool) { return tool.name == name; });
          tool_it != tools.cend()) {

        // Found the tool, check if there's a date for the revision
        const std::string date = [&tool_it, rev = revision ] {

          const auto &revisions = tool_it->toolchain;
          const auto revision_it =
              std::find_if(revisions.cbegin(), revisions.cend(),
                           [&rev](const auto &r) { return r.revision == rev; });

          return revision_it != revisions.cend() ? revision_it->date : "-1";
        }
        ();

        ages.push_back(std::strtod(date.c_str(), nullptr));
      }

    const double average_age =
        ages.empty()
            ? 0.0
            : std::accumulate(ages.cbegin(), ages.cend(), 0.0) / ages.size();

    summary << std::quoted(project_name) << ' ' << average_age << '\n';
  }

  // Dump summary to file
  if (std::ofstream out("summary.csv"); out.good())
    out << summary.str();
}
