package com.example.dicerollinggame2;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // reference objects
    private Button btnPlay;
    private EditText etPlayer;
    private TextView tvDisplay;
    private static int GAME_ACTIVITY_REQUEST_CODE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // handlers
        btnPlay = (Button)findViewById(R.id.btnPlay);
        etPlayer = (EditText)findViewById(R.id.editText);
        tvDisplay = (TextView)findViewById(R.id.tvDisplay);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == GAME_ACTIVITY_REQUEST_CODE) {
            if(resultCode == Activity.RESULT_OK){
                String result;
                if (data.hasExtra("betamount")) {
                    result = data.getStringExtra("betamount");
                    tvDisplay.setTextColor(Color.parseColor("#ff0000ff"));
                } else {
                    result = data.getStringExtra("gameresult");
                    tvDisplay.setTextColor(Color.parseColor("#ffff0000"));
                }
                tvDisplay.setText(result);
            }
        }
    }

    public void playGame(View view){
        Intent intentGame = new Intent(MainActivity.this, GameActivity.class);
        String name = etPlayer.getText().toString();
        intentGame.putExtra("playername", name);
        startActivityForResult(intentGame,GAME_ACTIVITY_REQUEST_CODE);
    }
}
