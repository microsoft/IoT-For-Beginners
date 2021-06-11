import io
import time
from picamera import PiCamera

from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
from msrest.authentication import ApiKeyCredentials

camera = PiCamera()
camera.resolution = (640, 480)
camera.rotation = 0

time.sleep(2)

image = io.BytesIO()
camera.capture(image, 'jpeg')
image.seek(0)

with open('image.jpg', 'wb') as image_file:
    image_file.write(image.read())

prediction_url = '<prediction_url>'
prediction_key = '<prediction key>'

parts = prediction_url.split('/')
endpoint = 'https://' + parts[2]
project_id = parts[6]
iteration_name = parts[9]

prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)

image.seek(0)
results = predictor.classify_image(project_id, iteration_name, image)

for prediction in results.predictions:
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')