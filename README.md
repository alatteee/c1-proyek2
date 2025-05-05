# 🏎️ C1 Brick Racer 🧱

**Selamat datang di C1 Brick Racer! Sebuah permainan balap 2D yang menantang kecepatan dan ketangkasan Anda. Hindari rintangan unik, kumpulkan skor, dan capai garis finis!**

*(Disarankan: Tambahkan GIF atau Screenshot gameplay di sini)*

---

## 🧑‍💻 Tim Pengembang

Proyek ini dikembangkan sebagai tugas Proyek 2 oleh mahasiswa D3 Teknik Informatika, Jurusan Teknik Komputer dan Informatika.

* **Manajer Proyek**: Yudi Widhiyasana, S.ST., M.T.
* **Anggota**:
    * ERSYA HASBY SATRIA (241511072) - `ErsyaHasby`
    * YAZID ALRASYID (241511093) - `yajidms`
    * NIKE KUSTIANE (241511086) - `nxmgh27`
    * AZKHA NAZZALA PRASADHA DIES (241511069) - `alatteee`
    * ANDHINI WIDYA PUTRI WASTIKA (241511068) - `andhinwdyp`

---

## ✨ Fitur Utama

* **Gameplay Balap**: Fokus pada menghindari rintangan dan mencapai garis finis.
* **Rintangan**: Menghadapi rintangan yang muncul didepan.
* **Pilihan Mobil Variatif**: Pilih mobil dari beberapa opsi (biasa/sport) sebelum memulai balapan.
* **Level Kesulitan**: Tersedia level Easy, Medium, dan Hard, yang mempengaruhi kecepatan rintangan.
* **Sistem Skor**: Peroleh skor untuk setiap rintangan yang berhasil dilewati.
* **Sistem Nyawa**: Mulai dengan 3 nyawa; tabrakan akan mengurangi nyawa.
* **Papan Skor Tertinggi (High Score)**: Catat nama dan skormu jika masuk dalam 10 besar.
* **Musik Latar**: Opsi untuk mengaktifkan atau menonaktifkan musik latar permainan.
* **Berbasis Raylib**: Dikembangkan menggunakan library C Raylib.

---

## 🎮 Panduan Bermain

1.  **Persiapan**: Jalankan game, masukkan nama pemain, pilih level kesulitan, dan pilih mobil yang diinginkan.
2.  **Kontrol**:
    * ⬅️ **Tombol Panah Kiri**: Gerakkan mobil ke kiri.
    * ➡️ **Tombol Panah Kanan**: Gerakkan mobil ke kanan.
    * *(Opsional)* ⬆️ **Tombol Panah Atas**: Gerakkan mobil ke atas.
    * *(Opsional)* ⬇️ **Tombol Panah Bawah**: Gerakkan mobil ke bawah.
    * **Enter**: Konfirmasi pilihan menu atau lanjut setelah permainan usai.
    * **Esc**: Keluar dari permainan atau kembali ke menu utama.
3.  **Navigasi & Rintangan**: Rintangan akan muncul dari arah atas layar. Arahkan mobil untuk menghindarinya.
4.  **Garis Finis**: Setelah periode waktu tertentu (sekitar 10 detik), garis finis akan terlihat. Capai garis ini untuk menyelesaikan level.
5.  **Skor & Nyawa**: Skor bertambah saat melewati rintangan. Nyawa berkurang saat terjadi tabrakan. Permainan berakhir jika nyawa habis.
6.  **Status Akhir**:
    * **Menang**: Berhasil mencapai garis finis dengan sisa nyawa.
    * **Kalah (Game Over)**: Kehabisan nyawa sebelum mencapai garis finis.
7.  **Pencatatan Skor**: Skor akhir akan dicatat di papan skor tertinggi jika memenuhi kriteria.

---

## 🔧 Instalasi & Menjalankan

1.  **Clone Repository**:
    ```bash
    git clone <URL_REPOSITORY_ANDA>
    cd <NAMA_FOLDER_REPOSITORY>
    ```
2.  **Prasyarat**:
    * Compiler C (misalnya GCC, MinGW, Clang).
    * Library Raylib terinstal.
        * **Windows**: Ikuti [panduan Raylib untuk Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows).
        * **Linux (Ubuntu/Debian)**: `sudo apt install libraylib-dev`
        * **MacOS**: `brew install raylib`
3.  **Kompilasi**:
    * **Via Makefile (Direkomendasikan)**:
        ```bash
        make
        ```
    * **Manual**:
        ```bash
        gcc main.c src/*.c -o c1_brick_racer -Iinclude -L/path/to/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lm -lpthread -lwinpthread
        ```
        *(Sesuaikan `-L/path/to/raylib/lib` jika diperlukan, terutama jika Raylib tidak diinstal di path standar).*
4.  **Jalankan**:
    ```bash
    ./c1_brick_racer
    ```
    atau di Windows:
    ```bash
    .\c1_brick_racer.exe
    ```

---

Selamat bermain C1 Brick Racer! Semoga Anda menikmati permainannya! 🏆
