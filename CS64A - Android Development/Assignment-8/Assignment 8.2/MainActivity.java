package com.example.listviewapp;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import static android.widget.AdapterView.*;

public class MainActivity extends Activity {

    private Button btnOpenSecondActivity;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        btnOpenSecondActivity = (Button) findViewById(R.id.btnStart);
    }

    // create onOpen handler for button Start
    public void onOpen(View view){
        Intent intendSecond = new Intent(this, SecondActivity.class);
        startActivity(intendSecond);
    }

}
