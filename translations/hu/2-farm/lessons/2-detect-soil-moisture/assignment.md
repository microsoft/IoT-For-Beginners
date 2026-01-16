<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "506d21b544d5de47406c89ad496a21cd",
  "translation_date": "2025-08-27T22:55:13+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/assignment.md",
  "language_code": "hu"
}
-->
# Kalibráld az érzékelődet

## Útmutató

Ebben a leckében talajnedvesség-érzékelővel gyűjtöttél adatokat, amelyeket 0-1023 közötti értékek formájában mértél. Ahhoz, hogy ezeket valódi talajnedvesség-értékekké alakítsd, kalibrálnod kell az érzékelőt. Ezt úgy teheted meg, hogy talajmintákból veszel leolvasásokat, majd kiszámítod a gravimetrikus talajnedvesség-tartalmat ezekből a mintákból.

Ezeket a lépéseket többször meg kell ismételned, hogy elegendő adatot gyűjts, minden alkalommal különböző nedvességtartalmú talajjal.

1. Vegyél egy talajnedvesség-leolvasást a talajnedvesség-érzékelővel. Jegyezd fel ezt az értéket.

1. Vegyél egy mintát a talajból, és mérd meg a súlyát. Jegyezd fel ezt a súlyt.

1. Szárítsd ki a talajt – egy meleg sütőben 110°C-on (230°F) néhány órán keresztül a legjobb módszer, de megteheted ezt napfényben, vagy helyezheted meleg, száraz helyre, amíg a talaj teljesen száraz nem lesz. A talajnak porhanyósnak és laza szerkezetűnek kell lennie.

    > 💁 Laboratóriumban a legpontosabb eredmények érdekében 48-72 órán keresztül szárítanád a talajt sütőben. Ha az iskoládban vannak szárítósütők, nézd meg, hogy használhatod-e ezeket hosszabb szárításra. Minél hosszabb ideig szárítod, annál szárazabb lesz a minta, és annál pontosabbak lesznek az eredmények.

1. Mérd meg újra a talaj súlyát.

    > 🔥 Ha sütőben szárítottad, győződj meg róla, hogy először lehűlt!

A gravimetrikus talajnedvesség-tartalom kiszámítása:

![A talajnedvesség % kiszámítása: nedves súly mínusz száraz súly, osztva száraz súllyal, szorozva 100-zal](../../../../../translated_images/hu/gsm-calculation.6da38c6201eec14e7573bb2647aa18892883193553d23c9d77e5dc681522dfb2.png)

* W - a nedves talaj súlya  
* W - a száraz talaj súlya  

Például, ha van egy talajmintád, amely nedvesen 212g, szárazon pedig 197g.

![A kitöltött számítás](../../../../../translated_images/hu/gsm-calculation-example.99f9803b4f29e97668e7c15412136c0c399ab12dbba0b89596fdae9d8aedb6fb.png)

* W = 212g  
* W = 197g  
* 212 - 197 = 15  
* 15 / 197 = 0.076  
* 0.076 * 100 = 7.6%  

Ebben a példában a talaj gravimetrikus talajnedvessége 7.6%.

Miután legalább 3 mintához gyűjtöttél adatokat, készíts egy grafikonon talajnedvesség %-ot a talajnedvesség-érzékelő leolvasásaihoz, és illessz egy legjobban illeszkedő vonalat a pontokhoz. Ezután ezt használhatod arra, hogy egy adott érzékelő-leolvasásból kiszámítsd a gravimetrikus talajnedvesség-tartalmat, a vonalról leolvasva az értéket.

## Értékelési szempontok

| Kritérium | Kiváló | Megfelelő | Fejlesztésre szorul |
| --------- | ------- | --------- | ------------------- |
| Kalibrációs adatok gyűjtése | Legalább 3 kalibrációs mintát rögzít | Legalább 2 kalibrációs mintát rögzít | Legalább 1 kalibrációs mintát rögzít |
| Kalibrált leolvasás készítése | Sikeresen elkészíti a kalibrációs grafikont, leolvasást végez az érzékelővel, és átalakítja gravimetrikus talajnedvesség-tartalommá | Sikeresen elkészíti a kalibrációs grafikont | Nem tudja elkészíteni a grafikont |

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget az ebből a fordításból eredő félreértésekért vagy téves értelmezésekért.