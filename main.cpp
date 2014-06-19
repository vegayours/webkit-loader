#include <QApplication>
#include "webloader.h"
#include <iostream>



int main(int argc, char *argv[])
{
    QUrl url = QUrl::fromUserInput(QString::fromUtf8(argv[1]));
    QString noJsFileName = QString::fromUtf8(argv[2]);
    QString jsFileName = QString::fromUtf8(argv[3]);
    QApplication a(argc, argv);
    WebLoader loader;
    bool executeJs = false;
    auto resultFn = [&] () {
        if (!executeJs) {
            executeJs = true;
            loader.load(url, jsFileName, executeJs);
        }
        else {
            QApplication::instance()->quit();
        }
    };

    QObject::connect(&loader, &WebLoader::finished, resultFn);
    loader.load(url, noJsFileName, executeJs);
    return a.exec();
}
