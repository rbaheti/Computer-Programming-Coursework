package com.example.myasynctask;

import android.app.Activity;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends Activity {

    ListView listView;
    String[] list;
    ProgressBar progressBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        listView = (ListView)findViewById(R.id.list);
        initializeArray();
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_expandable_list_item_1,
                new ArrayList());
        listView.setAdapter(adapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                String item = (String)listView.getItemAtPosition(position);
                Toast.makeText(MainActivity.this, "You Clicked " +item, Toast.LENGTH_SHORT).show();
            }
        });
        new myAsyncTask().execute();
    }

    void initializeArray() {
        list = new String[52];
        for(int i = 0; i < 26; ++i){
            list[i]=String.valueOf((char)('a'+i));
        }

        for(int i = 0; i < 26; ++i){
            list[i+26]=String.valueOf((char)('A'+i));
        }

    }

    class myAsyncTask extends AsyncTask<Void, String, Void>{
        ArrayAdapter<String> adapter;
        int count=0;
        public myAsyncTask() {
            super();
        }

        @Override
        protected void onPostExecute(Void aVoid) {
           Toast.makeText(MainActivity.this, "All items were loaded", Toast.LENGTH_SHORT).show();
            //setProgressBarVisibility(false);
            progressBar.setVisibility(View.GONE);
        }

        @Override
        protected void onPreExecute() {
            adapter = (ArrayAdapter<String>)listView.getAdapter();
            //setProgressBarIndeterminate(false);
            //setProgressBarVisibility(true);
            progressBar = (ProgressBar)findViewById(R.id.progressBar);
            progressBar.setIndeterminate(false);
            progressBar.setVisibility(View.VISIBLE);
        }

        @Override
        protected void onProgressUpdate(String... values) {
            adapter.add(values[0]);
            count++;
            //setProgress(count*10000/100);
            progressBar.setProgress(count*10000/100);
            if(count%20==0){
                Toast.makeText(MainActivity.this, count+"% data is loaded", Toast.LENGTH_SHORT).show();
            }
        }

        protected Void doInBackground(Void...parms){
            for(String item: list){
                publishProgress(item);
                try {
                    Thread.sleep(200);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            return null;
        }
    }
}
