#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Ez egy saj�t k�sz�t�s program. B�rmi hib�t �szrevesztek, sz�ljatok.
//B�r a m�dos�t�s, t�rl�s �s keres�s a Gimesi tan�r �r egyik �r�j�b�l val� de a bin�ris file-kezel�ssel �n k�t�ttem �ssze

//EXTR�M FONTOS R�SZ:
//Ez csak egy minta, hogy �rts�tek, hogy hogyan kell gondolkozni
//DE! pr�b�lj�tok meg m�shogy megcsin�lni. M�s megold�sokkal, m�shogyan gondolkozva. (az adatfelt�lt�sen k�v�l, mert azt a Gimesi tan�r �r mutatta)
//De ha �szreveszik, hogy sok program ugyanolyan, akkor sim�n be�rj�k az egyest, �gyhogy a ti �rdeketek, hogy megvari�lj�tok
//Amikor eszembe jut egy m�sik megold�s le�rom, de ti is gondolkozzatok m�s-m�s megold�sokon
//Hajr� ;)
//EXTR�M FONTOSS R�SZ V�GE;

//Csak jelzek neki, hogy ilyen f�ggv�nyeim lesznek
//A kezdes() f�ggv�ny a program megnyit�s�n�l
int kezdes();
void menupontok();
void uj_adat();
void kereses();
void modositas();
void torles();
void listazas();
void kilepes();

struct rec
{
    int id;
    char nev[20];
    int kor;
    rec *kovetkezo;
};

int id, kor, menu, keres;
char nev[20];
FILE *fp;
struct rec *uj, *elso = NULL, *aktualis, *elozo, tmp;


