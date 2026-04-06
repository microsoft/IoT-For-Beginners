# រាប់ស្តុកពីឧបករណ៍ IoT របស់អ្នក - ឧបករណ៍ IoT ក្រឡាឈាមមេនិង Raspberry Pi

ការរួមបញ្ចូលនៃការព្យាករណ៍និងប្រអប់កំណត់ដែនរបស់ពួកវាអាចប្រើបានដើម្បីរាប់ស្តុកក្នុងរូបភាពមួយ

## បង្ហាញប្រអប់កំណត់ដែន

ជាដំណាក់កាលជួយសំរាប់ការធ្វើដំណោះស្រាយបញ្ហា អ្នកអាចមិនត្រឹមតែបោះពុម្ពប្រអប់កំណត់ដែនបានទេ ប៉ុន្តែក៏អាចគូរក្នុងរូបភាពដែលត្រូវបានរក្សាទុកនៅលើថាសពេលរូបភាពត្រូវបានថត។

### កិច្ចការជាបោះពុម្ពប្រអប់កំណត់ដែន

1. ប្រាកដថាគម្រោង `stock-counter` ត្រូវបានបើកនៅក្នុង VS Code ហើយបរិយាកាសក្រឡាឈាម (virtual environment) ត្រូវបានដំណើរការបើអ្នកកំពុងប្រើឧបករណ៍ IoT ក្រឡាឈាម។

1. បម្លែងពាក្យបញ្ជា `print` ក្នុងលូប `for` ទៅដូចខាងក្រោមដើម្បីបោះពុម្ពប្រអប់កំណត់ដែនទៅកុងសុល៖

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. បើកកម្មវិធីជាមួយកាមេរ៉ាដាក់ទៅលើស្តុកខ្លះនៅលើទ្រាង។ ប្រអប់កំណត់ដែននឹងត្រូវបោះពុម្ពទៅកុងសុល រួមមានតំលៃ left, top, width និង height ពី 0 ទៅ 1។

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### កិច្ចការជាគូរប្រអប់កំណត់ដែនលើរូបភាព

