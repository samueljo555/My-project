<?php

if (isset($_GET['nama']) && isset($_GET['waktu']))
{
   $nama = $_GET['nama'];
   $waktu = $_GET['waktu'];
}

$current_data = file_get_contents('test.json');  
$array_data = json_decode($current_data, true);  
$extra = array(  
     'name'               =>     $nama,  
     'waktu'          =>     $waktu,  
);  
$array_data[] = $extra;  
$final_data = json_encode($array_data);  
if(file_put_contents('test.json', $final_data))  
{  
     echo "sukses";;  
}  
?>