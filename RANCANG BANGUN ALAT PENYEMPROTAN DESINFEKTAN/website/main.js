var cek = true
var myVar = setInterval(getData, 1000); 
function getData(){
$(document).ready(function(){
    $.getJSON("read.php",function(jsonData) {

            var status_masuk =  jsonData[0]["status_masuk"];
            var status_keluar =  jsonData[0]["status_keluar"];
            document.getElementById("sensor").innerHTML = jsonData[0]["suhu"] + "&deg;C";
            document.getElementById("tolak").innerHTML = jsonData[0]["tolak"];
            document.getElementById("dalam").innerHTML = jsonData[0]["dalam"];
            document.getElementById("keluar").innerHTML = jsonData[0]["keluar"];
            document.getElementById("total").innerHTML = jsonData[0]["total"];
            if(status_masuk == 1){
                document.getElementById("imageTitik").src = "benar.png";
                $.get("updatejson.php?data=A,,0,", function(data, status){
                    console.log(status);
                   });
            }
            else if(status_masuk == 2){
                document.getElementById("imageTitik").src = "silang.png";
                $.get("updatejson.php?data=A,,0,", function(data, status){
                    console.log(status);
                   });
            }
            else if(status_masuk == 3){
                document.getElementById("imageTitik").src = "error.png";
                $.get("updatejson.php?data=A,,0,", function(data, status){
                    console.log(status);
                   });
            }

            if(status_keluar == 1){
                $.get("updatejson.php?data=A,,,0", function(data, status){
                    console.log(status);
                   });
            }
    });
});
}

function reset(){
    $.get("updatejson.php?data=B,,,", function(data, status){
            console.log(status);
       });
       document.getElementById("imageTitik").src = "wait.png";  
}