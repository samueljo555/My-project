package com.example.ta;

//membuat class untuk tempat menyimpan data yang nanti diambil dari web yang berbentuk json
public class items {
    private String nama;
    private String waktu;
    private String imageurl;

    public items(String nama, String waktu,String imageurl) {
        this.nama = nama;
        this.waktu = waktu;
        this.imageurl = imageurl;
    }

    public String getNama() {
        return nama;
    }

    public String getWaktu() {
        return waktu;
    }

    public String getImageurl() {
        return imageurl;
    }
}
