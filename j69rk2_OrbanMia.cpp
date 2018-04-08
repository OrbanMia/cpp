#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*Ebben a programban tárolni fogjuk a NÉVeket és hozzá, hogy KOLESZos-e
  keresés: 1
  adatváltoztatás: 2
  új adat felvitele: 3
  törlés: 4
  adatbázis kiírása: 5
  kielepes: 0
  */


struct rec{
  int az;
  char nev [30];
  int kolesz;
  rec *kovetkezo;
};

struct rec *uj, *elso = NULL, *aktualis, *elozo, tmp;
FILE *fp;
int az,kolesz, keres;
char nev[30];

//keresés függvény. Végignézi az adatbazist, és ha egyezést talál, akkor visszaadja az egyező adat indexét
void kereses()
  {
    /*for (int i = 0; i < 40; i++)
    {
      if (az == adatbazis[i].az)
      {
        return i;
      }
    }
    return 40;*/

    printf("Keresett azonosito: ");
    scanf("%d",&keres);
    //Az els� elemre �llunk
    aktualis=elso;
    //am�g a l�ncolt lista v�g�re nem �r�nk
    while(aktualis)
    {
        //�sszeahsonl�tja a keresett sz�mot �s az aktu�lis elem az-k�t
        if(keres==aktualis->az)
        {
            //Ha megtal�lta ki�rja az aktualis elem adatait �s kil�p a ciklusb�l
              printf("%d\t\t%s\t\t%d\n",aktualis->az, aktualis->nev, aktualis->kolesz);
            //return aktualis->az;
            break;
        }
        //ha nem tal�lta meg a k�vetkez� elemre l�p
        aktualis=aktualis->kovetkezo;
    }
    //ha nem tal�lta meg a megold�st az 'aktualis' a l�nc v�g�re mutat, ami egy null, vagyis ki�rja, hogy nincs tal�lat
    if (aktualis==NULL) printf("Nincs ilyen elem.\n");

  }
