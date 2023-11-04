#include <QApplication>

#include "DocsParserUi.hpp"

int main(int argc, char const *argv[])
{
    QApplication app(argc, argv);

    DocsParserUi docsParserUi;
    docsParserUi.init();

    return app.exec();
}
