# C1 Proyek 2 - Markdown Kelompok

**Jurusan**: Teknik Komputer dan Informatika  
**Program Studi**: D3 - Teknik Informatika

**Proyek Manager**: Pa Yudi Widhiyasana

## Anggota:
- **ERSYA HASBY SATRIA** - 241511072 - ErsyaHasby
- **YAZID ALRASYID** - 241511093 - yajidms
- **NIKE KUSTIANE** - 241511086 - nxmgh27
- **AZKHA NAZZALA PRASADHA DIES** - 241511069 - alatteee
- **ANDHINI WIDYA PUTRI WASTIKA** - 241511068 - andhinwdyp

## Target Proyek:
Menyelesaikan proyek 2 pembuatan game dengan judul **C1 Brick Racer**.

## Pembagian Tugas:

### Header Files:
- **Ersya** - `menu.h` `high_score.h`
- **Ala**   - `mobil.h`, `lives.h`
            - Membuat level pada game
- **Nike**  - `jalur.h`
- **Andin** - `skor.h`
- **Yazid** - `rintangan.h`

---

### Tutorial Instalasi Game:


## Gameplay C1 Brick Racer

**C1 Brick Racer** adalah game balapan mobil di mana pemain harus menghindari rintangan yang muncul di sepanjang jalur balapan hingga mencapai garis finish untuk menang. Pemain harus bertahan selama mungkin dan mencapai garis finish tanpa menabrak rintangan.

### Tujuan Pemain:
- **Menghindari rintangan** yang muncul di sepanjang jalan.
- **Mencapai garis finish** tanpa menabrak rintangan untuk menang.
- Menyelesaikan setiap level dengan bertahan lebih lama dan tanpa kehilangan nyawa.

### Kontrol:
- **Arrow Keys**: Menggerakkan mobil ke kiri atau kanan untuk menghindari rintangan.
- **Enter**: Memulai permainan atau melanjutkan permainan setelah menang.
- **Escape**: Keluar dari permainan.

### Level dan Kesulitan:
Terdapat tiga level dengan tingkat kesulitan yang berbeda, dan perbedaannya terletak pada **kecepatan rintangan** yang semakin cepat seiring bertambahnya level:

1. **Level 1 (Easy)**:
   - Rintangan lebih sedikit.
   - Kecepatan rintangan lebih lambat, sehingga lebih mudah untuk menghindari rintangan.
   
2. **Level 2 (Medium)**:
   - Rintangan lebih banyak.
   - Kecepatan rintangan meningkat, membuat game lebih menantang.

3. **Level 3 (Hard)**:
   - Rintangan lebih banyak dan lebih cepat.
   - Kecepatan rintangan sangat tinggi, membuat game menjadi lebih sulit dan membutuhkan reaksi yang cepat.

### Mekanik Game:
- **Rintangan**: Rintangan akan muncul secara acak di sepanjang jalan. Pemain harus menghindari tabrakan dengan rintangan. Setiap kali mobil menabrak rintangan, pemain akan kehilangan satu nyawa.
- **Nyawa**: Pemain memiliki **tiga nyawa**. Jika nyawa habis, permainan berakhir.
- **Skor**: Setiap rintangan yang berhasil dihindari akan menambah skor pemain. Skor ini akan terus bertambah seiring berjalannya permainan.

### Menang:
- Pemain menang ketika berhasil mencapai **garis finish** tanpa menabrak rintangan dan dengan nyawa yang tersisa.

### Musik dan Suara:
- Musik latar dapat diaktifkan atau dinonaktifkan melalui menu utama.
- Efek suara muncul ketika mobil menabrak rintangan atau saat mencapai garis finish.
