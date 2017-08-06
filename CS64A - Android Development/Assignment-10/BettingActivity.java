package com.example.dicerollinggame2;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class BettingActivity extends AppCompatActivity {

    private TextView tvBetAmt;
    private EditText etBetAmount;
    private Button btnConfirm;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_betting);
        tvBetAmt = (TextView)findViewById(R.id.tvBetAmt);
        etBetAmount = (EditText)findViewById(R.id.etBetAmount);
        btnConfirm = (Button)findViewById(R.id.btnConfirm);
    }

    public void onConfirm(View view){
        Intent returnIntent = getIntent();
        String betAmount = etBetAmount.getText().toString();
        String result = "You have bet $" + betAmount + " on this game.";
        returnIntent.putExtra("betamount", result);
        setResult(Activity.RESULT_OK, returnIntent);
        BettingActivity.this.finish();
    }
}
