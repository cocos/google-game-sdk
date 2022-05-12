# Source Code

This project use google game sdk source code. Current dependency info:

- You can download from [github](https://android.googlesource.com/platform/frameworks/opt/gamesdk).
- **Branch**: android-games-sdk-release
- **CommitID**: 551ee6b30de541fabceb8424abfb3818b5037283

## How to use cloned code

- Copy 'GameActivity', 'GameController', 'GameTextInput' and 'src/extras' directories from cloned directories.
- First, modify cpp files and CMakeLists.txt, and then copy these files to the directory 'sources/Android-gamesdk' in the GIT [repository](https://github.com/cocos/cocos-engine-external.git)
- Modify onCreate function of GameActivity

    ``` Java
        String libname = "main";
        // following code is needed to be added
        if (null != getIntent().getStringExtra(META_DATA_LIB_NAME)) {
        libname = getIntent().getStringExtra(META_DATA_LIB_NAME);
        }
    ```

## How to Build

- Use gradle command. gradlew :lib-game-sdk::assembleRelease

## Where to copy classes.jar

- Copy classes.jar from build/intermediates/aar_main_jar/release
