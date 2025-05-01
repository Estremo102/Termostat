# Termostat
Projekt w ramach ideii DIY. Powstał on na potrzeby regulacji temperatury na mieszkaniu, we współpracy z piecem Ariston HS PREMIUM 24 EU2, jednak wiele piecy działa na podobnej zasadzie, a więc urządzenie to jest kompatybilne z wieloma modelami. 

Z pieca można wyprowadzić kabel który po zwarciu uruchamia grzanie, mechanizm działania termostatu jest więc prosty. Mikrokontroler na podstawie danych z czujnika temperatury zmienia stan switcha który jest połączony z piecem za pomocą dwużyłowego kabla. Aby móc łatwo regulować temperaturę termostat został wyposażony w enkoder cyfrowy oraz wyświetlacz.

Użyty czujnik zbiera informacje nie tylko o temperaturze, ale także o wilgotności, dlatego ta informacja jest wyświetlana obok temperatury, temperatury zadanej oraz histerezy.

Projekt płytki PCB można znaleźć w pliku Termostat_PCB.psb, użyte przeze mnie komponenty to:
mikrokontroler arduino nano
 wyświetlacz to 1.8 TFT SPI 128x160 V1.1
 czujnik temperatury i wilgoci AHT10
 switch JQC-3FF-S-Z
 Enkoder cyfrowy Cap EC11