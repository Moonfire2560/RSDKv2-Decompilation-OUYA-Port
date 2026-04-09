package com.decomp.rsdkv2;
import android.content.Context;
import android.os.Environment;
import android.os.Bundle;
import android.view.View;
import java.io.File;
import org.libsdl.app.*;
public class RSDKv2 extends SDLActivity {
    @Override
    protected String[] getLibraries() {
        return new String[] {
            "RetroEngine"
        };
    }
    private void hideSystemUI() {
        getWindow().getDecorView().setSystemUiVisibility(
            View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
            | View.SYSTEM_UI_FLAG_FULLSCREEN
            | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
            | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
            | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
            | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
        );
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        hideSystemUI();
    }
    @Override
    protected void onStart() {
        super.onStart();
        getBasePath();
        hideSystemUI();
    }
    @Override
    protected void onPause() {
        super.onPause();
        if (mHasMultiWindow) {
            pauseNativeThread();
        }
    }
    @Override
    protected void onResume() {
        super.onResume();
        if (mHasMultiWindow) {
            resumeNativeThread();
        }
        hideSystemUI();
    }
    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        if (hasFocus) {
            hideSystemUI();
        }
    }
    public String getBasePath() {
        Context c = getApplicationContext();
        String p = Environment.getExternalStorageDirectory().getAbsolutePath() + "/RSDK/v2";
        new File(p).mkdirs();
        return p + "/";
    }
}