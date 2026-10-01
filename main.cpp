#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include <QScreen>
int main(int argc, char *argv[])
{
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
    QApplication app(argc, argv);
    app.setStyle("Fusion");
    MainWindow window;
    window.show();
    const QStringList args = app.arguments();
    int i = args.indexOf("--screenshot");
    if (i >= 0 && i + 1 < args.size()) {
        const QString path = args.at(i + 1);
        QTimer::singleShot(1200, &window, [&window, path] { window.grab().save(path); });
    }
    return app.exec();
}
