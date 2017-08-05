package com.example.listviewapp;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

public class SecondActivity extends AppCompatActivity {

    ListView listView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);
        listView = (ListView)findViewById(R.id.list);
        String colors[] = {"Red", "Green", "Blue", "Yellow", "Purple", "White", "Black"};
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_expandable_list_item_1, colors);
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener(){
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l){
                int position = i;
                String item = listView.getItemAtPosition(position).toString();
                Toast.makeText(SecondActivity.this, (position+1) + ". " + item, Toast.LENGTH_LONG).show();
            }
        });
    }

    // create onReturn handler for button Return
    public void onReturn(View view){
        this.finish();
    }
}
