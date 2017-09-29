#include "tocGenerator.hpp"

#include <QCoreApplication>
#include <QDebug>

#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        qCritical() << "Incorrect number of arguments!";
        ToCGenerator::printUsage();
    }

    ToCGenerator generator(argv[1]);
    return generator.exec();;
}

ToCGenerator::ToCGenerator(QString sourceFile)
    : source(sourceFile), toc(sourceFile.replace(".md", "_ToC.md")), sourceStream(&source), tocStream(&toc) {}

int ToCGenerator::exec() {
    if (!source.exists()) {
        qCritical() << "Source file doesn't exist.";
        printUsage();
        return -1;
    }

    if (toc.exists()) {
        qWarning() << "Toc file already exists. Overwrite? [y/n]";
        std::string str;
        getline(std::cin, str);
        if (str != "y") {
            return 0;
        }
    }

    if (!source.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Couldn't open source file. Make sure it is valid .md file.";
        printUsage();
        return -1;
    }

    if (!toc.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Couldn't open toc file. Make sure it is valid .md file.";
        printUsage();
        return -1;
    }


    QTextStream in(&source);
    while (!in.atEnd()) {
        processLine(in.readLine());
    }
    return 0;
}

void ToCGenerator::printUsage() {
    qDebug() << "Usage:";
    qDebug() << "tocGenerator source.md toc.md";
}

bool ToCGenerator::isMdFile(const QString& file) {
    return file.contains(".md");
}

void ToCGenerator::processLine(QString line) {
    line = line.trimmed();
    if (line[0] != '#')
        return;

    line.remove(0, 1);

    QString out;
    while (line[0] == '#') {
        out.append('\t');
        line.remove(0, 1);
    }

    line = line.trimmed();
    out.append("* [");
    out.append(line);
    out.append("](#");

    QString keyword = line.toLower().replace(' ', '-');
    if (keywords.contains(keyword)) {
        QString val = QString::fromStdString(std::to_string(keywords[keyword]));
        ++keywords[keyword];

        keyword.append("-" + val);
    } else {
        keywords.insert(keyword, 1);
    }

    out.append(keyword);
    out.append(")\n");

    tocStream << out;
}




