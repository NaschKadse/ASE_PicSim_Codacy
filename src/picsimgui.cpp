#include "../header/picsimgui.h"
#include "../forms/ui_PicSimGui.h"

PicSimGui::PicSimGui(QWidget *parent) : QMainWindow(parent), ui(new Ui::PicSimGui) {
    ui->setupUi(this);
    picSim1.init(true); // Power on reset
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

// Button 000 - 015

void PicSimGui::on_pushButton_0_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 0);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_1_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 1);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_2_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 2);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_3_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 3);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_4_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 4);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_5_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 5);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_6_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 6);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_7_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 7);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_8_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 8);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_9_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 9);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_10_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 10);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_11_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 11);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_12_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 12);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_13_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 13);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_14_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 14);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_15_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 15);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 016 - 031

void PicSimGui::on_pushButton_16_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 16);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_17_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 17);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_18_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 18);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_19_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 19);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_20_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 20);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_21_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 21);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_22_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 22);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_23_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 23);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_24_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 24);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_25_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 25);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_26_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 26);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_27_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 27);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_28_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 28);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_29_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 29);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_30_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 30);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_31_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 31);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 032 - 047

void PicSimGui::on_pushButton_32_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 32);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_33_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 33);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_34_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 34);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_35_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 35);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_36_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 36);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_37_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 37);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_38_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 38);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_39_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 39);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_40_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 40);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_41_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 41);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_42_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 42);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_43_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 43);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_44_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 44);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_45_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 45);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_46_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 46);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_47_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 47);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 048 - 063

void PicSimGui::on_pushButton_48_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 48);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_49_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 49);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_50_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 50);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_51_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 51);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_52_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 52);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_53_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 53);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_54_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 54);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_55_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 55);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_56_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 56);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_57_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 57);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_58_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 58);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_59_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 59);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_60_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 60);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_61_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 61);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_62_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 62);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_63_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 63);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 064 - 079

void PicSimGui::on_pushButton_64_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 64);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_65_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 65);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_66_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 66);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_67_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 67);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_68_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 68);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_69_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 69);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_70_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 70);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_71_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 71);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_72_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 72);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_73_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 73);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_74_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 74);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_75_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 75);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_76_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 76);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_77_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 77);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_78_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 78);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_79_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 79);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 080 - 095

void PicSimGui::on_pushButton_80_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 80);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_81_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 81);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_82_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 82);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_83_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 83);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_84_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 84);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_85_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 85);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_86_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 86);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_87_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 87);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_88_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 88);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_89_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 89);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_90_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 90);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_91_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 91);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_92_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 92);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_93_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 93);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_94_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 94);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_95_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 95);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 096 - 111

void PicSimGui::on_pushButton_96_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 96);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_97_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 97);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_98_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 98);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_99_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 99);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_100_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 100);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_101_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 101);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_102_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 102);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_103_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 103);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_104_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 104);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_105_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 105);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_106_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 106);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_107_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 107);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_108_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 108);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_109_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 109);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_110_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 110);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_111_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 111);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 112 - 127

void PicSimGui::on_pushButton_112_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 112);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_113_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 113);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_114_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 114);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_115_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 115);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_116_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 116);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_117_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 117);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_118_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 118);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_119_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 119);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_120_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 120);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_121_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 121);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_122_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 122);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_123_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 123);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_124_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 124);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_125_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 125);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_126_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 126);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_127_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 127);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 128 - 143

void PicSimGui::on_pushButton_128_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 128);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_129_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 129);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_130_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 130);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_131_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 131);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_132_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 132);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_133_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 133);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_134_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 134);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_135_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 135);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_136_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 136);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_137_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 137);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_138_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 138);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_139_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 139);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_140_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 140);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_141_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 141);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_142_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 142);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_143_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 143);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 144 - 159

void PicSimGui::on_pushButton_144_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 144);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_145_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 145);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_146_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 146);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_147_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 147);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_148_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 148);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_149_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 149);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_150_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 150);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_151_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 151);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_152_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 152);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_153_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 153);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_154_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 154);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_155_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 155);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_156_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 156);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_157_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 157);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_158_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 158);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_159_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 159);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 160 - 175

void PicSimGui::on_pushButton_160_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 160);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_161_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 161);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_162_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 162);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_163_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 163);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_164_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 164);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_165_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 165);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_166_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 166);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_167_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 167);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_168_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 168);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_169_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 169);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_170_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 170);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_171_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 171);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_172_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 172);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_173_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 173);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_174_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 174);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_175_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 175);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 176 - 191

