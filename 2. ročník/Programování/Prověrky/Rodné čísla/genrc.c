/*
*
* Generace rodných validních rodných čísel
* podle data narození pohlaví a 3 číslic
* ========================================
*
* František Rubáček - 11.4.2025
*
*/



#include <stdio.h>
#include <time.h>

#define ROKMIN 1954
#define ROKMAX 2053


int zadaniDatum(){
    int rok, mesic, den;
    //vytvoří strukturu pro čas
    struct tm timeinfo = {0};
    time_t t;

    while (1) {
        printf("Zadejte rok narození (RRRR): ");
        scanf("%d", &rok);
        if (rok >= ROKMIN && rok <= ROKMAX) break;
        printf("Rok musí být v rozmezí %d-%d\n", ROKMIN, ROKMAX);
    }

    while (1) {
        printf("Zadejte měsíc narození (MM): ");
        scanf("%d", &mesic);
        if (mesic >= 1 && mesic <= 12) break;
        printf("Měsíc musí být v rozmezí 1-12\n");
    }

    while (1) {
        printf("Zadejte den narození (DD): ");
        scanf("%d", &den);
        
        // Validuje jestli je den platný s pomocí knihovny time
        timeinfo.tm_year = rok - 1900;
        timeinfo.tm_mon = mesic - 1;
        timeinfo.tm_mday = den;
        
        t = mktime(&timeinfo);
        if (t != -1 && timeinfo.tm_mday == den) {
            break;
        }
        
        printf("Neplatný den! Zkuste znovu.\n");
    }

    printf("Platné datum: %04d-%02d-%02d\n", rok, mesic, den);
    // vypočítá prvních 6 číslic RČ
    return ((rok % 100) * 10000 + mesic * 100 + den);
}

int zadejPohlavi(){
    int pohlavi;
    while (1) {
        printf("Zadejte pohlaví (0 - muž, 1 - žena): ");
        scanf("%d", &pohlavi);
        if (pohlavi == 0 || pohlavi == 1) break;
        printf("Pohlaví musí být 0 nebo 1\n");
    }
    return pohlavi;
}

int zadaniTrojcisli(){
    int trojcisli;
    while (1) {
        printf("Zadejte 3 číslice za lomítkem: ");
        scanf("%d", &trojcisli);
        if (trojcisli >= 0 && trojcisli <= 999) break;
        printf("Číslo musí být v rozmezí 0-999\n");
    }
    return trojcisli;
}

long generace(int datum, int trojcisli){
    int overeni;
    // long bo nechci integer overflow
    long rc;
    int soucet = 0;
    overeni = datum * 1000 + trojcisli;
    rc = datum * 1000 + trojcisli;

    while (overeni > 0) {
        // nechce se mi to dělat pitomě přes for a vybírání každého znaku zvlášť, udělám to líně heh
        soucet += overeni % 10;
        overeni = overeni / 10;
    }
    if (soucet % 11 == 10) {
        rc = rc * 10;
    } else {
        // - 1 protože netuším, bez toho to není validní
        rc = (rc * 10) + (soucet % 11)-1;
    }
    return rc;
}


int main() {
    int opakovani = 0;
    int datum;
    int pohlavi;
    int trojcisli;
    long rc;
    char konecnecislo[12];
    do {
        datum = zadaniDatum();
        pohlavi = zadejPohlavi();
        if (pohlavi == 1) {
            datum = datum + 5000;
        }
        trojcisli = zadaniTrojcisli();
        rc = generace(datum, trojcisli);
        snprintf(konecnecislo, sizeof(konecnecislo), "%06lld/%04lld", rc / 10000, rc % 10000);
        printf("Rodné číslo: %s\n", konecnecislo);
        printf("Chcete generovat další rodné číslo? (0 - ne, 1 - ano): ");
        scanf("%d", &opakovani);
    } while (opakovani == 1);
    return 0;
}
