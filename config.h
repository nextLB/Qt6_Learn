#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

// ============================================================
// 应用级常量：窗口尺寸、应用元信息等
// 规则：
//   - 与"视觉样式"无关的全局参数 → 放这里
//   - 颜色 / 字号 / 间距 / 圆角 → 放 theme.h
// ============================================================
namespace Config {

// ---------- 应用元信息 ----------
inline const QString AppName        = "Qt6Learn";
inline const QString AppDisplayName = "Qt6 学习";
inline const QString AppVersion     = "1.0.0";
inline const QString OrgName        = "next";

// ---------- 主窗口 ----------
// 与目标移动端竖屏比例对齐；桌面端方便预览
constexpr int WindowWidth  = 420;
constexpr int WindowHeight = 720;

} // namespace Config

#endif // CONFIG_H