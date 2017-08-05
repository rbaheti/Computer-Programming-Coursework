package com.example.imageapp;

import android.media.Image;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity {

    private ImageView iv;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        iv = (ImageView)findViewById(R.id.imageView1);
        iv.setClickable(true);
        iv.setOnClickListener(new View.OnClickListener(){
            public void onClick(View view){
                float scale = iv.getScaleX();
                if(scale == 1.0f){
                    iv.setScaleX(0.5f);
                    iv.setScaleY(0.5f);
                }
                else{
                    iv.setScaleX(1.0f);
                    iv.setScaleY(1.0f);
                }
            }
        });
    }

    public void onChange(View view){
        String tag = (String)iv.getTag();
        if(tag.equals("butterflies")){
            iv.setImageResource(R.mipmap.scenery);
            iv.setTag("scenery");
        }
        else{
            iv.setImageResource(R.mipmap.butterflies);
            iv.setTag("butterflies");
        }
    }
}
