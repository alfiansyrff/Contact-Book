/*
 * Contact Book
 * Muhammad Nur Alfian Syarif (222112218)
 */

/*
 * NOTE : 
 * Diharap melakukan penghapusan file yang berisi data -
 * kontak agar saat dijalankan dapat terbaca maksimal. 
 * Karena pada beberapa kasus ketika di jalankan ulang -
 * setelah keluar dari menu, terdapat data yang tidak -
 * terbaca, Salah satu solusi adalah dengan menghapus -
 * file contactsBook.txt tersebut dan saat program di-
 * jalankan agar terbentuk file tersebut lagi.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
  char first_name[20];
  char last_name[20];
  int age;
  char gender[2];
  char telNo[20];
  char email[50];
  char city[30];

} Contact;


Contact contactsBook[100];
int contacts_count;

// Variabel Global untuk proses undo an redo
Contact lastRemovedItem;
Contact tempForEdit;
int lastOperation; // 1: insert, 2:delete, 3: edit
bool isUndoDone = false;
int prevContactsBookLength;
int getIndexUndoRedoEdit; 

bool isRedoDone = false;

// Fungsi validasi stack
bool isStackFull() {
  if (contacts_count >= 100) {
    return true;
  }
  return false;
}

// Fungsi Tambah Contact
void insertContact()
{
  Contact *contact = contactsBook + contacts_count;

  if (isStackFull() == true) {
    puts("Tidak dapat menambahkan kontak. Penyimpanan penuh!");
  } else {
    puts("Nama depan:");
    scanf("%s", &contact->first_name);

    puts("Nama belakang: ");
    scanf("%s", &contact->last_name);

    puts("Usia: ");
    scanf("%d", &contact->age);
    
    puts("Jenis Kelamin (L/P): ");
    scanf("%s", &contact->gender);
    
    puts("Nomor telepon: ");
    scanf("%s", &contact->telNo);
    
    puts("Email: ");
    scanf("%s", &contact->email);
    
    puts("Kota asal: ");
    scanf("%s", &contact->city);

    puts("Kontak Berhasil di simpan!.");
    contacts_count++;

    lastOperation = 1;
    isUndoDone = false;
    isRedoDone = false;
  }
}

// Fungsi edit kontak
void editContact(int getIndex)
{
  Contact *contact = contactsBook + getIndex;
  getIndexUndoRedoEdit = getIndex;

  if (getIndex >= contacts_count || getIndex < 0)
  {
    puts("Tidak ditemukan Kontak dengan ID tersebut!");
    return;
  }

  strcpy(lastRemovedItem.first_name, contact->first_name);
  strcpy(lastRemovedItem.last_name, contact->last_name);
  strcpy(lastRemovedItem.telNo, contact->telNo);
  lastRemovedItem.age = contact->age;
  strcpy(lastRemovedItem.city, contact->city);
  strcpy(lastRemovedItem.email, contact->email);
  strcpy(lastRemovedItem.gender, contact->gender);

  lastOperation = 3;
  isUndoDone = false;
  isRedoDone = false;

  printf("Nama depan sebelumnya: %s\n", contact->first_name);
  puts("Nama depan baru:");
  scanf("%s", &contact->first_name);

  printf("Nama belakang sebelumnya: %s\n", contact->last_name);
  puts("Nama belakang baru: ");
  scanf("%s", &contact->last_name);

  printf("Umur sebelumnya: %d\n", contact->age);
  puts("Umur baru: ");
  scanf("%d", &contact->age);

  printf("Jenis kelamin sebelumnya: %s\n", contact->gender);
  puts("Jenis kelamin baru (L/P): ");
  scanf("%s", &contact->gender);

  printf("Nomor telepon sebelumnya: %s\n", contact->telNo);
  puts("Nomor telepon baru: ");
  scanf("%s", &contact->telNo);

  printf("email sebelumnya: %s\n", contact->email);
  puts("email baru: ");
  scanf("%s", &contact->email);

  printf("Kota sebelumnya: %s\n", contact->city);
  puts("Kota baru: ");
  scanf("%s", &contact->city);

  puts("Kontak berhasil diperbarui.");
}

// Fungsi hapus kontak
void deleteContact(int getIndex)
{
  Contact *contact, *last, *l;

  if (getIndex >= contacts_count || getIndex < 0)
  {
    puts("Tidak ditemukan Kontak dengan ID tersebut!");
    return;
  }

  contact = contactsBook + getIndex;
  last = contactsBook + contacts_count - 1 ;
  l = contactsBook + contacts_count; 

  strcpy(contact->first_name, last->first_name);
  strcpy(contact->last_name, last->last_name);
  strcpy(contact->telNo, last->telNo);
  contact->age = last->age;
  strcpy(contact->city, last->city);
  strcpy(contact->email, last->email);
  strcpy(contact->gender, last->gender);
  strcpy(lastRemovedItem.first_name, l->first_name);
  strcpy(lastRemovedItem.last_name, l->last_name);
  strcpy(lastRemovedItem.telNo, l->telNo);
  lastRemovedItem.age = l->age;
  strcpy(lastRemovedItem.city, l->city);
  strcpy(lastRemovedItem.email, l->email);
  strcpy(lastRemovedItem.gender, l->gender);
  prevContactsBookLength = contacts_count;
  contacts_count--;
  printf("Kontak dengan nomor telepon %s berhasil dihapus", contact->telNo);
  lastOperation = 2;
  isUndoDone = false;
  isRedoDone = false;
}

void show_contacts()
{
  int i;
  puts("ID | Nama | Nomor | Umur | JK | Email | Kota");
  for (i = 0; i < contacts_count; i++)
  {
    printf("%i | %s %s | %s | %d | %s | %s | %s\n", i + 1, contactsBook[i].first_name, contactsBook[i].last_name, contactsBook[i].telNo, contactsBook[i].age, contactsBook[i].gender, contactsBook[i].email, contactsBook[i].city);
  }
}

// Fungsi search by first name
void searchByfname() {
  char getfname[20];
  bool found = false;
  int i = 0;

  printf("Masukkan nama depan: ");
  scanf("%s", getfname);

  for (i = 0; i < contacts_count; i++) {
    if (strcmp(getfname, contactsBook[i].first_name) == 0)
    {
      found = true;
      break;
    }
  }
  if (found == false)
    printf("\t\nKontak tidak ditemukan!");
  else
  {
    printf("\t\nKontak dengan nama depan %s ditemukan! Detail kontak: ", getfname);
    // printf("\n\nCantact %2.2d{", i + 1);
    printf("\n\t Nama: %s %s\n\t Umur: %d\n\t Jenis kelamin: %s\n\t Email: %s\n\t Kota: %s\n\t No. telephone :%s\n\t", contactsBook[i].first_name, contactsBook[i].last_name, contactsBook[i].age, contactsBook[i].gender, contactsBook[i].email, contactsBook[i].city, contactsBook[i].telNo);
  }
}

// Fungsi search by last name
void searchBylname()
{
  char getlname[20];
  bool found = false;
  int i = 0;

  printf("Masukkan nama belakang: ");
  scanf("%s", getlname);

  for (i = 0; i < contacts_count; i++)
  {
    if (strcmp(getlname, contactsBook[i].last_name) == 0)
    {
      found = true;
      break;
    }
  }
  if (found == false)
    printf("\t\nKontak tidak ditemukan!");
  else
  {
    printf("\t\nKontak dengan nama belakang %s ditemukan! Detail kontak: ", getlname);
    // printf("\n\nCantact %2.2d{", i + 1);
    printf("\n\t Nama: %s %s\n\t Umur: %d\n\t Jenis kelamin: %s\n\t Email: %s\n\t Kota: %s\n\t No. telephone :%s\n\t", contactsBook[i].first_name, contactsBook[i].last_name, contactsBook[i].age, contactsBook[i].gender, contactsBook[i].email, contactsBook[i].city, contactsBook[i].telNo);
  }
}

// Fungsi search by telephone no
void searchBytelNo()
{
  char getTelNo[20];
  bool found = false;
  int i = 0;

  printf("Masukkan Nomor telephone: ");
  scanf("%s", getTelNo);

  for (i = 0; i < contacts_count; i++)
  {
    if (strcmp(getTelNo, contactsBook[i].telNo) == 0)
    {
      found = true;
      break;
    }
  }
  if (found == false)
    printf("\t\nKontak tidak ditemukan!");
  else
  {
    printf("\t\nKontak dengan Nomor %s ditemukan! Detail kontak: ", getTelNo);
    // printf("\n\nCantact %2.2d{", i + 1);
    printf("\n\t Nama: %s %s\n\t Umur: %d\n\t Jenis kelamin: %s\n\t Email: %s\n\t Kota: %s\n\t No. telephone :%s\n\t", contactsBook[i].first_name, contactsBook[i].last_name, contactsBook[i].age, contactsBook[i].gender, contactsBook[i].email, contactsBook[i].city, contactsBook[i].telNo);
  }
}


char read_string(char *s, FILE *file)
{
  char i, c;

  i = 0;
  s[0] = 0;

  while (1)
  {
    c = fgetc(file);

    if (c == 0)
    {
      s[i] = 0;
      return i;
    }
    else if (c == EOF)
    {
      return -1;
    }
    else
    {
      s[i] = c;
      i++;
    }
  }
}


void load_contacts()
{
  char r, *s;
  FILE *file = fopen("contactsBook.txt", "r");

  if (!file)
    return;

  contacts_count = 0;

  while (1)
  {
    s = contactsBook[contacts_count].first_name;

    r = read_string(s, file);

    if (r < 0)
      break;

    s = contactsBook[contacts_count].last_name;
    read_string(s, file);

    s = contactsBook[contacts_count].telNo;
    read_string(s, file);

    // s = contactsBook[contacts_count].age;
    getw(file);

    s = contactsBook[contacts_count].city;
    read_string(s, file);

    s = contactsBook[contacts_count].email;
    read_string(s, file);

    s = contactsBook[contacts_count].gender;
    read_string(s, file);

    contacts_count++;
  }

  fclose(file);
}

void save_contacts()
{
  int i;
  Contact *contact;
  FILE *file = fopen("contactsBook.txt", "w");

  if (!file)
    return;

  for (i = 0; i < contacts_count; i++)
  {
    contact = contactsBook + i;

    fputs(contact->first_name, file);
    fputc(0, file);

    fputs(contact->last_name, file);
    fputc(0, file);

    fputs(contact->telNo, file);
    fputc(0, file);

    putw(contact->age, file);

    fputs(contact->gender, file);
    fputc(0, file);

    fputs(contact->email, file);
    fputc(0, file);

    fputs(contact->city, file);
    fputc(0, file);
  }

  fclose(file);
}

void getMax() {
  int max = 0;
  for (int i = 1; i < contacts_count; i++) {
    if (contactsBook[i].age > contactsBook[max].age) {
      max = i;
    }
  }
  printf("Kontak dengan umur tertinggi: \n");
  printf("%i | %s %s | %s | %d | %s | %s | %s\n", max + 1, contactsBook[max].first_name, contactsBook[max].last_name, contactsBook[max].telNo, contactsBook[max].age, contactsBook[max].gender, contactsBook[max].email, contactsBook[max].city);
}

void getMin() {
  int min = 0;
  for (int i = 1; i < contacts_count; i++) {
    if (contactsBook[i].age < contactsBook[min].age) {
      min = i;
    }
  }
  printf("Kontak dengan umur terendah: \n");
  printf("%i | %s %s | %s | %d | %s | %s | %s\n", min + 1, contactsBook[min].first_name, contactsBook[min].last_name, contactsBook[min].telNo, contactsBook[min].age, contactsBook[min].gender, contactsBook[min].email, contactsBook[min].city);
}

void getAverage()
{
  float result;
  int sumAge = 0;
  int countPerson = 0;
  
  for (int i = 0; i < contacts_count; i ++) {
    sumAge += contactsBook[i].age;
    countPerson++;
  }

  result = sumAge / countPerson;

  printf("Rata-rata umur seluruh kontak adalah %.2f", result);
}

void sortByAge() {
  Contact c;
  register int i, j;
  for (i = contacts_count - 1; i > 0; i--)
    for (j = 0; j < i; j++)
      if (contactsBook[j].age > contactsBook[j+1].age)
      {
        c = contactsBook[j];
        contactsBook[j] = contactsBook[j + 1];
        contactsBook[j + 1] = c;
      }
  printf("\n Kontak berdasarkan urutan umur. \n");
  show_contacts();
}

void sortByfname()
{
  Contact c;
  register int i, j;
  for (i = contacts_count - 1; i > 0; i--)
    for (j = 0; j < i; j++)
      if (strcmp(contactsBook[j].first_name, contactsBook[j + 1].first_name) > 0)
      {
        c = contactsBook[j];
        contactsBook[j] = contactsBook[j + 1];
        contactsBook[j + 1] = c;
      }
  printf("Kontak berdasarkan urutan nama depan. \n");
  show_contacts();
}

void sortBylname()
{
  Contact c;
  register int i, j;
  for (i = contacts_count - 1; i > 0; i--)
    for (j = 0; j < i; j++)
      if (strcmp(contactsBook[j].last_name, contactsBook[j + 1].last_name) > 0)
      {
        c = contactsBook[j];
        contactsBook[j] = contactsBook[j + 1];
        contactsBook[j + 1] = c;
      }
  printf("\n Kontak berdasarkan urutan nama belakang. \n");
  show_contacts();
}

void sortByCity()
{
  Contact c;
  register int i, j;
  for (i = contacts_count - 1; i > 0; i--)
    for (j = 0; j < i; j++)
      if (strcmp(contactsBook[j].city, contactsBook[j + 1].city) > 0)
      {
        c = contactsBook[j];
        contactsBook[j] = contactsBook[j + 1];
        contactsBook[j + 1] = c;
      }
  printf("\n Kontak berdasarkan urutan kota.\n");
  show_contacts();
}

void sortByGender()
{
  Contact c;
  register int i, j;
  for (i = contacts_count - 1; i > 0; i--)
    for (j = 0; j < i; j++)
      if (strcmp(contactsBook[j].gender, contactsBook[j + 1].gender) > 0)
      {
        c = contactsBook[j];
        contactsBook[j] = contactsBook[j + 1];
        contactsBook[j + 1] = c;
      }
  printf("\n Kontak berdasarkan urutan jenis kelamin. \n");
  show_contacts();
}

void sortByEmail()
{
  Contact c;
  register int i, j;
  for (i = contacts_count - 1; i > 0; i--)
    for (j = 0; j < i; j++)
      if (strcmp(contactsBook[j].email, contactsBook[j + 1].email) > 0)
      {
        c = contactsBook[j];
        contactsBook[j] = contactsBook[j + 1];
        contactsBook[j + 1] = c;
      }
  printf("\n Kontak berdasarkan urutan email. \n");
  show_contacts();
}

void sortByTelNo()
{
  Contact c;
  register int i, j;
  for (i = contacts_count - 1; i > 0; i--)
    for (j = 0; j < i; j++)
      if (strcmp(contactsBook[j].telNo, contactsBook[j + 1].telNo) > 0)
      {
        c = contactsBook[j];
        contactsBook[j] = contactsBook[j + 1];
        contactsBook[j + 1] = c;
      }
  printf("\n Kontak berdasarkan urutan nomor telephone.\n");
  show_contacts();
}

bool wildCard(char *pattern, char *string)
{
  if (*pattern == '\0' && *string == '\0')
    return true;

  if (*pattern == '?' || *pattern == *string)
    return wildCard(pattern + 1, string + 1);

  if (*pattern == '*')
    return wildCard(pattern + 1, string) || wildCard(pattern, string + 1);

  return false;
}

void printWildCardResult()
{
  char telNo[20];

  printf("\nMasukkan nomer yang dicari (tambahkan * diakhir): \n");
  scanf("%s", &telNo);

  for (int i = 0; i < contacts_count; i++) {
    if (wildCard(telNo, contactsBook[i].telNo))
    {
      printf("\n ID | Nama | Nomor | Umur | Jenis Kelamin | Email | Kota ");
      printf("\n | %i | %s %s | %s | %d | %s | %s | %s |\n", i+1, contactsBook[i].first_name, contactsBook[i].last_name, contactsBook[i].telNo, contactsBook[i].age, contactsBook[i].gender, contactsBook[i].email, contactsBook[i].city);
    };
  }
}

int sortMenu() {
  int pilihan;
  printf("\nUrutkan kontak berdasarkan: \n");
  printf("1. Nama depan \n");
  printf("2. Nama belakang\n");
  printf("3. Umur\n");
  printf("4. Jenis kelamin\n");
  printf("5. No. Telephone\n");
  printf("6. Email\n");
  printf("7. Kota\n");
  printf("Masukkan pilihan: ");
  scanf("%d", &pilihan);
  return pilihan;
}

void searchNameAndEmail()
{
  char fname[50];
  char email[50];

  printf("\nMasukkan nama depan: \n");
  scanf("%s", &fname);
  printf("\nMasukkan email: \n");
  scanf("%s", &email);
  bool found = false;
  for (int i = 0; i < contacts_count; i++) {
    if (strcmp(fname, contactsBook[i].first_name) == 0 && strcmp(contactsBook[i].email, email) == 0) {
      printf("\n ID | Nama | Nomor | Umur | Jenis Kelamin | Email | Kota ");
      printf("\n | %i | %s %s | %s | %d | %s | %s | %s |\n", i + 1, contactsBook[i].first_name, contactsBook[i].last_name, contactsBook[i].telNo, contactsBook[i].age, contactsBook[i].gender, contactsBook[i].email, contactsBook[i].city);
      found = true;
    }
  }

  if (found == false)
    printf("Kontak tidak ditemukan!");
}

void searchNameOrEmail()
{
  char fname[50];
  char email[50];

  printf("\nMasukkan nama depan: \n");
  scanf("%s", &fname);
  printf("\nMasukkan email: \n");
  scanf("%s", &email);
  bool found = false;
  for (int i = 0; i < contacts_count; i++)
  {
    if (strcmp(fname, contactsBook[i].first_name) == 0)
    {
      printf("\n ID | Nama | Nomor | Umur | Jenis Kelamin | Email | Kota ");
      printf("\n | %i | %s %s | %s | %d | %s | %s | %s |\n", i + 1, contactsBook[i].first_name, contactsBook[i].last_name, contactsBook[i].telNo, contactsBook[i].age, contactsBook[i].gender, contactsBook[i].email, contactsBook[i].city);
      found = true;
    }
    if (strcmp(email, contactsBook[i].email) == 0)
    {
      printf("\n ID | Nama | Nomor | Umur | Jenis Kelamin | Email | Kota ");
      printf("\n | %i | %s %s | %s | %d | %s | %s | %s |\n", i + 1, contactsBook[i].first_name, contactsBook[i].last_name, contactsBook[i].telNo, contactsBook[i].age, contactsBook[i].gender, contactsBook[i].email, contactsBook[i].city);
      found = true;
    }
  }

  if (found == false) printf("Kontak tidak ditemukan!");

}


void undoMenu()
{
  if (isUndoDone) {
    printf("Undo sudah dilakukan!\n");
    return;
  } else {
    if (lastOperation == 1) {
      printf("Undo Insert\n");
      prevContactsBookLength = contacts_count;
      contacts_count--;
      isUndoDone = true;
    }
    else if (lastOperation == 2) {
      printf("Undo Delete\n");
      contacts_count = prevContactsBookLength;
      contactsBook[contacts_count] = lastRemovedItem;
      printf("%s", contactsBook[contacts_count].first_name);
      isUndoDone = true;
    }
    else if (lastOperation == 3) {
      printf("Undo edit\n");
      tempForEdit = contactsBook[getIndexUndoRedoEdit];
      contactsBook[getIndexUndoRedoEdit] = lastRemovedItem;
      lastRemovedItem = tempForEdit;
      isUndoDone = true;
    }
  }

  show_contacts();
}

void redo()
{
  if (!isUndoDone) {
    printf("Tidak dapat melakukan redo!\n");
    return;
  }

  if (isRedoDone) {
    printf("Redo sudah dilakukan!");
    return;
  } else {
    if (lastOperation == 1) {
      printf("Redo Insert\n");
      contacts_count++;
      isRedoDone = true;
    }
    else if(lastOperation == 2) {
      printf("Redo Delete\n");
      prevContactsBookLength = contacts_count;
      contacts_count--;
      isRedoDone = true;
    }
    else if (lastOperation == 3) {
      printf("Redo Edit\n");
      contactsBook[getIndexUndoRedoEdit] = lastRemovedItem;
      isRedoDone = true;
    }
  }

  show_contacts();
}

void cari_kontak()
{
  int pilihan1, pilihan2;
  printf("Jumlah Kategori Pencarian: (1/2) ");
  scanf("%d", &pilihan1);
  if (pilihan1 == 1) {
    puts("1. Cari berdasarkan nama depan");
    puts("2. Cari berdasarkan nama belakang");
    puts("3. Cari berdasarkan nomo telepon");
    printf(": ");
    scanf("%d", &pilihan2);

    if (pilihan2 == 1) {
      searchByfname();
    } else if (pilihan2 == 2) {
      searchBylname();
    } else if (pilihan2 == 3) {
      searchBytelNo();
      
    }
  } else if (pilihan1 == 2) {
    puts("1. Cari berdasarkan nama depan dan email");
    puts("2. Cari berdasarkan nama depan atau email");
    printf(": ");
    scanf("%d", &pilihan2);

    if (pilihan2 == 1) {
      searchNameAndEmail();
    }  else if (pilihan2 == 2) {
      searchNameOrEmail();
    }
  }
}

int user_interface()
{
  char c;
  int pilihanSort;
  system("cls");
  puts("************************************************");
  puts("              Aplikasi Contact Book             ");
  puts("************************************************");
  puts("Masukkan perintah: ");
  puts("    a) Tambah Kontak \t\t g) Urutkan Kontak");
  puts("    b) Edit Kontak \t\t h) Cari Kontak");
  puts("    c) Hapus Kontak \t\t i) Max / Min");
  puts("    d) Tampilkan Kontak \t j) Rata-rata");
  puts("    e) Undo  \t\t\t k) Wildcard Search");
  puts("    f) Redo \t\t\t l) Keluar ");
  printf("\n: ");

  scanf("%s", &c);

  switch (c)
  {
  case 'a':
    insertContact();
    break;

  case 'b':
    printf("Enter Contact ID: ");
    scanf("%i", &c);
    editContact(c - 1);
    break;

  case 'c':
    printf("Enter Contact ID: ");
    scanf("%i", &c);
    deleteContact(c - 1);
    break;

  case 'd':
    show_contacts();
    break;

  case 'l':
    puts("Terimakasih :)");
    return 0;

  case 'h' :
    cari_kontak();
    break;

  case 'e':
    undoMenu();
    break;
  
  case 'g':
    pilihanSort = sortMenu();
    if (pilihanSort == 1) {
      sortByfname();
    }
    else if (pilihanSort ==2) {
      sortBylname();
    }
    else if (pilihanSort ==3) {
      sortByAge();
    }
    else if (pilihanSort ==4) {
      sortByGender();
    }
    else if (pilihanSort ==5) {
      sortByTelNo();
    }
    else if (pilihanSort ==6) {
      sortByEmail();
    }
    else if (pilihanSort ==7) {
      sortByCity();
    }
    break;

  case 'k' :
    printWildCardResult();
    break; 
  case 'i' :;
    int pilihan;
    puts("1. Nilai maksimum");
    puts("2. Nilai minimum");
    printf(": ");
    scanf("%d", &pilihan);
    if (pilihan == 1) {
      getMax();
    } else if (pilihan == 2) {
      getMin();
    }
   break;
  case 'j':
    getAverage();
    break;
  case 'f':
    redo();
    break;
  default:
    puts("Menu Tidak Tersedia!");
    break;
  }
  getch();
  puts("");
  return 1;
}

int main()
{
  load_contacts();

  while (user_interface());
  save_contacts();

  return 0;
}