/* Copyright 2016 - Stefano Sinigardi, Alessandro Fabbri */

/***************************************************************************
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/

#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>

#include "json.hpp"

using json = nlohmann::json;

using namespace std;

#define MAJOR 0
#define MINOR 0

void usage(char * progname) {
  std::cout << "Usage: " << progname << " -o packed_name json_file1 json_file2 ... " << std::endl;
  std::cout << "       packed_name is the output name [optional, default = 'packed.json']" << std::endl;
  std::cout << "       each json_file must be a valid JSON archive, ellipsis (...) stand for an arbitrary number of files" << std::endl;
  exit(-6);
}

int main(int argc, char** argv) {
  std::cout << "Json Packer II v" << MAJOR << "." << MINOR << std::endl << std::endl;

  std::vector<std::string> input_files;
  std::string out_file = "";
  if (argc > 2) {
    for (int i = 1; i < argc; i++) {
      if (std::string(argv[i]) == "-o") out_file = argv[++i];
      else input_files.push_back(argv[i]);
    }
  }
  else {
    usage(argv[0]);
  }

  out_file += (out_file == "") ? "packed.json" : "";
  if (input_files.size() == 0) usage(argv[0]);
  else sort(input_files.begin(), input_files.end());

  std::cout << "Packing : ";
  for (auto i : input_files) std::cout << i << "  ";
  std::cout << std::endl << "Output  : " << out_file << std::endl;

  json out_json;
  int counter = 0;
  for (auto file : input_files) {
    std::ifstream ifs(file);
    json in_json;
    try {
      in_json = json(ifs);
    }
    catch (std::exception& e) {
      std::cerr << "ERROR in parsing file " << file << " : " << e.what() << endl;
      continue;
    }
    ifs.close();

    if (in_json.is_object()) {
      for (auto it = in_json.begin(); it != in_json.end(); ++it) {
        std::vector<std::string> tokens;
        std::string temp = it.key();
        boost::algorithm::split(tokens, temp, boost::is_any_of("_"), boost::algorithm::token_compress_off);

        std::stringstream obj_name;
        for (size_t i = 0; i < tokens.size() - 1; i++) obj_name << tokens[i] << "_";
        obj_name << std::setw(5) << std::setfill('0') << counter;
        out_json[it.key()] = it.value();

        counter++;
      }
    }
    else {
      std::cerr << "ERROR: JSON array not supported in file " << file << std::endl;
      exit(11);
    }
  }

  std::ofstream output(out_file);
  output << out_json.dump(2) << endl;
  output.close();

  return 0;
}
