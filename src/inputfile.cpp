#include "../header/inputfile.h"


inputfile::inputfile(std::string filepath) {
    this->filepath_l = std::move(filepath);
}

inputfile::~inputfile() = default;

std::string *inputfile::readFile() {
    std::string line;

    int i = 0;
    std::ifstream input(this->filepath_l);

    if (!input) {
        std::cerr << "Fehler beim Oeffnen der Datei " << this->filepath_l << "\n";

    } else {

        while (std::getline(input, line)) {
            if (isspace(line.at(0))) {
                continue;
            } else {

                utility convert(stoi(line.substr(5, 4), 0, 16));
                utility fillup(convert.toBinary(), 14);

                this->commandarray[stoi(line.substr(0, 4), 0, 16)] = fillup.fillup();
            }

        }


    }

    return commandarray;
}

