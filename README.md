# cpp-salary-calculato
Console-based Salary Calculator built with C++. Features robust input validation and clean code structure.
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

// Pozitif double değer almak için fonksiyon
double getPositiveDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value && value >= 0 && ss.eof()) return value;
        cout << "Gecersiz giris. Lutfen gecerli bir pozitif sayi girin.\n";
    }
}

// Sadece harf ve boşluk içeren string kontrol fonksiyonu
bool isAllLetters(const string& str) {
    for (char c : str)
        if (!isalpha(c) && !isspace(c)) return false;
    return true;
}

int main() {
    // Uygulama başında kullanıcıyı bilgilendirme
    cout << "Isim, soyad yazarken Ingilizce klavyeye gore yaziniz.\n";
    cout << "Girceginiz sayi kusurlu sayi ise (ornek: 0.9, 2.1, 99.99) seklinde yaziniz.\n\n";
    
    char restart;
    do {
        string firstName, lastName;
        
        // Ad ve soyad girişi
        cout << "Personelin adini girin: ";
        getline(cin, firstName);
        while (!isAllLetters(firstName)) {
            cout << "Gecersiz ad. Lutfen sadece harf kullanin: ";
            getline(cin, firstName);
        }

        cout << "Personelin soyadini girin: ";
        getline(cin, lastName);
        while (!isAllLetters(lastName)) {
            cout << "Gecersiz soyad. Lutfen sadece harf kullanin: ";
            getline(cin, lastName);
        }

        // Haftalık saatlerin alınması ve toplamının hesaplanması
        double totalHours = 0;
        for (int i = 1; i <= 4; ++i) {
            double hours = getPositiveDouble("Hafta " + to_string(i) + " icin saat sayisini girin: ");
            totalHours += hours;
        }

        // Saatlik ücret ve toplam maaş hesaplama
        double hourlyRate = getPositiveDouble("Saatlik ucreti girin: ");
        double totalEarnings = totalHours * hourlyRate;

        // Toplam satış ve prim oranının alınması ve prim hesaplama
        double totalSales = getPositiveDouble("Toplam satis miktarini girin: ");
        double commissionRate = getPositiveDouble("Prim oranini (yuzde olarak) girin: ") / 100.0;
        double commission = totalSales * commissionRate;

        // Raporun yazdırılması
        cout << fixed << setprecision(2);
        cout << "\nCalisma Raporu:\n";
        cout << "Personelin Adi: " << firstName << endl;
        cout << "Personelin Soyadi: " << lastName << endl;
        cout << "4 haftalik toplam calisma saati: " << totalHours << " saat\n";
        cout << "Saatlik ucret: " << hourlyRate << " TL\n";
        cout << "Alinmasi Gereken Maas: " << totalEarnings << " TL\n";
        cout << "Toplam Satis: " << totalSales << " TL\n";
        cout << "Prim Orani: " << (commissionRate * 100) << " %\n";
        cout << "Prim: " << commission << " TL\n";
        cout << "Toplam Maas: " << (totalEarnings + commission) << " TL\n";

        // Yeniden başlatma veya kapatma
        cout << "\nYeniden baslatmak icin '+' tusuna, uygulamayi kapatmak icin '-' tusuna basin: ";
        cin >> restart;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Önceki girişten kalan yeni satır karakterini temizle

    } while (restart == '+');

    return 0;
}
