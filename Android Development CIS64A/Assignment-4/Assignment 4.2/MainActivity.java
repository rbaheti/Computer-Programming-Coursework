package com.example.intentactivity;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import java.net.URI;

public class MainActivity extends AppCompatActivity {

    private Button btnOpenSecondActivity;
    private Button btnOpenWebpage;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //get button objects for respective buttons in main activity
        btnOpenSecondActivity = (Button) findViewById(R.id.btnOpenSecond);
        btnOpenWebpage = (Button) findViewById(R.id.btnOpenSearch);
    }

    // create onOpen handler for button open_second
    public void onOpen(View view){
        Intent intendSecond = new Intent(this, SecondActivity.class);
        startActivity(intendSecond);
    }

    // create onOpenWebpage handler for button open search
    public void onOpenWebpage(View view){
        Intent webIntent = new Intent();
        webIntent.setAction(Intent.ACTION_VIEW);
        webIntent.setData(Uri.parse("http://www.google.com"));
        startActivity(webIntent);
    }
}
