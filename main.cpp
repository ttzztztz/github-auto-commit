#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <ctime>
#include <sstream>

// get system() call stdout function from https://oomake.com/question/307885
char *exec(const char *command) {
    FILE *fp;
    char *result = nullptr;
    size_t len = 0;
    fflush(nullptr);
    fp = popen(command, "r");
    if (fp == nullptr) {
        printf("Cannot execute command:\n%s\n", command);
        return nullptr;
    }
    while (getline(&result, &len, fp) != -1) {
        fputs(result, stdout);
    }
    free(result);
    fflush(fp);
    if (pclose(fp) != 0) {
        perror("Cannot close stream.\n");
    }
    return result;
}

int main() {
    std::string repo = getenv("GIT_REPO");

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
        std::cout << exec("cd /home/repo && git add . && git commit -m \"daily commit\" && git push -u origin master")
                  << std::endl;
        sleep(24 * 60 * 60);
    }

    return 0;
}