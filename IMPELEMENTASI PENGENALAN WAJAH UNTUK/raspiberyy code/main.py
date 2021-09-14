#!/usr/bin/python3

# PENGGUNAAN
# python face-recognition-video.py --cascade haarcascade_frontalface_default.xml --encodings encodings.pickle

# import library yang di perlukan
from imutils.video import VideoStream
from imutils.video import FPS
import RPi.GPIO as GPIO
import face_recognition
import argparse
import imutils
import pickle
import time
import cv2
import requests
from datetime import datetime

# Parsing Argumen
timer = 120
timerr = 15
timer_pintu=60
pintu = 36
buzzer = 15
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(pintu,GPIO.OUT)
GPIO.setup(buzzer,GPIO.OUT)
GPIO.output(pintu, GPIO.HIGH)
GPIO.output(buzzer, GPIO.HIGH)
ap = argparse.ArgumentParser()
ap.add_argument("-c", "--cascade", required=True,
        help = "path to where the face cascade resides")
ap.add_argument("-e", "--encodings", required=True,
        help="path to serialized db of facial encodings")
args = vars(ap.parse_args())

# load pendeteksi wajah dari file cascade OpenCV
print("[INFO] loading encodings + face detector...")
data = pickle.loads(open(args["encodings"], "rb").read())
detector = cv2.CascadeClassifier(args["cascade"])
cek = True
time_start=0
time_start1=0
lastname=""
pintu_timer=0
cek_pintu=True
# Nyalakan Kamera
print("[INFO] Memulai Stream dari Pi Camera...")
vs = VideoStream(src=0).start()
time.sleep(2.0)

# Penghitung FPS (Frame per Second)
fps = FPS().start()

# loop dari semua frame yang di dapat
print("ready to detect")
while True:
        # dapatkan frame, dan resize ke 500pixel agar lebih cepat
        a = requests.get('http://databaseta.my.id/read.php?cek=0')
        if a.text == '1' and cek_pintu:
                pintu_timer=time.time()
                GPIO.output(pintu, GPIO.LOW)
                time.sleep(0.1)
#               GPIO.output(buzzer,GPIO.LOW)
                cek_pintu=False
        if time.time()-pintu_timer>4 and not cek_pintu:
                requests.get('http://databaseta.my.id/open_door.php?door=0')
#               GPIO.output(buzzer,GPIO.HIGH)
                time.sleep(0.1)
                GPIO.output(pintu,GPIO.HIGH)
                cek_pintu=True

        frame = vs.read()
        frame = imutils.resize(frame, width=500)

        # Konversi ke grayscale dan konversi ke RGB
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # deteksi wajah dari frame grayscale
        rects = detector.detectMultiScale(gray, scaleFactor=1.1,
                minNeighbors=5, minSize=(100, 100),
                flags=cv2.CASCADE_SCALE_IMAGE)

   # Tampilkan kotak di wajah yang dideteksi
        boxes = [(y, x + w, y + h, x) for (x, y, w, h) in rects]

        encodings = face_recognition.face_encodings(rgb, boxes)
        names = []

        # loop di semua wajah yang terdeteksi
        for encoding in encodings:
                path = "/home/pi/anggoro/gambar/"
                matches = face_recognition.compare_faces(data["encodings"],
                        encoding,tolerance=0.6)
                print(matches)
                name = "Unknown"

                # check apakah ada wajah yang di kenali
                if True in matches:
                        matchedIdxs = [i for (i, b) in enumerate(matches) if b]
                        counts = {}
                        for i in matchedIdxs:
                                name = data["names"][i]
                                counts[name] = counts.get(name, 0) + 1
                        name = max(counts, key=counts.get)
                names.append(name)

        for ((top, right, bottom, left), name) in zip(boxes, names):
                # tampilkan nama di wajah yang di kenali
                cv2.rectangle(frame, (left, top), (right, bottom),
                        (0, 255, 0), 2)
                y = top - 15 if top - 15 > 15 else top + 15
                cv2.putText(frame, name, (left, y), cv2.FONT_HERSHEY_SIMPLEX,
                        0.75, (0, 255, 0), 2)

                if name != lastname  or (time.time()-time_start) > timer:
                        time_start=time.time()
                        if  (time.time()-time_start1) > timerr:
                                time_start1=time.time()
                                lastname=name
                                timee = str(datetime.now().strftime("%d-%m-%Y %H-%M-%S"))
                                filename = name+"_"+timee+".jpg"
                                path = path + filename
                                cv2.imwrite(path,frame)
                                if name != "Unknown":
                                #       timee = str(datetime.now().strftime("%d-%m-%Y %H-%M-%S"))
                                        requests.get('http://databaseta.my.id/updatenotif.php?stat=' + name + " masuk ruangan pada waktu " + timee)
                                        requests.get('http://databaseta.my.id/updateJson.php?nama='+name+"&"+"waktu="+ "Masuk Ruangan Pada waktu "+timee+"&"+"imageurl="+"http://databaseta.my.id/gambar/"+filename)
                                        if cek_pintu:
                                                requests.get('http://databaseta.my.id/open_door.php?door=1')
                                        files = {'fileToUpload':open(path, 'rb')}
                                        requests.post("http://databaseta.my.id/upload.php",files=files)
                                else:
                                        requests.get('http://databaseta.my.id/updatenotif.php?stat=' + name + " masuk ruangan pada waktu " + timee)
                                        requests.get('http://databaseta.my.id/updateJson.php?nama='+name+"&"+"waktu="+ "Mencoba Masuk Ruangan Pada waktu "+timee+"&"+"imageurl="+"http://databaseta.my.id/gambar/"+filename)
                                        files = {'fileToUpload':open(path, 'rb')}
                                        requests.post("http://databaseta.my.id/upload.php",files=files)
                                        GPIO.output(buzzer,GPIO.LOW)
                                        time.sleep(0.5)
                                        GPIO.output(buzzer,GPIO.HIGH)
                                        time.sleep(0.5)
                                        GPIO.output(buzzer,GPIO.LOW)
                                        time.sleep(0.5)
                                        GPIO.output(buzzer,GPIO.HIGH)

        # Tampilkan gambar di layar
        cv2.imshow("Frame", frame)
        key = cv2.waitKey(1) & 0xFF

        # tunggu tombol 1 untuk keluar
        if key == ord("q"):
                break

        # update FPS
        fps.update()

#tampilkan info FPS
fps.stop()
print("[INFO] elasped time: {:.2f}".format(fps.elapsed()))
print("[INFO] approx. FPS: {:.2f}".format(fps.fps()))

# cleanup
cv2.destroyAllWindows()
vs.stop()