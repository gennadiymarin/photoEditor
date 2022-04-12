# Графические фильтры (image_processor)

Поддерживаемый формат изображений - [BMP](http://en.wikipedia.org/wiki/BMP_file_format)
<br/>24-битный BMP без сжатия и без таблицы цветов. Тип используемого `DIB header` - `BITMAPINFOHEADER`.

## Формат аргументов командной строки

Описание формата аргументов командной строки:

`{имя программы} {путь к входному файлу} {путь к выходному файлу}
[-{имя фильтра 1} [параметр фильтра 1] [параметр фильтра 2] ...]
[-{имя фильтра 2} [параметр фильтра 1] [параметр фильтра 2] ...] ...`

При запуске без аргументов программа выводит справку.

### Применение
`./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5`

В этом примере
1. Загружается изображение из файла `input.bmp`
2. Обрезается до изображения с началом в верхнем левом углу и размером 800х600 пикселей
3. Переводится в оттенки серого
4. Применяется размытие с сигмой 0.5
5. Полученное изображение сохраняется в файл `/tmp/output.bmp`

Список фильтров может быть пуст, тогда изображение сохраняется в неизменном виде.
Фильтры применяются в том порядке, в котором они перечислены в аргументах командной строки.

## Фильтры

### Crop (-crop width height)
Обрезает изображение до заданных ширины и высоты. Используется верхняя левая часть изображения.
<p align="center">
<img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/example.bmp" alt="drawing" width="450"/> <img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/out_crop.bmp" alt="drawing" width="200"/>
</p>

### Grayscale (-gs)
Преобразует изображение в оттенки серого.
<p align="center">
<img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/example.bmp" alt="drawing" width="450"/> <img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/out_gray.bmp" alt="drawing" width="450"/>
</p>

### Negative (-neg)
Преобразует изображение в негатив.
<p align="center">
<img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/example.bmp" alt="drawing" width="450"/> <img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/out_neg.bmp" alt="drawing" width="450"/>
</p>

### Sharpening (-sharp)
Повышение резкости.
<p align="center">
<img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/example.bmp" alt="drawing" width="450"/> <img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/out_sharp.bmp" alt="drawing" width="450"/>
</p>

### Edge Detection (-edge threshold)
Выделение границ. 
<br/>`-edge 0.25`
<p align="center">
<img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/example.bmp" alt="drawing" width="450"/> <img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/out_edge(0.25).bmp" alt="drawing" width="450"/>
</p>

### Gaussian Blur (-blur sigma)
[Гауссово размытие](https://ru.wikipedia.org/wiki/Размытие_по_Гауссу),
параметр – сигма.
<br/> `-blur 3`
<p align="center">
<img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/example.bmp" alt="drawing" width="450"/> <img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/out_blur(3).bmp" alt="drawing" width="450"/>
</p>

### Sobel (-sobel)
Преобразует изображение по Собелю.
<br/> `-sobel`
<p align="center">
<img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/example.bmp" alt="drawing" width="450"/> <img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/out_sobel.bmp" alt="drawing" width="450"/>
</p>

### Sketch (-sketch blur_arg sharpness x_move y_move)
Выделяет края изображения в белый цвет (создает скетч), двигает данный скетч относительно основного изображения.
<br/> `-sketch 2 0.3 350 -150`
<p align="center">
<img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/example.bmp" alt="drawing" width="450"/> <img src="https://github.com/gennadiymarin/photoEditor/blob/main/examples/out_sketch(2_0.3_350_-150).bmp" alt="drawing" width="450"/>
</p>