int main()
{
    //A 'kezdes' f�ggv�ny visszat�r�si �rt�ke 0 ha siker�lt �s -1 ha nem
    //A 'kezdes' fuggv�y nyitja meg a file-t �s t�lti fel a dinamikus mem�ri�ba a file-ban l�v� adatokat
    //A dinamikus mem�ri�ban l�v� adatokkal fogunk dolgozni �s onnan t�ltj�k vissza a file-ba
    if(kezdes()!=-1)
    {
        menupontok();
    }
    else
    {
        printf("Valami hiba tortent a file megnyitasa kozben");
    }

}
void menupontok()
{
    system("cls");

    printf("\t\t\tAdatbazis kezelo\n\n");
    printf("(Kerem nyomja meg azon sorszamot amely menupontot valasztani kivanja!)\n\n");
    printf("\t\t\t1. Uj adat bevitel\n");
    printf("\t\t\t2. Kereses\n");
    printf("\t\t\t3. Adatmodositas\n");
    printf("\t\t\t4. Torles\n");
    printf("\t\t\t5. Listazas\n");
    printf("\t\t\t6. Kilepes (es a modositott adatok mentese)\n");
    scanf("%d", &menu);

    switch (menu)
    {

    case 1:
        uj_adat();
        break;
    case 2:
        kereses();
        break;
    case 3:
        modositas();
        break;
    case 4:
        torles();
        break;
    case 5:
        listazas();
        break;
    case 6:
        kilepes();
        break;
    default:
        printf("Sajnos ehhez a karakterhez nincs hozzarendelve menupont, kerem adjon meg 1 es 6 kozotti egesz szamot!\n");
        system("pause");
    }
    menupontok();

}
int kezdes()
{
    //Ha l�tezik olvasunk bel�le
    fp = fopen("data.bin", "r+b");
    if(fp == NULL)
    {
        //Ha nem l�teik: a w+b l�trehoz vagy fel�l�r egy file-t att�l f�gg�en hogy l�tezett-e vagy nem
        //itt az if miatt csak akkor hoz l�tre egyet ha nem l�tezett el�tte
        fp = fopen("data.bin", "w+b");

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
        uj->id=tmp.id;
        //Itt karakterenk�nt is �tathatj�tok a stringet
        strcpy(uj->nev,tmp.nev);
        uj->kor=tmp.kor;

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
void uj_adat()
{
	//Ezt m�r le�rtam a beszuro_rendezes nev� programban
    printf("Kerek egy azonositot: ");
    scanf("%d",&id);
    printf("Kerem az azonositohoz tartozo nevet: ");
    scanf("%s",nev);
    printf("Kerem az azonositohoz tartozo kort: ");
    scanf("%d",&kor);
    while(id)
    {

        uj=(struct rec*)malloc(sizeof(struct rec));

        if (!uj)
        {
            printf("Nincs eleg memoria\n");
            system("pause");
        }

        uj->id=id;
        //Itt karakterenk�nt is �tathatj�tok a stringet
        strcpy(uj->nev,nev);
        uj->kor=kor;

        aktualis=elso;

        elozo=NULL;


        while(aktualis&&id>aktualis->id)
        {

            elozo=aktualis;
         aktualis=aktualis->kovetkezo;
        }

        if (!elozo) elso=uj;
        else elozo->kovetkezo=uj;

        uj->kovetkezo=aktualis;


        printf("Kerek egy azonositot: ");
        scanf("%d",&id);
        if(id==0) break;
        printf("Kerem az azonositohoz tartozo nevet: ");
        scanf("%s",nev);
        printf("Kerem az azonositohoz tartozo kort: ");
        scanf("%d",&kor);
    }
}
void kereses()
{
    aktualis=elso;

    while(aktualis)
    {
        printf("%d\n",aktualis->id);
        aktualis=aktualis->kovetkezo;
    }
    //Keres�s
    printf("Kerem a keresendo szamot!: ");
    scanf("%d",&keres);
    //Az els� elemre �llunk
    aktualis=elso;
    //am�g a l�ncolt lista v�g�re nem �r�nk
    while(aktualis)
    {
    	//�sszeahsonl�tja a keresett sz�mot �s az aktu�lis elem id-k�t
        if(keres==aktualis->id)
        {
        	//Ha megtal�lta ki�rja az aktualis elem adatait �s kil�p a ciklusb�l
            printf("A keresendo nev: %s aki %d eves", aktualis->nev, aktualis->kor);
            break;
        }
        //ha nem tal�lta meg a k�vetkez� elemre l�p
        aktualis=aktualis->kovetkezo;
    }
	//ha nem tal�lta meg a megold�st az 'aktualis' a l�nc v�g�re mutat, ami egy null, vagyis ki�rja, hogy nincs tal�lat
    if (aktualis==NULL) printf("Nincs ilyen elem.\n");

    system("pause");
    menupontok();
}
void modositas()
{
    aktualis=elso;

    while(aktualis)
    {
        printf("%d\n",aktualis->id);
        aktualis=aktualis->kovetkezo;
    }
    //keres�s
    printf("Kerem a keresendo szamot!: ");
    scanf("%d",&keres);
    aktualis=elso;
    while(aktualis)
    {
        if(keres==aktualis->id)
        {
            printf("A keresendo nev: %s aki %d eves", aktualis->nev, aktualis->kor);
            break;
        }
        aktualis=aktualis->kovetkezo;
    }
	//mivel kil�p a ciklusb�l, amikor megtal�lta az adott elemet, kil�ps vagyis:
	//azon az elemen �llunk, amit kerest�nk, �gyhogy nyugodtan m�dos�thatjuk
    printf("Kerem a modositott nevet: ");
    scanf("%s", nev);
    strcpy(aktualis->nev,nev);

    printf("Kerem a modositott nevhez tartozo kort: ");
    scanf("%d", &kor);
    aktualis->kor = kor;
    system("pause");
    menupontok();


}
void torles()
{
    printf("Kerem a torlendo szamot!: ");
    scanf("%d",&keres);
    aktualis=elso;
    elozo=NULL;
    while(aktualis)
    {
        if(keres==aktualis->id)
        {
        	//Ha az el�z� null, vagyis az el�sz�r fut le a ciklus, vagyis az els� elemet keress�k: az els�, most m�r az els� ut�ni elem lesz
            if (elozo==NULL) elso=aktualis->kovetkezo;
            //ha nem az els� lefut�s, akkor az el�z� elemet �sszek�tj�k az aktu�lis ut�mi elemmel, vagyis az aktu�lis elemet kihagyjuk a l�ncb�l
            else elozo->kovetkezo=aktualis->kovetkezo;
            //felszabad�tjuk a mem�ri�ban annak az elemnek a hely�t, amit kia akrtunk t�r�lni
            free(aktualis);
            printf("Meg kell kerdezni, hogy biztos-e a torlesben, mi azok vagyunk.\n");
            printf("Sikeres torles.\n");
            break;
        }
        //az el�z� most m�r az aktu�lis lesz
        elozo=aktualis;
        //az aktu�llis pedig az aktu�lis ut�ni elem
        aktualis=aktualis->kovetkezo;
    }
    if (aktualis==NULL) printf("Nincs ilyen elem.\n");
    system("pause");


}
void listazas()
{
	//Sima ki�rat�s, nem kell sorba tenni, mivel m�r alapb�l �gy olvastuk be az ideiglenes mem�ri�ba az adatokat
    aktualis=elso;

    while(aktualis)
    {
        printf("%d: %s %d eves\n",aktualis->id, aktualis->nev, aktualis->kor);
        aktualis=aktualis->kovetkezo;
    }
    system("pause");
}
void kilepes()
{
	//A m�dos�t�sokat csak akkor menti ha a 6-os gombbal l�p ki a programb�l
	//Ez csak az �n megold�som, ti is kital�lhattok valami m�st
	//pl megnyittok m�g egy file-t, abba mentitek az �j adatokat �s �tnevezitek(arra is van parancs)
	//vagy �ttszitek az ideiglenes file-b�l abba, amib�l kiolvass�tok az adatokat
	//itt:

	//Megnyitjuk �jra a file-t, vagyis ez teljesn sz�z, �res file
    fp = fopen("data.bin", "w+b");

    //bele�rjuk a m�dos�tott adatokat
    aktualis=elso;
    while(aktualis)
    {
    	//itt nem kell & jel, mert ez m�r egy mutat� alapb�l
        fwrite(aktualis, sizeof(rec), 1, fp);
        aktualis=aktualis->kovetkezo;
    }

	//csak a v�g�n kell bez�rni a file-t!!!!!!!
    fclose(fp);
    exit(EXIT_SUCCESS);

}
