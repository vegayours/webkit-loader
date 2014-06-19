#ifndef WEBLOADER_H
#define WEBLOADER_H

#include <QObject>
#include <QtWebKitWidgets/QtWebKitWidgets>

class WebLoader : public QObject
{
    Q_OBJECT
public:
    explicit WebLoader(QObject *parent = 0);
    void load(const QUrl& url, const QString& fileName, bool enableJs = true);

signals:
    void finished();

private slots:
    void save(bool);
private:
    QString fileName;
    QWebPage page;
};

#endif // WEBLOADER_H
