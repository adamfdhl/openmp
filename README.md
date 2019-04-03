# Tugas Praktikum 1 IF3230 - OpenMP #
 1. Adam Fadhel Ramdhan - 13516054
 2. Krishna Aurelio N. - 13516108

# Cara Menjalankan Program #
1. ketik "make" pada compiler untuk melakukan compile program
2. ketik "./radix_sort N" tanpa tanda petik dan N sebagai ukuran array yang ingin di-sort.

# Pembagian Tugas #
1. Adam Fadhel Ramadhan : membuat fungsi getExpMax, README, Makefile, time execution.
2. Krishna Aurelio N : membuat radixSort, countSort, getMax

# LAPORAN PENGERJAAN #

## Deskripsi Solusi Paralel ##
Radix Sort merupakan salah satu metode sorting di mana proses sorting dimulai dari digit pertama dilakukan sort kemudian maju ke digit selanjutnya untuk di-sort dan seterusnya sampai digit terakhir. Pada normalnya, digit yang di-sort merupakan digit satuan terlebih dahulu dan maju ke digit ratusan, ribuan, dan seterusnya. Namun pada solusi yang dibuat kali ini, digit yang di-sort akan dimulai dari most significant digit. 

Progam pertama-tama akan melakukan sort mulai dari most significant digit. Setelah di-sort, program akan melakukan "grouping" elemen-elemen array berdasarkan digit hasil sort sebelumnya, dalam hal ini berdasarkan most significant digit. Grouping dilakukan secara terurut membesar.

Contoh :
arr = [237, 318, 216, 462, 211, 268, 460]
1. Lakukan sort digit pertama dan dilakukan "grouping: sehingga array menjadi
    arr = [237, 216, 211, 268, 318, 462, 460]
2. Sort selanjutnya dilakukan pada masing-masing group. Misal pada group dengan angka pertama 2 menjadi : 216, 211, 237, 268.
3. Lakukan "grouping" lagi pada digit selanjutnya dan lakukan sort lagi.
4. Lakukan step 1-3 hingga seluruh elemen array terurut membesar.

Paralel yang digunakan ialah pada saat sorting antar group tersebut. Masing-masing group dalam proses sortingnya diberikan thread sendiri sehingga proses akan berjalan secara paralel.

Solusi yang diberikan ini mungkin bukan merupakan solusi yang terbaik, namun masih lebih cepat dibandingkan dengan menggunakan cara serial.

Jumlah thread yang digunakan bergantung pada elemen array yang akan diurutkan.

## Pengukuran Kinerja ##

### Paralel ###
1. Kasus Uji N = 5.000
    Time execution: 0.001093
2. Kasus Uji N = 50.000
    Time execution: 0.015311
3. kasus Uji N = 100.000
    Time execution: 0.025923
4. Kasus Uji N = 200.000
    Time execution: 0.044808
5. Kasus Uji N = 400.000
    Time execution: 0.069388

### Serial ###
1. Kasus Uji N = 5.000
    Time execution: 0.001523
2. Kasus Uji N = 50.000
    Time execution: 0.019279
3. kasus Uji N = 100.000
    Time execution: 0.030890
4. Kasus Uji N = 200.000
    Time execution: 0.063287
5. Kasus Uji N = 400.000
    Time execution: 0.136445

## Analisis Perbandingan Kinerja Paralel dan Serial ##
Pada hasil pengujian sebelumnya, dapat dilihat bahwa waktu eksekusi paralel berjalan lebih cepat dibandingkan waktu eksekusi serial. Hal tersebut diakibatkan oleh setiap proses "grouping" dan sorting yang dilakukan, digunakan beberapa thread yang dijalankan secara bersamaan. Akibatnya waktu yang diperlukan untuk melakukan pengurutan dapat lebih diminimalkan. Namun tetap saja solusi ini bukanlah solusi yang tercepat.