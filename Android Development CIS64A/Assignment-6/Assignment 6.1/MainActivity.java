package com.example.styleandtheme;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onOpenSecond(View view){
        Intent intentSecond = new Intent("android.intent.action.SecondActivity");
        startActivity(intentSecond);
    }

    public void onOpenThird(View view){
        Intent intentThird = new Intent("android.intent.action.ThirdActivity");
        startActivity(intentThird);
    }

}
