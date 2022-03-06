#include "LSTFileHandler.h"

void LSTFileHandler::readFile(std::string filepath, utility &utility1) {
    std::string line;
    std::ifstream input(filepath);

    if (!input) {
        std::cerr << "Fehler beim Oeffnen der Datei " << filepath << "\n";
    } else {
        while (std::getline(input, line)) {
            if (isspace(line.at(0))) {
                continue;
            } else {

                utility1.setToBin(stoi(line.substr(5, 4), 0, 16));
                utility1.setDigits(14);
                BinaryString = utility1.toBinary();
                utility1.setToFill(BinaryString);
                std::string FullString = utility1.fillup();
                picData1->setCommandArray(stoi(line.substr(0, 4), 0, 16), FullString);

                /*
                utility convert(stoi(line.substr(5, 4), 0, 16));
                utility fillup(convert.toBinary(), 14);
                picData1->setCommandArray(stoi(line.substr(0, 4), 0, 16), fillup.fillup());
                 */
            }
        }
    }
}