# RemoteCarSTM32

## Opis systemu

Projekt **RemoteCarSTM32** to zdalnie sterowany samochód oparty na mikrokontrolerach STM32 oraz modułach WiFi ESP8266/ESP32. System składa się z dwóch głównych części:

- **Kontroler (Controller)** – jednostka z manipulatorem (joystickiem), wyposażona w mikrokontroler STM32F303RE oraz moduł WiFi (ESP32). Czyta położenie joysticka i przyciski, a następnie bezprzewodowo przesyła polecenia sterujące do pojazdu.

- **Pojazd (Vehicle)** – jednostka na zdalnie sterowanym samochodzie, także oparta na STM32F303RE i module WiFi (ESP8266, model ESP-01). Odbiera dane sterujące i na ich podstawie kontroluje silniki pojazdu poprzez sterownik silników (DRV8835), a także odczytuje czujniki (np. ultradźwiękowy czujnik odległości HC-SR04).

Komunikacja między kontrolerem a pojazdem odbywa się bezprzewodowo z użyciem protokołu **ESP-NOW** (bezpośrednia komunikacja WiFi między modułami ESP). Dane sterujące (np. wartości wychylenia joysticka) są wysyłane z kontrolera do pojazdu w postaci pakietów binarnych.

## Wykorzystane technologie

- **Mikrokontrolery STM32F303RE** – 32-bitowe układy z rdzeniem ARM Cortex-M4, użyte zarówno w kontrolerze, jak i na pojeździe. Oprogramowanie mikrokontrolerów zostało stworzone w środowisku STM32CubeIDE z wykorzystaniem biblioteki HAL (Hardware Abstraction Layer).
- **Moduły WiFi ESP8266 i ESP32** – moduł ESP32 (np. DevKit) po stronie kontrolera oraz moduł ESP8266 (ESP-01) po stronie pojazdu. Oba moduły zostały zaprogramowane w środowisku Arduino (język C/C++ dla mikrokontrolerów ESP) i komunikują się ze sobą poprzez protokół ESP-NOW.
- **Protokoły komunikacji** – ESP-NOW (szybka komunikacja bezprzewodowa między modułami ESP, niewymagająca sieci WiFi ani routera) oraz UART (połączenie szeregowe między każdym STM32 a odpowiadającym mu modułem ESP do przekazywania danych sterujących).
- **Sterownik silników DRV8835** – dwukanałowy sterownik umożliwiający kontrolę dwóch silników prądu stałego (np. napędowych silników pojazdu) z wykorzystaniem sygnałów PWM i kierunku z mikrokontrolera STM32.
- **Czujnik odległości HC-SR04** – ultradźwiękowy dalmierz zamontowany na pojeździe do pomiaru odległości od przeszkód (opcjonalnie wykorzystywany w oprogramowaniu pojazdu do funkcji bezpieczeństwa).
- **Manipulator analogowy (joystick)** – dwukanałowy joystick analogowy (2 osie + przycisk), podłączony do wejść analogowych (ADC) kontrolera STM32. Służy do ręcznego sterowania prędkością i kierunkiem ruchu pojazdu; wciśnięcie drążka może pełnić funkcję przycisku (np. dodatkowej akcji).

## Struktura projektu

```
RemoteCarSTM32/
├── Controller/       # kod STM32 dla kontrolera (joystick + nadajnik WiFi)
│   ├── Core/         # źródła i nagłówki mikrokontrolera
│   ├── Drivers/      # biblioteki HAL dla STM32F3xx
│   ├── testADC.ioc   # konfiguracja CubeMX
│   └── .project/...  # pliki projektu STM32CubeIDE
├── Vehicle/          # kod STM32 dla pojazdu (odbiornik WiFi + silniki)
│   └── (pełna struktura projektu, gotowa do edycji)
├── esp32/            # kod ESP (Arduino IDE, dwa szkice .ino)
│   ├── wifi_ESP01.ino   # ESP8266 – odbiornik
│   └── wifi_ESP32.ino   # ESP32 – nadajnik
├── docs/             # dokumentacja projektu
│   └── Raport.pdf
├── README.md
└── .gitignore
```



## Instrukcja uruchomienia

