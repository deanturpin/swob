#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <sstream>
#include <tuple>
#include <vector>

using project_info =
    const std::map<std::string, std::map<std::string, std::string>>;

project_info tools{
    {"gcc",
     {
         {"4.1.2", "2007"},
         {"4.8.3", "2014"},
         {"4.8.5", "2015"},
         {"5", "2016"},
         {"6", "2017"},
         {"7", "2018"},
         {"8", "2018"},
     }},

    {"clang",
     {
         {"3.5", "2014"}, {"4", "2017"}, {"5", "2017"}, {"6", "2018"},
     }},
};

project_info projects{
    {"Dean laptop",
     {
         {
             "kali", "2018.2",
         },
         {
             "gcc", "8",
         },
         {
             "C++", "14",
         },
         {
             "kernel", "4.15",
         },
         {
             "python", "3.5.3",
         },
         {
             "Firefox", "53.7.3",
         },
         {
             "bash", "4.4",
         },
     }},

    {"Dean Travis",
     {{"Ubuntu", "14"},
      {"gcc", "6"},
      {"kernel", "4.14"},
      {"clang", "6"},
      {"C++", "14"}}},
};

int main() {

  for (const auto &project : projects) {
    std::cout << project.first << '\n';
    for (const auto &tool : project.second) {

      // Extract tool info
      std::string tool_name, revision;
      std::tie(tool_name, revision) = tool;

      // Try to find date for tool and version
      std::string date = "unknown";
      const auto tool_it = tools.find(tool_name);
      if (tool_it != tools.cend()) {
        date = "tbd";

        const auto revision_it = tool_it->second.find(revision);

        if (revision_it != tool_it->second.cend())
          date = revision_it->second;
      }

      std::cout << '\t' << tool_name << '\t' << revision << '\t' << date
                << '\n';
    }
  }

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
  //         std::accumulate(std::cbegin(tool_years), std::cend(tool_years),
  //         0.0) /
  //         tool_years.size();

  //   summary << p.name << '\t' << mean_year << '\n';
  // }

  // // Dump summary to file
  // std::ofstream out("summary.csv");
  // if (out.good())
  //   out << summary.str();
}
