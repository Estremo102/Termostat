# Termostat DIY

Projekt powstał w ramach idei DIY i został zaprojektowany do regulacji temperatury w mieszkaniu. Został przetestowany we współpracy z piecem **Ariston HS PREMIUM 24 EU2**, jednak dzięki prostemu mechanizmowi działania, może być kompatybilny z wieloma innymi modelami pieców.

## Zasada działania

Większość pieców umożliwia zdalne uruchomienie grzania poprzez zwarcie odpowiednich styków. Termostat wykorzystuje tę możliwość: mikrokontroler steruje stanem przekaźnika (switcha), który łączy lub rozłącza obwód, wywołując działanie pieca.

Termostat zbiera dane z czujnika temperatury i wilgotności, a użytkownik może regulować temperaturę za pomocą enkodera cyfrowego. Wszystkie informacje (temperatura, wilgotność, temperatura zadana oraz histereza) wyświetlane są na ekranie TFT.

## Komponenty

- **Mikrokontroler:** Arduino Nano  
- **Wyświetlacz:** 1.8" TFT SPI 128x160 (wersja V1.1)  
- **Czujnik:** AHT10 (pomiar temperatury i wilgotności)  
- **Przekaźnik (switch):** JQC-3FF-S-Z  
- **Enkoder cyfrowy:** Cap EC11  

## Pliki

- `Termostat_PCB.psb` – projekt płytki PCB w formacie kompatybilnym z [nazwa programu, np. Sprint Layout lub inny, jeśli dotyczy]

## Zdjęcia i schematy



## Licencja

GPL