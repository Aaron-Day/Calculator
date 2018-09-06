#include <iostream>
#include <QApplication>
#include "CalcDialog.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    CalcDialog dlg;
    dlg.show();

    return app.exec();
}

