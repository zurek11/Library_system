#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "kniznica.txt"     //zmena retazca "kniznica.txt" za slovo FILENAME
#define VELKOST_SIGNATURA 10+2      //konstanta s velkostou retazca signatura
#define VELKOST_ISBN 14+2           //konstanta s velkostou retazca ISBN
#define VELKOST_NAZOV_KNIHY 100+2   //konstanta s velkostou retazca nazovKnihy
#define VELKOST_AUTORI 100+2        //konstanta s velkostou retazca autori

typedef struct kniznica                             //definovanie struktury s nazvom potraviny a datovym typom KNIZNICA
{
    char signatura[VELKOST_SIGNATURA+1];    //deklaracia retazca signatura
    char ISBN[VELKOST_ISBN+1];              //deklaracia retazca ISBN
    char nazovKnihy[VELKOST_NAZOV_KNIHY+1]; //deklaracia retazca nazovKnihy
    char autori[VELKOST_AUTORI+1];          //deklaracia retazca autori
    int datumVypozicania;                   //deklaracia celociselnej premennej datumVypozicania
    int cisloPreukazu;                      //deklaracia celociselnej premennej cisloPreukazu
    struct kniznica *dalsia;                //deklaracia smernika na dalsi prvok v spajanom zozname struktur
}KNIZNICA;
void dealokaciaUdaje(KNIZNICA **prvyZaznam)         //funkcia s nazvom dealokaciaUdaje
{
    KNIZNICA *aktualnyZaznam=NULL;  //deklaracia smernika na struktury s nazvom aktualnyZaznam
    KNIZNICA *predchZaznam=NULL;    //deklaracia smernika na struktury s nazvom predchZaznam

    aktualnyZaznam=*prvyZaznam;     //priradenie smerniku aktualnyZaznam adresu smernika prvyZaznam ukazujuceho na strukturu
    while(aktualnyZaznam!=NULL)     //dokial sa smernik aktualnyZaznam nebude rovnat NULL
    {
        aktualnyZaznam=aktualnyZaznam->dalsia;  //priradenie adrese smernika aktualnyZaznam adresu na ktoru ukazuje smernik dalsia
        free(predchZaznam);                     //uvolnenie pamate pre predchZaznam
        predchZaznam=aktualnyZaznam;            //adrese smernika predchZaznam priradm adresu mernika aktalnyZaznam
    }
    *prvyZaznam=NULL;               //priradenie smerniku prvyZaznam NULL
}
void nacitajUdaje(FILE *fr, KNIZNICA **prvyZaznam)  //funkcia s nazvom nacitajUdaje
{
    KNIZNICA *aktualnyZaznam=NULL;      //deklaracia smernika na struktury s nazvom aktualnyZaznam
    int pocetStruktur=0;                //delkaracia celociselnej premennej pocetStruktur
    char retazec[4];                    //deklaracia retazca retazec

    rewind(fr);                         //posunutie kurzora na zaciatok suboru
    dealokaciaUdaje(prvyZaznam);        //zavolanie funkcie dealokaciaUdaje
    while((fscanf(fr,"%s",retazec))!=EOF)   //dokial retazec s nazvom retazec nenarazi na koniec subora
    {
        if(strcmp(retazec,"---")==0)        //ak sa retazec rovna "---"
        {
            fgetc(fr);                      //zober jeden znak zo suboru predstavujuci znak '\n'
            ++pocetStruktur;                //povysenie premennej pocetStruktur
            if(*prvyZaznam==NULL)           //ak sa smernik prvyZaznam rovna NULL
            {
                *prvyZaznam=(KNIZNICA*)malloc(sizeof(KNIZNICA));        //program alokuje pamat pre smernik prvyZaznam o velkosti typu KNIZNICA
                fgets((*prvyZaznam)->signatura,VELKOST_SIGNATURA,fr);   //nacita zo suboru riadok do velkosti konstanty VELKOST_SIGNATURA a ulozi ho do retazca signatura v strukture na ktoru ukazuje smernik prvyZaznam
                fgets((*prvyZaznam)->ISBN,VELKOST_ISBN,fr);             //nacita zo suboru riadok do velkosti konstanty VELKOST_ISBN a ulozi ho do retazca ISBN v strukture na ktoru ukazuje smernik prvyZaznam
                fgets((*prvyZaznam)->nazovKnihy,VELKOST_NAZOV_KNIHY,fr);//nacita zo suboru riadok do velkosti konstanty VELKOST_NAZOV_KNIHY a ulozi ho do retazca nazovKnihy v strukture na ktoru ukazuje smernik prvyZaznam
                fgets((*prvyZaznam)->autori,VELKOST_AUTORI,fr);         //nacita zo suboru riadok do velkosti konstanty VELKOST_AUTORI a ulozi ho do retazca autori v strukture na ktoru ukazuje smernik prvyZaznam
                fscanf(fr,"%d",&(*prvyZaznam)->datumVypozicania);       //nacita cislo zo suboru a ulozi ho do premenej datumVypozicania v strukture na ktoru ukazuje smernik prvyZaznam
                fscanf(fr,"%d",&(*prvyZaznam)->cisloPreukazu);          //nacita cislo zo suboru a ulozi ho do premenej cisloPreukazu v strukture na ktoru ukazuje smernik prvyZaznam
                aktualnyZaznam=*prvyZaznam;                             //adrese smernika aktualnyZaznam sa priradi adresa smernnika prvyZaznam
            }
            else                           //ak sa vyskitne ina moznost aka je v if
            {
                aktualnyZaznam=aktualnyZaznam->dalsia=(KNIZNICA*)malloc(sizeof(KNIZNICA));  //program alokuje pamat pre smernik aktualnyZaznam o velkosti typu KNIZNICA
                fgets(aktualnyZaznam->signatura,VELKOST_SIGNATURA,fr);                      //nacita zo suboru riadok do velkosti konstanty VELKOST_SIGNATURA a ulozi ho do retazca signatura v strukture na ktoru ukazuje smernik aktualnyZaznam
                fgets(aktualnyZaznam->ISBN,VELKOST_ISBN,fr);                                //nacita zo suboru riadok do velkosti konstanty VELKOST_ISBN a ulozi ho do retazca signatura v strukture na ktoru ukazuje smernik aktualnyZaznam
                fgets(aktualnyZaznam->nazovKnihy,VELKOST_NAZOV_KNIHY,fr);                   //nacita zo suboru riadok do velkosti konstanty VELKOST_NAZOV_KNIHY a ulozi ho do retazca nazovKnihy v strukture na ktoru ukazuje smernik aktualnyZaznam
                fgets(aktualnyZaznam->autori,VELKOST_AUTORI,fr);                            //nacita zo suboru riadok do velkosti konstanty VELKOST_AUTORI a ulozi ho do retazca autori v strukture na ktoru ukazuje smernik aktualnyZaznam
                fscanf(fr,"%d",&aktualnyZaznam->datumVypozicania);                          //nacita cislo zo suboru a ulozi ho do premenej datumVypozicania v strukture na ktoru ukazuje smernik aktualnyZaznam
                fscanf(fr,"%d",&aktualnyZaznam->cisloPreukazu);                             //nacita cislo zo suboru a ulozi ho do premenej cisloPreukazu v strukture na ktoru ukazuje smernik aktualnyZaznam
                aktualnyZaznam->dalsia=NULL;                                                //priradenie smerniku v strukture na ktoru ukazuje smernik aktualnyZaznam hodnotu NULL
            }
        }
    }
    if(pocetStruktur==0)printf("Zaznamy neboli nacitane\n");    //ak sa v subore nenachadza ziadny zaznam program vypise na obrazovku "Zaznamy neboli nacitane"
    else printf("Nacitalo sa %d zaznamov\n",pocetStruktur);     //ak sa if nevykonal program vypise na obrazovku kolko zaznamov sa nacitalo
}
void vypisUdaje(KNIZNICA *prvyZaznam)               //funkcia s nazvom vypisUdaje
{
    int pocet=0;                        //deklaracia celociselnej premennej pocet
    KNIZNICA *aktualnyZaznam=NULL;      //deklaracia smernika na struktury s nazvom aktualnyZaznam

    aktualnyZaznam=prvyZaznam;          //adrese smernika aktualnyZaznam sa priradi adresa smernika prvyZaznam
    while(aktualnyZaznam!=NULL)         //dokial sa smernik aktualnyZaznam nerovna NULL
    {
        printf("%d.\n",++pocet);        //program napise na obrazovku poradie nacitaneho zaznamu
        printf("signatura: %s",aktualnyZaznam->signatura);      //program vypise na obrazovku retazec signaturu v danom zazname
        printf("isbn: %s",aktualnyZaznam->ISBN);                //program vypise na obrazovku retazec ISBN v danom zazname
        printf("nazov: %s",aktualnyZaznam->nazovKnihy);         //program vypise na obrazovku retazec nazovKnihy v danom zazname
        printf("autori: %s",aktualnyZaznam->autori);            //program vypise na obrazovku retazec autori v danom zazname
        printf("datum: %d\n",aktualnyZaznam->datumVypozicania); //program vypise na obrazovku premennu datum v danom zazname
        printf("preukaz: %d\n",aktualnyZaznam->cisloPreukazu);  //program vypise na obrazovku premennu preukaz v danom zazname
        aktualnyZaznam=aktualnyZaznam->dalsia;                  //posunutie smernika v spajanom zozname struktur o jedno miesto
    }
}
void pridajUdaje(KNIZNICA **prvyZaznam)             //funkcia s nazvom pridajUdaje
{
    KNIZNICA *predchZaznam=NULL;            //deklaracia smernika na struktury s nazvom predchZaznam
    KNIZNICA *aktualnyZaznam=NULL;          //deklaracia smernika na struktury s nazvom aktualnyZaznam
    KNIZNICA *novyZaznam=NULL;              //deklaracia smernika na struktury s nazvom novyZaznam
    int pozicia=0;                          //deklaracia celociselnej premennej pozicia a jej inicializacia na hodnotu nula
    int pocet=1;                            //deklaracia celociselnej premennej pocet a jej inicializacia na hodnotu jedna

    scanf("%d",&pozicia);                   //nacitanie premennej pozicia z klavesnice
    getchar();                              //funkcia pre znak pre novy riadok 'ENTER'
    if(pozicia>0)                           //ak je velkost premennej pozicia vacsi ako nula
    {
        if(*prvyZaznam!=NULL)               //ak smernik prvyZaznam neukazuje na NULL
        {
            novyZaznam=(KNIZNICA*)malloc(sizeof(KNIZNICA));         //program alokuje pamat pre smernik novyZaznam o velkosti typu KNIZNICA
            fgets(novyZaznam->signatura,VELKOST_SIGNATURA,stdin);   //nacita zo suboru riadok do velkosti konstanty VELKOST_SIGNATURA a ulozi ho do retazca signatura v strukture na ktoru ukazuje smernik novyZaznam
            fgets(novyZaznam->ISBN,VELKOST_ISBN,stdin);             //nacita zo suboru riadok do velkosti konstanty VELKOST_ISBN a ulozi ho do retazca signatura v strukture na ktoru ukazuje smernik novyZaznam
            fgets(novyZaznam->nazovKnihy,VELKOST_NAZOV_KNIHY,stdin);//nacita zo suboru riadok do velkosti konstanty VELKOST_NAZOV_KNIHY a ulozi ho do retazca signatura v strukture na ktoru ukazuje smernik novyZaznam
            fgets(novyZaznam->autori,VELKOST_AUTORI,stdin);         //nacita zo suboru riadok do velkosti konstanty VELKOST_AUTORI a ulozi ho do retazca signatura v strukture na ktoru ukazuje smernik novyZaznam
            scanf("%d",&novyZaznam->datumVypozicania);              //nacita cislo zo suboru a ulozi ho do premenej datumVypozicania v strukture na ktoru ukazuje smernik novyZaznam
            scanf("%d",&novyZaznam->cisloPreukazu);                 //nacita cislo zo suboru a ulozi ho do premenej cisloPreukazu v strukture na ktoru ukazuje smernik novyZaznam
            novyZaznam->dalsia=NULL;                                //priradenie smerniku v strukture na ktoru ukazuje smernik novyZaznam hodnotu NULL
            predchZaznam=aktualnyZaznam=*prvyZaznam;                //adrese smernika predchZaznam a aktualnyZaznam sa priradi adresa smernika prvyZaznam
            while(aktualnyZaznam!=NULL)                 //dokial sa smernik aktualnyZaznam nerovna NULL
            {
                if(pozicia==1)                          //ak sa pozicia rovna nule
                {
                    novyZaznam->dalsia=*prvyZaznam;     //smernik v strukture dalsia na ktoru ukazuje smernik novyZaznam sa rovna adrese na ktoru ukazuje prvyZaznam
                    aktualnyZaznam=*prvyZaznam;         //adresa aktualnehoZaznamu sa rovna adrese prvehoZaznamu
                    *prvyZaznam=novyZaznam;             //adresa prvehoZaznamu sa rovna adrese novehoZaznamu
                    break;                              //ukonci sa cyklus while
                }
                if(pocet==pozicia)                      //ak sa pozicia rovna poctu
                {
                    predchZaznam->dalsia=novyZaznam;    //smernik v strukture dalsia na ktoru ukazuje smernik predchZaznam sa rovna adrese na ktoru ukazuje novyZaznam
                    novyZaznam->dalsia=aktualnyZaznam;  //smernik v strukture dalsia na ktoru ukazuje smernik novyZaznam sa rovna adrese na ktoru ukazuje aktualnyZaznam
                    break;                              //ukonci sa cyklus while
                }
                predchZaznam=aktualnyZaznam;            //adresa pedchZaznamu sa rovna adrese aktualnehoZaznamu
                aktualnyZaznam=aktualnyZaznam->dalsia;  //adresa aktualnehoZaznamu sa rovna smerniku dalsia v strukture na ktoru ukazuje smernik aktualnyZaznam
                predchZaznam->dalsia=aktualnyZaznam;    //smernik v strukture dalsia na ktoru ukazuje smernik predchZaznam sa rovna adrese na ktoru ukazuje aktualnyZaznam
                ++pocet;
            }
            if(aktualnyZaznam==NULL)                //ak sa smernik aktualnyZaznam rovna NULL
            {
                aktualnyZaznam=novyZaznam;          //adresa aktualnehoZaznamu sa rovna adrese novehoZaznamu
                predchZaznam->dalsia=aktualnyZaznam;//smernik v strukture dalsia na ktoru ukazuje smernik predchZaznam sa rovna adrese na ktoru ukazuje aktualnyZaznam
            }
        }
        if(*prvyZaznam==NULL)   //ak smernik prvyZaznam ukazuje na NULL
        {
            *prvyZaznam=(KNIZNICA*)malloc(sizeof(KNIZNICA));            //program alokuje pamat pre smernik novyZaznam o velkosti typu KNIZNICA
            fgets((*prvyZaznam)->signatura,VELKOST_SIGNATURA,stdin);    //nacita zo suboru riadok do velkosti konstanty VELKOST_SIGNATURA a ulozi ho do retazca signatura v strukture na ktoru ukazuje smernik prvyZaznam
            fgets((*prvyZaznam)->ISBN,VELKOST_ISBN,stdin);              //nacita zo suboru riadok do velkosti konstanty VELKOST_ISBN a ulozi ho do retazca signatura v strukture na ktoru ukazuje smernik prvyZaznam
            fgets((*prvyZaznam)->nazovKnihy,VELKOST_NAZOV_KNIHY,stdin); //nacita zo suboru riadok do velkosti konstanty VELKOST_NAZOV_KNIHY a ulozi ho do retazca signatura v strukture na ktoru ukazuje smernik prvyZaznam
            fgets((*prvyZaznam)->autori,VELKOST_AUTORI,stdin);          //nacita zo suboru riadok do velkosti konstanty VELKOST_AUTORI a ulozi ho do retazca signatura v strukture na ktoru ukazuje smernik prvyZaznam
            scanf("%d",&(*prvyZaznam)->datumVypozicania);               //nacita cislo zo suboru a ulozi ho do premenej datumVypozicania v strukture na ktoru ukazuje smernik prvyZaznam
            scanf("%d",&(*prvyZaznam)->cisloPreukazu);                  //nacita cislo zo suboru a ulozi ho do premenej cisloPreukazu v strukture na ktoru ukazuje smernik prvyZaznam
            (*prvyZaznam)->dalsia=NULL;                                 //priradenie smerniku v strukture na ktoru ukazuje smernik prvyZaznam hodnotu NULL
        }
    }
}
void zmazUdaje(KNIZNICA **prvyZaznam)               //funkcia s nazvom zmazUdaje
{
    KNIZNICA *predchZaznam=NULL;            //deklaracia smernika na struktury s nazvom predchZaznam
    KNIZNICA *aktualnyZaznam=NULL;          //deklaracia smernika na struktury s nazvom aktualnyZaznam
    KNIZNICA *temp=NULL;                    //deklaracia smernika na struktury s nazvom temp
    char hladanyRetazec[VELKOST_AUTORI];    //deklaracia retazca z nazvom hladanyRetazec velkosti konstanty VELKOST_AUTORI
    char autorTemp[VELKOST_AUTORI];         //deklaracia retazca z nazvom autorTemp velkosti konstanty VELKOST_AUTORI
    int pocet=0;                            //deklaracia celociselnej premennej pocet a jej nasledne inicializovanie na nula
    int i;                                  //deklaracia pocitadla prveho stupna

    scanf("%s",hladanyRetazec);                 //nacitanie retazca hladanyRetazec z klavesnice
    predchZaznam=aktualnyZaznam=*prvyZaznam;    //adrese smernika predchZaznam a aktualnyZaznam sa priradi adresa smernika prvyZaznam
    while(aktualnyZaznam!=NULL)                 //dokial sa smernik aktualnyZaznam nerovna NULL
    {
        strcpy(autorTemp,aktualnyZaznam->autori);   //volanie funkcie strcpy ktora nakopiruje do danej struktury autori retazec autorTemp
        for(i=0;hladanyRetazec[i];++i)              //vsetky velke pismena v retazci hladanyRetazec zmeni na male
        {
            hladanyRetazec[i]=(char)tolower(hladanyRetazec[i]);
        }
        for(i=0;autorTemp[i];++i)                   //vsetky velke pismena v retazci autorTemp zmeni na male
        {
            autorTemp[i]=(char)tolower(autorTemp[i]);
        }
        if(strstr(autorTemp,hladanyRetazec)!=NULL)  //ak sa podretazec autorTemp nachadza v retazci hladany retazec
        {
            if (aktualnyZaznam==*prvyZaznam)    //ak sa adresa smernika aktualnyZaznam rovna adrese smernika prvyZaznam
            {
                temp=*prvyZaznam;               //adresa smernika temp sa rovna adrese smernika prvyZaznam
                *prvyZaznam=temp->dalsia;       //adresa prvehoZaznamu sa rovna smerniku dalsia v strukture na ktoru ukazuje smernik temp
                free(temp);                     //uvolnenie pamate na ktoru ukazuje smernik temp
                aktualnyZaznam=*prvyZaznam;     //adresa smernika aktualnyZaznam sa rovna adrese smernika prvyZaznam
            }
            else    //ak if neprebehne
            {
                predchZaznam->dalsia=aktualnyZaznam->dalsia;    //adresa smerniku dalsia v strukture na ktoru ukazuje smernik predchZaznam sa rovna adrese smernika dalsia v strukture na ktoru ukazuje smernik aktualnyZaznam
                free(aktualnyZaznam);                           //uvolnenie pamate na ktoru ukazuje smernik aktualnyZaznam
                aktualnyZaznam=predchZaznam->dalsia;            //adresa aktualnehoZaznamu sa rovna smerniku dalsia v strukture na ktoru ukazuje smernik predchZaznam
            }
            ++pocet;        //povysenie premennej pocet o jedna
        }
        else                                        //ak neprebehne if
        {
            predchZaznam=aktualnyZaznam;            //adresa v smerniku predchZaznam sa rovna adrese smernika aktualnyZaznam
            aktualnyZaznam=aktualnyZaznam->dalsia;  //adresa aktualnehoZaznamu sa rovna smerniku dalsia v strukture na ktoru ukazuje smernik aktualnyZaznam
        }
    }
    printf("Vymazalo sa %d zaznamov\n",pocet);  //program vypise na obrazovku pocet vymazanych zaznamov
}
void vyhladajUdaje(KNIZNICA *prvyZaznam)            //funkcia s nazvom vyhladajUdaje
{
    KNIZNICA *aktualnyZaznam;   //deklaracia smernika na struktury s nazvom aktualnyZaznam
    int preukaz;                //deklaracia celociselnej premennej preukaz
    int pocet=0;                //deklaracia celociselnej premennej pocet a jej nasledna inicializacia na nula
    int naslo=0;                //deklaracia celociselnej premennej naslo a jej nasledna inicializacia na nula

    scanf("%d",&preukaz);       //nacitanie hodnoty preukaz z klavesnice
    aktualnyZaznam=prvyZaznam;  //adresa smernika aktualnyZaznam sa rovna adrese smernika prvyZaznam
    while(aktualnyZaznam!=NULL) //dokial sa smernik aktualnyZaznam nerovna NULL
    {
        if(aktualnyZaznam->cisloPreukazu==preukaz)  //ak sa hodnota cislaPreukazu danej struktury rovna nacitanemu preukazu
        {
            printf("%d.\n",++pocet);                            //vypisanie na obrazovku poradia danych struktur
            printf("signatura: %s",aktualnyZaznam->signatura);  //program vypise na obrazovku retazec signaturu v danom zazname
            printf("isbn: %s",aktualnyZaznam->ISBN);            //program vypise na obrazovku retazec ISBN v danom zazname
            printf("nazov: %s",aktualnyZaznam->nazovKnihy);     //program vypise na obrazovku retazec nazovKnihy v danom zazname
            printf("autori: %s",aktualnyZaznam->autori);        //program vypise na obrazovku retazec autori v danom zazname
            printf("datum: %d\n",aktualnyZaznam->datumVypozicania); //program vypise na obrazovku premennu datum v danom zazname
            printf("preukaz: %d\n",aktualnyZaznam->cisloPreukazu);  //program vypise na obrazovku premennu preukaz v danom zazname
            naslo=1;
        }
        aktualnyZaznam=aktualnyZaznam->dalsia;  //posunutie smernika v spajanom zozname struktur o jedno miesto
    }
    if(naslo==0)printf("Pre dane cislo preukazu neevidujeme vypozicky\n");  //ak sa nenasla zhoda (neprebehol if) tak program vypise na obrazovku ze nenasiel zhodu
}
void zmenUdaje(KNIZNICA *prvyZaznam)                //funkcia s nazvom zmenUdaje
{
    KNIZNICA *aktualnyZaznam=NULL;      //deklaracia smernika na struktury s nazvom aktualnyZaznam
    int pocet=0;                        //deklaracia celociselnej premennej pocet a jej nasledna inicializacia na nulu
    int datum;                          //deklaracia celociselnej premennej datum

    scanf("%d",&datum);                 //nacitanie hodnoty premennej datum z klavesnice
    aktualnyZaznam=prvyZaznam;          //adrese smernika aktualnyZaznam sa priradi adresa smernika prvyZaznam
    while(aktualnyZaznam!=NULL)         //dokial sa smernik aktualnyZaznam nerovna NULL
    {
        if(aktualnyZaznam->datumVypozicania<=datum) //ak v danej strukture na ktoru ukazuje smernik aktualnyZaznam je velkost cisla datumVypozicania mensi alebo rovny ako zadany datum
        {
            aktualnyZaznam->datumVypozicania+=10000;    //pripocitanie datumuVypocitania hodnotu 10000
            ++pocet;                                    //povysenie premennej pocet o jedna
        }
        aktualnyZaznam=aktualnyZaznam->dalsia;          //posunutie smernika v spajanom zozname struktur o jedno miesto
    }
    printf("Aktualizovalo sa %d zaznamov\n",pocet);     //program vypise na obrazovku hodnotu premennej pocet teda pocet aktualizovanych zaznamov
}
int main()                                          //hlavna funkcia main
{
    FILE *fr;                   //deklaracia suboru na citanie
    KNIZNICA *prvyZaznam=NULL;  //deklaracia smernika prvyZaznam a nasledovna inicializacia ho na NULL
    char znak;                  //deklaracia premennej typu znak

    while((znak=(char)getchar())!='k')          //dokial sa nenacita znak z klavesnice 'k'
    {
        switch(znak)    //rozvetvenie programu podla zadaneho vstupu
        {
            case'n':    //ak sa vstup rovna 'n'
            {
                if((fr=fopen(FILENAME,"r"))==NULL)  //ak neeexistuje subor na citanie s nazvom kniznica.txt program vypise chybu a vrati hodnotu 1
                {
                    printf("Zaznamy neboli nacitane\n");
                    return 1;
                }
                nacitajUdaje(fr,&prvyZaznam);   //ak program pokracuje teda neprebehol if main zavola funkciu nacitajUdaje
                if(fclose(fr)==EOF)return 1;    //ak sa subor nepodarilo zatvorit program vrati hodnotu 1 a ukonci sa
                break;                          //program sa vrati na zaciatok switchu a ignoruje ostatne moznosti vstupu
            }
            case'v':                            //ak sa vstup rovna 'v'
            {
                vypisUdaje(prvyZaznam);         //main zavola funkciu vypisUdajek

                break;                          //program sa vrati na zaciatok switchu a ignoruje ostatne moznosti vstupu
            }
            case'p':                            //ak sa vstup rovna 'p'
            {
                pridajUdaje(&prvyZaznam);       //main zavola funkciu pridajUdaje
                break;                          //program sa vrati na zaciatok switchu a ignoruje ostatne moznosti vstupu
            }
            case'z':                            //ak sa vstup rovna 'z'
            {
                zmazUdaje(&prvyZaznam);         //main zavola funkciu zmazUdaje
                break;                          //program sa vrati na zaciatok switchu a ignoruje ostatne moznosti vstupu
            }
            case'h':                            //ak sa vstup rovna 'h'
            {
                vyhladajUdaje(prvyZaznam);      //main zavola funkciu vyhladajUdaje
                break;                          //program sa vrati na zaciatok switchu a ignoruje ostatne moznosti vstupu
            }
            case'a':                            //ak sa vstup rovna 'a'
            {
                zmenUdaje(prvyZaznam);          //main zavola funkciu zmenUdaje
                break;                          //program sa vrati na zaciatok switchu a ignoruje ostatne moznosti vstupu
            }
            case'k':                            //ak sa vstup rovna 'k'
            {
                dealokaciaUdaje(&prvyZaznam);   //main zavola funkciu dealokaciaUdaje
                break;                          //program sa vrati na zaciatok switchu a ignoruje ostatne moznosti vstupu
            }
            default:break;                      //ak pouzivatel zadal iny znak ako bolo vo volbe program sa vrati na zaciatok switchu a ignoruje ostatne moznosti vstupu
        }
    }
    return 0;                       //ak prebehlo vsetko v poriadku a bol zadany vstup 'k' program sa ukonci
}
