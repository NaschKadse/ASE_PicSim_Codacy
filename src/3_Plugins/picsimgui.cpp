#include "../../header/picsimgui.h"
#include "../../forms/ui_PicSimGui.h"
#include <QButtonGroup>
#include <fstream>

PicSimGui::PicSimGui(QWidget *parent) : QMainWindow(parent), ui(new Ui::PicSimGui) {

    ui->setupUi(this);
    picSim1.init(true); // Power on reset

    QButtonGroup* rambuttonGroup = new QButtonGroup(this);

    for (int i = 0; i < 256; i++) {
        rambuttonGroup->addButton(this->findChild<QPushButton *>(QString::fromStdString("pushButton_" + std::to_string(i))),i);
    }

    connect(rambuttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(ramButtons(int)));

    QApplication::setFont(fixedFont);
    ui->table->setColumnWidth(0, 25);
    ui->table->setColumnWidth(1, 925);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);
    ui->table->horizontalHeader()->hide();
    ui->table->verticalHeader()->hide();
    ui->pushButton_resetruntime->setFont(fixedFont);
    ui->pushButton_schnellLaden->setFont(fixedFont);
    ui->pushButton_laden->setFont(fixedFont);
    ui->pushButton_start->setFont(fixedFont);
    ui->pushButton_stop->setFont(fixedFont);
    ui->pushButton_next->setFont(fixedFont);
    ui->pushButton_reset->setFont(fixedFont);
    ui->pushButton_test->setFont(fixedFont);
    ui->comboBox->setFont(fixedFont);
    ui->comboBox_2->setFont(fixedFont);
    ui->comboBox->addItem("TPicSim1.LST");
    ui->comboBox->addItem("TPicSim2.LST");
    ui->comboBox->addItem("TPicSim3.LST");
    ui->comboBox->addItem("TPicSim4.LST");
    ui->comboBox->addItem("TPicSim5.LST");
    ui->comboBox->addItem("TPicSim6.LST");
    ui->comboBox->addItem("TPicSim7.LST");
    ui->comboBox->addItem("TPicSim8.LST");
    ui->comboBox->addItem("TPicSim9.LST");
    ui->comboBox->addItem("TPicSim10.LST");
    ui->comboBox->addItem("TPicSim11.LST");
    ui->comboBox->addItem("TPicSim12.LST");
    ui->comboBox->addItem("TPicSim13.LST");
    ui->comboBox->addItem("TPicSim14.LST");
    ui->comboBox->addItem("TPicSim15.LST");
    ui->comboBox->addItem("TPicSim101.LST");
    ui->comboBox_2->addItem("0,032768 MHz");                //1
    ui->comboBox_2->addItem("0,100000 MHz");                //2
    ui->comboBox_2->addItem("0,455000 MHz");                //3
    ui->comboBox_2->addItem("0,500000 MHz");                //4
    ui->comboBox_2->addItem("1,000000 MHz");                //5
    ui->comboBox_2->addItem("2,000000 MHz");                //6
    ui->comboBox_2->addItem("2,457600 MHz");                //7
    ui->comboBox_2->addItem("3,000000 MHz");                //8
    ui->comboBox_2->addItem("3,276800 MHz");                //9
    ui->comboBox_2->addItem("3,680000 MHz");                //10
    ui->comboBox_2->addItem("3,686411 MHz");                //11
    ui->comboBox_2->addItem("4,000000 MHz", 1);    //12
    ui->comboBox_2->addItem("4,096000 MHz");                //13
    ui->comboBox_2->addItem("4,194304 MHz");                //14
    ui->comboBox_2->addItem("4,433619 MHz");                //15
    ui->comboBox_2->addItem("4,915200 MHz");                //16
    ui->comboBox_2->addItem("5,000000 MHz");                //17
    ui->comboBox_2->addItem("6,000000 MHz");                //18
    ui->comboBox_2->addItem("6,144000 MHz");                //19
    ui->comboBox_2->addItem("6,250000 MHz");                //20
    ui->comboBox_2->addItem("6,553600 MHz");                //21
    ui->comboBox_2->addItem("8,000000 MHz");                //22
    ui->comboBox_2->addItem("10,000000 MHz");               //23
    ui->comboBox_2->addItem("12,000000 MHz");               //24
    ui->comboBox_2->addItem("16,000000 MHz");               //25
    ui->comboBox_2->addItem("20,000000 MHz");               //26
    ui->comboBox_2->addItem("24,000000 MHz");               //27
    ui->comboBox_2->addItem("32,000000 MHz");               //28
    ui->comboBox_2->addItem("40,000000 MHz");               //29
    ui->comboBox_2->addItem("80,000000 MHz");               //30
    int index = ui->comboBox_2->findData(tablevalue);
    ui->comboBox_2->setCurrentIndex(index);
    pong();
    connect(ui->table, SIGNAL(cellClicked(int, int)), this, SLOT(breakpointclicked(int, int)));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT (runTimeMultiplier(int)));
}
PicSimGui::~PicSimGui() {
    delete ui;
}
std::string filepath;
void PicSimGui::on_pushButton_laden_clicked() {
    run = false;
    QTimer::singleShot(50, this, &PicSimGui::runTrue);
    QTimer::singleShot(100, this, &PicSimGui::laden);
}
void PicSimGui::on_pushButton_schnellLaden_clicked() {
    run = false;
    QTimer::singleShot(50, this, &PicSimGui::runTrue);
    QTimer::singleShot(100, this, &PicSimGui::fastladen);
}
void PicSimGui::on_actionLaden_triggered() {
    run = false;
    QTimer::singleShot(50, this, &PicSimGui::runTrue);
    QTimer::singleShot(100, this, &PicSimGui::laden);
}
void PicSimGui::on_actionClose_triggered() {
    QApplication::quit();
}
void PicSimGui::on_actionDoku_triggered() {
    QDesktopServices::openUrl(QUrl::fromLocalFile("../doku/doku.pdf"));
}
void PicSimGui::on_actionInfo_triggered() {
    Info *dialog = new Info(this);
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_start_clicked() {
    if (loaded) {
        if (manipulate) {
            if (!filepath.empty()) {
                pclold = positionArray[count];
                count = picSim1.run(filepath, count);
            }
            pong();
            manipulate = false;
            highlightcmds();
            if (run) {
                QTimer::singleShot(50, this, &PicSimGui::on_pushButton_start_clicked);
            }
        } else {
            if (!checkBreakpoint()) {
                if (!filepath.empty()) {
                    pclold = positionArray[count];
                    count = picSim1.run(filepath, count);
                }
                pong();
                highlightcmds();
                if (run) {
                    QTimer::singleShot(50, this, &PicSimGui::on_pushButton_start_clicked);
                }
            } else {
                manipulate = true;
            }
        }
    }
}
void PicSimGui::on_pushButton_next_clicked() {
    if (loaded) {
        if (!filepath.empty()) {
            pclold = positionArray[count];
            count = picSim1.run(filepath, count);
        }
        pong();
        highlightcmds();
    }
}
void PicSimGui::on_pushButton_stop_clicked() {
    run = false;
    QTimer::singleShot(50, this, &PicSimGui::runTrue);
}
void PicSimGui::on_pushButton_resetruntime_clicked() {
    picSim1.resetRuntime();
    pong();
}
void PicSimGui::runTrue() {
    run = true;
}
void PicSimGui::on_pushButton_reset_clicked() {
    run = false;
    QTimer::singleShot(50, this, &PicSimGui::runTrue);
    QTimer::singleShot(100, this, &PicSimGui::resetButton);
}

// Button 256 - 263 STATUS Register

void PicSimGui::on_pushButton_256_clicked() {
    QString test = ui->pushButton_256->text();
    if (test == "0") {
        ramGui->ramBitInputGui(3, 7, true);
        pong();
        ui->pushButton_256->setText(QString::fromStdString(ramGui->getBitGui(3, 7)));
    } else {
        ramGui->ramBitInputGui(3, 7, false);
        pong();
        ui->pushButton_256->setText(QString::fromStdString(ramGui->getBitGui(3, 7)));
    }
}
void PicSimGui::on_pushButton_257_clicked() {
    QString test = ui->pushButton_257->text();
    if (test == "0") {
        ramGui->ramBitInputGui(3, 6, true);
        pong();
        ui->pushButton_257->setText(QString::fromStdString(ramGui->getBitGui(3, 6)));
    } else {
        ramGui->ramBitInputGui(3, 6, false);
        pong();
        ui->pushButton_257->setText(QString::fromStdString(ramGui->getBitGui(3, 6)));
    }
}
void PicSimGui::on_pushButton_258_clicked() {
    QString test = ui->pushButton_258->text();
    if (test == "0") {
        ramGui->ramBitInputGui(3, 5, true);
        pong();
        ui->pushButton_258->setText(QString::fromStdString(ramGui->getBitGui(3, 5)));
    } else {
        ramGui->ramBitInputGui(3, 5, false);
        pong();
        ui->pushButton_258->setText(QString::fromStdString(ramGui->getBitGui(3, 5)));
    }
}
void PicSimGui::on_pushButton_259_clicked() {
    QString test = ui->pushButton_259->text();
    if (test == "0") {
        ramGui->ramBitInputGui(3, 4, true);
        pong();
        ui->pushButton_259->setText(QString::fromStdString(ramGui->getBitGui(3, 4)));
    } else {
        ramGui->ramBitInputGui(3, 4, false);
        pong();
        ui->pushButton_259->setText(QString::fromStdString(ramGui->getBitGui(3, 4)));
    }
}
void PicSimGui::on_pushButton_260_clicked() {
    QString test = ui->pushButton_260->text();
    if (test == "0") {
        ramGui->ramBitInputGui(3, 3, true);
        pong();
        ui->pushButton_260->setText(QString::fromStdString(ramGui->getBitGui(3, 3)));
    } else {
        ramGui->ramBitInputGui(3, 3, false);
        pong();
        ui->pushButton_260->setText(QString::fromStdString(ramGui->getBitGui(3, 3)));
    }
}
void PicSimGui::on_pushButton_261_clicked() {
    QString test = ui->pushButton_261->text();
    if (test == "0") {
        ramGui->ramBitInputGui(3, 2, true);
        pong();
        ui->pushButton_261->setText(QString::fromStdString(ramGui->getBitGui(3, 2)));
    } else {
        ramGui->ramBitInputGui(3, 2, false);
        pong();
        ui->pushButton_261->setText(QString::fromStdString(ramGui->getBitGui(3, 2)));
    }
}
void PicSimGui::on_pushButton_262_clicked() {
    QString test = ui->pushButton_262->text();
    if (test == "0") {
        ramGui->ramBitInputGui(3, 1, true);
        pong();
        ui->pushButton_262->setText(QString::fromStdString(ramGui->getBitGui(3, 1)));
    } else {
        ramGui->ramBitInputGui(3, 1, false);
        pong();
        ui->pushButton_262->setText(QString::fromStdString(ramGui->getBitGui(3, 1)));
    }
}
void PicSimGui::on_pushButton_263_clicked() {
    QString test = ui->pushButton_263->text();
    if (test == "0") {
        ramGui->ramBitInputGui(3, 0, true);
        pong();
        ui->pushButton_263->setText(QString::fromStdString(ramGui->getBitGui(3, 0)));
    } else {
        ramGui->ramBitInputGui(3, 0, false);
        pong();
        ui->pushButton_263->setText(QString::fromStdString(ramGui->getBitGui(3, 0)));
    }
}

// Button 264 - 271 Option Register

void PicSimGui::on_pushButton_264_clicked() {
    QString test = ui->pushButton_264->text();
    if (test == "0") {
        ramGui->ramBitInputGui(129, 7, true);
        pong();
        ui->pushButton_264->setText(QString::fromStdString(ramGui->getBitGui(129, 7)));
    } else {
        ramGui->ramBitInputGui(129, 7, false);
        pong();
        ui->pushButton_264->setText(QString::fromStdString(ramGui->getBitGui(129, 7)));
    }
}
void PicSimGui::on_pushButton_265_clicked() {
    QString test = ui->pushButton_265->text();
    if (test == "0") {
        ramGui->ramBitInputGui(129, 6, true);
        pong();
        ui->pushButton_265->setText(QString::fromStdString(ramGui->getBitGui(129, 6)));
    } else {
        ramGui->ramBitInputGui(129, 6, false);
        pong();
        ui->pushButton_265->setText(QString::fromStdString(ramGui->getBitGui(129, 6)));
    }
}
void PicSimGui::on_pushButton_266_clicked() {
    QString test = ui->pushButton_266->text();
    if (test == "0") {
        ramGui->ramBitInputGui(129, 5, true);
        pong();
        ui->pushButton_266->setText(QString::fromStdString(ramGui->getBitGui(129, 5)));
    } else {
        ramGui->ramBitInputGui(129, 5, false);
        pong();
        ui->pushButton_266->setText(QString::fromStdString(ramGui->getBitGui(129, 5)));
    }
}
void PicSimGui::on_pushButton_267_clicked() {
    QString test = ui->pushButton_267->text();
    if (test == "0") {
        ramGui->ramBitInputGui(129, 4, true);
        pong();
        ui->pushButton_267->setText(QString::fromStdString(ramGui->getBitGui(129, 4)));
    } else {
        ramGui->ramBitInputGui(129, 4, false);
        pong();
        ui->pushButton_267->setText(QString::fromStdString(ramGui->getBitGui(129, 4)));
    }
}
void PicSimGui::on_pushButton_268_clicked() {
    QString test = ui->pushButton_268->text();
    if (test == "0") {
        ramGui->ramBitInputGui(129, 3, true);
        pong();
        ui->pushButton_268->setText(QString::fromStdString(ramGui->getBitGui(129, 3)));
    } else {
        ramGui->ramBitInputGui(129, 3, false);
        pong();
        ui->pushButton_268->setText(QString::fromStdString(ramGui->getBitGui(129, 3)));
    }
}
void PicSimGui::on_pushButton_269_clicked() {
    QString test = ui->pushButton_269->text();
    if (test == "0") {
        ramGui->ramBitInputGui(129, 2, true);
        pong();
        ui->pushButton_269->setText(QString::fromStdString(ramGui->getBitGui(129, 2)));
    } else {
        ramGui->ramBitInputGui(129, 2, false);
        pong();
        ui->pushButton_269->setText(QString::fromStdString(ramGui->getBitGui(129, 2)));
    }
}
void PicSimGui::on_pushButton_270_clicked() {
    QString test = ui->pushButton_270->text();
    if (test == "0") {
        ramGui->ramBitInputGui(129, 1, true);
        pong();
        ui->pushButton_270->setText(QString::fromStdString(ramGui->getBitGui(129, 1)));
    } else {
        ramGui->ramBitInputGui(129, 1, false);
        pong();
        ui->pushButton_270->setText(QString::fromStdString(ramGui->getBitGui(129, 1)));
    }
}
void PicSimGui::on_pushButton_271_clicked() {
    QString test = ui->pushButton_271->text();
    if (test == "0") {
        ramGui->ramBitInputGui(129, 0, true);
        pong();
        ui->pushButton_271->setText(QString::fromStdString(ramGui->getBitGui(129, 0)));
    } else {
        ramGui->ramBitInputGui(129, 0, false);
        pong();
        ui->pushButton_271->setText(QString::fromStdString(ramGui->getBitGui(129, 0)));
    }
}

// Button 272 - 279 ITERRUPT Register

void PicSimGui::on_pushButton_272_clicked() {
    QString test = ui->pushButton_272->text();
    if (test == "0") {
        ramGui->ramBitInputGui(11, 7, true);
        pong();
        ui->pushButton_272->setText(QString::fromStdString(ramGui->getBitGui(11, 7)));
    } else {
        ramGui->ramBitInputGui(11, 7, false);
        pong();
        ui->pushButton_272->setText(QString::fromStdString(ramGui->getBitGui(11, 7)));
    }
}
void PicSimGui::on_pushButton_273_clicked() {
    QString test = ui->pushButton_273->text();
    if (test == "0") {
        ramGui->ramBitInputGui(11, 6, true);
        pong();
        ui->pushButton_273->setText(QString::fromStdString(ramGui->getBitGui(11, 6)));
    } else {
        ramGui->ramBitInputGui(11, 6, false);
        pong();
        ui->pushButton_273->setText(QString::fromStdString(ramGui->getBitGui(11, 6)));
    }
}
void PicSimGui::on_pushButton_274_clicked() {
    QString test = ui->pushButton_274->text();
    if (test == "0") {
        ramGui->ramBitInputGui(11, 5, true);
        pong();
        ui->pushButton_274->setText(QString::fromStdString(ramGui->getBitGui(11, 5)));
    } else {
        ramGui->ramBitInputGui(11, 5, false);
        pong();
        ui->pushButton_274->setText(QString::fromStdString(ramGui->getBitGui(11, 5)));
    }
}
void PicSimGui::on_pushButton_275_clicked() {
    QString test = ui->pushButton_275->text();
    if (test == "0") {
        ramGui->ramBitInputGui(11, 4, true);
        pong();
        ui->pushButton_275->setText(QString::fromStdString(ramGui->getBitGui(11, 4)));
    } else {
        ramGui->ramBitInputGui(11, 4, false);
        pong();
        ui->pushButton_275->setText(QString::fromStdString(ramGui->getBitGui(11, 4)));
    }
}
void PicSimGui::on_pushButton_276_clicked() {
    QString test = ui->pushButton_276->text();
    if (test == "0") {
        ramGui->ramBitInputGui(11, 3, true);
        pong();
        ui->pushButton_276->setText(QString::fromStdString(ramGui->getBitGui(11, 3)));
    } else {
        ramGui->ramBitInputGui(11, 3, false);
        pong();
        ui->pushButton_276->setText(QString::fromStdString(ramGui->getBitGui(11, 3)));
    }
}
void PicSimGui::on_pushButton_277_clicked() {
    QString test = ui->pushButton_277->text();
    if (test == "0") {
        ramGui->ramBitInputGui(11, 2, true);
        pong();
        ui->pushButton_277->setText(QString::fromStdString(ramGui->getBitGui(11, 2)));
    } else {
        ramGui->ramBitInputGui(11, 2, false);
        pong();
        ui->pushButton_277->setText(QString::fromStdString(ramGui->getBitGui(11, 2)));
    }
}
void PicSimGui::on_pushButton_278_clicked() {
    QString test = ui->pushButton_278->text();
    if (test == "0") {
        ramGui->ramBitInputGui(11, 1, true);
        pong();
        ui->pushButton_278->setText(QString::fromStdString(ramGui->getBitGui(11, 1)));
    } else {
        ramGui->ramBitInputGui(11, 1, false);
        pong();
        ui->pushButton_278->setText(QString::fromStdString(ramGui->getBitGui(11, 1)));
    }
}
void PicSimGui::on_pushButton_279_clicked() {
    QString test = ui->pushButton_279->text();
    if (test == "0") {
        ramGui->ramBitInputGui(11, 0, true);
        pong();
        ui->pushButton_279->setText(QString::fromStdString(ramGui->getBitGui(11, 0)));
    } else {
        ramGui->ramBitInputGui(11, 0, false);
        pong();
        ui->pushButton_279->setText(QString::fromStdString(ramGui->getBitGui(11, 0)));
    }
}

// Button 280 - 287 RA

void PicSimGui::on_pushButton_280_clicked() {
    QString test = ui->pushButton_280->text();
    if (test == "0") {
        ramGui->ramBitInputGui(5, 7, true);
        pong();
        ui->pushButton_280->setText(QString::fromStdString(ramGui->getBitGui(5, 7)));
    } else {
        ramGui->ramBitInputGui(5, 7, false);
        pong();
        ui->pushButton_280->setText(QString::fromStdString(ramGui->getBitGui(5, 7)));
    }
}
void PicSimGui::on_pushButton_281_clicked() {
    QString test = ui->pushButton_281->text();
    if (test == "0") {
        ramGui->ramBitInputGui(5, 6, true);
        pong();
        ui->pushButton_281->setText(QString::fromStdString(ramGui->getBitGui(5, 6)));
    } else {
        ramGui->ramBitInputGui(5, 6, false);
        pong();
        ui->pushButton_281->setText(QString::fromStdString(ramGui->getBitGui(5, 6)));
    }
}
void PicSimGui::on_pushButton_282_clicked() {
    QString test = ui->pushButton_282->text();
    if (test == "0") {
        ramGui->ramBitInputGui(5, 5, true);
        pong();
        ui->pushButton_282->setText(QString::fromStdString(ramGui->getBitGui(5, 5)));
    } else {
        ramGui->ramBitInputGui(5, 5, false);
        pong();
        ui->pushButton_282->setText(QString::fromStdString(ramGui->getBitGui(5, 5)));
    }
}
void PicSimGui::on_pushButton_283_clicked() {
    QString test = ui->pushButton_283->text();
    if (test == "0") {
        ramGui->ramBitInputGui(5, 4, true);
        pong();
        ui->pushButton_283->setText(QString::fromStdString(ramGui->getBitGui(5, 4)));
    } else {
        ramGui->ramBitInputGui(5, 4, false);
        pong();
        ui->pushButton_283->setText(QString::fromStdString(ramGui->getBitGui(5, 4)));
    }
}
void PicSimGui::on_pushButton_284_clicked() {
    QString test = ui->pushButton_284->text();
    if (test == "0") {
        ramGui->ramBitInputGui(5, 3, true);
        pong();
        ui->pushButton_284->setText(QString::fromStdString(ramGui->getBitGui(5, 3)));
    } else {
        ramGui->ramBitInputGui(5, 3, false);
        pong();
        ui->pushButton_284->setText(QString::fromStdString(ramGui->getBitGui(5, 3)));
    }
}
void PicSimGui::on_pushButton_285_clicked() {
    QString test = ui->pushButton_285->text();
    if (test == "0") {
        ramGui->ramBitInputGui(5, 2, true);
        pong();
        ui->pushButton_285->setText(QString::fromStdString(ramGui->getBitGui(5, 2)));
    } else {
        ramGui->ramBitInputGui(5, 2, false);
        pong();
        ui->pushButton_285->setText(QString::fromStdString(ramGui->getBitGui(5, 2)));
    }
}
void PicSimGui::on_pushButton_286_clicked() {
    QString test = ui->pushButton_286->text();
    if (test == "0") {
        ramGui->ramBitInputGui(5, 1, true);
        pong();
        ui->pushButton_286->setText(QString::fromStdString(ramGui->getBitGui(5, 1)));
    } else {
        ramGui->ramBitInputGui(5, 1, false);
        pong();
        ui->pushButton_286->setText(QString::fromStdString(ramGui->getBitGui(5, 1)));
    }
}
void PicSimGui::on_pushButton_287_clicked() {
    QString test = ui->pushButton_287->text();
    if (test == "0") {
        ramGui->ramBitInputGui(5, 0, true);
        pong();
        ui->pushButton_287->setText(QString::fromStdString(ramGui->getBitGui(5, 0)));
    } else {
        ramGui->ramBitInputGui(5, 0, false);
        pong();
        ui->pushButton_287->setText(QString::fromStdString(ramGui->getBitGui(5, 0)));
    }
}

// Button 288 - 295 RB

void PicSimGui::on_pushButton_288_clicked() {
    QString test = ui->pushButton_288->text();
    if (test == "0") {
        ramGui->ramBitInputGui(6, 7, true);
        pong();
        ui->pushButton_288->setText(QString::fromStdString(ramGui->getBitGui(6, 7)));
    } else {
        ramGui->ramBitInputGui(6, 7, false);
        pong();
        ui->pushButton_288->setText(QString::fromStdString(ramGui->getBitGui(6, 7)));
    }
}
void PicSimGui::on_pushButton_289_clicked() {
    QString test = ui->pushButton_289->text();
    if (test == "0") {
        ramGui->ramBitInputGui(6, 6, true);
        pong();
        ui->pushButton_289->setText(QString::fromStdString(ramGui->getBitGui(6, 6)));
    } else {
        ramGui->ramBitInputGui(6, 6, false);
        pong();
        ui->pushButton_289->setText(QString::fromStdString(ramGui->getBitGui(6, 6)));
    }
}
void PicSimGui::on_pushButton_290_clicked() {
    QString test = ui->pushButton_290->text();
    if (test == "0") {
        ramGui->ramBitInputGui(6, 5, true);
        pong();
        ui->pushButton_290->setText(QString::fromStdString(ramGui->getBitGui(6, 5)));
    } else {
        ramGui->ramBitInputGui(6, 5, false);
        pong();
        ui->pushButton_290->setText(QString::fromStdString(ramGui->getBitGui(6, 5)));
    }
}
void PicSimGui::on_pushButton_291_clicked() {
    QString test = ui->pushButton_291->text();
    if (test == "0") {
        ramGui->ramBitInputGui(6, 4, true);
        pong();
        ui->pushButton_291->setText(QString::fromStdString(ramGui->getBitGui(6, 4)));
    } else {
        ramGui->ramBitInputGui(6, 4, false);
        pong();
        ui->pushButton_291->setText(QString::fromStdString(ramGui->getBitGui(6, 4)));
    }
}
void PicSimGui::on_pushButton_292_clicked() {
    QString test = ui->pushButton_292->text();
    if (test == "0") {
        ramGui->ramBitInputGui(6, 3, true);
        pong();
        ui->pushButton_292->setText(QString::fromStdString(ramGui->getBitGui(6, 3)));
    } else {
        ramGui->ramBitInputGui(6, 3, false);
        pong();
        ui->pushButton_292->setText(QString::fromStdString(ramGui->getBitGui(6, 3)));
    }
}
void PicSimGui::on_pushButton_293_clicked() {
    QString test = ui->pushButton_293->text();
    if (test == "0") {
        ramGui->ramBitInputGui(6, 2, true);
        pong();
        ui->pushButton_293->setText(QString::fromStdString(ramGui->getBitGui(6, 2)));
    } else {
        ramGui->ramBitInputGui(6, 2, false);
        pong();
        ui->pushButton_293->setText(QString::fromStdString(ramGui->getBitGui(6, 2)));
    }
}
void PicSimGui::on_pushButton_294_clicked() {
    QString test = ui->pushButton_294->text();
    if (test == "0") {
        ramGui->ramBitInputGui(6, 1, true);
        pong();
        ui->pushButton_294->setText(QString::fromStdString(ramGui->getBitGui(6, 1)));
    } else {
        ramGui->ramBitInputGui(6, 1, false);
        pong();
        ui->pushButton_294->setText(QString::fromStdString(ramGui->getBitGui(6, 1)));
    }
}
void PicSimGui::on_pushButton_295_clicked() {
    QString test = ui->pushButton_295->text();
    if (test == "0") {
        ramGui->ramBitInputGui(6, 0, true);
        pong();
        ui->pushButton_295->setText(QString::fromStdString(ramGui->getBitGui(6, 0)));
    } else {
        ramGui->ramBitInputGui(6, 0, false);
        pong();
        ui->pushButton_295->setText(QString::fromStdString(ramGui->getBitGui(6, 0)));
    }
}
void PicSimGui::on_pushButton_296_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        picDataGui->setWreg(std::stoi(helper, 0, 16));
        pong();
    });
 window(dialog);
}
void PicSimGui::on_pushButton_297_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 4);
        pong();
    });
 window(dialog);
}
void PicSimGui::on_pushButton_298_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 2);
        pong();
    });
 window(dialog);
}
void PicSimGui::on_pushButton_299_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 10);
        pong();
    });
 window(dialog);
}
void PicSimGui::on_pushButton_300_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 3);
        pong();
    });
 window(dialog);
}
void PicSimGui::on_pushButton_301_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 129);
        pong();
    });
 window(dialog);
}
void PicSimGui::on_pushButton_302_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 11);
        pong();
    });
 window(dialog);
}
void PicSimGui::on_pushButton_test_clicked() {
    ui->table->setRowCount(0);
    resetload();
    picSim1.reset();
    picSim1.init(true);
    pong();
}
void PicSimGui::highlightcmds() {
    int line = positionArray[count];
    if (pclold != 0) {
        ui->table->item(pclold, 1)->setForeground(Qt::black);
        ui->table->item(pclold, 1)->setBackground(Qt::white);
        ui->table->scrollToItem(ui->table->item(line, 1), QAbstractItemView::PositionAtCenter);
    }
    ui->table->item(line, 1)->setForeground(Qt::white);
    ui->table->item(line, 1)->setBackground(Qt::blue);
    ui->table->scrollToItem(ui->table->item(line, 1), QAbstractItemView::PositionAtCenter);
}
void PicSimGui::pong() {
    std::string hexString;
    std::string statusReg;
    std::string optionReg;
    std::string interruptReg;
    std::string RA;
    std::string RB;
    std::string TRISA;
    std::string TRISB;
    std::string PC;
    std::string PSA;
    std::string CYCLES;
    std::string RUNTIME;

    //RAM
    for (int i = 0; i < 256; i++) {
        hexString = intToHexString(picSim1.ping(i));
        std::transform(hexString.begin(), hexString.end(), hexString.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        utility fillUp(hexString, 2);
        hexString = fillUp.fillup();
        QString qHexToString = QString::fromStdString(hexString);
        std::string buttonName = "pushButton_" + std::to_string(i);
        QString qString = QString::fromStdString(buttonName);
        QPushButton *button = ui->centralwidget->findChild<QPushButton *>(qString);
        button->setText(qHexToString);
    }
    //STATUS Register
    int j = 7;
    for (int i = 256; i < 264; i++) {
        statusReg = ramGui->getBitGui(3, j);
        QString qstatusReg = QString::fromStdString(statusReg);
        std::string buttonName = "pushButton_" + std::to_string(i);
        QString qString = QString::fromStdString(buttonName);
        QPushButton *button = ui->centralwidget->findChild<QPushButton *>(qString);
        button->setText(qstatusReg);
        j--;
    }

    //OPTION Register
    int k = 7;
    for (int i = 264; i < 272; i++) {
        optionReg = ramGui->getBitGui(129, k);
        QString qoptionReg = QString::fromStdString(optionReg);
        std::string buttonName = "pushButton_" + std::to_string(i);
        QString qString = QString::fromStdString(buttonName);
        QPushButton *button = ui->centralwidget->findChild<QPushButton *>(qString);
        button->setText(qoptionReg);
        k--;
    }

    //INTERRUPT Register
    int l = 7;
    for (int i = 272; i < 280; i++) {
        interruptReg = ramGui->getBitGui(11, l);
        QString qinterruptReg = QString::fromStdString(interruptReg);
        std::string buttonName = "pushButton_" + std::to_string(i);
        QString qString = QString::fromStdString(buttonName);
        QPushButton *button = ui->centralwidget->findChild<QPushButton *>(qString);
        button->setText(qinterruptReg);
        l--;
    }

    //RA
    int m = 7;
    for (int i = 280; i < 288; i++) {
        RA = ramGui->getBitGui(5, m);
        QString qRA = QString::fromStdString(RA);
        std::string buttonName = "pushButton_" + std::to_string(i);
        QString qString = QString::fromStdString(buttonName);
        QPushButton *button = ui->centralwidget->findChild<QPushButton *>(qString);
        button->setText(qRA);
        m--;
    }

    //RB
    int n = 7;
    for (int i = 288; i < 296; i++) {
        RB = ramGui->getBitGui(6, n);
        QString qRB = QString::fromStdString(RB);
        std::string buttonName = "pushButton_" + std::to_string(i);
        QString qString = QString::fromStdString(buttonName);
        QPushButton *button = ui->centralwidget->findChild<QPushButton *>(qString);
        button->setText(qRB);
        n--;
    }

    //TRISA
    int o = 7;
    for (int i = 76; i < 84; i++) {
        TRISA = ramGui->getBitGui(133, o);
        if (TRISA == "0") {
            TRISA = "o";
        } else {
            TRISA = "i";
        }
        QString qTRISA = QString::fromStdString(TRISA);
        std::string buttonName = "label_" + std::to_string(i);
        QString qString = QString::fromStdString(buttonName);
        QLabel *button = ui->centralwidget->findChild<QLabel *>(qString);
        button->setText(qTRISA);
        o--;
    }

    //TRISB
    int p = 7;
    for (int i = 95; i < 103; i++) {
        TRISB = ramGui->getBitGui(134, p);
        if (TRISB == "0") {
            TRISB = "o";
        } else {
            TRISB = "i";
        }
        QString qTRISB = QString::fromStdString(TRISB);
        std::string buttonName = "label_" + std::to_string(i);
        QString qString = QString::fromStdString(buttonName);
        QLabel *button = ui->centralwidget->findChild<QLabel *>(qString);
        button->setText(qTRISB);
        p--;
    }

    //W-Reg Button
    for (int i = 1; i < 2; i++) {
        hexString = intToHexString(picDataGui->getWreg().to_ulong());
        std::transform(hexString.begin(), hexString.end(), hexString.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        utility fillUp(hexString, 2);
        hexString = fillUp.fillup();
        QString qHexToString = QString::fromStdString(hexString);
        ui->pushButton_296->setText(qHexToString);
    }

    //FSR Button
    for (int i = 4; i < 5; i++) {
        hexString = intToHexString(picSim1.ping(i));
        std::transform(hexString.begin(), hexString.end(), hexString.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        utility fillUp(hexString, 2);
        hexString = fillUp.fillup();
        QString qHexToString = QString::fromStdString(hexString);
        ui->pushButton_297->setText(qHexToString);
    }

    //PCL Button
    for (int i = 2; i < 3; i++) {
        hexString = intToHexString(picSim1.ping(i));
        std::transform(hexString.begin(), hexString.end(), hexString.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        utility fillUp(hexString, 2);
        hexString = fillUp.fillup();
        QString qHexToString = QString::fromStdString(hexString);
        ui->pushButton_298->setText(qHexToString);
    }

    //PCLATH Button
    for (int i = 10; i < 11; i++) {
        hexString = intToHexString(picSim1.ping(i));
        std::transform(hexString.begin(), hexString.end(), hexString.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        utility fillUp(hexString, 2);
        hexString = fillUp.fillup();
        QString qHexToString = QString::fromStdString(hexString);
        ui->pushButton_299->setText(qHexToString);
    }

    //STATUS Button
    for (int i = 3; i < 4; i++) {
        hexString = intToHexString(picSim1.ping(i));
        std::transform(hexString.begin(), hexString.end(), hexString.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        utility fillUp(hexString, 2);
        hexString = fillUp.fillup();
        QString qHexToString = QString::fromStdString(hexString);
        ui->pushButton_300->setText(qHexToString);
    }

    //OPTION Button
    for (int i = 129; i < 130; i++) {
        hexString = intToHexString(picSim1.ping(i));
        std::transform(hexString.begin(), hexString.end(), hexString.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        utility fillUp(hexString, 2);
        hexString = fillUp.fillup();
        QString qHexToString = QString::fromStdString(hexString);
        ui->pushButton_301->setText(qHexToString);
    }

    //INTCON Button
    for (int i = 11; i < 12; i++) {
        hexString = intToHexString(picSim1.ping(i));
        std::transform(hexString.begin(), hexString.end(), hexString.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        utility fillUp(hexString, 2);
        hexString = fillUp.fillup();
        QString qHexToString = QString::fromStdString(hexString);
        ui->pushButton_302->setText(qHexToString);
    }

    //Stack
    QVector<QLabel*> labels;
    labels.append(ui->label_138);
    labels.append(ui->label_137);
    labels.append(ui->label_136);
    labels.append(ui->label_135);
    labels.append(ui->label_134);
    labels.append(ui->label_133);
    labels.append(ui->label_132);
    labels.append(ui->label_131);
    for(int i=0; i<labels.size(); i++){
        hexString = customStackGui->getstack(i).to_string();
        if (hexString == "0000000000000") {
            hexString = "-";
        }
        labels[i]->setText(QString::fromStdString(hexString));
    }

    //PSA Label
    for (int i = 1; i < 2; i++) {
        PSA = std::to_string(picSim1.getPSA());
        QString qPSA = QString::fromStdString(PSA);
        ui->label_114->setText(qPSA);
    }

    //Cycles Label
    for (int i = 1; i < 2; i++) {
        CYCLES = std::to_string(picDataGui->getCycle());
        QString qCYCLES = QString::fromStdString(CYCLES);
        ui->label_115->setText(qCYCLES);
    }

    //Laufzeit Label
    for (int i = 1; i < 2; i++) {
        QString qRUNTIME = QString::number(picDataGui->getRuntime() / 1.0, 'f', 2);
        ui->label_123->setText(qRUNTIME);
    }

    //Mult Label
    for (int i = 1; i < 2; i++) {
        QString qMULT = QString::number(picDataGui->getMultiplier() / 1.0, 'f', 3);
        ui->label_121->setText(qMULT);
    }

    //PC Label
    for (int i = 1; i < 2; i++) {
        hexString = intToHexString(count);
        std::transform(hexString.begin(), hexString.end(), hexString.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        utility fillUp(hexString, 4);
        hexString = fillUp.fillup();
        QString qHexToString = QString::fromStdString(hexString);
        ui->label_113->setText(qHexToString);
    }
}
std::string PicSimGui::intToHexString(int i) {
    std::stringstream stream;
    stream << std::hex << i;
    //std::string result = stream.str();
    return stream.str();
}
void PicSimGui::breakpointclicked(int row, int column) {
    ui->table->hide();
    if (carray[row]) {
        if (ui->table->item(row, 0)->text() == QString::fromUtf8("🔴")) {
            ui->table->item(row, 0)->setText("");
            breakarray[pcarray[row]] = false;
        } else {
            ui->table->item(row, 0)->setText("🔴");
            breakarray[pcarray[row]] = true;
        }
    }
    ui->table->show();
}
bool PicSimGui::checkBreakpoint() {
    if (breakarray[count]) {
        return true;
    } else {
        return false;
    }
}
void PicSimGui::runTimeMultiplier(int index) {
    switch (index) {
        case 0:
            picDataGui->setMultiplier(122.070); // 0.032
            pong();
            break;
        case 1:
            picDataGui->setMultiplier(40.000); // 0.100
            pong();
            break;
        case 2:
            picDataGui->setMultiplier(8.791); // 0.455
            pong();
            break;
        case 3:
            picDataGui->setMultiplier(8.000); // 0.5
            pong();
            break;
        case 4:
            picDataGui->setMultiplier(4.000); // 1.00
            pong();
            break;
        case 5:
            picDataGui->setMultiplier(2.000); // 2.00
            pong();
            break;
        case 6:
            picDataGui->setMultiplier(1.628); // 2.457
            pong();
            break;
        case 7:
            picDataGui->setMultiplier(1.333); // 3.00
            pong();
            break;
        case 8:
            picDataGui->setMultiplier(1.221); // 3.276
            pong();
            break;
        case 9:
            picDataGui->setMultiplier(1.087); // 3.68
            pong();
            break;
        case 10:
            picDataGui->setMultiplier(1.085); // 3.686
            pong();
            break;
        case 11:
            picDataGui->setMultiplier(1.000); // 4.00
            pong();
            break;
        case 12:
            picDataGui->setMultiplier(0.977);
            pong();
            break;
        case 13:
            picDataGui->setMultiplier(0.954);
            pong();
            break;
        case 14:
            picDataGui->setMultiplier(0.902);
            pong();
            break;
        case 15:
            picDataGui->setMultiplier(0.814);
            pong();
            break;
        case 16:
            picDataGui->setMultiplier(0.800);
            pong();
            break;
        case 17:
            picDataGui->setMultiplier(0.667);
            pong();
            break;
        case 18:
            picDataGui->setMultiplier(0.651);
            pong();
            break;
        case 19:
            picDataGui->setMultiplier(0.640);
            pong();
            break;
        case 20:
            picDataGui->setMultiplier(0.610);
            pong();
            break;
        case 21:
            picDataGui->setMultiplier(0.500);
            pong();
            break;
        case 22:
            picDataGui->setMultiplier(0.400);
            pong();
            break;
        case 23:
            picDataGui->setMultiplier(0.333);
            pong();
            break;
        case 24:
            picDataGui->setMultiplier(0.250);
            pong();
            break;
        case 25:
            picDataGui->setMultiplier(0.200);
            pong();
            break;
        case 26:
            picDataGui->setMultiplier(0.167);
            pong();
            break;
        case 27:
            picDataGui->setMultiplier(0.125);
            pong();
            break;
        case 28:
            picDataGui->setMultiplier(0.100);
            pong();
            break;
        case 29:
            picDataGui->setMultiplier(0.050);
            pong();
            break;
        default:
            std::cout << "Wrong Input -> Default Value";
            picDataGui->setMultiplier(1.000); // 4.00
            pong();
            break;
    }
}
void PicSimGui::resetload() {
    count = 0;
    pclold = 0;
    tablevalue = 1;
    loaded = false;
    manipulate = false;
    run = true;
    carray.fill(false);
    breakarray.fill(false);
    pcarray.fill(0);
    positionArray.fill(0);
}
void PicSimGui::resetButton() {
    if (loaded) {
        customStackGui->clearStack();
        pclold = positionArray[ramGui->getRam(2).to_ulong()];
        ui->table->item(pclold - 1, 1)->setForeground(Qt::black);
        ui->table->item(pclold - 1, 1)->setBackground(Qt::white);
        count = 0;
        //run = true;
        picSim1.init(false); // other reset
        highlightcmds();
        pong();
    }
}
void PicSimGui::laden() {
    QFile file(QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("LST Files (*.LST)")));
    if (file.size() == 0) {
    } else {
        resetload();
        picSim1.reset();
        picSim1.init(false);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QDir d = QFileInfo(file).absoluteFilePath();
        QString absolute = d.absolutePath();
        filepath = absolute.toStdString();
        QTextStream stream(&file);
        std::ifstream input(filepath);
        lines = std::count(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>(), '\n');
        ui->table->setColumnCount(2);
        ui->table->setRowCount(lines);
        std::string line;
        std::ifstream file1(filepath);
        int i = 0;
        int j = 0;
        while (std::getline(file1, line)) {
            QTableWidgetItem *itemx = new QTableWidgetItem;
            itemx->setText(QString::fromStdString(line));
            ui->table->setItem(i, 1, itemx);
            ui->table->setRowHeight(i, 25);
            QTableWidgetItem *itemy = new QTableWidgetItem;
            itemy->setText("");
            ui->table->setItem(i, 0, itemy);
            i++;
            if (isspace(line.at(0))) {
                j++;
                continue;
            } else {
                positionArray[stoi(line.substr(0, 4), 0, 16)] = j;
                pcarray[j] = stoi(line.substr(0, 4), 0, 16);
                carray[j] = true;
                j++;
            }
        }
        highlightcmds();
        pong();
        loaded = true;
        int start = positionArray[count];
        ui->table->scrollToItem(ui->table->item(start, 1), QAbstractItemView::PositionAtCenter);
    }
}
void PicSimGui::fastladen() {
    QFile file("../LST/" + ui->comboBox->currentText());
    resetload();
    picSim1.reset();
    picSim1.init(false);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QDir d = QFileInfo(file).absoluteFilePath();
    QString absolute = d.absolutePath();
    filepath = absolute.toStdString();
    QTextStream stream(&file);
    std::ifstream input(filepath);
    lines = std::count(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>(), '\n');
    ui->table->setColumnCount(2);
    ui->table->setRowCount(lines);
    std::string line;
    std::ifstream file1(filepath);
    int i = 0;
    int j = 0;
    while (std::getline(file1, line)) {
        QTableWidgetItem *itemx = new QTableWidgetItem;
        itemx->setText(QString::fromStdString(line));
        ui->table->setItem(i, 1, itemx);
        ui->table->setRowHeight(i, 25);
        QTableWidgetItem *itemy = new QTableWidgetItem;
        itemy->setText("");
        ui->table->setItem(i, 0, itemy);
        i++;
        if (isspace(line.at(0))) {
            j++;
            continue;
        } else {
            positionArray[stoi(line.substr(0, 4), 0, 16)] = j;
            pcarray[j] = stoi(line.substr(0, 4), 0, 16);
            carray[j] = true;
            j++;
        }
    }
    highlightcmds();
    pong();
    loaded = true;
    int start = positionArray[count];
    ui->table->scrollToItem(ui->table->item(start, 1), QAbstractItemView::PositionAtCenter);
}

void PicSimGui::window(InfoDialog *dialog){
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void PicSimGui::ramButtons(int button){

    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, button);
        pong();
    });
    window(dialog);
}

