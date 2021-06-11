## find devices

aplay -l

arecord -l

## configure defaults

sudo nano /usr/share/alsa/alsa.conf

defaults.pcm.card 1

speaker-test -t wav -c 2

## test

arecord --format=S16_LE --duration=5 --rate=16000 --file-type=raw out.raw
aplay --format=S16_LE --rate=16000 out.raw

## Create service

az group create --name smart-timer --location westus2

az cognitiveservices account create \
    --name smart-timer \
    --resource-group smart-timer \
    --kind SpeechServices \
    --sku F0 \
    --location westus2 \
    --yes

copy endpoint for token issuer

az cognitiveservices account keys list \
    --name smart-timer \
    --resource-group smart-timer