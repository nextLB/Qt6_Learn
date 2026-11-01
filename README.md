# Qt6 Learn



    (base) next@next:~/桌面/Qt6_Learn$ ~/Qt/6.12.0/gcc_64/bin/qt-cmake -S . -B build-desktop -GNinja
    -- The CXX compiler identification is GNU 14.2.0
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
    -- Found Threads: TRUE
    -- Performing Test HAVE_STDATOMIC
    -- Performing Test HAVE_STDATOMIC - Success
    -- Found WrapAtomic: TRUE
    -- Found OpenGL: /usr/lib/x86_64-linux-gnu/libOpenGL.so
    -- Found WrapOpenGL: TRUE
    -- Found WrapVulkanHeaders: /usr/include
    -- Configuring done (0.8s)
    -- Generating done (0.1s)
    -- Build files have been written to: /home/next/桌面/Qt6_Learn/build-desktop
    (base) next@next:~/桌面/Qt6_Learn$ cmake --build build-desktop
    [4/4] Linking CXX executable StyleProbe
    (base) next@next:~/桌面/Qt6_Learn$ ./build-desktop/StyleProbe
    (base) next@next:~/桌面/Qt6_Learn$ 







    (base) next@next:~/桌面/Qt6_Learn$ ~/Qt/6.12.0/android_arm64_v8a/bin/qt-cmake   -DANDROID_SDK_ROOT=$HOME/Android/Sdk   -DANDROID_NDK_ROOT=$HOME/Android/Sdk/ndk/27.2.12479018   -S .   -B build   -GNinja

    (base) next@next:~/桌面/Qt6_Learn$ cmake --build build --target apk



