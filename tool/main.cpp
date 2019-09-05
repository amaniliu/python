#include "settingDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SettingDialog window;
    window.show();

    return a.exec();
}
