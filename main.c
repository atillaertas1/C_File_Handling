//Atilla Ertas 22181616018
//BMT103 - PROJE ODEVI



#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#define satir_uzunlugu 1000

//global degiskenler
int secim = 0;//test ekle, test coz ve kapat secimi icin tanimlanmistir
int sonuc_sayisi;
int atlanacak_satir = 1;
int soru_sayisi_sayaci = 0;
int baslangic_satiri = 1;
int satir_sayaci = 0;
int test_numarasi_sayaci = 0;
int bitir = 1;//bitir degiskeni 1 oldugu surece program calisir. Programin bitip bitmemesini kontrol eder
int secilen_test;
double sonuc_indkesi;
double secilen_testin_sorusayisi = 0;
double puan_toplami = 0;//secilen seceneklere gore puan toplamini tutan degisken

void sorulari_cagir();
void soru_ekle();
void secenekleri_cagir();
void secenek_ekle();
void sonuclari_goster();


//test
void testleri_goster()
{
    int x;
    test_numarasi_sayaci = 0;//1.test 2.tes .... indislemeyi tutar
    FILE* test_adlari_dosyasi;

    //Dosyanin bos olup olmadigi kontrol edilir
    if ((test_adlari_dosyasi = fopen("config.txt", "r")) == NULL)
    {
        //egerki bos ise hata yazisini yazdir
        printf("Error! dosya bulunamadi\n");
        printf("Lutfen once test ekleyin!!\n");
        printf("Uygulamayi kapatmak icin herhangi bir tusa basip entera basin!\n");
        scanf("%d",&x); //ekranin hemen kapanmamasi icin uyari mesajini kullanici okuyabilsin diye
        exit(1);
        
    }

    char satir[satir_uzunlugu];
    //config dosyasini okumak icin acilir
    test_adlari_dosyasi = fopen("config.txt", "r");
    printf("Test secin:\n");
    while (fgets(satir, satir_uzunlugu, test_adlari_dosyasi)) //satir satir okur txt
    {
        satir_sayaci++;
       //satir sayisi tek ise yazdirir cünkü config 
       //dosyasinda test adi <soru sayisi> test adi <soru sayisi> 

       //Ornegin: en sevdiginiz yemege gore kilonuzu tahmin ediyoruz
       //         1
       //         dikkat seviyene gore sen aslinda kimsin
       //         5
       //         1. test 1 sorudan olusuyor
       //         2.test 5 sorudan olusuyor
       
        if (satir_sayaci % 2 == 1)
        {
            test_numarasi_sayaci++;//test numarasi tutar
            printf("%d.",test_numarasi_sayaci);//x.test
            printf("%s", satir);//satiri yazdirir
        }
    }
    fclose(test_adlari_dosyasi);
    sorulari_cagir();
}
void sorulari_cagir()//secilen testin sorularini cagirir
{
    int satir_sayisi = 0;
    secilen_test = 0;
    atlanacak_satir = 0;
    FILE* test_adlari;
    if ((test_adlari = fopen("config.txt", "r")) == NULL)
    {
        printf("Error! Dosya bulunamadi");
        exit(1);
    }
    //int bufferLength = 255;
    char satir[satir_uzunlugu];
    test_adlari = fopen("config.txt", "r");
    scanf("%d", &secilen_test);
    while (fgets(satir, satir_uzunlugu, test_adlari))
    {
        satir_sayisi++;
        if (secilen_test * 2 == satir_sayisi && satir_sayisi % 2 == 0)//testin soru sayisini bulur 1
        {
            secilen_testin_sorusayisi = atoi(satir);
        }
        if (secilen_test * 2 == satir_sayisi)
        {
            atlanacak_satir += atoi(satir) * 6;//baslangic satirindan sonra ne kadar okuyacak atlanacak_satir 6
            break;
        }
        if (satir_sayisi % 2 == 0)
        {
            baslangic_satiri += atoi(satir) * 6;//baslangic satirini bulur 0
        }
    }
    fclose(test_adlari);
    satir_sayisi = 0;
    FILE* sonuc_sayisi_dosyasi;
    if ((sonuc_sayisi_dosyasi = fopen("cfgg.txt", "r")) == NULL)
    {
        printf("Error! Dosya Bulunamadi");
        exit(1);
    }
    sonuc_sayisi_dosyasi = fopen("cfgg.txt", "r");
    while (fgets(satir, satir_uzunlugu, sonuc_sayisi_dosyasi))
    {
        satir_sayisi++;
        if (secilen_test == satir_sayisi)
        {
            break;
            //baslangic satiri default olarak 1 seklinde atanir
        }
        else
        {
            baslangic_satiri += atoi(satir) + 1;//cevap sayisini ekler +1 textdeki bosluk icin
        }
    }
    fclose(sonuc_sayisi_dosyasi);
    secenekleri_cagir();
}

