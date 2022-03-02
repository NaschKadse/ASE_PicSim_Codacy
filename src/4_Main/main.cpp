#include "../../header/picsimgui.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    PicSimGui w;
    w.show();
    return a.exec();
}
