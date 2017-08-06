package com.example.viewgroupapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onClickView(View view){
        Button btn = (Button) view;
        LinearLayout innerGrp = (LinearLayout)findViewById(R.id.innerVGroup);
        if(innerGrp.getVisibility() == View.VISIBLE){
            innerGrp.setVisibility(View.INVISIBLE);
            btn.setText("Show View");
        }
        else{
            innerGrp.setVisibility(View.VISIBLE);
            btn.setText("Hide View");
        }

        CheckBox chkAdmin = (CheckBox)findViewById(R.id.ckbAdmin);
        TextView tvAdmin = (TextView)findViewById(R.id.tvAdmin);
        TextView tvUser = (TextView)findViewById(R.id.tvUser);

        if(chkAdmin.isChecked()){
            tvAdmin.setVisibility(View.VISIBLE);
            tvUser.setVisibility(View.GONE);
        }
        else {
            tvUser.setVisibility(View.VISIBLE);
            tvAdmin.setVisibility(View.GONE);
        }
    }
}
