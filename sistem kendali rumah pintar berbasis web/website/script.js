var file;
var cek = false;
var ac = {
  init : function () {
  // ac.init() : start the alarm clock

    // Get the current time - hour, min, seconds

    ac.chr = document.getElementById("chr");
    ac.cmin = document.getElementById("cmin");
    ac.csec = document.getElementById("csec");

    ac.chr2 = document.getElementById("chr2");
    ac.cmin2 = document.getElementById("cmin2");
    ac.csec2 = document.getElementById("csec2");

    ac.chr3 = document.getElementById("chr3");
    ac.cmin3 = document.getElementById("cmin3");
    ac.csec3 = document.getElementById("csec3");

    ac.chr4 = document.getElementById("chr4");
    ac.cmin4 = document.getElementById("cmin4");
    ac.csec4 = document.getElementById("csec4");

    ac.chr5 = document.getElementById("chr5");
    ac.cmin5 = document.getElementById("cmin5");
    ac.csec5 = document.getElementById("csec5");
    // The time picker - Hr, Min, Sec
    ac.thr = ac.createSel(23);
    document.getElementById("tpick-h").appendChild(ac.thr);
    ac.thm = ac.createSel(59);
    document.getElementById("tpick-m").appendChild(ac.thm);
    ac.ths = ac.createSel(59);
    document.getElementById("tpick-s").appendChild(ac.ths);
    ac.thr_a = ac.createSel(23);
    document.getElementById("tpick-h_a").appendChild(ac.thr_a);
    ac.thm_a = ac.createSel(59);
    document.getElementById("tpick-m_a").appendChild(ac.thm_a);
    ac.ths_a = ac.createSel(59);
    document.getElementById("tpick-s_a").appendChild(ac.ths_a);

    ac.thr2 = ac.createSel(23);
    document.getElementById("tpick-h2").appendChild(ac.thr2);
    ac.thm2 = ac.createSel(59);
    document.getElementById("tpick-m2").appendChild(ac.thm2);
    ac.ths2 = ac.createSel(59);
    document.getElementById("tpick-s2").appendChild(ac.ths2);
    ac.thr2_a = ac.createSel(23);
    document.getElementById("tpick-h2_a").appendChild(ac.thr2_a);
    ac.thm2_a = ac.createSel(59);
    document.getElementById("tpick-m2_a").appendChild(ac.thm2_a);
    ac.ths2_a = ac.createSel(59);
    document.getElementById("tpick-s2_a").appendChild(ac.ths2_a);

    ac.thr3 = ac.createSel(23);
    document.getElementById("tpick-h3").appendChild(ac.thr3);
    ac.thm3 = ac.createSel(59);
    document.getElementById("tpick-m3").appendChild(ac.thm3);
    ac.ths3 = ac.createSel(59);
    document.getElementById("tpick-s3").appendChild(ac.ths3);
    ac.thr3_a = ac.createSel(23);
    document.getElementById("tpick-h3_a").appendChild(ac.thr3_a);
    ac.thm3_a = ac.createSel(59);
    document.getElementById("tpick-m3_a").appendChild(ac.thm3_a);
    ac.ths3_a = ac.createSel(59);
    document.getElementById("tpick-s3_a").appendChild(ac.ths3_a);

    ac.thr4 = ac.createSel(23);
    document.getElementById("tpick-h4").appendChild(ac.thr4);
    ac.thm4 = ac.createSel(59);
    document.getElementById("tpick-m4").appendChild(ac.thm4);
    ac.ths4 = ac.createSel(59);
    document.getElementById("tpick-s4").appendChild(ac.ths4);
    ac.thr4_a = ac.createSel(23);
    document.getElementById("tpick-h4_a").appendChild(ac.thr4_a);
    ac.thm4_a = ac.createSel(59);
    document.getElementById("tpick-m4_a").appendChild(ac.thm4_a);
    ac.ths4_a = ac.createSel(59);
    document.getElementById("tpick-s4_a").appendChild(ac.ths4_a);

    ac.thr5 = ac.createSel(23);
    document.getElementById("tpick-h5").appendChild(ac.thr5);
    ac.thm5 = ac.createSel(59);
    document.getElementById("tpick-m5").appendChild(ac.thm5);
    ac.ths5 = ac.createSel(59);
    document.getElementById("tpick-s5").appendChild(ac.ths5);
    ac.thr5_a = ac.createSel(23);
    document.getElementById("tpick-h5_a").appendChild(ac.thr5_a);
    ac.thm5_a = ac.createSel(59);
    document.getElementById("tpick-m5_a").appendChild(ac.thm5_a);
    ac.ths5_a = ac.createSel(59);
    document.getElementById("tpick-s5_a").appendChild(ac.ths5_a);
    // The time picker - Set, reset
    ac.tset = document.getElementById("tset");
    ac.tset.addEventListener("click", ac.set);
    ac.treset = document.getElementById("treset");
    ac.treset.addEventListener("click", ac.reset);

    ac.tset2 = document.getElementById("tset2");
    ac.tset2.addEventListener("click", ac.set2);
    ac.treset2 = document.getElementById("treset2");
    ac.treset2.addEventListener("click", ac.reset2);

    ac.tset3 = document.getElementById("tset3");
    ac.tset3.addEventListener("click", ac.set3);
    ac.treset3 = document.getElementById("treset3");
    ac.treset3.addEventListener("click", ac.reset3);

    ac.tset4 = document.getElementById("tset4");
    ac.tset4.addEventListener("click", ac.set4);
    ac.treset4 = document.getElementById("treset4");
    ac.treset4.addEventListener("click", ac.reset4);

    ac.tset5 = document.getElementById("tset5");
    ac.tset5.addEventListener("click", ac.set5);
    ac.treset5 = document.getElementById("treset5");
    ac.treset5.addEventListener("click", ac.reset5);


    // The alarm sound
    ac.sound = document.getElementById("alarm-sound");
    ac.sound2 = document.getElementById("alarm-sound2");
   	ac.sound3 = document.getElementById("alarm-sound3");
    ac.sound4 = document.getElementById("alarm-sound4");
    ac.sound5 = document.getElementById("alarm-sound5");


    // Start the clock
    ac.alarm = null;
    ac.alarm_a = null;
    ac.alarm2= null;
    ac.alarm2_a= null;
    ac.alarm3 = null;
    ac.alarm3_a = null;
    ac.alarm4= null;
    ac.alarm4_a= null;
    ac.alarm5= null;
    ac.alarm5_a= null;
    setInterval(ac.tick, 1000);
  },

  createSel : function (max) {
  // createSel() : support function - creates a selector for hr, min, sec

    var selector = document.createElement("select");
    for (var i=0; i<=max; i++) {
      var opt = document.createElement("option");
      i = ac.padzero(i);
      opt.value = i;
      opt.innerHTML = i;
      selector.appendChild(opt);
    }
    return selector
  },


  padzero : function (num) {
  // ac.padzero() : support function - pads hr, min, sec with 0 if <10

    if (num < 10) { num = "0" + num; }
    else { num = num.toString(); }
    return num;
  },

  tick : function () {
  // ac.tick() : update the current time

    // Current time
    var now = new Date();
    var hr = ac.padzero(now.getHours());
    var min = ac.padzero(now.getMinutes());
    var sec = ac.padzero(now.getSeconds());

    // Update current clock
    ac.chr.innerHTML = ac.chr2.innerHTML= ac.chr3.innerHTML= ac.chr4.innerHTML = ac.chr5.innerHTML = hr;
    ac.cmin.innerHTML = ac.cmin2.innerHTML = ac.cmin3.innerHTML = ac.cmin4.innerHTML = ac.cmin5.innerHTML = min;
    ac.csec.innerHTML = ac.csec2.innerHTML = ac.csec3.innerHTML = ac.csec4.innerHTML = ac.csec5.innerHTML = sec;

    // Check and sound alarm
    if (ac.alarm != null || ac.alarm_a != null ) {
      now = hr + min + sec;
       var data={}
      if (now == ac.alarm) {
        data.id = "off1";        
        document.lamp1.src="images/0_0.png";
        document.form1.checkbox1.checked = false;
        $.ajax({
            type: "POST",
            url: "test.php",
            data: data,
        });
      }
      if (now == ac.alarm_a) {
        data.id = "on1";        
        document.lamp1.src="images/1_0.png";
        document.form1.checkbox1.checked = true;
        $.ajax({
            type: "POST",
            url: "test.php",
            data: data,
        });
      }
  }
    if (ac.alarm2 != null || ac.alarm2_a != null) {
      now = hr + min + sec;
      var data={}
      if (now == ac.alarm2) {
        data.id = "off2"
        document.lamp2.src="images/0_0.png";
        document.form2.checkbox2.checked = false;
        $.ajax({
            type: "POST",
            url: "test.php",
            data: data,
        });
      }
      if(now == ac.alarm2_a){
        data.id="on2";
        document.lamp2.src="images/1_0.png";
        document.form2.checkbox2.checked = true;
        $.ajax({
            type: "POST",
            url: "test.php",
            data: data,
        });
    }
    }
    if (ac.alarm3 != null || ac.alarm3_a != null) {
      now = hr + min + sec;
      var data={}
      if (now == ac.alarm3) {
        data.id = "close"
          document.tirai.src="images/curtain_closed.jpg";
          document.form3.checkbox3.checked = false;
        $.ajax({
            type: "POST",
            url: "test.php",
            data: data,
        });
        }
      if(now==ac.alarm3_a){
        data.id = "open"
        document.tirai.src="images/curtain_open.jpg";
        document.form3.checkbox3.checked = true;
        $.ajax({
            type: "POST",
            url: "test.php",
            data: data,
        });        
      }

    }
    if (ac.alarm4 != null || ac.alarm4_a != null) {
      now = hr + min + sec;
      var data={}
      if (now == ac.alarm4_a) {
        cek=true;
        data.id = "on3";
        data.rgb = document.getElementById("bulb").value;
        if (data.rgb== "green") {
          document.rgb.src = "images/green.png";
        }
        else if (data.rgb== "white") {
          document.rgb.src = "images/white.png";
        }
        else if (data.rgb== "blue") {
          document.rgb.src = "images/blue.png";
        }
        else if (data.rgb== "red") {
          document.rgb.src = "images/red.png";
        }
        else if (data.rgb== "orange") {
          document.rgb.src = "images/orange.png";
        }
        else if (data.rgb== "yellow") {
          document.rgb.src = "images/yellow.png";
        }
        document.form4.checkbox4.checked = true;  
      $.ajax({
          type: "POST",
          url: "test.php",
          data: data,
      });
     } 
    }
    if(now == ac.alarm4){
      data.id="off3";
      document.rgb.src="images/0_0.png";
      document.form4.checkbox4.checked = false;
      $.ajax({
          type: "POST",
          url: "test.php",
          data: data,
      });
      }

    if (ac.alarm5 != null || ac.alarm5_a != null) {
      now = hr + min + sec;
      var data={}
      if (now == ac.alarm5) {
        data.id = "off5"
        document.colokan.src="images/colokan.jpg";
        document.form5.checkbox5.checked = false;c
        $.ajax({
            type: "POST",
            url: "test.php",
            data: data,
        });
      }
      if(now == ac.alarm5_a){
        data.id="on5";
        document.colokan.src="images/colokan1.jpg";
        document.form5.checkbox5.checked = true;
        $.ajax({
            type: "POST",
            url: "test.php",
            data: data,
        });
    }
    }
    
},

  set : function () {
  // ac.set() : set the alarm
    ac.alarm = ac.thr.value + ac.thm.value + ac.ths.value;
    ac.alarm_a = ac.thr_a.value + ac.thm_a.value + ac.ths_a.value;
    ac.thr.disabled = true;
    ac.thm.disabled = true;
    ac.ths.disabled = true;
    ac.thr_a.disabled = true;
    ac.thm_a.disabled = true;
    ac.ths_a.disabled = true;
    ac.tset.disabled = true;
    ac.treset.disabled = false;
  },

  set2 : function () {
  // ac.set() : set the alarm

    ac.alarm2 = ac.thr2.value + ac.thm2.value + ac.ths2.value;
    ac.alarm2_a = ac.thr2_a.value + ac.thm2_a.value + ac.ths2_a.value;
    ac.thr2.disabled = true;
    ac.thm2.disabled = true;
    ac.ths2.disabled = true;
    ac.thr2_a.disabled = true;
    ac.thm2_a.disabled = true;
    ac.ths2_a.disabled = true;
    ac.tset2.disabled = true;
    ac.treset2.disabled = false;
  },


  set3 : function () {
  // ac.set() : set the alarm

    ac.alarm3 = ac.thr3.value + ac.thm3.value + ac.ths3.value;
    ac.alarm3_a = ac.thr3_a.value + ac.thm3_a.value + ac.ths3_a.value;
    ac.thr3.disabled = true;
    ac.thm3.disabled = true;
    ac.ths3.disabled = true;
    ac.thr3_a.disabled = true;
    ac.thm3_a.disabled = true;
    ac.ths3_a.disabled = true;
    ac.tset3.disabled = true;
    ac.treset3.disabled = false;
  },


  set4 : function () {
  // ac.set() : set the alarm

    ac.alarm4 = ac.thr4.value + ac.thm4.value + ac.ths4.value;
    ac.alarm4_a = ac.thr4_a.value + ac.thm4_a.value + ac.ths4_a.value;
    document.getElementById("bulb").disabled = true;
    ac.thr4.disabled = true;
    ac.thm4.disabled = true;
    ac.ths4.disabled = true;
    ac.thr4_a.disabled = true;
    ac.thm4_a.disabled = true;
    ac.ths4_a.disabled = true;
    ac.tset4.disabled = true;
    ac.treset4.disabled = false;
  },

  set5 : function () {
  // ac.set() : set the alarm

    ac.alarm5 = ac.thr5.value + ac.thm5.value + ac.ths5.value;
    ac.alarm5_a = ac.thr5_a.value + ac.thm5_a.value + ac.ths5_a.value;
    ac.thr5.disabled = true;
    ac.thm5.disabled = true;
    ac.ths5.disabled = true;
    ac.thr5_a.disabled = true;
    ac.thm5_a.disabled = true;
    ac.ths5_a.disabled = true;
    ac.tset5.disabled = true;
    ac.treset5.disabled = false;
  },
  reset : function () {
  // ac.reset() : reset the alarm

    if (!ac.sound.paused) {
      ac.sound.pause();
    }
    ac.alarm = null;
    ac.alarm_a = null;
    ac.thr.disabled = false;
    ac.thm.disabled = false;
    ac.ths.disabled = false;
    ac.thr_a.disabled = false;
    ac.thm_a.disabled = false;
    ac.ths_a.disabled = false;
    ac.tset.disabled = false;
    ac.treset.disabled = true;
  },

  reset2 : function () {
  // ac.reset() : reset the alarm

    if (!ac.sound2.paused) {
      ac.sound2.pause();
    }
    ac.alarm2 = null;
    ac.alarm2_a = null;
    ac.thr2.disabled = false;
    ac.thm2.disabled = false;
    ac.ths2.disabled = false;
    ac.thr2_a.disabled = false;
    ac.thm2_a.disabled = false;
    ac.ths2_a.disabled = false;
    ac.tset2.disabled = false;
    ac.treset2.disabled = true;
  },

  reset3 : function () {
  // ac.reset() : reset the alarm

    if (!ac.sound3.paused) {
      ac.sound3.pause();
    }
    ac.alarm3 = null;
    ac.alarm3_a = null;
    ac.thr3.disabled = false;
    ac.thm3.disabled = false;
    ac.ths3.disabled = false;
    ac.thr3_a.disabled = false;
    ac.thm3_a.disabled = false;
    ac.ths3_a.disabled = false;
    ac.tset3.disabled = false;
    ac.treset3.disabled = true;
  },

  reset4 : function () {
  // ac.reset() : reset the alarm

    if (!ac.sound4.paused) {
      ac.sound4.pause();
    }
    ac.alarm4 = null;
    ac.alarm4_a = null;
    ac.thr4.disabled = false;
    ac.thm4.disabled = false;
    ac.ths4.disabled = false;
    document.getElementById("bulb").disabled = false;
    ac.thr4_a.disabled = false;
    ac.thm4_a.disabled = false;
    ac.ths4_a.disabled = false;
    ac.tset4.disabled = false;
    ac.treset4.disabled = true;
  },
  reset5 : function () {
  // ac.reset() : reset the alarm

    if (!ac.sound5.paused) {
      ac.sound5.pause();
    }
    ac.alarm5 = null;
    ac.alarm5_a = null;
    ac.thr5.disabled = false;
    ac.thm5.disabled = false;
    ac.ths5.disabled = false;
    ac.thr5_a.disabled = false;
    ac.thm5_a.disabled = false;
    ac.ths5_a.disabled = false;
    ac.tset5.disabled = false;
    ac.treset5.disabled = true;
  }
};

