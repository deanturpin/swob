#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

// using project_info =
// const std::map<std::string, std::vector<std::pair<std::string, std::string>>>;
//

struct project_info {
	std::string name;
	std::vector<std::pair<std::string, std::string>> toolchain;
};


std::vector<project_info> get_config(const std::string &);
std::vector<project_info> get_config(const std::string &file) {

	std::ifstream in(file);
	std::vector<project_info> info;
	for(std::string line; std::getline(in, line);) {
		const std::string name (line);
		std::getline(in, line);
		const std::string pairs (line);
		std::getline(in, line);

		if (line.empty()) {
			// std::cout << name << " stored\n";
			project_info p{name, {}};
			info.emplace_back(p);
		}

		// std::cout << name << '\n';
	}

	return info;
}

int main() {

  const auto tools = get_config("tools.txt");
  std::cout << tools.size() << " tools\n";
  const auto projects = get_config("projects.txt");
  std::cout << projects.size() << " projects\n";

  std::stringstream summary;

  for (const auto & [ project_name, toolchain ] : projects) {
    std::cout << project_name << '\n';

    std::vector<double> ages;
    for (const auto & [ tool_name, revision ] : toolchain) {

      // Try to find date for tool and version
      std::string date = "0";
      const auto tool_it = std::find_if(tools.cbegin(),
		      tools.cend(), [name = tool_name](const auto &tool){
		      	return tool.name == name;
		      });

      if (tool_it != tools.cend()) {
        date = "-1";

	const auto &revisions = tool_it->toolchain;
        const auto revision_it = std::find_if(revisions.cbegin(),
			revisions.cend(), [rev = revision](const auto &r){
				return r.first == rev;
			});

        if (revision_it != revisions.cend())
          date = revision_it->second;
      }

      ages.push_back(std::strtod(date.c_str(), nullptr));

      std::cout << '\t' << tool_name << '\t' << revision << '\t' << date
                << '\n';
    }

    const double average_age =
        ages.empty()
            ? 0.0
            : std::accumulate(std::cbegin(ages), std::cend(ages), 0.0) /
                  ages.size();

    std::cout << "\tAverage age of " << std::quoted(project_name) << ' '
              << average_age << '\n';
    summary << std::quoted(project_name) << ' ' << average_age << '\n';
  }

  // Dump summary to file
  std::ofstream out("summary.csv");
  if (out.good())
    out << summary.str();
}
