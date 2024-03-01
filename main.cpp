#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <vector>
#include <filesystem>

#define DEBUG false

bool isPipedInput() {
    return !isatty(STDIN_FILENO);
}

void writeTo(std::string& output, std::string& path){

    if(std::filesystem::exists(path)){
        std::ofstream file_out(path);
        if (file_out.is_open()) {
            file_out << output << std::endl;
            std::cout << "File created and data written." << std::endl;
            file_out.close();
        } else {
            std::cerr << "Error creating file for writing." << std::endl;
        }
    } else {
        std::ofstream file_out(path, std::ios::app);
        if (file_out.is_open()) {
            file_out << output << std::endl;
            file_out.close();
        } else {
            std::cerr << "Error opening file for writing." << std::endl;
        }
    }
}

void lineByLine(std::vector<int>& sight, std::vector<std::string>& line_buffer, std::string path = ""){
    int index = 0;
    std::string memo = "";
    std::fstream file;

    if (!path.empty()) {
        file.open(path);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << path << std::endl;
            return;
        }
    }

    for (std::string line; std::getline(path.empty() ? std::cin : file, line); ) {
        if(line != memo){
            if(index > 0){
                sight.push_back(index);
            }
            line_buffer.push_back(line);
            index = 1;
        } else if (line == memo) {
            index++;
        }
        memo = line;
    };
}


int main(int argc,char* argv[]){
    std::string output_path;
    std::string input_path;

    std::vector<int> sight;
    std::vector<std::string> line_buffer;

    bool shouldCount = false;
    bool shouldRepeated = false;
    bool shouldUnique = false;

    if(argc > 0){

        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];

            if(arg == "-c"){
                shouldCount = true;
            } else if(arg == "-d") {
                shouldRepeated = true;
            } else if(arg == "-u") {
                shouldUnique = true;
            } else if(arg == "-") {
                input_path = "-";
            } else {
                if(input_path.empty()) {
                    input_path = arg;
                } else if (output_path.empty()) {
                    output_path = arg;
                }
            }
        }
    }

#if DEBUG
    std::cout << "shouldCount: " << shouldCount << " shouldRepeated: " << shouldRepeated << " shouldUnique: " << shouldUnique  << "\n";
    std::cout << "input path: " << input_path << "\n" << "output path: " << output_path  << "\n";
#endif

    if (isPipedInput()) {
        lineByLine(sight, line_buffer);
    } else {
        lineByLine(sight, line_buffer, input_path);

    }


    std::string output = "";

    for (int i = 0; i < sight.size(); i++) {
        std::string reconstructed_line = (shouldCount ? (std::to_string(sight[i]) + " ") : "") + line_buffer[i] + "\n";
 
        if(sight[i] > 1 && shouldRepeated){
            output.append(reconstructed_line);
        } else if(sight[i] == 1 && shouldUnique){
            output.append(reconstructed_line);
        } else if(!shouldUnique && !shouldRepeated) {
            output.append(reconstructed_line);
        }
    }

    if(output_path.empty()){
        std::cout << output << "\n"; 
    } else {
        writeTo(output, output_path);
    }

    return 1;
}