1. **Kompilacja oprogramowania STM32 (kontroler):** Otwórz folder `Controller` jako projekt w STM32CubeIDE (plik `.project` oraz konfiguracja są dołączone). Skompiluj firmware dla kontrolera i pojazdu*
2. **Programowanie mikrokontrolerów:** Wgraj skompilowany firmware do odpowiednich płytek STM32F303RE – dla kontrolera oraz dla pojazdu. Można to zrobić za pomocą programatora ST-Link/V2 albo bezpośrednio z STM32CubeIDE (np. jeśli używane są płytki Nucleo z wbudowanym ST-Link).
3. **Programowanie modułów ESP:** 
   - Otwórz `esp32/wifi_ESP32.ino` w Arduino IDE (lub innym środowisku dla ESP32). Wybierz odpowiednią płytkę (np. *ESP32 Dev Module*) oraz port COM. **Uwaga:** Przed kompilacją upewnij się, że adres MAC odbiorcy jest poprawnie ustawiony w kodzie (`receiverMacAddress`). Domyślnie wpisany jest MAC przykładowego modułu ESP-01; jeśli Twój moduł ESP8266 ma inny adres, zmień tę wartość na adres MAC swojego modułu (można go odczytać np. za pomocą funkcji `WiFi.macAddress()` w krótkim szkicu testowym).
   - Otwórz `esp32/wifi_ESP01.ino` w Arduino IDE. Wybierz płytkę **Generic ESP8266 Module** (lub odpowiednią dla posiadanego ESP-01) oraz właściwy port/programator USB-UART. Skompiluj i wgraj ten kod do modułu ESP8266.
4. **Montaż hardware:** Podłącz moduły ESP do odpowiednich mikrokontrolerów STM32. W projekcie wykorzystano interfejs UART4 do komunikacji między STM32 a ESP:
    - Po stronie kontrolera: wyjście TX UART4 (pin PC10 na STM32F303RE) podłącz do wejścia RX modułu ESP32, a RX UART4 (pin PC11) do TX modułu ESP32. Dodatkowo połącz ze sobą masy (GND) obu urządzeń.
    - Po stronie pojazdu: wyjście TX UART4 (PC10) podłącz do RX modułu ESP-01, a RX UART4 (PC11) do TX modułu ESP-01. Połącz również masy układów.
    - Joystick analogowy podłącz do wejść analogowych kontrolera (w kodzie wykorzystano kanały ADC1_IN1 i IN2, odpowiadające pinom PA0 i PA1 na STM32F303RE) oraz wyprowadź przycisk joysticka do cyfrowego wejścia STM32 (w przykładowej konfiguracji użyto wbudowanego przycisku użytkownika na pinie PC13).
    - Silniki DC oraz zasilanie pojazdu podłącz do sterownika DRV8835 zgodnie z dokumentacją sterownika. Wyjścia sterujące z STM32 (sygnały PWM i kierunek) należy połączyć z wejściami sterownika (w kodzie przypisano odpowiednie piny i timery, patrz pliki `drv8835.c` oraz `tim.c`).
    - Czujnik HC-SR04 (opcjonalnie): podłącz wyprowadzenia TRIG i ECHO do wolnych pinów cyfrowych STM32 (zgodnie z konfiguracją w pliku `hc_sr04.c`, gdzie zdefiniowano obsługę tego czujnika).
5. **Uruchomienie systemu:** Włącz zasilanie obu modułów (kontrolera i pojazdu). Po uruchomieniu:
   - Kontroler zacznie odczytywać pozycję joysticka i cyklicznie wysyłać pakiety danych sterujących (wciśnięcie przycisku joysticka również może być obsługiwane – do zaimplementowania według potrzeb).
   - Pojazd (STM32 na pojeździe) odbierze dane poprzez moduł ESP8266 i przetworzy je na sygnały sterujące silnikami (np. prędkość i kierunek każdego z silników poprzez PWM). Jeśli zainstalowano czujnik ultradźwiękowy, oprogramowanie pojazdu może wykorzystać jego odczyty do reagowania na przeszkody (np. zatrzymanie pojazdu – jeśli taka funkcjonalność zostanie zaimplementowana).
6. **Sterowanie:** Używaj manipulatora (joysticka), przechylając go w osiach X i Y, aby sterować ruchiem pojazdu (jazda w przód/tył oraz skręty). Dzięki zastosowaniu protokołu ESP-NOW transmisja danych odbywa się z niewielkim opóźnieniem, co pozwala na płynne, **real-time** sterowanie pojazdem.


