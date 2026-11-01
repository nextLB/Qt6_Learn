#include "theme.h"

QString buildGlobalQss() {
    return QString(R"(
QMainWindow, QWidget {
    background: %1;
    color: %2;
    font-size: %3px;
}
QWidget#central {
    background: %1;
}
)")
        .arg(Theme::Bg)
        .arg(Theme::Text)
        .arg(Theme::FontSize::Body);
}