void secenekleri_cagir()//secilen testin secenek ve sorularini cagirir.
{
    int soru_sayisi = 0;
    int satir_sayisi = 0;//soru sayisini tutar her 5 olusunda bir soru ve cevaplarini cagirmak icindir
    int secilen_secenek = 0;//kullanicinin sectigi secenegi tutar
    FILE* secenekler_dosyasi;
    if ((secenekler_dosyasi = fopen("config.txt", "r")) == NULL)
    {
        printf("Error! Dosya Bulunamadi");
        exit(1);
    }

    char satir[satir_uzunlugu];
    secenekler_dosyasi = fopen("qst.txt", "r");
    printf("\n");
    while (fgets(satir, satir_uzunlugu, secenekler_dosyasi))
    {
        if (satir_sayisi == 5)//her 5 satirda 1 soru 4 secenek var o yüden burda satir sayisi sifirlanir
        {
            satir_sayisi = 0; soru_sayisi++; continue;
        }
        if (soru_sayisi >= baslangic_satiri && soru_sayisi < atlanacak_satir + baslangic_satiri && satir_sayisi != 0)
        {
            printf("%d.%s", satir_sayisi, satir); 
            satir_sayisi++;
        }
        if (soru_sayisi >= baslangic_satiri && soru_sayisi < atlanacak_satir + baslangic_satiri && satir_sayisi == 0)
        {
            printf("Soru:%s", satir);
            satir_sayisi++;
        }
        if (satir_sayisi == 5)
        {
            scanf("%d", &secilen_secenek); //kullanicidan girilen secenegi tutar
            puan_toplami += secilen_secenek;//1. ise 1 puan 2. ise 2 ....
        }
        soru_sayisi++;
    }
    fclose(secenekler_dosyasi);
    sonuclari_goster();
}

void sonuclari_goster()
{
    double prcntb = 0;//sonuclarin yüzdelik hesabi icin tanimlanmistir
    int satir_sayisi = 1;//imlec hangi satirda oldugunu tutar
    FILE* cevap_sayisi_dosyasi;
    if ((cevap_sayisi_dosyasi = fopen("cfgg.txt", "r")) == NULL)
    {
        printf("Error! Dosya Bulunamadi");
        exit(1);
    }
    char buffer[satir_uzunlugu];
    satir_sayisi = 1;
    prcntb = 0;//hesaplama yüzdesi
    cevap_sayisi_dosyasi = fopen("cfgg.txt", "r");//sonuclari tutar
    while (fgets(buffer, satir_uzunlugu, cevap_sayisi_dosyasi))
    {
        if (satir_sayisi == secilen_test)
        {
            prcntb = 100.0 / atoi(buffer);//snuc sayisina gore yuzde verir
            sonuc_sayisi = atoi(buffer);
            break;
        }
        else {}//bug
        satir_sayisi++;
    }
    fclose(cevap_sayisi_dosyasi);
    satir_sayisi = 0;
    FILE* fpt;
    if ((fpt = fopen("qst.txt", "r")) == NULL)
    {
        printf("Error! Dosya Bulunamadi");
        exit(1);
    }
    char buff[satir_uzunlugu];
    fpt = fopen("qst.txt", "r");//soru ve secenekleri tutar
    printf("\n");
    
    //textte 1 boşluk oldugu icin 1 ekledi
    // int ve double karsilastirmada sorun oldugu icin 1.0* carptm
    
    for (double a = 1.0; a < sonuc_sayisi * 1.0 + 1.0; ++a)//soru saysisina kadar tekrar ediyo
    {
        //16-4 enkto
        //soru basina dusen faizi bulur
        //a satir sayisini tutmak icin olusturulmustur
        if ((puan_toplami - secilen_testin_sorusayisi) * (100 / (secilen_testin_sorusayisi * 3)) <= a * prcntb)
        {
            
            sonuc_indkesi = a;
            break;
        }
    }
    satir_sayaci = 0;
    while (fgets(buff, satir_uzunlugu, fpt))
    {
        if (satir_sayisi * 1.0 == baslangic_satiri * 1.0 + atlanacak_satir * 1.0 + sonuc_indkesi - 1.0)
        {
            printf("%s", buff);//sonucu yazdirir
            break;//sonucu yazdirir
        }
        else {}
        satir_sayisi++;
    }
}

