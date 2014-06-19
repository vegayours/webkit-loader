#include <QtWebKit>
#include <QFile>
#include "webloader.h"
#include <iostream>


std::ostream& operator<<(std::ostream& stream, const QWebPage& page) {
    return stream << "url: " << qPrintable(page.mainFrame()->url().toString())
           << "js enabled: " << page.settings()->testAttribute(QWebSettings::JavascriptEnabled);
}

WebLoader::WebLoader(QObject *parent) :
    QObject(parent)
{
    connect(&page, SIGNAL(loadFinished(bool)), this, SLOT(save(bool)));
    const QWebPage& p = page;
    connect(&page, &QWebPage::loadStarted, [&p] {
        std::cout << "load started for " << p << std::endl;
    });
    page.settings()->setAttribute(QWebSettings::AutoLoadImages, false);
    /*connect(&page, &QWebPage::loadProgress, [&p] (int progress){
        std::cout << "load progress " << progress << " for page " << p << std::endl;
    });*/
}

void WebLoader::load(const QUrl &url, const QString &fileName, bool enableJs)
{
    page.settings()->setAttribute(QWebSettings::JavascriptEnabled, enableJs);
    page.mainFrame()->load(url);
    this->fileName = fileName;
}

void WebLoader::save(bool success)
{
    if (!success) {
        std::cerr << "failed to load " << page << std::endl;
        emit finished();
    }
    else {
        std::cout << "load successful for page " << page << std::endl;
    }
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(page.mainFrame()->toPlainText().toUtf8());
    file.close();
    emit finished();
}
