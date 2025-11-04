package com.example.mygame;

import android.os.Bundle;
import com.raylib.RaylibActivity; // Raylib provides this

public class MainActivity extends RaylibActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // RaylibActivity handles loading your libMyGame.so automatically
    }
}
