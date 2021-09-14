<?php
if (isset($_GET['stat']))
{
   $stat = $_GET['stat'];
}

$myfile = fopen("data.txt", "w");
fwrite($myfile, $stat);
fclose($myfile);
?>