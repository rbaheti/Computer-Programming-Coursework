package com.example.dicerollinggame;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.EditText;
import java.util.Random;

import static com.example.dicerollinggame.R.id.btnWinner;

public class MainActivity extends AppCompatActivity {

    // create Button variables
    private Button btnRoll1;
    private Button btnRoll2;
    private Button btnRoll3;
    private Button btnWinner;

    // create TextView variables
    private TextView tvResult1;
    private TextView tvResult2;
    private TextView tvResult3;

    // create EditText variables
    private EditText etName1;
    private EditText etName2;
    private EditText etName3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //get button objects for respective buttons in main activity
        btnRoll1 = (Button)findViewById(R.id.btnRoll1);
        tvResult1 = (TextView)findViewById(R.id.tvResult1);
        etName1 = (EditText) findViewById(R.id.etName1);

        btnRoll2 = (Button)findViewById(R.id.btnRoll2);
        tvResult2 = (TextView)findViewById(R.id.tvResult2);
        etName2 = (EditText) findViewById(R.id.etName2);

        btnRoll3 = (Button)findViewById(R.id.btnRoll3);
        tvResult3 = (TextView)findViewById(R.id.tvResult3);
        etName3 = (EditText) findViewById(R.id.etName3);

        btnWinner = (Button)findViewById(R.id.btnWinner);

        // create onclick listeners:
        btnRoll1.setOnClickListener(new View.OnClickListener(){
            public void onClick(View view){
                Random rand = new Random();
                int result1 = rand.nextInt(6)+1;
                tvResult1.setText(String.valueOf(result1));
            }
        });

        btnRoll2.setOnClickListener(new View.OnClickListener(){
            public void onClick(View view){
                Random rand = new Random();
                int result2 = rand.nextInt(6)+1;
                tvResult2.setText(String.valueOf(result2));
            }
        });

        btnRoll3.setOnClickListener(new View.OnClickListener(){
            public void onClick(View view){
                Random rand = new Random();
                int result3 = rand.nextInt(6)+1;
                tvResult3.setText(String.valueOf(result3));
            }
        });

        btnWinner.setOnClickListener(new View.OnClickListener(){
            public void onClick(View view){

                int num1 =  Integer.parseInt(tvResult1.getText().toString());
                int num2 =  Integer.parseInt(tvResult2.getText().toString());
                int num3 =  Integer.parseInt(tvResult3.getText().toString());

                if(num1 >= num2 && num1 >= num3){
                    btnWinner.setText("Winner is Player1" + " " + etName1.getText());
                } else if(num2 >= num1 && num2 >= num3){
                    btnWinner.setText("Winner is Player2" + " " + etName2.getText());
                } else {
                    btnWinner.setText("Winner is Player3" + " " + etName3.getText());
                }
            }
        });
    }
}
