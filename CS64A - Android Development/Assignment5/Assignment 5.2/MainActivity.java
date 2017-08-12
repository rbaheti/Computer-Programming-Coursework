package com.example.calculatorapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    EditText display;
    Button btnClear;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        display = (EditText) findViewById(R.id.editText);
        display.setText("");
        btnClear = (Button) findViewById(R.id.btnClear);
        btnClear.setOnLongClickListener(new View.OnLongClickListener() {
            public boolean onLongClick(View view) {
                display.setText("##########");
                return true;
            }
        });
    }

    public void btnDigitClicked(View view) {
        String displayStr = display.getText().toString();
        displayStr += ((Button)view).getText();
        display.setText(displayStr);
    }

    public void btnClearClicked(View view){
        display.setText("");
    }

}
