<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T22:37:47+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "tl"
}
-->
# Paggawa at pagpoproseso - paggamit ng IoT upang mapabuti ang pagpoproseso ng pagkain

Kapag ang pagkain ay nakarating na sa isang sentral na hub o planta ng pagpoproseso, hindi ito palaging direktang ipinapadala sa mga supermarket. Madalas, ang pagkain ay dumadaan muna sa ilang hakbang ng pagpoproseso, tulad ng pagsasala batay sa kalidad. Ito ay isang proseso na dati ay manu-mano - nagsisimula ito sa bukid kung saan ang mga tagapitas ay pumipili lamang ng hinog na prutas, at pagkatapos sa pabrika, ang mga prutas ay dumadaan sa conveyor belt at manu-manong inaalis ng mga empleyado ang mga bugbog o bulok na prutas. Bilang isang taong nakaranas ng pagpitas at pagsasala ng mga strawberry bilang trabaho tuwing tag-init noong ako'y nag-aaral, masasabi kong hindi ito masayang gawain.

Ang mas modernong mga sistema ay umaasa na ngayon sa IoT para sa pagsasala. Ang ilan sa mga pinakaunang kagamitan tulad ng mga sorter mula sa [Weco](https://wecotek.com) ay gumagamit ng optical sensors upang matukoy ang kalidad ng ani, tulad ng pagtanggi sa mga berdeng kamatis. Ang mga ito ay maaaring gamitin sa mga harvester mismo sa bukid, o sa mga planta ng pagpoproseso.

Habang umuunlad ang Artificial Intelligence (AI) at Machine Learning (ML), ang mga makinang ito ay nagiging mas sopistikado, gamit ang mga ML model na sinanay upang makilala ang pagkakaiba ng prutas at mga banyagang bagay tulad ng bato, lupa, o insekto. Ang mga modelong ito ay maaari ring sanayin upang matukoy ang kalidad ng prutas, hindi lamang ang mga bugbog na prutas kundi pati na rin ang maagang pagtukoy ng sakit o iba pang problema sa ani.

> 🎓 Ang terminong *ML model* ay tumutukoy sa resulta ng pagsasanay ng machine learning software gamit ang isang set ng data. Halimbawa, maaari kang magsanay ng isang ML model upang makilala ang hinog at hilaw na kamatis, at pagkatapos ay gamitin ang modelong ito sa mga bagong larawan upang makita kung hinog na ang mga kamatis o hindi.

Sa 4 na araling ito, matututuhan mo kung paano magsanay ng mga AI model na nakabatay sa imahe upang matukoy ang kalidad ng prutas, kung paano gamitin ang mga ito mula sa isang IoT device, at kung paano patakbuhin ang mga ito sa edge - ibig sabihin, sa isang IoT device sa halip na sa cloud.

> 💁 Ang mga araling ito ay gagamit ng ilang cloud resources. Kung hindi mo matatapos ang lahat ng aralin sa proyektong ito, siguraduhing [linisin ang iyong proyekto](../clean-up.md).

## Mga Paksa

1. [Magsanay ng detector ng kalidad ng prutas](./lessons/1-train-fruit-detector/README.md)
1. [Suriin ang kalidad ng prutas mula sa isang IoT device](./lessons/2-check-fruit-from-device/README.md)
1. [Patakbuhin ang iyong fruit detector sa edge](./lessons/3-run-fruit-detector-edge/README.md)
1. [I-trigger ang pagtukoy ng kalidad ng prutas mula sa isang sensor](./lessons/4-trigger-fruit-detector/README.md)

## Mga Kredito

Ang lahat ng aralin ay isinulat nang may ♥️ nina [Jen Fox](https://github.com/jenfoxbot) at [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.