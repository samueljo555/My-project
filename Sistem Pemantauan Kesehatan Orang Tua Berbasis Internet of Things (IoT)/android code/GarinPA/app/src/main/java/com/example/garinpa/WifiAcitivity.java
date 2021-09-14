package com.example.garinpa;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class WifiAcitivity extends AppCompatActivity {

    TextView ph,suhu;
    DatabaseReference dref;
    String status;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.wifiacitivity);
        suhu = (TextView) findViewById(R.id.suhu);
        ph = (TextView) findViewById(R.id.ph);

        dref= FirebaseDatabase.getInstance().getReference();
        dref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                status=dataSnapshot.child("data").getValue().toString();
                String[] arrOfStr = status.split(",");
                suhu.setText(arrOfStr[2]);
                ph.setText(arrOfStr[1]);
            }
            @Override
            public void onCancelled(DatabaseError databaseError) {
            }
        });

    }
}
