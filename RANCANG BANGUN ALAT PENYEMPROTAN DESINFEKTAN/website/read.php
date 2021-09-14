<?php
$myFile="data.json";
$json = file_get_contents('data.json');
$json_data = json_decode($json,true);
print(json_encode($json_data));
?>