void PicSimGui::on_pushButton_176_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 176);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_177_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 177);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_178_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 178);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_179_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 179);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_180_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 180);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_181_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 181);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_182_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 182);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_183_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 183);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_184_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 184);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_185_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 185);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_186_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 186);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_187_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 187);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_188_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 188);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_189_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 189);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_190_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 190);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_191_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 191);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 192 - 207

void PicSimGui::on_pushButton_192_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 192);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_193_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 193);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_194_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 194);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_195_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 195);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_196_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 196);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_197_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 197);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_198_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 198);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_199_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 199);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_200_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 200);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_201_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 201);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_202_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 202);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_203_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 203);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_204_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 204);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_205_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 205);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_206_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 206);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_207_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 207);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 208 - 223

void PicSimGui::on_pushButton_208_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 208);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_209_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 209);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_210_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 210);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_211_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 211);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_212_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 212);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_213_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 213);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_214_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 214);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_215_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 215);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_216_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 216);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_217_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 217);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_218_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 218);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_219_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 219);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_220_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 220);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_221_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 221);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_222_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 222);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_223_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 223);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 224 - 239

void PicSimGui::on_pushButton_224_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 224);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_225_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 225);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_226_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 226);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_227_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 227);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_228_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 228);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_229_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 229);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_230_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 230);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_231_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 231);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_232_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 232);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_233_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 233);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_234_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 234);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_235_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 235);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_236_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 236);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_237_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 237);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_238_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 238);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_239_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 239);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

// Button 240 - 255

void PicSimGui::on_pushButton_240_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 240);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_241_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 241);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_242_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 242);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_243_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 243);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_244_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 244);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_245_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 245);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_246_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 246);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_247_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 247);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_248_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 248);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_249_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 249);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_250_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 250);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_251_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 251);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_252_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 252);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_253_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 253);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_254_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 254);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
void PicSimGui::on_pushButton_255_clicked() {
    InfoDialog *dialog = new InfoDialog(this);
    connect(dialog, &InfoDialog::accepted, [=]() {
        std::string helper;
        QString input = dialog->getPosition();
        helper = input.toStdString();
        ramGui->ramInput(helper, 255);
        pong();
    });
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
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
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
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
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
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
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
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
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
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
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
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
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
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
    dialog->show();
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowCloseButtonHint);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
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
    for (int i = 1; i < 2; i++) {
        hexString = customStackGui->getstack(0).to_string();
        if (hexString == "0000000000000") {
            hexString = "-";
        }
        QString qHexToString0 = QString::fromStdString(hexString);
        ui->label_138->setText(qHexToString0);
        hexString = customStackGui->getstack(1).to_string();
        if (hexString == "0000000000000") {
            hexString = "-";
        }
        QString qHexToString1 = QString::fromStdString(hexString);
        ui->label_137->setText(qHexToString1);
        hexString = customStackGui->getstack(2).to_string();
        if (hexString == "0000000000000") {
            hexString = "-";
        }
        QString qHexToString2 = QString::fromStdString(hexString);
        ui->label_136->setText(qHexToString2);
        hexString = customStackGui->getstack(3).to_string();
        if (hexString == "0000000000000") {
            hexString = "-";
        }
        QString qHexToString3 = QString::fromStdString(hexString);
        ui->label_135->setText(qHexToString3);
        hexString = customStackGui->getstack(4).to_string();
        if (hexString == "0000000000000") {
            hexString = "-";
        }
        QString qHexToString4 = QString::fromStdString(hexString);
        ui->label_134->setText(qHexToString4);
        hexString = customStackGui->getstack(5).to_string();
        if (hexString == "0000000000000") {
            hexString = "-";
        }
        QString qHexToString5 = QString::fromStdString(hexString);
        ui->label_133->setText(qHexToString5);
        hexString = customStackGui->getstack(6).to_string();
        if (hexString == "0000000000000") {
            hexString = "-";
        }
        QString qHexToString6 = QString::fromStdString(hexString);
        ui->label_132->setText(qHexToString6);
        hexString = customStackGui->getstack(7).to_string();
        if (hexString == "0000000000000") {
            hexString = "-";
        }
        QString qHexToString7 = QString::fromStdString(hexString);
        ui->label_131->setText(qHexToString7);
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
    std::string result = stream.str();
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