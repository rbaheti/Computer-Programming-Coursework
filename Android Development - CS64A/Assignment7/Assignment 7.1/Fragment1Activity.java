package com.example.frangmentapp;


import android.app.Fragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

public class Fragment1Activity extends Fragment {
    public Fragment1Activity() {
        super();
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.activity_fragment1, container, false);
        ImageView imageview = (ImageView)view.findViewById(R.id.image);
        TextView textView = (TextView)view.findViewById(R.id.textView1);
        imageview.setImageResource(R.drawable.scenary);
        textView.setText("Have a good Trip!");
        return view;
    }

    @Override
    public void onPause() {
        super.onPause();
    }
}
