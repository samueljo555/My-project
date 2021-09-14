<?php
$myFile="data.json";
$json = file_get_contents('data.json');
$user = $_REQUEST['id'];
$rgb = $_REQUEST['rgb'];
$json_data = json_decode($json,true);
if($user == "on1" || $user == "off1"){
$json_data[0]["switch"] = $user;
}
elseif ($user == "on2" || $user == "off2") {
	$json_data[1]["switch"] = $user;
}
elseif ($user == "on5" || $user == "off5") {
	$json_data[3]["switch"] = $user;
}
elseif($user == "open" || $user == "close")
{
		$json_data[2]["switch"] = $user;
}
elseif($user == "on3" || $user == "off3" || $user == "null")
{
	if($user != "null"){
		$json_data[4]["switch"] = $user;
	}
	if($rgb != "null"){
		$json_data[4]["rgb"] = $rgb;
	}
}
$jsondata = json_encode($json_data, JSON_PRETTY_PRINT);
file_put_contents($myFile, $jsondata)
?>