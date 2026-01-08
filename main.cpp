#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

// --- Yardımcı Tasarım Fonksiyonları ---
void printLine(int width, char symbol = '-') {
    cout << setfill(symbol) << setw(width) << "" << setfill(' ') << endl;
}

void printHeader(const string& title) {
    printLine(50, '=');
    cout << "|" << setw((50 + title.length()) / 2) << title << setw((50 - title.length()) / 2) << "|" << endl;
    printLine(50, '=');
}

// --- Personel Sınıfı (OOP Tasarımı) ---
class Employee {
private:
    string firstName;
    string lastName;
    vector<double> weeklyHours;
    double hourlyRate;
    double totalSales;
    double commissionRate;

public:
    // Yapıcı Metot
    Employee() : totalSales(0), commissionRate(0), hourlyRate(0) {}

    // Setter Metotları
    void setName(string first, string last) {
        firstName = first;
        lastName = last;
    }

    void addHours(double hours) {
        weeklyHours.push_back(hours);
    }

    void setFinancials(double rate, double sales, double commRate) {
        hourlyRate = rate;
        totalSales = sales;
        commissionRate = commRate;
    }

    // Hesaplama Metotları
    double getTotalHours() const {
        double total = 0;
        for (double h : weeklyHours) total += h;
        return total;
    }

    double calculateBaseSalary() const {
        return getTotalHours() * hourlyRate;
    }

    double calculateCommission() const {
        return totalSales * (commissionRate / 100.0);
    }

    double calculateTotalSalary() const {
        return calculateBaseSalary() + calculateCommission();
    }

    // Rapor Yazdırma (Tasarım Kısmı)
    void printReport() const {
        cout << "\n\n";
        printLine(50, '*');
        string title = "MAAS HESAPLAMA RAPORU";
        cout << "*" << setw((48 + title.length()) / 2) << title << setw((50 - title.length()) / 2) << "*\n";
        printLine(50, '*');

        cout << left << setw(30) << "Personel Adi:" << right << setw(18) << (firstName + " " + lastName) << " \n";
        printLine(50, '-');
        
        cout << left << setw(30) << "Toplam Calisma Saati:" << right << setw(15) << fixed << setprecision(2) << getTotalHours() << " sa\n";
        cout << left << setw(30) << "Saatlik Ucret:" << right << setw(15) << hourlyRate << " TL\n";
        cout << left << setw(30) << "Taban Maas:" << right << setw(15) << calculateBaseSalary() << " TL\n";
        printLine(50, '-');

        cout << left << setw(30) << "Toplam Satis:" << right << setw(15) << totalSales << " TL\n";
        cout << left << setw(30) << "Prim Orani:" << right << setw(14) << commissionRate << " %\n";
        cout << left << setw(30) << "Satis Primi:" << right << setw(15) << calculateCommission() << " TL\n";
        printLine(50, '=');

        cout << left << setw(30) << "ODENECEK NET MAAS:" << right << setw(15) << calculateTotalSalary() << " TL\n";
        printLine(50, '*');
        cout << "\n";
    }
};

// --- Yardımcı Giriş Fonksiyonları ---
double getPositiveDouble(const string& prompt) {
    double value;
    while (true) {
        cout << ">> " << prompt;
        string input;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value && value >= 0 && ss.eof()) return value;
        cout << "   [HATA] Gecersiz giris! Lutfen pozitif bir sayi girin.\n";
    }
}

bool isAllLetters(const string& str) {
    if (str.empty()) return false;
    for (char c : str)
        if (!isalpha(c) && !isspace(c)) return false;
    return true;
}

string getStringInput(const string& prompt) {
    string value;
    while (true) {
        cout << ">> " << prompt;
        getline(cin, value);
        if (isAllLetters(value)) return value;
        cout << "   [HATA] Isim sadece harf icerebilir.\n";
    }
}

// --- Ana Program ---
int main() {
    printHeader("PERSONEL MAAS SISTEMI v2.0");
    cout << "Not: Ondalikli sayilari nokta (.) ile giriniz.\n\n";

    char restart;
    do {
        Employee emp;
        string fName, lName;

        // Giriş Ekranı Tasarımı
        printLine(50, '-');
        cout << "[ADIM 1] Kisisel Bilgiler\n";
        fName = getStringInput("Ad: ");
        lName = getStringInput("Soyad: ");
        emp.setName(fName, lName);

        cout << "\n[ADIM 2] Calisma Saatleri\n";
        for (int i = 1; i <= 4; ++i) {
            emp.addHours(getPositiveDouble("Hafta " + to_string(i) + " saati: "));
        }

        cout << "\n[ADIM 3] Finansal Veriler\n";
        double rate = getPositiveDouble("Saatlik Ucret (TL): ");
        double sales = getPositiveDouble("Toplam Satis (TL): ");
        double comm = getPositiveDouble("Prim Orani (%): ");
        emp.setFinancials(rate, sales, comm);

        // Raporu Göster
        emp.printReport();

        cout << "Yeni hesaplama yapmak icin '+' tusuna, cikis icin '-' tusuna basin: ";
        cin >> restart;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\n";

    } while (restart == '+');

    printHeader("IYI GUNLER DILERIZ");
    return 0;
}
