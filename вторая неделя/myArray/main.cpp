
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <iostream>

class Command{
public:
    virtual void exec() = 0;
    virtual ~Command() = default;
};

class sentenceWithoutHello : public Command{
private:
    QString sentence;
public:
    sentenceWithoutHello(const QString &_sentence) : sentence(_sentence) {};

    void getD(){
        qInfo() << sentence;
    };

    ~sentenceWithoutHello() = default;
    void exec() override {
        std::cout << 5;
        QStringList words = sentence.split(' ');
        QString excludeWord = "hello";
        QStringList resultWords;
        std::cout << 6;
        for(auto & word : words){
            if(word.toLower() != excludeWord){
                resultWords.append(word);
            }
        }
        std::cout << 7;
        qInfo() << "Result words:";
        for (auto &word : resultWords) {
            qInfo() << word;
        }
        std::cout <<8;
    }
};




#include <QApplication>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include <QtLogging>
#include <QtGlobal>

#include <iostream>
QtMessageHandler originalHandler = nullptr;

void customMessageHandlerToFile(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    static QFile logFile("log.txt");
    if (!logFile.isOpen()) {
        if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            qCritical() << "Failed to open log file:" << logFile.errorString();
            return;
        }
    }

    QTextStream stream(&logFile);
    stream.setEncoding(QStringConverter::Utf8);
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    QString message;
    switch (type) {
    case QtDebugMsg:
        message = QString("Debug: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtInfoMsg:
        message = QString("Info: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtWarningMsg:
        message = QString("Info: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtCriticalMsg:
        message = QString("Critical: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        break;
    case QtFatalMsg:
        message = QString("Fatal: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
        abort();
    }
    stream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << " " << message << '\n';
    logFile.flush();
    logFile.close();
    fprintf(stderr, "%s\n", message.toLocal8Bit().constData());
}






#include <QString>
#include <QTextStream>
#include <unordered_map>
#include <QDebug>
#include <iostream>
class findDoubleLetters : public Command{
private:
    QString word;
public:
    findDoubleLetters(const QString &_word) : word(_word) {};

    ~findDoubleLetters() = default;
    void exec() override {
        std::cout << 2;
        std::unordered_map<QChar, int> letters;
        for(QChar& letter : word){
            letters[letter.toLower()]++;
        }
        std::cout << 3;
        for(const auto &letter : letters){
            if(letter.second == 2){
                qInfo() << "Duplicate letter:" << letter.first;
            }
        }
    }
};

int main(int argc, char *argv[]){
    // setlocale(LC_ALL,"ru");
    originalHandler = qInstallMessageHandler(customMessageHandlerToFile);
    QApplication app(argc, argv);
    findDoubleLetters fdl("hello");
    QString sent("hello how are you?");
    sentenceWithoutHello swh(sent);
    std::cout << 1;
    fdl.exec();
    std::cout << 1;
    swh.getD();
    swh.exec();
    std::cout << 1;
    return 0;
}
