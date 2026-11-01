# Qt6 Learn


## 环境配置与Demo的运行

以一台安装好Linux系统的电脑为例

最终目标：用 Qt 6.12.0 Desktop版构建Demo程序，在Debian图形桌面运行
Android端: 用 Qt 6.12.0 Android arm64-v8a + Android SDK/NDK 构建出 android-build-debug.apk，通过微信/ADB 安装到 OPPO 安卓手机并运行。



#### 阶段A 系统基础依赖

刚装好的 Debian13 里没有JDK、C++编译器、Ninja、系统cmake、需要先补齐

    sudo apt update
    sudo apt install -y openjdk-21-jdk libstdc++6 libncurses6
    sudo apt install -y build-essential ninja-build cmake
    sudo apt install -y libgl1-mesa-dev libglu1-mesa-dev libegl1-mesa-dev \
    libxkbcommon-dev libxkbcommon-x11-dev libxcb-cursor0 libvulkan-dev

设置JDK环境变量

    echo 'export JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64' >> ~/.bashrc
    echo 'export PATH=$JAVA_HOME/bin:$PATH' >> ~/.bashrc
    source ~/.bashrc
    java -version   # 应显示 21.x


可能遇到的问题一: openjdk-17-jdk 和 libncurses5 在 trixie 里已经不存在。改用 openjdk-21-jdk 和 libncurses6 即可。




### 阶段B 安装Qt6.12.0 (含Android组件)

Debian官方源没有可用于Android的Qt,必须用Qt官方在线安装器

下载安装器件 （以清华源为例，但可能清华源也不行，要用腾讯源之类的）

    wget https://mirrors.tuna.tsinghua.edu.cn/qt/official_releases/online_installers/qt-online-installer-linux-x64-online.run
    chmod +x qt-online-installer-linux-x64-online.run

用国内镜像启动安装器

    ./qt-online-installer-linux-x64-online.run --mirror https://mirrors.ustc.edu.cn/qtproject

如果中科大源报“未知异常”，换腾讯云

    ./qt-online-installer-linux-x64-online.run --mirror https://mirrors.cloud.tencent.com/qt/

必要时先清缓存

    rm -rf ~/.config/QtProject ~/.local/share/Qt

可能遇到的问题二: 安装器卡在“正在从远程资料档案中检索元信息”。原因是默认连海外服务器超时，用 --mirror 指定国内镜像即可。清华源有时限流，中科大/腾讯云更稳。


组件勾选

在组件选择页勾选下面这样之类的即可

    Qt 6.12.0 → Android ARM64-v8a（android_arm64_v8a）

    Qt 6.12.0 → Desktop gcc 64-bit（gcc_64，作为宿主编译工具）

    Developer and Designer Tools → Qt Creator（可选，命令行流程不强制）

安装完成后确认

    ls ~/Qt/6.12.0/android_arm64_v8a/bin/qt-cmake
    ls ~/Qt/6.12.0/gcc_64/bin/qmake

两条都有输出即可成功



### 阶段C 安装 Android SDK / NDK

下载 command-line tools

    mkdir -p ~/Android/Sdk/cmdline-tools
    wget https://dl.google.com/android/repository/commandlinetools-linux-11076708_latest.zip -O /tmp/cmdline-tools.zip
    unzip -q /tmp/cmdline-tools.zip -d ~/Android/Sdk/cmdline-tools
    mv ~/Android/Sdk/cmdline-tools/cmdline-tools ~/Android/Sdk/cmdline-tools/latest


用sdkmanager安装组件

    ~/Android/Sdk/cmdline-tools/latest/bin/sdkmanager --sdk_root=$HOME/Android/Sdk \
    "platform-tools" \
    "platforms;android-35" \
    "platforms;android-36" \
    "build-tools;35.0.0" \
    "ndk;27.2.12479018"


一路输入y接受许可 随后验证


    ls ~/Android/Sdk/ndk/27.2.12479018
    ls ~/Android/Sdk/platform-tools/adb
    ls ~/Android/Sdk/platforms   # 应看到 android-35 和 android-36


可能遇到的问题三: 最初只装了 android-35，后来 Gradle 报 androidx.core:core:1.17.0 要求 compileSdk 36，才补装 android-36。建议一开始就把 35 和 36 都装上。


### 阶段D 创建Demo 并桌面运行

这里一个简单的计时器应用来尝试

建项目文件

    mkdir -p ~/timer_app && cd ~/timer_app
    touch CMakeLists.txt main.cpp mainwindow.h mainwindow.cpp

CMakeLists.txt关键内容

    cmake_minimum_required(VERSION 3.16)
    project(TimerApp VERSION 1.0.0 LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)

    find_package(Qt6 REQUIRED COMPONENTS Widgets)
    qt_standard_project_setup()

    qt_add_executable(TimerApp
        main.cpp
        mainwindow.cpp
        mainwindow.h
    )

    target_link_libraries(TimerApp PRIVATE Qt6::Widgets)

    set_target_properties(TimerApp PROPERTIES
        ANDROID_MIN_SDK_VERSION 28
        QT_ANDROID_TARGET_SDK_VERSION 36
        QT_ANDROID_COMPILE_SDK_VERSION 36
    )

    qt_finalize_target(TimerApp)



main.cpp

    #include <QApplication>
    #include "mainwindow.h"

    int main(int argc, char *argv[]) {
        QApplication app(argc, argv);
        MainWindow w;
        w.show();
        return app.exec();
    }



