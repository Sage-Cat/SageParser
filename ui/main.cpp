#include <QApplication>

#include "SageDocsUi.hpp"

int main(int argc, char const *argv[])
{
    QApplication app(argc, argv);

    SageDocsUi SageDocsUi;
    SageDocsUi.init();

    return app.exec();
}
