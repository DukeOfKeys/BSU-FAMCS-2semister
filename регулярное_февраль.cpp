#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <QQueue>
#include <QRegularExpression>
#include <QDebug>
using namespace std;
bool febuary(const QString &input)
{
    static QRegularExpression dateRe("^(0[1-9]|1[0-9]|2[0-8])\\.02\\.2025$");
    return dateRe.match(input).hasMatch();
}
using namespace std;
int main(int argc, char *argv[])
{
    // QString test1 = "01.05.2025";
    // qDebug() << febuary(test1) << '\n';
    QFile file("info.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Не удалось открыть файл:" << file.errorString();
        return 0;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        static QRegularExpression dateRe("(0[1-9]|1[0-9]|2[0-8])\\.02\\.2025");

        QRegularExpressionMatchIterator iterator = dateRe.globalMatch(line);

        while (iterator.hasNext())
        {
            QRegularExpressionMatch match = iterator.next();
            QString matchedDate = match.captured(0);

            qDebug() << matchedDate << '\n';
        }
    }

    return 0;
}
