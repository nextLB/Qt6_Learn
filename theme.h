#ifndef THEME_H
#define THEME_H

#include <QString>

// ============================================================
// 设计令牌 · 科技霓虹（Theme D）
// 所有色值 / 字号 / 间距 / 圆角在此集中定义，严禁在业务代码里硬编码。
// 扩展流程：
//   1) 需要新令牌 → 在本命名空间加一项
//   2) 需要让令牌生效到控件 → 在 theme.cpp 的 QSS 里引用它
//   3) 换主题 → 只需整体替换本文件里的色值
// ============================================================
namespace Theme {

// ---------- 颜色 ----------
inline const QString Bg         = "#080B12";   // 全局底色
inline const QString Surface    = "#0D1420";   // 卡片表面
inline const QString SurfaceTop = "#101A28";   // 表面渐变起点
inline const QString SurfaceBot = "#0A0F18";   // 表面渐变终点
inline const QString Border     = "#2A3F5A";   // 描边
inline const QString Accent     = "#00E5FF";   // 主强调色（青）
inline const QString AccentAlt  = "#FF2E88";   // 次强调色（品红，备用）
inline const QString Text       = "#C8D6E5";   // 主文字
inline const QString TextMuted  = "#5A7A9A";   // 次文字

// ---------- 字号（px） ----------
namespace FontSize {
    constexpr int Display = 28;
    constexpr int Title   = 20;
    constexpr int Body    = 15;
    constexpr int Caption = 12;
}

// ---------- 间距（8pt 栅格） ----------
namespace Spacing {
    constexpr int XS  = 4;
    constexpr int S   = 8;
    constexpr int M   = 12;
    constexpr int L   = 16;
    constexpr int XL  = 24;
    constexpr int XXL = 32;
}

// ---------- 圆角（px） ----------
namespace Radius {
    constexpr int S = 8;
    constexpr int M = 12;
    constexpr int L = 16;
}

// ---------- 触控目标 ----------
constexpr int MinTouchTarget = 44;

} // namespace Theme

// 由设计令牌生成的全局 QSS（主题唯一入口）
QString buildGlobalQss();

#endif // THEME_H