# Gym Assistant


## Introducere

In acest proiect imi propun sa dezvolt un sistem de "supervizare"
pentru [**Machine Chest Press**](https://musclewiki.com/machine/male/triceps/machine-chest-press/).

<!-- Ce face si care este scopul lui: -->
Dispozitivul meu va avea urmatoarele functionalitati:
1. Numara repetarile/pauzele facute la acest aparat,
  alaturi de durata lor
2. Reda muzica in timpul antrenamentului
3. Motiveaza utilizatorii in momente de inactivitatea,
  prin redarea unor mesake audio inspirationale (ex. **David Goggins**)
4. Stimuleaza utilizatorii sa faca macar 3 seturi de 8 repetari,
  cu pauze maxim 45 de secunde
5. Simuleaza accesul la o sala de fitness pe baza unei cartele

<!-- Ideea de la care am pornit: -->
Am gasit inspiratie pentru acest proiect la sala.
Aici, cel mai important e sa te concentrezi pe exercitiul efectiv,
nu sa stai sa-ti numeri repetarile.

<!-- De ce cred ca este util pentru altii si pentru mine: -->
Desi pare un task simplu,
sa ai pe cineva (sau **ceva**) care sa faca asta pentru tine este o mare diferenta.

Mai ales daca iti impinge limitele la maxim prin mesaje motivationale precum
*"mai poti inca 3"*, *"hai inca una"*,  sau clasicul *"Who's gonna carry the boats?"*.
Aduce energia care te face sa nu renunti.

Consider ca dispozitivul meu este ideal pentru persoanele care vin singure
la sala si nu au pe nimeni care sa faca asta pentru ei.


> Avand in vederea pozitionarea senzorilor,
> proiectul meu poate monitoriza DOAR exercitiul de [**Machine Chest Press**](https://musclewiki.com/machine/male/triceps/machine-chest-press/),
> un exercitiu simplu in care doar trebuie sa impingi o bara in fata.




## Descriere generala



### Schema bloc

![img](./Images/PM-Project-schema-bloc.jpg)


> Diagrama a fost realizata in [draw.io](https://app.diagrams.net/).


### Audio Files

Pentru a descarca melodii de pe YouTube drept fisiere **MP3**, am fosolosit:
- <https://y2mate.nu/en-CVeZ/>

Pentru a transforma **MP3**-urile in fisiere **WAV**, am folosit:
- <https://audio.online-convert.com/convert-to-wav>


Optiunile folosite la convertirea **MP3 -> WAV**:
- Bit resolution: **8 bit**
- Audio frequency: **16 kHz**
- Audio channels: **Mono**


Inainte de a pune fisierele audio pe microSD,
am formatat cardul in modul **FAT32**
si am denumit fisierele corespunzator.

⚠️ Atentie! Sistemele de fisiere **FAT** folosesc conventia [8.3 filename](https://en.wikipedia.org/wiki/8.3_filename)
(*also called a **short filename** or **SFN***),
ceea ce inseamna ca denumirea fisierelor:
- nu poate avea mai mult de **8** caractere inainte de punct
- maxim **3** caractere pentru extensie

### Conectarea butoanelor

- Data Sheet Push-Buttons: <https://wiki-content.arduino.cc/documents/datasheets/Button.pdf>
- <https://components101.com/switches/push-button>

<img src="https://components101.com/sites/default/files/component_pin/Push-button-Pinout.gif" height=250px width=auto>


> Picioursele care formeaza o line sunt **direct conectate**.

Inainte de a face cablajul intre butoanele de pe cutie si breadboard,
am facut urmatoarele *"simulari"* in TinkerCAD.
Asa trebuie sa arate conexiunea cu un push-buton:

<img src="./Images/vertical-button.png" height=250px width=auto>
<img src="./Images/horizontal-button.png" height=250px width=auto>


Exemplu cod (basic) pentru a detecta apasarea butonului:


```cpp
#define PIN_BUTTON 3

void setup()
{
  pinMode(PIN_BUTTON, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if (digitalRead(PIN_BUTTON) == LOW) {
  	Serial.println("butonul a fost apasat!");
  }
  delay(100);
}
```


## Hardware Design



### Lista piese

- Arduino UNO R3
- 4 x [push-buttons](https://ardushop.ro/ro/butoane--switch-uri/713-buton-mic-push-button-trough-hole-6427854009050.html)
- Ecran LCD 16x2 cu modul I2C
- Rezistente 220Ω
- [MicroSD Module](https://ardushop.ro/ro/module/1553-groundstudio-microsd-module-6427854023056.html?gad_source=1&gbraid=0AAAAADlKU-7r0Viay1-t361QlB21iOgs0&gclid=Cj0KCQjwqv2_BhC0ARIsAFb5Ac84XfsbeL3-M0mj8zEMxlvniXkfdQ1SGlEzoFS0otF-lMW6SyWNGnUaAvFmEALw_wcB)
- [Card MicroSD 16 GB](https://www.optimusdigital.ro/ro/memorii/8678-card-microsd-original-de-16-gb-cu-noobs-compatibil-cu-raspberry-pi-4-model-b-varianta-bulk.html?search_query=%090104110000057297%09&results=1)
  - Nu am gasit un card mai mic 🙁
- [Speaker for Micro:bit](https://www.emag.ro/modul-difuzor-waveshare-36-52x43-44-mm-compatibil-cu-micro-bit-arduino-speakerformicro-bitwaveshare14542/pd/D785XQMBM/?ref=history-shopping_418333718_138738_1)
  - Cred ca erau si alte optiuni mult mai ieftine 🙂
- [Stabilizator de 3.3 V](https://www.optimusdigital.ro/ro/electronica-de-putere-stabilizatoare-liniare/168-modul-cu-sursa-de-alimentare-de-33-v.html?search_query=0104110000000521&results=1) (pentru Vin al Speaker-ului)
- 2 x [Senzor ultrasonic HC-SR04](https://www.optimusdigital.ro/ro/senzori-senzori-ultrasonici/9-senzor-ultrasonic-hc-sr04-.html?search_query=0104110000000866&results=1)
- [Breadboard 830 puncte](https://www.optimusdigital.ro/ro/prototipare-breadboard-uri/8-breadboard-830-points.html?search_query=breadboard+830&results=15)
- [Fire Colorate Mamă-Tată](https://www.optimusdigital.ro/ro/fire-fire-mufate/878-set-fire-mama-tata-40p-30-cm.html?search_query=Fire+Colorate&results=49)
- [Fire Colorate Tată-Tată](https://www.optimusdigital.ro/ro/fire-fire-mufate/890-set-fire-tata-tata-40p-30-cm.html?search_query=Fire+Colorate&results=49)
- [Modul RFID RC522](https://www.optimusdigital.ro/ro/wireless-rfid/67-modul-cititor-rfid-mfrc522.html?search_query=rfid&results=37)



### Schema circuit

![img](./Images/circuit_design.png)


> Schema a fost realizata in [Cirkit Designer IDE](https://app.cirkitdesigner.com/).



