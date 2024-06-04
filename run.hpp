#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <string>
#include "OpenAddressingHash.hpp"
#include "ChainedHash.hpp"
#include "CuckooHash.hpp"
#include "Timer.hpp"

void run() {
    Timer timer;
    int choice = 0;

    while (choice != 4) {
        std::cout << "Wybierz strukture dla tablicy mieszajacej:" << std::endl;
        std::cout << "1. Tablica mieszajaca z adresowaniem otwartym" << std::endl;
        std::cout << "2. Tablica mieszajaca z lancuchowa metoda" << std::endl;
        std::cout << "3. Tablica mieszajaca z Cuckoo Hashing" << std::endl;
        std::cout << "4. Wyjdz" << std::endl;

        std::cin >> choice;
        system("cls");

        if (choice == 1) {
            OpenAddressingHash hashTable(40000);
            int innerChoice = 0;
            while (innerChoice != 5) {
                std::cout << "Wybrano tablice mieszajaca z adresowaniem otwartym." << std::endl;
                std::cout << "Wybierz operacje:" << std::endl;
                std::cout << "1. Wstawienie nowej wartosci" << std::endl;
                std::cout << "2. Usuniecie pary zwiazanej z kluczem" << std::endl;
                std::cout << "3. Generowanie losowych liczb" << std::endl;
                std::cout << "4. Wyswietlenie tablicy" << std::endl;
                std::cout << "5. Powrot do wyboru struktury" << std::endl;
                std::cin >> innerChoice;

                switch (innerChoice) {
                case 1: {
                    system("cls");
                    int klucz;
                    std::string wartosc;
                    double totalElapsedTime = 0.0;
                    std::cout << "Podaj klucz: ";
                    std::cin >> klucz;
                    std::cout << "Podaj wartosc: ";
                    std::cin >> wartosc;

                    for (int i = 0; i < 100; ++i) {
                        OpenAddressingHash hashTableCopy = hashTable; // Tworzenie kopii
                        timer.start();
                        hashTableCopy.insert(klucz, wartosc);
                        timer.stop();
                        totalElapsedTime += timer.elapsed_nanoseconds();
                    }

                    double averageTime = totalElapsedTime / 100.0;
                    std::cout << "Sredni czas wykonania operacji: " << averageTime << " ns" << std::endl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Czyszczenie bufora wejścia
                    std::cout << "Naciśnij Enter, aby kontynuowac...";
                    std::cin.get(); // Oczekiwanie na naciśnięcie Enter
                    break;
                }
                case 2: {
                    system("cls");
                    double totalElapsedTime = 0.0;
                    int key;
                    std::cout << "Podaj klucz do usuniecia: ";
                    std::cin >> key;
                    for (int i = 0; i < 100; ++i) {
                        OpenAddressingHash hashTableCopy = hashTable; // Tworzenie kopii
                        timer.start();
                        hashTableCopy.remove(key);
                        timer.stop();
                        totalElapsedTime += timer.elapsed_nanoseconds();
                    }
                    double averageTime = totalElapsedTime / 100.0;
                    std::cout << "Sredni czas wykonania operacji: " << averageTime << " ns" << std::endl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Czyszczenie bufora wejścia
                    std::cout << "Naciśnij Enter, aby kontynuowac...";
                    std::cin.get(); // Oczekiwanie na naciśnięcie Enter
                    break;
                }
                case 3: {
                    system("cls");
                    int dataSize;
                    std::cout << "Podaj ilosc danych do wygenerowania:" << std::endl;
                    std::cin >> dataSize;
                    for (int i = 0; i < dataSize; ++i) {
                        int key = rand() % 1000;
                        std::string value = "Wartosc " + std::to_string(i);
                        hashTable.insert(key, value);
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Czyszczenie bufora wejścia
                    std::cout << "Naciśnij Enter, aby kontynuowac...";
                    std::cin.get(); // Oczekiwanie na naciśnięcie Enter
                    break;
                }
                case 4: {
                    system("cls");
                    std::cout << "Tablica mieszajaca z adresowaniem otwartym:" << std::endl;
                    hashTable.print();
                    std::cout << "Naciśnij Enter, aby kontynuowac...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    break;
                }

                case 5:
                    system("cls");
                    break;
                }
            }
        }
        if (choice == 2) {
            ChainedHash hashTable(40000);
            int innerChoice = 0;
            while (innerChoice != 5) {
                std::cout << "Wybrano tablice mieszajaca z lancuchowa metoda." << std::endl;
                std::cout << "Wybierz operacje:" << std::endl;
                std::cout << "1. Wstawienie nowej wartosci" << std::endl;
                std::cout << "2. Usuniecie pary zwiazanej z kluczem" << std::endl;
                std::cout << "3. Generowanie losowych liczb" << std::endl;
                std::cout << "4. Wyswietlenie tablicy" << std::endl;
                std::cout << "5. Powrot do wyboru struktury" << std::endl;
                std::cin >> innerChoice;

                switch (innerChoice) {
                case 1: {
                    system("cls");
                    int klucz;
                    std::string wartosc;
                    double totalElapsedTime = 0.0;
                    std::cout << "Podaj klucz: ";
                    std::cin >> klucz;
                    std::cout << "Podaj wartosc: ";
                    std::cin >> wartosc;

                    for (int i = 0; i < 100; ++i) {
                        ChainedHash hashTableCopy = hashTable; // Tworzenie kopii
                        timer.start();
                        hashTableCopy.insert(klucz, wartosc);
                        timer.stop();
                        totalElapsedTime += timer.elapsed_nanoseconds();
                    }

                    double averageTime = totalElapsedTime / 100.0;
                    std::cout << "Sredni czas wykonania operacji: " << averageTime << " ns" << std::endl;
                    break;
                }
                case 2: {
                    system("cls");
                    double totalElapsedTime = 0.0;
                    int key;
                    std::cout << "Podaj klucz do usuniecia: ";
                    std::cin >> key;
                    try {
                        for (int i = 0; i < 100; ++i) {
                            ChainedHash hashTableCopy = hashTable; // Tworzenie kopii
                            timer.start();
                            hashTableCopy.remove(key);
                            timer.stop();
                            totalElapsedTime += timer.elapsed_nanoseconds();
                        }
                        double averageTime = totalElapsedTime / 100.0;
                        std::cout << "Sredni czas wykonania operacji: " << averageTime << " ns" << std::endl;
                    }
                    catch (const std::runtime_error& e) {
                        std::cerr << "Wyjatek: " << e.what() << std::endl;
                    }
                    break;
                }

                case 3: {
                    system("cls");
                    int dataSize;
                    std::cout << "Podaj ilosc danych do wygenerowania:" << std::endl;
                    std::cin >> dataSize;
                    for (int i = 0; i < dataSize; ++i) {
                        int key = rand() % 1000;
                        std::string value = "Wartosc " + std::to_string(i);
                        hashTable.insert(key, value);
                    }
                    break;
                }
                case 4: {
                    system("cls");
                    std::cout << "Tablica mieszajaca z lancuchowa metoda:" << std::endl;
                    hashTable.print();
                    std::cout << "Naciśnij Enter, aby kontynuowac...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Czyszczenie bufora
                    std::cin.get();
                    break;
                }
                case 5:
                    system("cls");
                    break;
                }
            }
        }
        if (choice == 3) {
            CuckooHash hashTable(15000);
            int innerChoice = 0;
            while (innerChoice != 5) {
                std::cout << "Wybrano tablice mieszajaca z Cuckoo Hashing." << std::endl;
                std::cout << "Wybierz operacje:" << std::endl;
                std::cout << "1. Wstawienie nowej wartosci" << std::endl;
                std::cout << "2. Usuniecie pary zwiazanej z kluczem" << std::endl;
                std::cout << "3. Generowanie losowych liczb" << std::endl;
                std::cout << "4. Wyswietlenie tablicy" << std::endl;
                std::cout << "5. Powrot do wyboru struktury" << std::endl;

                std::cin >> innerChoice;
                switch (innerChoice) {
                case 1: {
                    system("cls");
                    int klucz;
                    std::string wartosc;
                    double totalElapsedTime = 0.0;
                    std::cout << "Podaj klucz: ";
                    std::cin >> klucz;
                    std::cout << "Podaj wartosc: ";
                    std::cin >> wartosc;

                    for (int i = 0; i < 100; ++i) {
                        CuckooHash hashTableCopy(hashTable); // Tworzenie kopii
                        timer.start();
                        hashTableCopy.insert(klucz, wartosc);
                        timer.stop();
                        totalElapsedTime += timer.elapsed_nanoseconds();
                    }

                    double averageTime = totalElapsedTime / 100.0;
                    std::cout << "Sredni czas wykonania operacji: " << averageTime << " ns" << std::endl;
                    break;
                }
                case 2: {
                    system("cls");
                    double totalElapsedTime = 0.0;
                    int key;
                    std::cout << "Podaj klucz do usuniecia: ";
                    std::cin >> key;
                    for (int i = 0; i < 100; ++i) {
                        CuckooHash hashTableCopy(hashTable); // Tworzenie kopii
                        timer.start();
                        hashTableCopy.remove(key);
                        timer.stop();
                        totalElapsedTime += timer.elapsed_nanoseconds();
                    }
                    double averageTime = totalElapsedTime / 100.0;
                    std::cout << "Sredni czas wykonania operacji: " << averageTime << " ns" << std::endl;
                    break;
                }
                case 3: {
                    int dataSize;
                    std::cout << "Podaj ilosc danych do wygenerowania:" << std::endl;
                    std::cin >> dataSize;

                    int successfulInsertsBefore = hashTable.getSuccessfulInserts();
                    for (int i = 0; i < dataSize; ++i) {
                        bool inserted = false;
                        std::string value = "Wartosc " + std::to_string(i);
                        while (!inserted) {
                            int key = rand() % 10000;
                            size_t successfulInsertsAfter = hashTable.getSuccessfulInserts();
                            hashTable.insert(key, value);
                            if (hashTable.getSuccessfulInserts() > successfulInsertsAfter) {
                                inserted = true;
                            }
                        }
                    }
                    int successfulInsertsAfter = hashTable.getSuccessfulInserts();
                    std::cout << "Udalo sie dodac " << (successfulInsertsAfter - successfulInsertsBefore) << " kluczy." << std::endl;

                    break;
                }
                case 4: {
                    system("cls");
                    std::cout << "Tablica mieszajaca z Cuckoo Hashing:" << std::endl;
                    hashTable.print();
                    std::cout << "Naciśnij Enter, aby kontynuowac...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    break;
                }

                case 5:
                    system("cls");
                    break;
                }
            }

        }
        if (choice == 4) {
            break;
        }

    }
}
