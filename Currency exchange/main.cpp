#include<iostream>
#include<string>
#include <windows.h>
#include<fstream>
#include<deque>
#pragma comment(lib, "urlmon.lib")

using namespace std;

void SaveToFile(const char* destination, const char* URL);

int main() {
    setlocale(LC_ALL, "Russian");
    wstring container, result,temp;
    string srcURL = "https://api.privatbank.ua/p24api/pubinfo?exchange&coursid=5";
    string destFile = "privat.txt";
    SaveToFile(destFile.c_str(), srcURL.c_str());
    std::ios::sync_with_stdio(false);
    wifstream OutFile(destFile.c_str(), ios::in | ios::_Nocreate);
    if (OutFile.is_open()) {
        while (!OutFile.eof()) {
            getline(OutFile, temp);
            container.append(temp);
        }
    }
    cout << "\n\nPrivatbank:\n";
    for (int i = container.find(L"buy\":\"") + sizeof("buy\":\"") - 1; container[i] != '"'; i++)result.push_back(container[i]);
    wcout << "EUR:\t\t" << result << endl;
    result.clear();
    for (int i = container.rfind(L"buy\":\"") + sizeof("buy\":\"") - 1; container[i] != '"'; i++)result.push_back(container[i]);
    wcout << "USD:\t\t" << result << endl;
    result.clear();
    temp.clear();
    OutFile.close();
    container.clear();


    deque<TCHAR>resGovBank;

    srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchangenew?json";
    destFile = "govbank.txt";
    SaveToFile(destFile.c_str(), srcURL.c_str());

    OutFile.open(destFile.c_str(), ios::in | ios::_Nocreate);
    if (OutFile.is_open()) {
        while (!OutFile.eof()) {
            getline(OutFile, temp);
            container.append(temp);
        }
    }
    cout << "\n\nGov. bank:\n";
    for (int i = container.find(L",\"cc\":\"EUR\"") - 1; container[i] != ':'; i--)
        resGovBank.push_front(container[i]);
    for (int i = 0; i < resGovBank.size(); i++) {
        result.push_back(resGovBank[i]);
    }
    wcout << "EUR:\t\t" << result << endl;
    resGovBank.clear();
    result.clear();
    for (int i = container.find(L",\"cc\":\"USD\"")  - 1; container[i] != ':'; i--)
        resGovBank.push_front(container[i]);
    for (int i = 0; i < resGovBank.size(); i++) {
        result.push_back(resGovBank[i]);
    }
    wcout << "USD:\t\t" << result << endl;
    result.clear();
    OutFile.close();
    container.clear();
}

void SaveToFile(const char* destination, const char* URL) {
    if (S_OK != URLDownloadToFileA(NULL, URL, destination, 0, NULL))
    {
        cout << "Downloadinf error\n";
        exit(-5);
    }
}