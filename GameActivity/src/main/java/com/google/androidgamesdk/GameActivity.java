/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.google.androidgamesdk;

import static android.view.inputmethod.EditorInfo.IME_ACTION_GO;
import static android.view.inputmethod.EditorInfo.IME_ACTION_NONE;
import static android.view.inputmethod.EditorInfo.IME_MASK_ACTION;
import static android.view.inputmethod.EditorInfo.IME_FLAG_NO_ENTER_ACTION;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.content.res.Configuration;
import android.graphics.PixelFormat;
import android.os.Build;
import android.os.Bundle;
import android.text.InputType;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.WindowManager;
import android.view.inputmethod.EditorInfo;
import android.widget.FrameLayout;

import dalvik.system.BaseDexClassLoader;
import java.io.File;

public class GameActivity
    extends Activity
    implements SurfaceHolder.Callback2 {
  private static final String LOG_TAG = "GameActivity";

  /**
   * Optional meta-that can be in the manifest for this component, specifying
   * the name of the native shared library to load.  If not specified,
   * "main" is used.
   */
  public static final String META_DATA_LIB_NAME = "android.app.lib_name";

  /**
   * Optional meta-that can be in the manifest for this component, specifying
   * the name of the main entry point for this native activity in the
   * {@link #META_DATA_LIB_NAME} native code.  If not specified,
   * "GameActivity_onCreate" is used.
   */
  public static final String META_DATA_FUNC_NAME = "android.app.func_name";

  private static final String KEY_NATIVE_SAVED_STATE = "android:native_state";

  protected int contentViewId;

  private EditorInfo imeEditorInfo;

  /**
   * The SurfaceView used by default for displaying the game and getting a text input.
   * You can override its creation in `onCreateSurfaceView`.
   * This can be null, usually if you override `onCreateSurfaceView` to render on the whole activity
   * window.
   */
  protected SurfaceView mSurfaceView;

  @Override
  public boolean onTouchEvent(MotionEvent event) {
    return onTouchEventNative(mNativeHandle, event);
  }

  @Override
  public boolean onGenericMotionEvent(MotionEvent event) {
    return super.onGenericMotionEvent(event);
//    return onTouchEventNative(mNativeHandle, event);
  }

  @Override
  public boolean onKeyUp(final int keyCode, KeyEvent event) {
    return onKeyUpNative(mNativeHandle, event);
  }

  @Override
  public boolean onKeyDown(final int keyCode, KeyEvent event) {
    return onKeyDownNative(mNativeHandle, event);
  }

  private long mNativeHandle;

  private SurfaceHolder mCurSurfaceHolder;

  protected final int[] mLocation = new int[2];

  protected boolean mDestroyed;

  protected native long loadNativeCode(String path, String funcname, String internalDataPath,
      String obbPath, String externalDataPath, AssetManager assetMgr, byte[] savedState);

  protected native String getDlError();

  protected native void unloadNativeCode(long handle);

  protected native void onStartNative(long handle);

  protected native void onResumeNative(long handle);

  protected native byte[] onSaveInstanceStateNative(long handle);

  protected native void onPauseNative(long handle);

  protected native void onStopNative(long handle);

  protected native void onConfigurationChangedNative(long handle);

  protected native void onTrimMemoryNative(long handle, int level);

  protected native void onWindowFocusChangedNative(long handle, boolean focused);

  protected native void onSurfaceCreatedNative(long handle, Surface surface);

  protected native void onSurfaceChangedNative(
      long handle, Surface surface, int format, int width, int height);

  protected native void onSurfaceRedrawNeededNative(long handle, Surface surface);

  protected native void onSurfaceDestroyedNative(long handle);

  protected native boolean onTouchEventNative(long handle, MotionEvent motionEvent);

  protected native boolean onKeyDownNative(long handle, KeyEvent keyEvent);

  protected native boolean onKeyUpNative(long handle, KeyEvent keyEvent);

  protected native void onWindowInsetsChangedNative(long handle);

  /**
   * Get the pointer to the C `GameActivity` struct associated to this activity.
   * @return the pointer to the C `GameActivity` struct associated to this activity.
   */
  public long getGameActivityNativeHandle() {
    return this.mNativeHandle;
  }

  /**
   * Called to create the SurfaceView when the game will be rendered. It should be stored in
   * the mSurfaceView field, and its ID in contentViewId (if applicable).
   *
   * You can also redefine this to not create a SurfaceView at all,
   * and call `getWindow().takeSurface(this);` instead if you want to render on the whole activity
   * window.
   */
  protected void onCreateSurfaceView() {
    mSurfaceView = new SurfaceView(this);
    FrameLayout frameLayout = new FrameLayout(this);
    contentViewId = View.generateViewId();
    frameLayout.setId(contentViewId);
    frameLayout.addView(mSurfaceView);

    setContentView(frameLayout);
    frameLayout.requestFocus();

    mSurfaceView.getHolder().addCallback(
        this); // Register as a callback for the rendering of the surface, so that we can pass this
               // surface to the native code

  }

  /**
   * Called to set up the window after the SurfaceView is created. Override this if you want to
   * change the Format (default is `PixelFormat.RGB_565`) or the Soft Input Mode (default is
   * `WindowManager.LayoutParams.SOFT_INPUT_STATE_UNSPECIFIED |
   * WindowManager.LayoutParams.SOFT_INPUT_ADJUST_RESIZE`).
   */
  protected void onSetUpWindow() {
    getWindow().setFormat(PixelFormat.RGB_565);
    getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_UNSPECIFIED
        | WindowManager.LayoutParams.SOFT_INPUT_ADJUST_RESIZE);
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    onCreateSurfaceView();
    onSetUpWindow();

    String libname = "main";
    if (null != getIntent().getStringExtra(META_DATA_LIB_NAME)) {
      libname = getIntent().getStringExtra(META_DATA_LIB_NAME);
    }
    String funcname = "GameActivity_onCreate";
    ActivityInfo ai;
    try {
      ai = getPackageManager().getActivityInfo(
          getIntent().getComponent(), PackageManager.GET_META_DATA);
      if (ai.metaData != null) {
        String ln = ai.metaData.getString(META_DATA_LIB_NAME);
        if (ln != null)
          libname = ln;
        ln = ai.metaData.getString(META_DATA_FUNC_NAME);
        if (ln != null)
          funcname = ln;
      }
    } catch (PackageManager.NameNotFoundException e) {
      throw new RuntimeException("Error getting activity info", e);
    }

    BaseDexClassLoader classLoader = (BaseDexClassLoader) getClassLoader();
    String path = classLoader.findLibrary(libname);

    if (path == null) {
      throw new IllegalArgumentException("Unable to find native library " + libname
          + " using classloader: " + classLoader.toString());
    }

    byte[] nativeSavedState =
        savedInstanceState != null ? savedInstanceState.getByteArray(KEY_NATIVE_SAVED_STATE) : null;

    mNativeHandle = loadNativeCode(path, funcname, getAbsolutePath(getFilesDir()),
        getAbsolutePath(getObbDir()), getAbsolutePath(getExternalFilesDir(null)),
        getAssets(), nativeSavedState);

    if (mNativeHandle == 0) {
      throw new UnsatisfiedLinkError(
          "Unable to load native library \"" + path + "\": " + getDlError());
    }

    super.onCreate(savedInstanceState);
  }

  private static String getAbsolutePath(File file) {
    return (file != null) ? file.getAbsolutePath() : null;
  }

  @Override
  protected void onDestroy() {
    mDestroyed = true;
    if (mCurSurfaceHolder != null) {
      onSurfaceDestroyedNative(mNativeHandle);
      mCurSurfaceHolder = null;
    }

    unloadNativeCode(mNativeHandle);
    super.onDestroy();
  }

  @Override
  protected void onPause() {
    super.onPause();
    onPauseNative(mNativeHandle);
  }

  @Override
  protected void onResume() {
    super.onResume();
    onResumeNative(mNativeHandle);
  }

  @Override
  protected void onSaveInstanceState(Bundle outState) {
    super.onSaveInstanceState(outState);
    byte[] state = onSaveInstanceStateNative(mNativeHandle);
    if (state != null) {
      outState.putByteArray(KEY_NATIVE_SAVED_STATE, state);
    }
  }

  @Override
  protected void onStart() {
    super.onStart();
    onStartNative(mNativeHandle);
  }

  @Override
  protected void onStop() {
    super.onStop();
    onStopNative(mNativeHandle);
  }

  @Override
  public void onConfigurationChanged(Configuration newConfig) {
    super.onConfigurationChanged(newConfig);
    if (!mDestroyed) {
      onConfigurationChangedNative(mNativeHandle);
    }
  }

  @Override
  public void onTrimMemory(int level) {
    super.onTrimMemory(level);
    if (!mDestroyed) {
      onTrimMemoryNative(mNativeHandle, level);
    }
  }

  @Override
  public void onWindowFocusChanged(boolean hasFocus) {
    super.onWindowFocusChanged(hasFocus);
    if (!mDestroyed) {
      onWindowFocusChangedNative(mNativeHandle, hasFocus);
    }
  }

  public void surfaceCreated(SurfaceHolder holder) {
    if (!mDestroyed) {
      mCurSurfaceHolder = holder;
      onSurfaceCreatedNative(mNativeHandle, holder.getSurface());
    }
  }

  public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
    if (!mDestroyed) {
      mCurSurfaceHolder = holder;
      onSurfaceChangedNative(mNativeHandle, holder.getSurface(), format, width, height);
    }
  }

  public void surfaceRedrawNeeded(SurfaceHolder holder) {
    if (!mDestroyed) {
      mCurSurfaceHolder = holder;
      onSurfaceRedrawNeededNative(mNativeHandle, holder.getSurface());
    }
  }

  public void surfaceDestroyed(SurfaceHolder holder) {
    mCurSurfaceHolder = null;
    if (!mDestroyed) {
      onSurfaceDestroyedNative(mNativeHandle);
    }
  }

  void setWindowFlags(int flags, int mask) {
    getWindow().setFlags(flags, mask);
  }

  void setWindowFormat(int format) {
    getWindow().setFormat(format);
  }

  /**
   * Get the EditorInfo structure used to initialize the IME when it is requested.
   * The default is to forward key requests to the app (InputType.TYPE_NULL) and to
   * have no action button (IME_ACTION_NONE).
   * See https://developer.android.com/reference/android/view/inputmethod/EditorInfo.
   */
  public EditorInfo getImeEditorInfo() {
    if (imeEditorInfo==null) {
      imeEditorInfo = new EditorInfo();
      imeEditorInfo.inputType = InputType.TYPE_NULL;
      imeEditorInfo.actionId = IME_ACTION_NONE;
      imeEditorInfo.imeOptions = IME_FLAG_NO_ENTER_ACTION;
    }
    return imeEditorInfo;
  }

  /**
   * Set the EditorInfo structure used to initialize the IME when it is requested.
   * Set the inputType and actionId in order to customize how the IME behaves.
   * See https://developer.android.com/reference/android/view/inputmethod/EditorInfo.
   */
  public void setImeEditorInfo(EditorInfo info) {
    imeEditorInfo = info;
  }

  /**
   * Set the inpuType and actionId fields of the EditorInfo structure used to
   * initialize the IME when it is requested.
   * This is called from the native side by GameActivity_setImeEditorInfo.
   * See https://developer.android.com/reference/android/view/inputmethod/EditorInfo.
   */
  public void setImeEditorInfoFields(int inputType, int actionId, int imeOptions) {
    EditorInfo info = getImeEditorInfo();
    info.inputType = inputType;
    info.actionId = actionId;
    info.imeOptions = imeOptions;
  }
}
