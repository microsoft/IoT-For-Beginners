import io
import os
import requests

import librosa
import soundfile as sf
import azure.functions as func

location = os.environ['SPEECH_LOCATION']
speech_key = os.environ['SPEECH_KEY']

def get_access_token():
    headers = {
        'Ocp-Apim-Subscription-Key': speech_key
    }

    token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
    response = requests.post(token_endpoint, headers=headers)
    return str(response.text)

playback_format = 'riff-48khz-16bit-mono-pcm'

def main(req: func.HttpRequest) -> func.HttpResponse:
    req_body = req.get_json()
    language = req_body['language']
    voice = req_body['voice']
    text = req_body['text']
    
    url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': 'application/ssml+xml',
        'X-Microsoft-OutputFormat': playback_format
    }

    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'

    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))

    raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
    resampled = librosa.resample(raw_audio, sample_rate, 44100)
    
    output_buffer = io.BytesIO()
    sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
    output_buffer.seek(0)

    return func.HttpResponse(output_buffer.read(), status_code=200)
