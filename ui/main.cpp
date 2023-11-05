#include <QApplication>

#include "SageDocsUi.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SageDocsUi SageDocsUi;
    SageDocsUi.init();

    return app.exec();
}
