#include <QApplication>
#include "mainwindow.h"
void debugMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    QByteArray localMsg = msg.toLocal8Bit();
    fprintf(stderr, "Debug Message: %s\n", localMsg.constData());
}
int main(int argc, char *argv[]) {
    qInstallMessageHandler(debugMessageHandler);
    QApplication app(argc, argv);

    MainWindow window;
    window.resize(800, 600);
    window.show();

    return app.exec();
}
