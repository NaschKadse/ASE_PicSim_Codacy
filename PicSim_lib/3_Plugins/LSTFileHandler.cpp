#include "LSTFileHandler.h"
void LSTFileHandler::readFile(std::string filepath) {
    std::string line;
    std::ifstream input(filepath);
    if (!input) {
        std::cerr << "Fehler beim Oeffnen der Datei " << filepath << "\n";
    } else {
        while (std::getline(input, line)) {
            if (isspace(line.at(0))) {
                continue;
            } else {
                utility convert(stoi(line.substr(5, 4), 0, 16));
                utility fillup(convert.toBinary(), 14);
                picData1->setCommandArray(stoi(line.substr(0, 4), 0, 16), fillup.fillup());
            }
        }
    }

}

