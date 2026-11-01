#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QFont>

#include "config.h"
#include "theme.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setApplicationName(Config::AppName);
    app.setApplicationVersion(Config::AppVersion);
    app.setOrganizationName(Config::OrgName);

    // Fusion 是 QSS 支持最完整、跨平台表现最一致的 style
    QApplication::setStyle("Fusion");

    // 字体 fallback：优先等宽/几何，中文缺失时回落到 Noto CJK
    QFont font;
    font.setFamilies({"JetBrains Mono", "Noto Sans CJK SC", "Ubuntu", "sans-serif"});
    font.setPointSize(10);
    app.setFont(font);

    app.setStyleSheet(buildGlobalQss());

    QMainWindow w;
    w.setWindowTitle(Config::AppDisplayName);
    w.resize(Config::WindowWidth, Config::WindowHeight);

    auto *central = new QWidget(&w);
    central->setObjectName("central");
    w.setCentralWidget(central);

    w.show();
    return app.exec();
}