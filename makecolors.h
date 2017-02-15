#ifndef MAKECOLORS_H
#define MAKECOLORS_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDirIterator>
#include <QImage>
#include <QDebug>
#include <QMutex>
#include <QColor>
#include <QRgb>
#include <QDateTime>

class MakeColors : public QThread
{
    Q_OBJECT
public:
    explicit MakeColors(const QString nodesTxt, const QString colorsTxt, const QStringList searchPaths, QObject *parent);
    explicit MakeColors();
    ~MakeColors();
    void startProcess();
    void setFileNodesTxt(const QString &value);

    void setFileColorsTxt(const QString &value);

    void setTextureSearchDirectorys(const QStringList &value);

    enum LogLevel {
        NONE,
        VERBOSE,
        INFO,
        WARNING,
        ERROR
    };
    Q_ENUM(LogLevel)

    void setLogLevel(const LogLevel &value);

signals:
    void outputLog(QString message, int level);
    void progressChanged(int);
    void maxProgressChanged(int);

public slots:
    void stopProcess();

protected:
    void run();
private slots:
    QColor processImage(QString path);
    bool parseNodesTxt(QString nodesTxt);
    bool searchAndProgressTextures(const QString path);
private:
    bool abort;
    int numberOfNodes = 0;
    int numberOfColors = 0;
    QString fileNodesTxt;
    QString fileColorsTxt;
    QStringList textureSearchDirectorys;
    QStringList textureFileFilter;
    LogLevel logLevel = INFO;

    QHash<QString, QColor> requiredColors;
    QMap<QString, QString> nodeList;
    bool writeColorsTxt(const QString file);
    void output(QString message, LogLevel level = NONE);
    QMutex mutex;
};

#endif // MAKECOLORS_H