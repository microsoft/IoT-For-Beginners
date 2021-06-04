import io
import time
from picamera import PiCamera

camera = PiCamera()
camera.resolution = (640, 480)
camera.rotation = 0

time.sleep(2)

image = io.BytesIO()
camera.capture(image, 'jpeg')
image.seek(0)

with open('image.jpg', 'wb') as image_file:
    image_file.write(image.read())