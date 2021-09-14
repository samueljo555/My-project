<?php
$myFile="data.json";
$json = file_get_contents('data.json');
$data = $_REQUEST['data'];
$a = explode(",",$data);
echo $a[2];

$json_data = json_decode($json,true);
if($a[0]=="A"){
    if($a[1]!=null)
        $json_data[0]["suhu"] = (int) $a[1];
    if($a[2]!=null){
        $json_data[0]["status_masuk"] = (int) $a[2];
        if($a[2]==1){
            $json_data[0]["dalam"] = (int) $json_data[0]["dalam"] + 1;
            $json_data[0]["total"] = (int) $json_data[0]["dalam"] + (int) $json_data[0]["tolak"]+ (int) $json_data[0]["keluar"] ;
        }
        else if($a[2]==2){
            $json_data[0]["tolak"] = (int) $json_data[0]["tolak"] + 1 ;
            $json_data[0]["total"] = (int) $json_data[0]["dalam"] + (int) $json_data[0]["tolak"]+ (int) $json_data[0]["keluar"] ;
        }

    }
    if($a[3]!=null){
        $json_data[0]["status_keluar"] = (int) $a[3];
        if($a[3]){
            $json_data[0]["keluar"] = (int) $json_data[0]["keluar"] + 1;
            $nilai = (int)$json_data[0]["dalam"] - 1;
            if($nilai < 0){
                $nilai = 0;
            }
            $json_data[0]["dalam"] = $nilai;
        }
    }
}
else if($a[0]=="B"){
    $json_data[0]["suhu"] = 0;
    $json_data[0]["status_masuk"] = 0;
    $json_data[0]["status_keluar"] = 0;
    $json_data[0]["tolak"] = 0;
    $json_data[0]["keluar"] = 0;
    $json_data[0]["dalam"] = 0;
    $json_data[0]["total"] = 0;
}

$jsondata = json_encode($json_data, JSON_PRETTY_PRINT);
file_put_contents($myFile, $jsondata);

?>