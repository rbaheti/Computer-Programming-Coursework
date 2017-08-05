package com.example.scrollapplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ScrollView;
import android.widget.TextView;

public class  MainActivity extends AppCompatActivity implements GestureDetector.OnGestureListener {

    // Create objects for TextView, Button, String and GestureDetector types
    private TextView display;
    private Button btnClear;
    private String eventStr;
    private GestureDetector detector;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // instantiate objects created above
        display = (TextView)findViewById(R.id.textView1);
        btnClear = (Button) findViewById(R.id.btnClear);
        detector = new GestureDetector(this, this);
    }

    public void onClear(View view){
        display.setText("");
    }

    public boolean onTouchEvent(MotionEvent event){
        return detector.onTouchEvent(event);
    }

    @Override
    public boolean onDown(MotionEvent e) {
        eventStr = String.format("onDown: (%f, %f)\n", e.getX(), e.getY());
        display.setText(display.getText()+eventStr);
        return true;
    }

    @Override
    public void onShowPress(MotionEvent e) {
        eventStr = String.format("onShowPress: (%f, %f)\n", e.getX(), e.getY());
        display.setText(display.getText()+eventStr);
    }

    @Override
    public boolean onSingleTapUp(MotionEvent e) {
        eventStr = String.format("onSingleTapUp: (%f, %f)\n", e.getX(), e.getY());
        display.setText(display.getText()+eventStr);
        return true;
    }

    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
        eventStr = String.format("onScroll: (%f, %f), (%f, %f)\n\tdX=%f, dY=%f",
                e1.getX(), e1.getY(), e2.getX(), e2.getY(), distanceX, distanceY);
        display.setText(display.getText()+eventStr);
        return true;
    }

    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        eventStr = String.format("onFling: (%f, %f), (%f, %f)\n\tdX=%f, dY=%f\n",
                e1.getX(), e1.getY(), e2.getX(), e2.getY(), velocityX, velocityY);
        display.setText(display.getText()+eventStr);
        return true;
    }

    @Override
    public void onLongPress(MotionEvent e) {
        eventStr = String.format("onLongPress: (%f, %f)\n", e.getX(), e.getY());
        display.setText(display.getText()+eventStr);
    }
}
