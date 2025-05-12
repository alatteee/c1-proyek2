# 🏎️ C1 Brick Racer 🧱

![image](https://github.com/alatteee/c1-proyek2/blob/docs-c1/docs/image/015533.png)

---

## 🧑‍💻 Tim Pengembang

Proyek ini dikembangkan sebagai bentuk tugas Proyek 2 oleh mahasiswa D3 Teknik Informatika, Jurusan Teknik Komputer dan Informatika.

* **Manajer Proyek**: Yudi Widhiyasana, S.ST., M.T.

* **Anggota Kelompok**:

| No  | Anggota                                                                        | NIM       |
| --- | -------------------------------------------------------------------------------| --------- |
| 1   | **ANDHINI WIDYA PUTRI WASTIKA** ([@andhinwdyp](https://github.com/andhinwdyp)) | 241511068 |
| 2.  | **AZKHA NAZZALA PRASADHA DIES** ([@alateee](https://github.com/alatteee))      | 241511069 |
| 3.  | **ERSYA HASBY SATRIA** ([@ErsyaHasby](https://github.com/ErsyaHasby))          | 241511072 |
| 4.  | **NIKE KUSTIANE** ([@nxmgh27](https://github.com/nxmgh27))                     | 241511086 |
| 5.  | **YAZID ALRASYID** ([@yajidms](https://github.com/yajidms))                    | 241511093 |

### Target Proyek:
Menyelesaikan proyek 2 pembuatan game dengan judul **C1 Brick Racer**.

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
    * ⬆️ **Tombol Panah Atas**: Gerakkan mobil ke atas.
    * ⬇️ **Tombol Panah Bawah**: Gerakkan mobil ke bawah.
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
    git clone <https://github.com/alatteee/c1-proyek2>
    cd <c1-proyek2>
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
        make run
        ```
    * **Manual**:
        ```bash
        gcc main.c src/*.c -o c1_brick_racer -Iinclude -L/path/to/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lm -lpthread -lwinpthread
        ```
4.  **Jalankan**:
    ```bash
    ./racing_game
    ```
    atau di Windows:
    ```bash
    .\racing_game.exe
    ```

---
