# GameActivity

GameActivity is an Android `Activity` modeled on the API of `NativeActivity`, but with a few changes to make it a better starting point for game developers.

* It inherits from `androidx.appcompat.app.AppCompatActivity` - allowing you to use Jetpack components architecture (and still use some of the newer platform features on older Android devices).
* It renders into a `SurfaceView` that allows you to interface with any other Android UI element.
* It handles *events* like a Java activity would do, allowing any Android UI element (like a text edit, a webview, an ad or a form) to work as usual, but still exposes the events to your game using a C interface that makes them easy to consume in your game loop.
* It offers a C API similar to `NativeActivity`, and to the *android_native_app_glue* library.

## Build the GameActivity AAR from sources

From the `gamesdk` directory:

* `./gradlew packageLocalZip -Plibraries=game_activity`

The AAR is output in the `package` directory. It contains GameActivity, both the Java class and its C++ implementation, and the "android_native_app_glue" library.

## Integrate GameActivity AAR to your build

Refer to the integration guide for now. Link to it and other documentation will be added here later.

Note that the library has a dependency on androidx.core version 1.5.0 or later. You should add the following to your app's build.gradle file:
`
dependencies {
    ...
    implementation "androidx.core:core:1.5.0"
    ...
`
Not adding this will cause a JNI crash at startup.
