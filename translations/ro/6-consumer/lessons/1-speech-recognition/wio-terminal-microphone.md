<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-28T09:14:27+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "ro"
}
-->
# Configurează microfonul și difuzoarele - Wio Terminal

În această parte a lecției, vei adăuga difuzoare la Wio Terminal. Wio Terminal are deja un microfon integrat, care poate fi folosit pentru captarea vocii.

## Hardware

Wio Terminal are deja un microfon integrat, care poate fi folosit pentru captarea audio necesară recunoașterii vocale.

![Microfonul de pe Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917.ro.png)

Pentru a adăuga un difuzor, poți folosi [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Acesta este o placă externă care conține 2 microfoane MEMS, un conector pentru difuzor și o priză pentru căști.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab16.ro.png)

Va trebui să adaugi fie căști, un difuzor cu jack de 3.5mm, fie un difuzor cu conexiune JST, cum ar fi [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Pentru a conecta ReSpeaker 2-Mics Pi Hat, vei avea nevoie de 40 de cabluri jumper pin-to-pin (cunoscute și ca male-to-male).

> 💁 Dacă te simți confortabil să folosești un pistol de lipit, poți utiliza [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) pentru a conecta ReSpeaker.

De asemenea, vei avea nevoie de un card SD pentru descărcarea și redarea audio. Wio Terminal suportă doar carduri SD de până la 16GB, care trebuie să fie formatate ca FAT32 sau exFAT.

### Sarcină - conectează ReSpeaker Pi Hat

1. Cu Wio Terminal oprit, conectează ReSpeaker 2-Mics Pi Hat la Wio Terminal folosind cablurile jumper și prizele GPIO de pe spatele Wio Terminal:

    Pinii trebuie conectați astfel:

    ![Diagrama pinilor](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa65081038.ro.png)

1. Poziționează ReSpeaker și Wio Terminal cu prizele GPIO orientate în sus și pe partea stângă.

1. Începe de la priza din colțul stâng sus al prizei GPIO de pe ReSpeaker. Conectează un cablu jumper pin-to-pin de la priza din colțul stâng sus al ReSpeaker la priza din colțul stâng sus al Wio Terminal.

1. Repetă acest proces pe toată lungimea prizelor GPIO de pe partea stângă. Asigură-te că pinii sunt bine fixați.

    ![ReSpeaker cu pinii din partea stângă conectați la pinii din partea stângă a Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba2400.ro.png)

    ![ReSpeaker cu pinii din partea stângă conectați la pinii din partea stângă a Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f.ro.png)

    > 💁 Dacă cablurile jumper sunt conectate în panglici, păstrează-le împreună - acest lucru face mai ușor să te asiguri că ai conectat toate cablurile în ordine.

1. Repetă procesul folosind prizele GPIO din partea dreaptă a ReSpeaker și Wio Terminal. Aceste cabluri trebuie să treacă pe lângă cablurile deja conectate.

    ![ReSpeaker cu pinii din partea dreaptă conectați la pinii din partea dreaptă a Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa930.ro.png)

    ![ReSpeaker cu pinii din partea dreaptă conectați la pinii din partea dreaptă a Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437.ro.png)

    > 💁 Dacă cablurile jumper sunt conectate în panglici, împarte-le în două panglici. Trece câte una pe fiecare parte a cablurilor existente.

    > 💁 Poți folosi bandă adezivă pentru a fixa pinii într-un bloc, astfel încât să previi ieșirea lor în timp ce îi conectezi.
    >
    > ![Pinii fixați cu bandă adezivă](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3.ro.png)

1. Va trebui să adaugi un difuzor.

    * Dacă folosești un difuzor cu cablu JST, conectează-l la portul JST de pe ReSpeaker.

      ![Un difuzor conectat la ReSpeaker cu un cablu JST](../../../../../translated_images/respeaker-jst-speaker.a441d177809df945.ro.png)

    * Dacă folosești un difuzor cu jack de 3.5mm sau căști, introdu-le în priza jack de 3.5mm.

      ![Un difuzor conectat la ReSpeaker prin priza jack de 3.5mm](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751.ro.png)

### Sarcină - configurează cardul SD

1. Conectează cardul SD la computer, folosind un cititor extern dacă nu ai un slot pentru card SD.

1. Formatează cardul SD folosind instrumentul corespunzător de pe computer, asigurându-te că utilizezi sistemul de fișiere FAT32 sau exFAT.

1. Introdu cardul SD în slotul pentru card SD de pe partea stângă a Wio Terminal, chiar sub butonul de pornire. Asigură-te că cardul este complet introdus și face clic - s-ar putea să ai nevoie de un instrument subțire sau de un alt card SD pentru a-l împinge complet.

    ![Introducerea cardului SD în slotul pentru card SD de sub comutatorul de pornire](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f.ro.png)

    > 💁 Pentru a scoate cardul SD, trebuie să-l împingi ușor și acesta va ieși. Vei avea nevoie de un instrument subțire, cum ar fi o șurubelniță cu cap plat sau un alt card SD.

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.