// az adatbázis minden elemét megvizsgálja, és ha nem 0 az azonosító,tehát szerepelnek benne adatok, akkor kiírja
void adatmodositas(){
  printf("Melyik adatot szeretned modositani? (azonosito)\n");
  scanf("%d",&keres);
  /*int az;
  fflush(stdin);
  scanf("%d", &az);
  int i = keres(adatbazis, az);
  printf("Regi adatok:\n Nev: %s\n Kolesz: %d\n", adatbazis[i].nev,adatbazis[i].kolesz);
  printf("\nUj adatok megadasa:\n");
  fflush(stdin);
  printf("Nev:");
  scanf("%[^\n]" , &adatbazis[i].nev);
  fflush(stdin);
  printf("Kolesz: ");
  scanf("%d", &adatbazis[i].kolesz);
  fflush(stdin);*/

  kereses ();
  printf("\nKerem a modositott nevet: ");
  scanf("%s", nev);
  strcpy(aktualis->nev,nev);

  printf("Kerem a koleszt: ");
  scanf("%d", &kolesz);
  aktualis->kolesz = kolesz;

  //aktualis=elso;

  // while(aktualis)
  // {
  //     printf("%d\t\t%s\t\t%d\n",aktualis->az, aktualis->nev, aktualis->kolesz);
  //     aktualis=aktualis->kovetkezo;
  // }

}
// megnézi, hol van az első üresmező az adatbázisban, majd bekéri az adatokat, és elhelyezi az adatbázisba
void kiir()
{
  /*for (int i = 0; i < 40 ; i++)
  {
  if (adatbazis[i].az != 0)
  {
  printf("%d\t\t%s\t\t%d\n", adatbazis[i].az, adatbazis[i].nev, adatbazis[i].kolesz);
}
}*/

while(aktualis)
{
  //�rd ki az adatot
  printf("%d\t\t%s\t\t%d\n",aktualis->az, aktualis->nev, aktualis->kolesz);
  //L�pj a k�vetkez� elemre
  aktualis=aktualis->kovetkezo;
}
//system("pause");
//return 0;



}
void torles()
{
  //bekérem az azonosítót, majd az adatokat kiírom a felhasználónak.
  printf("Torles azonosito alapjan.\n");
  printf("Azonosito megadasa: \n");
  scanf("%d",&keres);
  //int valasz;
  //char talalat = kereses();
  //if (i != 40) {
  //printf("%s torlese az adatbazisbol\n", talalat);
  printf("Biztosan torolni szeretned? [I/N]\n");
  char val;
  scanf("%s", &val);
  //ha jóváhagyja a törlést, akkor a törlendő adat indexétől előrehozom eggyel az összes
  //többi adatot, majd az utolsó adatot kitörlöm
  if (val == 'i' || val == 'I')
  {
    printf("Torles\n");
    /*for (int z = i; z < 39; z++)
    {
    adatbazis[z].az = adatbazis[z+1].az;
    strcpy(adatbazis[z].nev, adatbazis[z+1].nev);
    adatbazis[z].kolesz = adatbazis[z+1].kolesz;
  }
  adatbazis[39].az = 0;
  strcpy(adatbazis[39].nev , "");
  adatbazis[39].kolesz = 0;*/
  aktualis=elso;
  elozo=NULL;
  while(aktualis)
  {
    if(keres==aktualis->az)
    {
      //Ha az el�z� null, vagyis az el�sz�r fut le a ciklus, vagyis az els� elemet keress�k: az els�, most m�r az els� ut�ni elem lesz
      if (elozo==NULL) elso=aktualis->kovetkezo;
      //ha nem az els� lefut�s, akkor az el�z� elemet �sszek�tj�k az aktu�lis ut�mi elemmel, vagyis az aktu�lis elemet kihagyjuk a l�ncb�l
      else elozo->kovetkezo=aktualis->kovetkezo;
      //felszabad�tjuk a mem�ri�ban annak az elemnek a hely�t, amit kiakartunk t�r�lni
      free(aktualis);
      /*printf("Meg kell kerdezni, hogy biztos-e a torlesben, mi azok vagyunk.\n");
      printf("Sikeres torles.\n");*/
      break;
    }
    //az el�z� most m�r az aktu�lis lesz
    elozo=aktualis;
    //az aktu�llis pedig az aktu�lis ut�ni elem
    aktualis=aktualis->kovetkezo;
  }
  if (aktualis==NULL) printf("Nincs ilyen elem.\n");


}
else
{
  printf("Torles megszakitasa\n");
}
printf("A torles befejezodott\n");
}
int kiolvas (){

  //  /Ha l�tezik olvasunk bel�le
  fp = fopen("badandohoz.bin", "r+b");
  if(fp == NULL)
  {
    //Ha nem l�teik: a w+b l�trehoz vagy fel�l�r egy file-t att�l f�gg�en hogy l�tezett-e vagy nem
    //itt az if miatt csak akkor hoz l�tre egyet ha nem l�tezett el�tte
    fp = fopen("beadandohoz.bin", "w+b");

    //Ha egyeltal�n nem siker�lt a file megnyit�s
    if(fp == NULL)
    {
      printf("Hiba a file megnyitasa kozben");
      system("pause");
      return -1;

    }
  }
  //A file-unkb�l egy adatot kiolvasunk. Milyen t�pus� egy adat? Egy rec t�pus� strukt�ra. �gyhogy azt kell kiolvasni
  fread(&tmp, sizeof(rec), 1, fp);

  //Am�g a file-v�g�ig nem �r
  //Ha nincs m�g adat, bele se megy a ciklusba
  while (!feof(fp))
  {
    //Ezt m�r le�rtam a lancolt_lista_beszuro_rendezessel nev� programban
    //A k�l�nbs�g csak az adatok �thelyez�s�ben van.
    //Viszont ez nem felt�tlen egy j� megold�s. Mivel m�r rendezve �rtuk bele a file-ba, nem kell rendezve kiolvasni
    //Ezt �rdemes �t�rni kicsit

    uj=(struct rec*)malloc(sizeof(struct rec));

    if (!uj)
    {
      printf("Nincs eleg memoria\n");
      system("pause");
      return -1;
    }
    //mivel a file-b�l egy adatot kellett kiszedj�nk, egy adat pedig egy strukt�ra, a tmp.vmilyen_adat-ot kell �tadni
    uj->az=tmp.az;
    //Itt karakterenk�nt is �tathatj�tok a stringet
    strcpy(uj->nev,tmp.nev);
    uj->kolesz=tmp.kolesz;

    aktualis=elso;

    elozo=NULL;


    while(aktualis)
    {

      elozo=aktualis;
      aktualis=aktualis->kovetkezo;
    }

    if (!elozo) elso=uj;
    else elozo->kovetkezo=uj;

    uj->kovetkezo=aktualis;

    //Kiolvassuk a k�vetkez� adatot
    fread(&tmp, sizeof(rec), 1, fp);



  }
}
void ujadat ()
  {
    /*for (int i = 0; i < 40; i++)
    {
      if (adatbazis[i].az == 0)
      {
        printf("Azonosito: %d\n", i+1);
        adatbazis[i].az = i+1;
        fflush(stdin);
        printf("Nev:");
        scanf("%[^\n]" , &adatbazis[i].nev);
        fflush(stdin);
        printf("Kolesz: ");
        scanf("%d", &adatbazis[i].kolesz);
        fflush(stdin);
        break;
      }
    }*/
    //Ezt m�r le�rtam a beszuro_rendezes nev� programban
      printf("Kerek egy azonositot! ");
      scanf("%d",&az);
      printf("Kerem a nevet! ");
      scanf("%s",nev);
      printf("Kerem a koleszt! ");
      scanf("%d",&kolesz);
      while(az)
      {

          uj=(struct rec*)malloc(sizeof(struct rec));

          if (!uj)
          {
              printf("Nincs eleg memoria\n");
              system("pause");
          }

          uj->az=az;
          //Itt karakterenk�nt is �tathatj�tok a stringet
          strcpy(uj->nev,nev);
          uj->kolesz =kolesz;

          aktualis=elso;

          elozo=NULL;


          while(aktualis&&az>aktualis->az)
          {

              elozo=aktualis;
              aktualis=aktualis->kovetkezo;
          }

          if (!elozo) elso=uj;
          else elozo->kovetkezo=uj;

          uj->kovetkezo=aktualis;


  }
}

  // bekérem az azonosítót, ami alapján megkeresem, hogy hol van a tömbben, a keres függvénnyel
