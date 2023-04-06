#include <stdio.h>

void main()
{
    int ano_a, mes_a, dia_a;
    int resp, horas;
    int anos, meses, dias;
    printf("ANO ATUAL: ");
    scanf("%d", &ano_a);
    printf("MES ATUAL: ");
    scanf("%d", &mes_a);
    printf("DIA ATUAL: ");
    scanf("%d", &dia_a);

    printf("De qual forma deseja fornecer o tempo vivido: ");
    printf("\n[1] em horas;");
    printf("\n[2] em dias");
    printf("\n[3] em dias/meses/anos");
    printf("\nEscolha usando o respectivo numero, digite: ");
    scanf("%d", &resp);

    switch(resp)
    {
        case 1:
        {
            printf("Horas vividas: ");
            scanf("%d", &horas);
            //seu calculo
            anos = horas/8760;
            meses = anos*12;
            dias = meses%30;
            meses = (mes_a * 30.417 - dias)/30.417;
            dias = (mes_a - meses)*30.417;

            printf("\n%d/%d/%d", dias, meses, anos);
            //meu calculo
            dias = horas/24;
            meses = dias/30.417;
            dias = dias % 30;
            anos = meses/12;
            meses = meses % 12;

            printf("\n%d/%d/%d", dias, meses, anos);
            //minha esimativa nascimento
            dias = dia_a - dias;
            if(dias <= 0)
            {
                dias = 30 + dias;
            }
            meses = mes_a - meses;
            if(meses <= 0)
            {
                meses = 12 + meses;
            }
            anos = ano_a - anos;
            printf("\n%d/%d/%d\n", dias, meses, anos);
            break;
        }
    }
}
