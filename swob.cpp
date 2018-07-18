#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <tuple>
#include <vector>
#include <string>

int main() {

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

      {"ubuntu",
       {
           {"12", "2012"},
           {"13", "2013"},
           {"14", "2014"},
           {"15", "2015"},
           {"16", "2016"},
           {"17", "2017"},
           {"18", "2018"},
           {"19", "2019"},
       }},

      {"c++",
       {
           {"98", "1998"},
           {"03", "2003"},
           {"0x", "2008"},
           {"11", "2011"},
           {"14", "2014"},
           {"17", "2017"},
           {"2a", "2020"},
       }},

      {"clang",
       {
           {"3.5", "2014"}, {"4", "2017"}, {"5", "2017"}, {"6", "2018"},
       }},

      {"kali",
       {
           {"2018.2", "2018"},
       }},

      {"bash",
       {
           {"4.4", "2018"},
       }},

      {"python",
       {
           {"3.5.3", "2017"},
           {"3.6.5", "2018"},
       }},

      {"kernel",
       {
           {"4.14", "2018"},
           {"4.15", "2018"},
           {"4.16", "2018"},
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
               "c++", "17",
           },
           {
               "kernel", "4.16",
           },
           {
               "python", "3.5.3",
           },
           {
               "bash", "4.4",
           },
       }},

      {"Dean Travis",
       {{"ubuntu", "14"},
        {"gcc", "6"},
        {"kernel", "4.14"},
        {"clang", "6"},
        {"c++", "14"}}},
  };

  std::stringstream summary;

  for (const auto &project : projects) {
    std::cout << project.first << '\n';

    std::vector<double> ages;
    for (const auto &tool : project.second) {

      // Extract tool info
      std::string tool_name, revision;
      std::tie(tool_name, revision) = tool;

      // Try to find date for tool and version
      std::string date = "0";
      const auto tool_it = tools.find(tool_name);
      if (tool_it != tools.cend()) {
        date = "tbd";

        const auto revision_it = tool_it->second.find(revision);

        if (revision_it != tool_it->second.cend())
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

    std::cout << "\tAverage age of " << std::quoted(project.first) << ' ' << average_age << '\n';
    summary << std::quoted(project.first) << ' ' << average_age << '\n';
  }

  // Dump summary to file
  std::ofstream out("summary.csv");
  if (out.good())
    out << summary.str();
}