//voaz kereses ()


int main()
{


  //adatok adatbazis [40];
// az adatbázis minden értékét az alapbeállításra állítom, hogy ne a memóriában maradt adatok jelenjenek meg
  /*for (int i = 0; i < 40; i++) {
    adatbazis[i].az = 0;
    strcpy(adatbazis[i].nev , "");
    adatbazis[i]. kolesz   = 0;*/

// felveszek teszt adatokat a könnyebb kezelhetőség érdekében
  /*adatbazis[0].az   =1;
  strcpy(adatbazis[0].nev , "Anna");
  adatbazis[0]. kolesz   = 35;
  adatbazis[1].az   =2;
  strcpy(adatbazis[1].nev , "Bela");
  adatbazis[1]. kolesz   = 23;
  adatbazis[2].az   =3;
  strcpy(adatbazis[2].nev , "Mia");
  adatbazis[2]. kolesz   = 11;
  adatbazis[3].az   =4;
  strcpy(adatbazis[3].nev , "Zsolt");
  adatbazis[3]. kolesz   = 111;*/

    int valasz;

    if (kiolvas () != -1)
        {
          // megmutatom a lehetőségeket, majd bekérem a választ, ez alapján futtatom a megfelelő függvényt
          do
          {
            //menü

            printf ("%35s","Kereses: \t\t1\n");
            printf ("%35s","Adatvaltoztatas: \t2\n");
            printf ("%35s","Uj adat felvitele: \t3\n");
            printf ("%35s","Torles: \t\t4\n");
            printf ("%35s","Adatbazis megjelenitese:\t5\n");
            printf ("%35s","Kilepes: \t\t0\n");



            scanf("%d", &valasz);
            printf("\n" );
            system("cls");



          switch (valasz) {
              case 1: kereses ();
                      break;
              case 2: adatmodositas ();
                      break;
              case 3:ujadat ();
                      break;
              case 4:torles ();
                      break;
              case 5: kiir ();
                      break;
              case 0: printf ("\nSzia!\n");
                  	break;
            }
          } while(valasz != 0);
        }
          system("pause");
  }
