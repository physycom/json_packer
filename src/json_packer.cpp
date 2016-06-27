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

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <boost/algorithm/string.hpp>

#include "jsoncons/json.hpp"

#define MAJOR 1
#define MINOR 0

void usage(char * progname) {
  std::cout << "Usage: " << progname << " -o packed_name json_file1 json_file2 ... " << std::endl;
  std::cout << "       packed_name is the output name [optional, default = 'packed.json']" << std::endl;
  std::cout << "       each json_file must be a valid JSON archive, ellipsis (...) stand for an arbitrary number of files" << std::endl;
  exit(-6);
}

int main(int argc, char** argv) {
  std::cout << "Json Packer v" << MAJOR << "." << MINOR << std::endl << std::endl;

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
  if( input_files.size() == 0) usage(argv[0]);

  std::cout << "Packing : ";
  for (auto i : input_files) std::cout << i << "  ";
  std::cout << std::endl << "Output  : " << out_file << std::endl;

  jsoncons::json out_json;
  int counter = 0;
  for (auto file : input_files) {
    jsoncons::json in_json;
    try {
      in_json = jsoncons::json::parse_file(file);
    }
    catch (std::exception &e) {
      std::cout << "EXCEPTION: " << e.what() << std::endl;
    }

    if (in_json.is_object()) {
      for (auto it = in_json.begin_members(); it != in_json.end_members(); it++) {
        counter++;
        std::vector<std::string> tokens;
        boost::algorithm::split(tokens, it->name(), boost::is_any_of("_"), boost::algorithm::token_compress_off);
        std::stringstream obj_name;
        obj_name << tokens[0] << "_" << std::setw(5) << std::setfill('0') << counter;
        out_json[obj_name.str()] = it->value();
      }
    }
    else {
      std::cout << "ERROR: JSON array not supported" << std::endl;
      exit(-11);
    }
  }

  std::ofstream output(out_file);
  output << jsoncons::pretty_print(out_json);
  output.close();
  
  return 0;
}