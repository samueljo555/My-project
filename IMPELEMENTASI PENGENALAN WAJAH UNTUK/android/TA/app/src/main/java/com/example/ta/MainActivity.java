package com.example.ta;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;

import android.view.View;
import android.widget.Button;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

public class MainActivity extends AppCompatActivity {

    private String url ="http://databaseta.my.id/open_door.php?door=1";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button open = findViewById(R.id.open);
        Button log = findViewById(R.id.log);
        //menapilkan data orang yang membuka pintu
        log.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent  = new Intent(MainActivity.this,history.class);
                startActivity(intent);
            }
        });
        //memberi sinyal ke raspi untuk membuka pintu , dengan menekan tombol open
        open.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getdata();
            }
        });
        startService(new Intent(MainActivity.this, background.class));
    }

    //fungsi yand digunakan untuk mengirimkan sinyal ke raspbery untuk membuka pintu
private void getdata(){
    RequestQueue queue= Volley.newRequestQueue(MainActivity.this);
    StringRequest stringRequest=new StringRequest(Request.Method.GET, url, new Response.Listener<String>() {
        @Override
        public void onResponse(String response) {

        }
    }, new Response.ErrorListener() {
        @Override
        public void onErrorResponse(VolleyError error) {

        }
    });

    queue.add(stringRequest);
}
}