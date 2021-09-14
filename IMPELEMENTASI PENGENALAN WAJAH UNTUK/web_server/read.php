<?php

if (isset($_GET['cek']))
{
   $cek = $_GET['cek'];
}
if($cek==1){
$myfile = fopen("data.txt", "r") or die("Unable to open file!");
if( 0 != filesize('data.txt')){
$data = fread($myfile,filesize("data.txt"));
    print "$data";
}

fclose($myfile);
}
elseif ($cek==0) {
$myfile = fopen("door.txt", "r") or die("Unable to open file!");
if( 0 != filesize('door.txt')){
$data = fread($myfile,filesize("door.txt"));
    print "$data";
}

fclose($myfile);
}
?>