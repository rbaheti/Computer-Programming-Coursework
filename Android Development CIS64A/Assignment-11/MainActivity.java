package com.example.databaseapp;

import android.database.Cursor;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private EditText etName, etMajor;
    private TextView tvDisplay;
    private DBAdapter myDBAdapter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        etName = (EditText)findViewById(R.id.etName);
        etMajor = (EditText)findViewById(R.id.etMajor);
        tvDisplay = (TextView)findViewById(R.id.tvDisplay);
        openDB();
    }

    public void openDB(){
        myDBAdapter = new DBAdapter(this);
        myDBAdapter.open();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        myDBAdapter.close();
    }

    public void onUpdateClicked(View view){
        String name = etName.getText().toString();
        String major = etMajor.getText().toString();
        long id = myDBAdapter.insertRow(name, major);
        if(id > 0){
            tvDisplay.setText("Inserted row to database, id = " +id);
        }
        else{
            tvDisplay.setText("Insert row to database failed.");
        }
    }

    public void onClearClicked(View view){
        myDBAdapter.deleteAll();
    }

    public void onQueryClicked(View view){
        Cursor cursor = myDBAdapter.getAllRows();
        displayRecords(cursor);
    }

    public void displayRecords(Cursor cursor){
        String output = "";
        if(cursor.getCount()>0){
            cursor.moveToFirst();
            do{
                long id = cursor.getLong(DBAdapter.COL_ROWID);
                String name = cursor.getString(DBAdapter.COL_NAME);
                String major = cursor.getString(DBAdapter.COL_MAJOR);
                output += "id="+id+" name:"+name+" major:"+major+"\n";
            }while(cursor.moveToNext());
        }
        tvDisplay.setText(output);
        cursor.close();
    }

}
