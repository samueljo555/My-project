package com.example.ta;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import com.squareup.picasso.Picasso;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class Adapter extends RecyclerView.Adapter<Adapter.ViewHolder> {
    private List<items> listItems;
    private Context context;
    public Adapter(List<items> listItems, Context context) {
        this.listItems = listItems;
        this.context = context;
    }
    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.listitems,parent,false);
        return new ViewHolder(v);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        // memuat setiap element pada list_item untuk di masukkan reyclerview
        items Items = listItems.get(position);

        holder.textViewNama.setText(Items.getNama());
        holder.textViewWaktu.setText(Items.getWaktu());

        Picasso.with(context)
                .load(Items.getImageurl())
                .into(holder.imageView);
    }
    //menghitung size dari data yang didapat dari server
    @Override
    public int getItemCount() {
        return listItems.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder{
        // memasukkan setiap listitem ke recyclerView untuk di tampilkan di layar
        public TextView textViewNama;
        public TextView textViewWaktu;
        public ImageView imageView;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);

            textViewNama = (TextView) itemView.findViewById(R.id.Nama);
            textViewWaktu = (TextView) itemView.findViewById(R.id.Waktu);
            imageView = (ImageView) itemView.findViewById(R.id.imageView);
        }
    }
}
