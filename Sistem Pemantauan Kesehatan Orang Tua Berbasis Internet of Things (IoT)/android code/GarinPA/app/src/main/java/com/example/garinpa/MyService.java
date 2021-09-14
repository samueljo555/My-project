package com.example.garinpa;

import android.app.ActivityManager;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;

import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.List;

public class MyService extends Service {
    String status;
    String message;
    Integer ceking=0;
    DatabaseReference dref;
    boolean cek=false;
    public Handler handler = new Handler();
    //membuat handler dimana handler ini akan mengecek setiap 1 detik apakah ada orang yang terdeteksi atau tidak,
    //jika ada maka notifikasi akan muncul pada hp

    Runnable my_runnable = new Runnable() {
        @Override
        public void run() {
                sendGetRequest();
            handler.postDelayed(this, 4000);
        }
    };
    private NotificationManagerCompat notificationManager;
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        //fungsi yang dijalankan saat aplikasi berjalan di backround
        createNotificationChannel();
        my_runnable.run();
        return START_STICKY;
    }


    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    private void sendGetRequest() {
        if(isAppIsInBackground(getApplicationContext())) {
            dref = FirebaseDatabase.getInstance().getReference();
            dref.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(DataSnapshot dataSnapshot) {
                    status = dataSnapshot.child("data").getValue().toString();
                    String[] arrOfStr = status.split(",");

                    if (arrOfStr[0].equals("1")) {
                        Integer Hr = Integer.parseInt(arrOfStr[1]);
                        Float suhu = Float.parseFloat(arrOfStr[2]);
                        if(Hr<60 && suhu < 35) {
                            ceking++;
                            message = "Heart rate dan suhu tubuh pasien sangat rendah";
                            cek =true;
                        }
                        else if(Hr>100 && suhu > 38){
                            ceking++;
                            message = "Heart rate dan suhu tubuh pasien sangat sangat tinggi";
                            cek =true;
                        }
                        else if (Hr<60){
                            ceking++;
                            message = "Heart rate  pasien sangat rendah";
                            cek =true;
                        }
                        else if(Hr>100){
                            ceking++;
                            message = "Heart rate  pasien sangat tinggi";
                            cek =true;
                        }
                        else if (suhu<35){
                            ceking++;
                            message = "Suhu  pasien sangat rendah";
                            cek =true;
                        }
                        else if(suhu>38){
                            ceking++;
                            message = "Suhu  pasien sangat tinggi";
                            cek =true;
                        }
                        else{
                            ceking = 0;
                        }
                        if(cek && ceking > 3) {
                            cek = false;
                            ceking = 0;
                            Intent intent = new Intent(MyService.this, MainActivity.class);
                            PendingIntent pendingIntent = PendingIntent.getActivity(
                                    MyService.this,
                                    0,
                                    intent,
                                    PendingIntent.FLAG_UPDATE_CURRENT);
                            NotificationCompat.Builder builder = new NotificationCompat.Builder(MyService.this, "jose")
                                    .setSmallIcon(R.drawable.ic_baseline_add_alert_24)
                                    .setContentTitle("Monitoring Pasien")
                                    .setContentText(message)
                                    .setAutoCancel(true)
                                    .setContentIntent(pendingIntent)
                                    .setPriority(NotificationCompat.PRIORITY_DEFAULT);

                            NotificationManagerCompat notificationManager = NotificationManagerCompat.from(MyService.this);
                            builder.build().flags |= Notification.FLAG_AUTO_CANCEL;
                            notificationManager.notify(100, builder.build());
                        }
                    }
                }

                @Override
                public void onCancelled(DatabaseError databaseError) {
                }
            });
        }
    }
    //melakukan get pada server
    //membuat notification channel
    private void createNotificationChannel(){
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            CharSequence name = "studentChannel";
            String description = "Channel for student notification";
            int importance = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel channel = new NotificationChannel("jose",name,importance);
            channel.setDescription(description);

            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }
    }
    // untuk mengecek apakah aplikasi berjalan di background atau tidak, jika tidak maka notifikasi tidak akan di munculkan
    // jika berada di background maka notifikasi akan muncul
    private boolean isAppIsInBackground(Context context) {
        boolean isInBackground = true;

        ActivityManager am = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.KITKAT_WATCH) {
            List<ActivityManager.RunningAppProcessInfo> runningProcesses = am.getRunningAppProcesses();
            for (ActivityManager.RunningAppProcessInfo processInfo : runningProcesses) {
                if (processInfo.importance == ActivityManager.RunningAppProcessInfo.IMPORTANCE_FOREGROUND) {
                    for (String activeProcess : processInfo.pkgList) {
                        if (activeProcess.equals(context.getPackageName())) {
                            isInBackground = false;
                        }
                    }
                }
            }
        }
        else
        {
            List<ActivityManager.RunningTaskInfo> taskInfo = am.getRunningTasks(1);
            ComponentName componentInfo = taskInfo.get(0).topActivity;
            if (componentInfo.getPackageName().equals(context.getPackageName())) {
                isInBackground = false;
            }
        }
        return isInBackground;
    }
}
