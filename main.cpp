#include "maindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDialog w;
    a.setStyleSheet("QDialog   {background-color: rgb(59,59,59);}"
                    "QMainWindow {background-color: rgb(59,59,59);}"
                    "QGroupBox {border-style: outset;"
                                "font: oblique 20pt Purisa;"
                                "background-color: rgb(31, 31, 31);"
                                "color: rgb(200, 200, 200);"
                                "border-width: 5px;"
                                "border-radius: 20px;"
                                "border-top-color: rgb(34, 215, 255);"
                                "border-left-color: rgb(34, 215, 255);"
                                "border-right-color: rgb(255, 148, 25);"
                                "border-bottom-color: rgb(255, 148, 25);}"
                    "QPushButton {border-style: outset;"
                                  "font: oblique 20pt Purisa;"
                                  "background-color: rgb(31, 31, 31);"
                                  "color: rgb(200, 200, 200);"
                                  "border-width: 5px;"
                                  "border-radius: 20px;"
                                  "border-top-color: rgb(34, 215, 255);"
                                  "border-left-color: rgb(34, 215, 255);"
                                  "border-right-color: rgb(255, 148, 25);"
                                  "border-bottom-color: rgb(255, 148, 25);}"
                    "QLineEdit {border-style: outset;"
                               "font: oblique 20pt Purisa;"
                                "background-color: rgb(31, 31, 31);"
                                "color: rgb(200, 200, 200);"
                                "border-width: 1px;"
                                "border-radius: 0px;"
                                "border-top-color: rgb(34, 215, 255);"
                                "border-left-color: rgb(34, 215, 255);"
                                "border-right-color: rgb(255, 148, 25);"
                                "border-bottom-color: rgb(255, 148, 25);}"
                     "QLabel {font: oblique 20pt Purisa;"
                            "background-color: rgb(31, 31, 31);"
                            "color: rgb(200, 200, 200);}");
    w.showMaximized();

    return a.exec();
}
