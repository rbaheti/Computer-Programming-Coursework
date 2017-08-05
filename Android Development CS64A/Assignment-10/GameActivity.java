package com.example.dicerollinggame2;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import java.util.Random;

public class GameActivity extends AppCompatActivity {

    private Button btnQuit, btnRoll, btnBetMoney;
    private TextView tvWelcome, tvRandom, tvResult;
    private Random random;
    private int winCount = 0, loseCount = 0;
    private String player;
    private static int BETTING_ACTIVITY_REQUEST_CODE = 2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
        btnQuit = (Button)findViewById(R.id.btnQuit);
        btnRoll = (Button)findViewById(R.id.btnRoll);
        tvWelcome = (TextView)findViewById(R.id.tvWelcome);
        tvRandom = (TextView)findViewById(R.id.tvRandom);
        tvResult = (TextView)findViewById(R.id.tvDisplay);
        random = new Random();
        Bundle extra = getIntent().getExtras();
        player = extra.getString("playername");
        tvWelcome.setText(player + "! " + tvWelcome.getText());
        btnBetMoney = (Button)findViewById(R.id.btnBetMoney);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(requestCode == BETTING_ACTIVITY_REQUEST_CODE) {
            if(resultCode == Activity.RESULT_OK){
                Intent returnIntent = getIntent();
                if (data.hasExtra("betamount")) {
                    returnIntent.putExtra("betamount", data.getStringExtra("betamount"));
                }
                setResult(Activity.RESULT_OK, returnIntent);
                this.finish();
            }
        }
    }

    public void onQuit(View view){
        String result = player + ", you have won " + winCount + " times and lost " + loseCount + " times.";
        Intent returnIntent = getIntent();
        returnIntent.putExtra("gameresult", result);
        setResult(Activity.RESULT_OK, returnIntent);
        GameActivity.this.finish();
    }

    public void rollDice(View view){
        int gameRandom = random.nextInt(12)+2;
        tvRandom.setText("Random number is "+gameRandom);
        int playerRandom = random.nextInt(12)+2;
        if(playerRandom > gameRandom){
            winCount++;
            tvResult.setText("Your number is "+ playerRandom + ". You win!");
        }
        else{
            loseCount++;
            tvResult.setText("Your number is "+ playerRandom + ". You lose!");
        }
    }

    public void betMoney(View view){
        Intent intentBetMoney = new Intent(GameActivity.this, BettingActivity.class);
        startActivityForResult(intentBetMoney, BETTING_ACTIVITY_REQUEST_CODE);
    }
}
