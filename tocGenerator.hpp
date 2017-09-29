#ifndef TOCGENERATOR_H
#define TOCGENERATOR_H

#include <QString>
#include <QFile>
#include <QMap>
#include <QTextStream>

class ToCGenerator {
public:
    ToCGenerator(QString sourceFile);
    int exec();

    static void printUsage();
    bool isMdFile(const QString& file);
    void processLine(QString line);
private:
    QFile source;
    QFile toc;

    QMap<QString, int> keywords;

    QTextStream sourceStream;
    QTextStream tocStream;
};

#endif // TOCGENERATOR_H
