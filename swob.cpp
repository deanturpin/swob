#include <algorithm>
#include <fstream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>
#include <iostream>

// A project needs a name and a list of attributes of the format:
struct project {
  std::string name;
  std::vector<std::string> toolchain;

  friend std::istream& operator>>(std::istream &in, project &p) {
	  p.toolchain = {std::istream_iterator<std::string>(in), {}};
	  return in;
  }
};

auto parse_config(const std::string file) {

// We will return a vector of projects
  std::vector<project> projects;

  std::ifstream project_file(file);
  std::string line;
  project proj;

  while (getline(project_file, line)) {

	  // Skip blank lines
	  if (!line.empty()) {

		  // Store the unpopulated param
		  std::stringstream ss(line);
		  if (proj.name.empty())
			  ss >> proj.name;
		  else
			  ss >> proj;
	  }

	  // If project is complete store it and clear down local
	  if (!proj.toolchain.empty()) {
		  projects.emplace_back(proj);
		  proj.name.clear();
		  proj.toolchain.clear();
	  }
  }

  return projects;
}

int main() {

  // Read project and tool info
  const auto &projects = parse_config("projects.txt");
  const auto &tools = parse_config("tools.txt");

  // Print summary
  for (const auto &type: {tools, projects})
	  for (const auto &i: type)
		  std::cout << i.name << '\n';

  // std::stringstream summary;
  // for (const auto &p : projects) {

  //   std::istringstream iss(p.toolchain);
  //   std::stringstream warnings;

  //   std::vector<unsigned long> tool_years;

  //   // Tokenise the toolchain and extract the years
  //   for (const auto &t :
  //        std::vector<std::string>{std::istream_iterator<std::string>{iss},
  //                                 std::istream_iterator<std::string>{}}) {

  //     // Split token into tool name and revision
  //     std::istringstream token(t);
  //     std::string name, revision;
  //     std::getline(token, name, '-');
  //     token >> revision;

  //     // Look up the provenance of the tool
  //     const auto tool_iterator =
  //         std::find_if(std::cbegin(tools), std::cend(tools),
  //                      [&name](const auto &a) { return a.name == name; });

  //     // If we've found the tool then look for the revision
  //     if (tool_iterator != std::cend(tools)) {
  //       const auto revision_iterator = std::find_if(
  //           std::cbegin(tool_iterator->releases),
  //           std::cend(tool_iterator->releases),
  //           [&revision](const auto &b) { return b.name == revision; });

  //       if (revision_iterator != std::cend(tool_iterator->releases))
  //         tool_years.push_back(revision_iterator->year);
  //       else
  //         warnings << revision << " missing, ";

  //     } else
  //       warnings << name << " missing, ";
  //   }

  //   double mean_year = 0;
  //   if (!tool_years.empty())
  //     mean_year =
  //         std::accumulate(std::cbegin(tool_years), std::cend(tool_years), 0.0) /
  //         tool_years.size();

  //   summary << p.name << '\t' << mean_year << '\n';
  // }

  // // Dump summary to file
  // std::ofstream out("summary.csv");
  // if (out.good())
  //   out << summary.str();
}
