# APPUNTI GROWBOX

Il sistema è composto da:

* Una camera isolata
* Una lampada per l'illuminazione
* Un sistema di monitoraggio

## Sistema di monitoraggio

Il sistema di monitoraggio si occupa di misurare dati ricevuti da diversi sensori,
per avere sotto controllo:

- Ciclo notturno diurno all'interno della GROWBOX
- umidità e temperatura presenti all'interno della GROWBOX
- Livello di CO2 presente all'interno della GROWBOX

La misurazione avviene tramite sensori collegati ad Arduino, il quale a seconda dei dati misurati potrà:

1- Attivare un disco che traccia il ciclo diurno / notturno
2- Mostrare sul display i dati letti e permettere la modifica di valori soglia
3- Spegnere e accendere le ventole posteriori per l'areazione

I dati letti verranno spediti via internet ad un server amazon dove verranno graficati tramite grafana.

La comunicazione via internet è demandata ad un raspberry pi sempre connesso alla rete che leggerà i dati inviati da arduino tramite la porta seriale.

Il raspberry pi scatterà inoltre (solo nel ciclo diurno) una foto ogni 5 minuti per
poterne generare un timelapse.

### ELENCO SENSORI

* 1 x DHT11 (Sensore di temperatura / umidità)
* 1 x Foto resistore (riconoscere il giorno dalla notte)
* 1 x Sensore CO2
* 2 x Igrometro (uno per ogni "zona" del vaso)

## SISTEMI DI INPUT

* 3 x Bottone (1 Mode e uno per segno "+" e uno per segno "-")
* 1 x Relè (per collegare/scollegare le ventole posteriori)

## SISTEMI DI OUTPUT
* 3 x Ventole (2 posteriori e una di raffredamento pc)
* 1 x Servo (disco giorno/notte)
* 1 x Display LCD 16x2
* 1 x Led VERDE alimentazione generale
* 1 x Led ROSSO alimentazione/operatività Arduino
* 1 x Led ROSSO piccolo per lampeggiamento durante invio/dati
* 1 x Led GIALLO alimentazione/operatività raspberry
* 1 x Led GIALLO piccolo per lampeggiamento durante invio/fotografia

## RESISTENZE

* 3 x 10 Kohm (pull down per bottone)
* 2 x 220 Ohm per LED ROSSO
* 2 x 206 Ohm per LED GIALLO
* 1 x 200 Ohm per LED VERDE


## ALIMENTAZIONE

 * 1 x Alimentatore PC


## COLLEGAMENTO SENSORI

### DHT11

Il DHT 11 è un sensore di temperatura e umidità digitale.

N. Poli : 3

* 1 VCC (+5V - ALIMENTATORE PC)
* 1 GROUND
* 1 Collegamento dati

# FOTORESISTORE

* N. Poli : 2
* 1 VCC (+5V ARDUINO)
* 1 GROUND (GROUND COMUNE)

La resistenza varia al variare della luce, con un pin analogico è possibile effettuae la lettura di questo valore andando a misurare la tensione tra il photoresistore e una resistenza posta in serie.

# IGROMETRO
N. Poli: 3
* 1 VCC (5V)
* 1 GROUND
* 1 Dati (porte analogiche)

# DISPLAY
N. Poli: 4

* 1 VCC (5V)
* 1 GROUND
* 1 SDC
* 1 SDL

# SERVO
N. Poli: 3
* 1 VCC
* 1 GROUND
* 1 INPUT

# RELAY
N. Poli: 3
* 1 VCC
* 1 GROUND
* 1 INPUT

# SENSORE CO2

N. Poli: 3
* 1 VCC
* 1 GROUND
* 1 DATI (ANALOG)


### PIN UTILIZZA
TI Arduino

|#| SENSORE/OUTPUT  |
|--|--|
|1| NON UTILIZZABILE SE SERIALE IN USO |
|2| NON UTILIZZABILE SE SERIALE IN USO |
|3| Led di operatività |
|4| Led di trasmissione |
|5| DHT11 |
|6| RELE  |
|7| BOTTOME "MODE"  |
|8| BOTTONE "+"  |
|9| BOTTONE "-"  |
|10| SERVO (obbligatorio o 9 o 10) |
|11| RELAY ATTIVAZIONE Ventole |

|#| INGRESSI ANALOGICI  |
|--|--|
|A0| Photoresistore|
|A1| IGROMETRO SINISTRA|
|A2| IGROMETRO DESTRA|
|A3| SENSORE CO2|
|A4| SCL DISPLAY|
|A5| SDA DISPLAY|