mainwindow.h

    #ifndef MAINWINDOW_H
    #define MAINWINDOW_H

    #include <QMainWindow>
    #include <QTimer>
    #include <QLCDNumber>
    #include <QPushButton>

    class MainWindow : public QMainWindow {
        Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);

    private slots:
        void updateTime();
        void toggleTimer();

    private:
        QTimer *timer;
        QLCDNumber *lcdNumber;
        QPushButton *startButton;
        int seconds;
    };
    #endif



桌面构建

    cd ~/timer_app
    ~/Qt/6.12.0/gcc_64/bin/qt-cmake -S . -B build-desktop -GNinja
    cmake --build build-desktop
    ./build-desktop/TimerApp


可能遇到的问题四: No CMAKE_CXX_COMPILER could be found。原因是只装了 gcc 没装 g++，sudo apt install build-essential 解决。

可能遇到的问题五: Qt6Widgets could not be found because dependency Qt6Gui could not be found。缺 OpenGL/EGL 开发包，安装 libgl1-mesa-dev libglu1-mesa-dev libegl1-mesa-dev libxkbcommon-dev libxkbcommon-x11-dev libxcb-cursor0 libvulkan-dev 后重新配置。

可能遇到的问题六: cmake: 未找到命令。系统没装独立 cmake，sudo apt install cmake 解决；也可以用 ~/Qt/Tools/CMake/bin/cmake。


### 阶段E 构建 Android AOK

用Android版 qt-cmake 配置

    cd ~/timer_app
    ~/Qt/6.12.0/android_arm64_v8a/bin/qt-cmake \
    -DANDROID_SDK_ROOT=$HOME/Android/Sdk \
    -DANDROID_NDK_ROOT=$HOME/Android/Sdk/ndk/27.2.12479018 \
    -S . \
    -B build \
    -GNinja

构建 APK

    cmake --build build --target apk


可能遇到的问题七: ninja: no work to do.
最初 CMakeLists.txt 用的是 add_executable，不会触发 Android 部署流程。改成 qt_add_executable + qt_standard_project_setup() + qt_finalize_target()，并清掉 build 重新配置。

可能遇到的问题八: androiddeployqt 调用 Gradle wrapper 从 services.gradle.org 下载 gradle-9.5.1-bin.zip，国内极慢。手动从腾讯云镜像下载

    wget https://mirrors.cloud.tencent.com/gradle/gradle-9.5.1-bin.zip -O /tmp/gradle-9.5.1-bin.zip

找到wrapper缓存哈希目录

    find ~/.gradle/wrapper/dists/gradle-9.5.1-bin -maxdepth 1 -type d
    # 例如 .../gradle-9.5.1-bin/iq79hdu3mqx29lgffhp8bfmx

清掉 .park/.lck,把zip放进去

    cd ~/.gradle/wrapper/dists/gradle-9.5.1-bin/iq79hdu3mqx29lgffhp8bfmx/
    rm -f *.part *.lck
    cp /tmp/gradle-9.5.1-bin.zip .

可能遇到的问题九: checkDebugAarMetadata 失败，要求 compileSdk 36
androidx.core:core:1.17.0 要求 API 36。补装 platforms;android-36，并在 CMakeLists.txt 的 set_target_properties 里加

    QT_ANDROID_COMPILE_SDK_VERSION 36
    QT_ANDROID_TARGET_SDK_VERSION 36
    ANDROID_MIN_SDK_VERSION 28

清理build重新配置、重新构建




成功标志

    BUILD SUCCESSFUL in 13s
    Android package built successfully...
    -- File: /home/next/timer_app/build/android-build/build/outputs/apk/debug/android-build-debug.apk


### 阶段F  APK安装到手机测试

把 APK 拷到桌面或共享文件夹，发到手机微信。注意：

微信会把 .apk 改名成 .apk.1，需要在文件管理器里改回 .apk。

Android 11+ 无法直接访问 Android/data/com.tencent.mm/...。可以在微信里点开文件，找右上角“…”→“保存到手机”，存到 Download；或者用 adb pull 从微信目录拉出来。

安装时提示“禁止安装未知来源应用”，去设置里给“文件管理”或微信打开“安装未知应用”权限。


可能遇到的问题10: 微信接收 APK 后没有安装按钮、Android/data 目录看不到文件。原因是微信改后缀 + 分区存储限制。解决：改回 .apk 后缀；用“保存到手机”存到公共 Download；或 ADB pull。







## 本项目的基本运行

### Linux桌面级的编译运行测试

    (base) next@next:~/桌面/Qt6_Learn$ ~/Qt/6.12.0/gcc_64/bin/qt-cmake -S . -B build-desktop -GNinja

    (base) next@next:~/桌面/Qt6_Learn$ cmake --build build-desktop

    (base) next@next:~/桌面/Qt6_Learn$ ./build-desktop/Qt6Learn

### APK Android的实际安装测试



    (base) next@next:~/桌面/Qt6_Learn$ ~/Qt/6.12.0/android_arm64_v8a/bin/qt-cmake   -DANDROID_SDK_ROOT=$HOME/Android/Sdk   -DANDROID_NDK_ROOT=$HOME/Android/Sdk/ndk/27.2.12479018   -S .   -B build   -GNinja

    (base) next@next:~/桌面/Qt6_Learn$ cmake --build build --target apk