1. កញ្ចប់ Pip [Pillow](https://pypi.org/project/Pillow/) អាចប្រើសម្រាប់គូរលើរូបភាព។ តំឡើងវាជាមួយពាក្យបញ្ជាខាងក្រោម៖

    ```sh
    pip3 install pillow
    ```

    ប្រសិនបើអ្នកកំពុងប្រើឧបករណ៍ IoT ក្រឡាឈាម សូមប្រាកដថាប្រតិបត្តិវានៅក្នុងបរិយាកាសក្រឡាឈាមដែលបានដំណើរការ។

1. បន្ថែមពាក្យសម្ងាត់នាំចូលខាងក្រោមទៅក្បាលឯកសារ `app.py`៖

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    នេះនាំចូលកូដដែលត្រូវការសម្រាប់កែប្រែរូបភាព។

1. បន្ថែមកូដខាងក្រោមទៅចុងឯកសារ `app.py`៖

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    កូដនេះបើករូបភាពដែលបានរក្សាទុកមុនសម្រាប់កែប្រែ។ បន្ទាប់មកវាប្រតិបត្តិលើការព្យាករណ៍ដោយទទួលបានប្រអប់កំណត់ដែន ហើយគណនាផ្ចិតមុខត្រង់ខាងស្តាំក្រោមដោយប្រើតំលៃប្រអប់កំណត់ដែនពី 0 ទៅ 1។ តំលៃទាំងនេះបម្លែងទៅកូអរដោនេររូបភាពដោយគុណនឹងវិមាត្រសមស្របនៃរូបភាព។ ឧទាហរណ៍ ប្រសិនបើតំលៃ left គឺ 0.5 លើរូបភាពដែលទទឹង 600 ភីកសែល នោះវានឹងបម្លែងទៅ 300 (0.5 x 600 = 300)។

    ប្រអប់កំណត់ដែននីមួយៗត្រូវគូរនៅលើរូបភាពដោយបន្ទាត់ក្រហម។ ចុងក្រោយ រូបភាពដែលបានកែប្រែត្រូវបានរក្សាទុកជំនួសរូបភាពដើម។

1. បើកកម្មវិធីជាមួយកាមេរ៉ាដាក់ទៅលើស្តុកខ្លះនៅលើទ្រាង។ អ្នកនឹងឃើញឯកសារ `image.jpg` ក្នុងអ្នកមើល VS Code ហើយអ្នកអាចជ្រើសរើសវាដើម្បីមើលប្រអប់កំណត់ដែន។

    ![4 cans of tomato paste with bounding boxes around each can](../../../../../translated_images/km/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

## រាប់ស្តុក

នៅក្នុងរូបភាពដែលបង្ហាញខាងលើ ប្រអប់កំណត់ដែនមានការផ្ទុះតិចតួច។ ប្រសិនបើការផ្ទុះនេះធំជាងនេះ ពេលនោះប្រអប់កំណត់ដែនអាចបង្ហាញវត្ថុដូចគ្នា។ ដើម្បីរាប់វត្ថុត្រឹមត្រូវ អ្នកត្រូវដែលមិនគិតប្រអប់ដែលមានការផ្ទុះយ៉ាងសំខាន់។

### កិច្ចការ - រាប់ស្តុកដោយមិនគិតការផ្ទុះ

1. កញ្ចប់ Pip [Shapely](https://pypi.org/project/Shapely/) អាចប្រើហើយសម្រាប់គណនាការឆ្លុះគ្នា។ ប្រសិនបើអ្នកប្រើ Raspberry Pi អ្នកត្រូវតំឡើងបណ្ណាល័យភាសាច្រើនមុន៖

    ```sh
    sudo apt install libgeos-dev
    ```

1. តំឡើងកញ្ចប់ Pip Shapely៖

    ```sh
    pip3 install shapely
    ```

    ប្រសិនបើអ្នកកំពុងប្រើឧបករណ៍ IoT ក្រឡាឈាម សូមប្រាកដថាប្រតិបត្តិវានៅក្នុងបរិយាកាសក្រឡាឈាមដែលបានដំណើរការ។

1. បន្ថែមពាក្យសម្ងាត់នាំចូលខាងក្រោមទៅក្បាលឯកសារ `app.py`៖

    ```python
    from shapely.geometry import Polygon
    ```

    នេះនាំចូលកូដដែលត្រូវការសម្រាប់បង្កើតប៊ីហ្គោណាល់ដើម្បីគណនាការផ្ទុះគ្នា។

1. មុនកូដដែលគូរប្រអប់កំណត់ដែន បន្ថែមកូដខាងក្រោម៖

    ```python
    overlap_threshold = 0.20
    ```

    នេះកំណត់ភាគរយនៃការផ្ទុះដែលចូលត្រួតមុនពេលប្រអប់កំណត់ដែនត្រូវបានចាត់ទុកថាជាវត្ថុដូចគ្នា។ 0.20 កំណត់ពីការផ្ទុះ 20%។

1. ដើម្បីគណនាការផ្ទុះដោយប្រើ Shapely ប្រអប់កំណត់ដែនត្រូវតែបម្លែងទៅជាប៊ីហ្គោណាល់ Shapely។ បន្ថែមមុខងារខាងក្រោមដើម្បីធ្វើបច្ចុប្បន្នភាពនេះ៖

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    នេះបង្កើតប៊ីហ្គោណាល់ដោយប្រើប្រអប់កំណត់ដែននៃការព្យាករណ៍មួយ។

1. ទ្រឹស្តីសម្រាប់ដកស្រង់វត្ថុដូចគ្នាដាក់ក្នុងការប្រៀបធៀបទាំងអស់នៃប្រអប់កំណត់ដែន ហើយប្រសិនបើគូរpredictionណាមួយមានប្រអប់កំណត់ដែនដែលផ្ទុះគ្នាច្រើនជាងចំណាត់ថ្នាក់ នឹងលុបpredictionមួយចេញ។ ដើម្បីប្រៀបធៀបpredictionទាំងអស់ អ្នកប្រៀបធៀបprediction១ជាមួយ២, ៣, ៤, ទៀតបន្តទៅ បន្ទាប់មក២ជាមួយ ៣, ៤, ល។ កូដខាងក្រោមធ្វើការនេះ៖

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    ការផ្ទុះគ្នាត្រូវបានគណនាដោយវិធីសាស្រ្ត Shapely `Polygon.intersection` ដែលត្រឡប់ប៊ីហ្គោណាល់ដែលមានការផ្ទុះគ្នា។ បន្ទាប់មកត្រូវគណនាតំបន់ពីប៊ីហ្គោណាលនេះ។ ចំណាត់ថ្នាក់នេះមិនមែនតម្លៃបរិច្ឆេទទេ ត្រូវតែជាភាគរយនៃប្រអប់កំណត់ដែន ដូច្នេះតំបន់តូចជាងសម្រាប់ប្រអប់កំណត់ដែនត្រូវបានស្វែងរក ហើយចំណាត់ថ្នាក់ប្រើសម្រាប់គណនាថាតំបន់ផ្ទុះអាចមានគន្លងប៉ុនណា ដើម្បីមិនឲ្យលើសភាគរយការផ្ទុះនៃប្រអប់កំណត់ដែនតូចជាង។ ប្រសិនបើការផ្ទុះលើសនេះ predictionនឹងត្រូវបានសម្គាល់សម្រាប់លុប។

    ពេលpredictionត្រូវបានសម្គាល់សម្រាប់លុប វាមិនចាំបាច់ត្រូវត្រួតពិនិត្យទៀតទេ ដូច្នេះលូបក្នុងតំណហ៊ុយខាងក្នុងនឹងផ្លាស់ចេញចូលទៅត្រួតពិនិត្យpredictionបន្ទាប់។ អ្នកមិនអាចលុបវត្ថុពីបញ្ជីខណៈពេលកំពុងដំណើរការតាមវា ហើយប្រអប់កំណត់ដែនដែលផ្ទុះច្រើនជាងចំណាត់ថ្នាក់នឹងត្រូវបន្ថែមទៅបញ្ជី `to_delete` ហើយត្រូវលុបទៅក្រោយ។

    ចុងក្រោយហើយ ការរាប់ស្តុកត្រូវបានបោះពុម្ពទៅកុងសុល។ នេះអាចផ្ញើទៅសេវាកម្ម IoT ដើម្បីដាក់អារម្មណ៍បើជាន់ស្តុកទាប។ កូដទាំងអស់នេះស្ថិតនៅមុនពេលគូរប្រអប់កំណត់ដែន ដូច្នេះអ្នកនឹងឃើញការព្យាករណ៍ស្តុកដោយគ្មានការផ្ទុះលើរូបភាពដែលបង្កើតឡើង។

    > 💁 វិធីនេះគឺសាមញ្ញខ្លាំងនៅក្នុងការដកចេញការផ្ទុះ គ្រាន់តែដកជាដំបូងនៃគូផ្ទុះមួយ។ សម្រាប់កូដផលិតកម្ម អ្នកអាចចង់បន្ថែមតុល្យភាពច្រើនជាងនេះ ដូចជាការពិចារណាចំពោះការផ្ទុះរវាងវត្ថុជាច្រើន ឬប្រអប់កំណត់ដែនមួយមាននៅក្នុងមួយផ្សេងទៀត។

1. បើកកម្មវិធីជាមួយកាមេរ៉ាដាក់ទៅលើស្តុកខ្លះនៅលើទ្រាង។ លទ្ធផលនឹងបង្ហាញចំនួនប្រអប់កំណត់ដែនដែលគ្មានការផ្ទុះខុសពីចំណាត់ថ្នាក់។ សូមព្យាយាមកែប្រែតម្លៃ `overlap_threshold` ដើម្បីមើលការព្យាករណ៍ត្រូវបានមិនគិត។

> 💁 អ្នកអាចស្វែងរកកូដនេះនៅក្នុងថត [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) ឬ [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device)។

😀 កម្មវិធីរាប់ស្តុករបស់អ្នកបានជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ច្រកទ្វារ**៖
ឯកសារនេះត្រូវបានបកប្រែដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលយើងខិតខំក្នុងការធានាការត្រឹមត្រូវ សូមយល់ថាការបកប្រែដោយស្វ័យប្រវត្តិអាចមានកំហុស ឬ ការខ្វះត្រឹមត្រូវ។ ឯកសារដើមជាភាសាដើមគួរត្រូវបានចាត់ទុកជាប្រភពត្រឹមត្រូវបំផុត។ សម្រាប់ព័ត៌មានសំខាន់ៗ យើងសូមផ្ដល់អនុសាសន៍អោយប្រើការបកប្រែដោយអ្នកជំនាញមនុស្ស។ យើងមិនទទួលបន្ទុកចំពោះការយល់ច្រឡំនោះ ឬ ការបកប្រែខុសពីការប្រើប្រាស់ការបកប្រែនេះទេ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->