void soru_ekle()//test ekleme islemi yaparken teste sorularin girisini saglayan fonksiyondur
{
    FILE* sorular_dosyasi;
    sorular_dosyasi = fopen("qst.txt", "a");
    if (sorular_dosyasi == NULL) {
        printf("Error! Dosya Bulunamadi");
        exit(1);
    }
    char soru_metini[75];
    int soru_sayisi = 0;
    int secenek_sayisi = 0;
    fprintf(sorular_dosyasi, "\n");
    fgets(soru_metini, sizeof(soru_metini), stdin);
    while (soru_sayisi != soru_sayisi_sayaci)
    {
        printf("Sual basligi:");
        fgets(soru_metini, sizeof(soru_metini), stdin);
        fprintf(sorular_dosyasi, "%s", soru_metini);
        while (secenek_sayisi != 4)
        {
            printf("Cavablari giriniz:");
            fgets(soru_metini, sizeof(soru_metini), stdin);
            fprintf(sorular_dosyasi, "%s", soru_metini);
            secenek_sayisi++;
        }
        fprintf(sorular_dosyasi, "\n");
        secenek_sayisi = 0;
        soru_sayisi++;
    }
    fclose(sorular_dosyasi);
    secenek_ekle();
}
void secenek_ekle()
{
    FILE* sorular_dosyasi;
    sorular_dosyasi = fopen("qst.txt", "a");
    if (sorular_dosyasi == NULL)
    {
        printf("Error! Dosya Bulunamadi");
        exit(1);
    }
    char name[50];
    char qst[75];
    int sonuc_sayisi = 0;
    printf("Sonuc sayisin giriniz:");
    scanf("%d", &sonuc_sayisi);
    printf("Dikkat sonuclar kucuk degerlikten buyuk deferlik olarak tutulur \n");
    fgets(qst, sizeof(qst), stdin);
    while (satir_sayaci != sonuc_sayisi)
    {
        printf("Sonuclari yaziniz:");
        fgets(qst, sizeof(qst), stdin);
        fprintf(sorular_dosyasi, "%s", qst);
        satir_sayaci++;
    }
    fclose(sorular_dosyasi);

    FILE* fp;
    fp = fopen("cfgg.txt", "a");
    fprintf(sorular_dosyasi, "%d", sonuc_sayisi);
    fclose(fp);
}
void test_basligi_ekle()
{
    FILE* test_adi_dosyasi; //Bu dosyada test adi ve icindeki soru sayisi tutulur
    test_adi_dosyasi = fopen("config.txt", "a");
    if (test_adi_dosyasi == NULL)
    {
        printf("Error! dosya bulunamadi");
        exit(1);
    }
    char test_adi[70];
    int kac_sorudan_oluscak;
    fgets(test_adi, sizeof(test_adi), stdin);
    printf("Testin adini yaziniz:");
    fgets(test_adi, sizeof(test_adi), stdin);
    fprintf(test_adi_dosyasi, "%s", test_adi);
    printf("Sual sayisini giriniz:");
    scanf("%d", &kac_sorudan_oluscak);
    fprintf(test_adi_dosyasi, "%d", kac_sorudan_oluscak);
    fprintf(test_adi_dosyasi, "\n");
    fclose(test_adi_dosyasi);
    soru_sayisi_sayaci = kac_sorudan_oluscak;
    soru_ekle();
}

void ana_ekran()
{
    printf("Test cozmek icic:1 \n");
    printf("Test eklemek icin:2 \n");
    printf("kapatmak icin:3 \n");
    scanf("%d", &secim);
    if (secim == 1) {
        testleri_goster();
    }
    else if (secim == 2)
    {
        test_basligi_ekle();
    }
    else if (secim == 3)
    {
        bitir = 0;
    }
    else
    {
        printf("hatali secim yeniden deneyin... \n");
    }
}
int main()
{
    while (bitir)
    {
        secim = 0;//menu degiskeni(tescozmek...kapatmak)
        sonuc_indkesi = 0;  
        sonuc_sayisi = 0;
        secilen_testin_sorusayisi = 0;
        atlanacak_satir = 1;
        soru_sayisi_sayaci = 0;
        baslangic_satiri = 1;
        puan_toplami = 0;
        satir_sayaci = 0;
        test_numarasi_sayaci = 0;//test numarasi sayacini 0 lanir tekrar baslaninca belli bir degerden baslanmamasi icin
        bitir = 1;//programin sonlanip sonlamandigini kontrol eder
        secilen_test = 0;
        ana_ekran();
    }
    return 0;
}