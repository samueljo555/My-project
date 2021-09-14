package com.example.ta;
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

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import java.util.List;

public class background extends Service {
    //creating a mediaplayer object

    private boolean cekk= true;
    public Handler handler = new Handler();
    //membuat handler dimana handler ini akan mengecek setiap 1 detik apakah ada orang yang terdeteksi atau tidak,
    //jika ada maka notifikasi akan muncul pada hp
    Runnable my_runnable = new Runnable() {
        @Override
        public void run() {
            if(cekk)
            sendGetRequest();
            else
                sendGetRequest1();

            handler.postDelayed(this, 1000);
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
        RequestQueue queue= Volley.newRequestQueue(background.this);
        String url="http://databaseta.my.id/read.php?cek=1";
        StringRequest stringRequest=new StringRequest(Request.Method.GET, url, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {

                if(!response.isEmpty() && cekk) {
                    //jika response dari server tidak null maka aplikasi akan menamnpilkan notifikasi kalau ada orang yang membuka pintu
                    if(isAppIsInBackground(getApplicationContext())) {
                        System.out.println(response);
                        Intent intent = new Intent(background.this,history.class);
                        PendingIntent pendingIntent = PendingIntent.getActivity(
                                background.this,
                                0,
                                intent,
                                PendingIntent.FLAG_UPDATE_CURRENT);
                        NotificationCompat.Builder builder = new NotificationCompat.Builder(background.this, "notif")
                                .setSmallIcon(R.drawable.ic_baseline_add_alert_24)
                                .setContentTitle("notification")
                                .setContentText(response)
                                .setAutoCancel(true)
                                .setContentIntent(pendingIntent)
                                .setPriority(NotificationCompat.PRIORITY_DEFAULT);

                        NotificationManagerCompat notificationManager = NotificationManagerCompat.from(background.this);
                        builder.build().flags |= Notification.FLAG_AUTO_CANCEL;
                        notificationManager.notify(100, builder.build());
                    }

                    cekk=false;
                }

                System.out.println(response);

            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                System.out.println("Gagal");
            }
        });

        queue.add(stringRequest);
    }
    private void sendGetRequest1() {
        RequestQueue queue= Volley.newRequestQueue(background.this);
        String url="http://databaseta.my.id/updatenotif.php?stat=";
        StringRequest stringRequest=new StringRequest(Request.Method.GET, url, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                cekk=true;
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
//                Toast.makeText(MainActivity.this,"Failed",Toast.LENGTH_LONG).show();
                System.out.println("Gagal");
            }
        });

        queue.add(stringRequest);
    }
    //membuat notification channel
    private void createNotificationChannel(){
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            CharSequence name = "studentChannel";
            String description = "Channel for student notification";
            int importance = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel channel = new NotificationChannel("notif",name,importance);
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