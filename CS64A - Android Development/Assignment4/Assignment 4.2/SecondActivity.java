package com.example.intentactivity;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class SecondActivity extends AppCompatActivity {

    private Button btnBack;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);
        //get button object for button in second activity
        btnBack = (Button)findViewById(R.id.btnBack);
    }

    // create onBack handler for button BACK
    public void onBack(View view){
        this.finish();
    }
}