// INIT - RUN ALARM CLOCK
window.addEventListener("load", ac.init);
	//https://www.webdeveloper.com/d/73662-swap-image-by-clicking-on-checkbox
function changePic1(){
var data={}  
if (document.form1.checkbox1.checked){
data.id="on1";
document.lamp1.src="images/1_0.png";
}
else{
data.id="off1";
document.lamp1.src="images/0_0.png";
}
$.ajax({
    type: "POST",
    url: "test.php",
    data: data,
});
}
function changePic2(){
var data={}  
if (document.form2.checkbox2.checked){
data.id="on2";
document.lamp2.src="images/1_0.png";
}
else{
data.id="off2";
document.lamp2.src="images/0_0.png";
}
$.ajax({
    type: "POST",
    url: "test.php",
    data: data,
});
}
function changePic5(){
var data={}  
if (document.form5.checkbox5.checked){
data.id="on5";
document.colokan.src="images/colokan1.jpg";
}
else{
data.id="off5";
document.colokan.src="images/colokan.jpg";
}
$.ajax({
    type: "POST",
    url: "test.php",
    data: data,
});
}
function changePic4(){
var data={}
if (document.form4.checkbox4.checked){
  cek=true;
  data.id="on3";
  if(file==null){
    alert("pilih warna terlebih dahulu");
    document.form4.checkbox4.checked = false;
    cek=false;
    data.id = "off3";
  }
  else{
  document.rgb.src=file;    
  }


}else{
document.rgb.src="images/0_0.png";
cek=false;
data.id="off3";
}

  data.rgb="null";
  $.ajax({
    type: "POST",
    url: "test.php",
    data: data,
});
}
function curtain_co(){
var data={}  
if (document.form3.checkbox3.checked){
data.id="open";
document.tirai.src="images/curtain_open.jpg";
}else{
data.id="close";
document.tirai.src="images/curtain_closed.jpg";
}
$.ajax({
    type: "POST",
    url: "test.php",
    data: data,
});
}
function ckChange(ckType){
    var ckName = document.getElementsByName(ckType.name);
    var checked = document.getElementById(ckType.id);
    var data={};
    if (checked.checked) {
      for(var i=0; i < ckName.length; i++){

          if(!ckName[i].checked){
              ckName[i].disabled = true;
          }else{
            if (checked.id== "green") {
              file = "images/green.png";
            }
            else if (checked.id== "white") {
              file = "images/white.png";
            }
            else if (checked.id== "blue") {
              file = "images/blue.png";
            }
            else if (checked.id== "red") {
              file = "images/red.png";
            }
            else if (checked.id== "orange") {
              file = "images/orange.png";
            }
            else if (checked.id== "yellow") {
              file = "images/yellow.png";
            }                                                     
              ckName[i].disabled = false;
          }
      }
      if (cek) {          
        document.rgb.src=file;
        } 
    }
    else {
      for(var i=0; i < ckName.length; i++){
        ckName[i].disabled = false;
      } 
    }
    data.rgb=checked.id;
    data.id="null";
    $.ajax({
    type: "POST",
    url: "test.php",
    data: data,
});
}


