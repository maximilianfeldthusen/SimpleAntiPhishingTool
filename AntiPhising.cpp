#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QUrl>
#include <QDebug>

class AntiPhishingTool {
public:
    AntiPhishingTool(const QString& phishingListFile) {
        loadPhishingList(phishingListFile);
    }

    bool isPhishingUrl(const QString& url) {
        QUrl qUrl(url);
        QString host = qUrl.host();
        return phishingList.contains(host);
    }

private:
    QStringList phishingList;

    void loadPhishingList(const QString& fileName) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Could not open phishing list file.";
            return;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                phishingList.append(line);
            }
        }
        file.close();
    }
};

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    AntiPhishingTool tool("phishing_sites.txt");

    QString testUrl = "http://example-phishing.com";
    if (tool.isPhishingUrl(testUrl)) {
        qDebug() << testUrl << "is a phishing site!";
    } else {
        qDebug() << testUrl << "is safe.";
    }

    return a.exec();
}


