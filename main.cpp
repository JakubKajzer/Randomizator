#include <windows.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "zasoby.h"

#define ID_RADIAL1 501
#define ID_RADIAL2 502
#define ID_BUTTON1 503
#define ID_TEKSTOWE1 504
#define ID_TEKSTOWE2 505
#define ID_TEKSTOWE3 506
#define ID_TEKSTOWE4 507
LPSTR NazwaKlasy = "Klasa Okienka";
MSG Komunikat;
HWND g_hPrzycisk;
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
HFONT hNormalFont =( HFONT ) GetStockObject( DEFAULT_GUI_FONT );
LPSTR BuforILOSC;
DWORD dlugoscILOSC;
HWND hText1;
HWND hText2;
HWND hText3;
HWND hText4;
DWORD dlugoscNAJMNIEJSZA ;
LPSTR BuforNAJMNIEJSZA;
DWORD dlugoscNAJWIEKSZA;
LPSTR BuforNAJWIEKSZA;
DWORD dlugoscNazwa;
LPSTR BuforNazwa;
bool odstep=true; // true to spacja false to enter;
int ilosc_liczb,najmniejsza,najwieksza;
bool flaga_error=false;
HGLOBAL pMusic;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);

    HRSRC hMusic = FindResource( hInstance, MAKEINTRESOURCE( MUZYKA ), RT_RCDATA );
    if( hMusic != NULL )
    {
        pMusic = LoadResource( hInstance, hMusic );
    }

    PlaySoundA ((LPCSTR)MUZYKA, hInstance, SND_RESOURCE|SND_LOOP|SND_ASYNC);



    HICON hLogo = LoadIcon( hInstance, MAKEINTRESOURCE( IKONKA ) );
    // WYPEŁNIANIE STRUKTURY
    WNDCLASSEX wc;

    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = hLogo;
    wc.hIconSm = hLogo;
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;

    // REJESTROWANIE KLASY OKNA
    if( !RegisterClassEx( & wc ) )
    {
        MessageBox( NULL, "Wysoka Komisja odmawia rejestracji tego okna!", "Niestety...",MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }

    // TWORZENIE OKNA
    HWND hwnd;

    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy, "Generator liczb losowych", WS_OVERLAPPED + WS_CAPTION + WS_SYSMENU,CW_USEDEFAULT, CW_USEDEFAULT, 320, 210, NULL, NULL, hInstance, NULL );

    if( hwnd == NULL )
    {
        MessageBox( NULL, "Okno odmówiło przyjścia na świat!", "Ale kicha...", MB_ICONEXCLAMATION );
        return 1;
    }
    HWND hStatic = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 0, 0, 320, 210, hwnd, NULL, hInstance, NULL );

    g_hPrzycisk = CreateWindowEx( 0, "BUTTON", "GENERUJ!", WS_CHILD | WS_VISIBLE | SS_CENTER ,60, 110, 200, 60, hwnd,(HMENU) ID_BUTTON1, hInstance, NULL );

    hStatic = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 0, 0, 400, 20, hwnd, NULL, hInstance, NULL );
    SendMessage( hStatic, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    SetWindowText( hStatic, "Witaj w generatorze liczb losowych by Jakub Kajzer" );

    hStatic = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 120, 25, 400, 20, hwnd, NULL, hInstance, NULL );
    SendMessage( hStatic, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    SetWindowText( hStatic, "Nazwa pliku:" );

    hText1 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER , 190, 20, 100, 25, hwnd,(HMENU) ID_TEKSTOWE1, hInstance, NULL );
    SendMessage( hText1, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    SetWindowText( hText1, "losowe" );

    hStatic = CreateWindowExW( 0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 120, 45, 400, 20, hwnd,NULL, hInstance, NULL );
    SendMessageW( hStatic, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    SetWindowTextW( hStatic, L"Ilość liczb:" );

    hText2 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER , 190, 40, 100, 25, hwnd, (HMENU)ID_TEKSTOWE2, hInstance, NULL );
    SendMessage( hText2, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    SetWindowText( hText2, "0" );


    hStatic = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 120, 65, 400, 20, hwnd, NULL, hInstance, NULL );
    SendMessage( hStatic, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    SetWindowText( hStatic, "Najmniejsza:" );

    hText3 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER , 190, 60, 100, 25, hwnd, (HMENU) ID_TEKSTOWE3, hInstance, NULL );
    SendMessage( hText3, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    SetWindowText( hText3, "0" );


    hStatic = CreateWindowExW( 0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 120, 85, 400, 20, hwnd, NULL, hInstance, NULL );
    SendMessageW( hStatic, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    SetWindowTextW( hStatic, L"Największa:" );

    hText4 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER , 190, 80, 100, 25, hwnd, (HMENU) ID_TEKSTOWE4, hInstance, NULL );
    SendMessage( hText4, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    SetWindowText( hText4, "0" );

    hStatic = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 295, 25, 400, 20, hwnd, NULL, hInstance, NULL );
    SendMessage( hStatic, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    SetWindowText( hStatic, ".txt" );

    g_hPrzycisk = CreateWindowEx( 0, "BUTTON", "Spacja", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,15, 40, 60, 20, hwnd,( HMENU ) ID_RADIAL1, hInstance, NULL );
    SendMessage( g_hPrzycisk, WM_SETFONT,( WPARAM ) hNormalFont, 0 );
    CheckDlgButton( hwnd, ID_RADIAL1, BST_CHECKED );
    g_hPrzycisk = CreateWindowEx( 0, "BUTTON", "Enter", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,15, 60, 60, 20, hwnd,( HMENU ) ID_RADIAL2, hInstance, NULL );
    SendMessage( g_hPrzycisk, WM_SETFONT,( WPARAM ) hNormalFont, 0 );

    g_hPrzycisk = CreateWindowExW( 0, L"BUTTON",L"Rodzaj odstępu:", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,10, 20, 90, 65, hwnd, NULL, hInstance, NULL );
    SendMessageW( g_hPrzycisk, WM_SETFONT,( WPARAM ) hNormalFont, 0 );


    ShowWindow( hwnd, nCmdShow ); // Pokaż okienko...
    UpdateWindow( hwnd );

    // Pętla komunikatów
    while( GetMessage( & Komunikat, NULL, 0, 0 ) )
    {
        TranslateMessage( & Komunikat );
        DispatchMessage( & Komunikat );
    }
    return Komunikat.wParam;
}

// OBSŁUGA ZDARZEŃ
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

    switch( msg )
    {
        case WM_COMMAND:
        switch( wParam )
        {
        case ID_RADIAL1:
            odstep=true;
            break;

        case ID_RADIAL2:
            odstep=false;
            break;
        case ID_BUTTON1:
                std::string nazwa;
                dlugoscNazwa = GetWindowTextLength( hText1 );
                BuforNazwa =( LPSTR ) GlobalAlloc( GPTR, dlugoscNazwa + 1 );
                GetWindowText( hText1, BuforNazwa, dlugoscNazwa + 1 );
                nazwa=(std::string)BuforNazwa+".txt";

                dlugoscILOSC = GetWindowTextLength( hText2 );
                BuforILOSC =( LPSTR ) GlobalAlloc( GPTR, dlugoscILOSC + 1 );
                GetWindowText( hText2, BuforILOSC, dlugoscILOSC + 1 );
                ilosc_liczb=atoi( BuforILOSC );

                if(ilosc_liczb<=0) flaga_error=true;

                dlugoscNAJMNIEJSZA = GetWindowTextLength( hText3 );
                BuforNAJMNIEJSZA =( LPSTR ) GlobalAlloc( GPTR, dlugoscNAJMNIEJSZA + 1 );
                GetWindowText( hText3, BuforNAJMNIEJSZA, dlugoscNAJMNIEJSZA + 1 );
                najmniejsza=atoi( BuforNAJMNIEJSZA );

                dlugoscNAJWIEKSZA = GetWindowTextLength( hText4 );
                BuforNAJWIEKSZA =( LPSTR ) GlobalAlloc( GPTR, dlugoscNAJWIEKSZA + 1 );
                GetWindowText( hText4, BuforNAJWIEKSZA, dlugoscNAJWIEKSZA + 1 );
                najwieksza=atoi( BuforNAJWIEKSZA );

                if(najmniejsza >=najwieksza)flaga_error=true;

            if(flaga_error)
            {
                MessageBoxW( hwnd, L"Wprowadzono nieprawidłowe dane.", L"Błąd", MB_ICONERROR);
                flaga_error=false;
            }
            else
            {
                srand(time( NULL));
                std::ofstream wyjscie(nazwa.c_str());
                for(int i = 0; i < ilosc_liczb; i++)
                    {
                        if(odstep)
                        wyjscie << ( std::rand() % abs(najwieksza-najmniejsza+1) ) + najmniejsza<<" ";
                        else
                        wyjscie << ( std::rand() % abs(najwieksza-najmniejsza+1) ) + najmniejsza<<std::endl;
                    }
                GlobalFree(BuforILOSC);
                GlobalFree(BuforNAJMNIEJSZA);
                GlobalFree(BuforNAJWIEKSZA);
                GlobalFree(BuforNazwa);
                wyjscie.close();
                MessageBox( hwnd, "Plik wygenerowano.", "Komunikat", MB_ICONASTERISK );
                PostQuitMessage( 0 );
                FreeConsole();
            }
            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow( hwnd );
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;

        default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
    }

    return 0;
}
