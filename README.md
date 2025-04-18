# 🌊 Smart Waste Gutter Manager 🚀

**Smart Waste Gutter Manager** adalah project IoT berbasis **ESP32** yang memanfaatkan sensor ultrasonic buat deteksi ketinggian air atau sampah di saluran (got/sumur/tong sampah), lalu ngontrol **servo motor** buat buka-tutup otomatis. Data real-time bisa dipantau via **Ubidots Dashboard**, plus bisa ngirim notifikasi ke **Telegram** kalo kondisi penuh. Project ini cocok buat solusi smart city atau sistem monitoring otomatis.(masih prototype btw)

---

## 📸 Demo  
![Dashboard Preview](images/dashboard-preview.png)

---

## 📖 Table of Contents  
- [✨ Fitur](#-fitur)
- [🛠️ Tools, Platform & API](#-tools-platform--api)
- [⚙️ Hardware & Komponen](#-hardware--komponen)
- [📥 Instalasi & Setup](#-instalasi--setup)
- [🔍 Cara Kerja](#-cara-kerja)


---

## ✨ Fitur
- Deteksi jarak menggunakan JSN-SR04T / HC-SR04
- Kontrol servo otomatis (buka/tutup)
- Kirim data ke **Ubidots Cloud**
- Notifikasi Telegram saat kondisi penuh
- Monitoring via **Ubidots Dashboard**(kalau iot terpasang)

---

## 🛠️ Tools, Platform & API

### 🛠️ Tools  
- **Arduino IDE**  
- **Serial Monitor**

### 📡 Platform  
- **Ubidots**  
- **MGX** *(opsional buat custom dashboard)*

### 🔗 API  
- **Ubidots Device API**  
- **Telegram Bot API**

---

## ⚙️ Hardware & Komponen
- 1x ESP32 Dev Module  
- 1x JSN-SR04T atau HC-SR04 Ultrasonic Sensor  
- 1x SG90 Servo Motor  
- Kabel Jumper  
- WiFi hotspot / router  

---

## 📥 Instalasi & Setup

### 1️⃣ Install Library di Arduino IDE  
- `WiFi.h`  
- `HTTPClient.h`  
- `ESP32Servo.h`  

### 2️⃣ Buat Akun & Setup Device di Ubidots  
- Daftar di [Ubidots](https://industrial.ubidots.com/)
- Buat **Device**
- Catat **Token** dan **Device API Label**
- Tambahkan variable misal `jarak`

### 3️⃣ Setting Telegram Bot  
- Cari **@BotFather** di Telegram  
- Buat bot baru  
- Simpan **Token API** bot  
- Catat chat ID (bisa pake [IDBot](https://t.me/myidbot))

### 4️⃣ Upload Kode ke ESP32  
- Ganti `ssid`, `password`, `token`, `deviceLabel`, dan `chatId` di kode sesuai konfigurasi lu  
- Upload ke board  

---

## 🔍 Cara Kerja

- Sensor ultrasonic ngukur jarak permukaan air / sampah  
- Nilai jarak dikirim ke **Ubidots** tiap interval  
- Jika jarak di bawah threshold, servo buka/tutup otomatis  
- Jika kondisi penuh (jarak < batas aman), kirim notif ke **Telegram**  

---


