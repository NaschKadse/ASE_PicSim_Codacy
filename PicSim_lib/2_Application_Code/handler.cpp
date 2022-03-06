#include "handler.h"

void handler::read(std::string filepath, utility &utility1) {
    localhandler->readFile(filepath, utility1);
}
