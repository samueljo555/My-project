<?php
if (isset($_GET['door']))
{
   $door = $_GET['door'];
}

$myfile = fopen("door.txt", "w");
fwrite($myfile, $door);
fclose($myfile);
?>