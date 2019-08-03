#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <ctime>
#include <sstream>

int main() {
    std::cout << "Init global config..." << std::endl;
    while (true) {
        std::fstream rand_stream;
        std::time_t timestamp = time(nullptr);
        std::stringstream ss;
        ss << "/home/repo/fake_file_" << timestamp << ".temp";
        std::string fake_file_path;
        ss >> fake_file_path;

        rand_stream.open(fake_file_path, std::ios_base::out);
        rand_stream << timestamp;
        rand_stream.close();

        std::cout << timestamp << " will push to remote repo." << std::endl;
        std::cout << system("cd /home/repo && git add . && git commit -m \"daily commit\" && git push -u origin master")
                  << std::endl;
        sleep(24 * 60 * 60);
    }

    return 0;
}