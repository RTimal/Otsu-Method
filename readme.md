Project 1 - Otsu Method Implementation
Rajiev Timal - 0220052

My project implements the Otsu Method using c++ on the 4 test images:
These images are located in the "Otsu" Folder within the "Otsu Method"  Folder along with the converted images



Converted Images:
Airplane256otsu.bmp
Lena256otsu.bmp - looks better, background and foreground are reversed
Lena256otsu2.bmp - as project describes with background black and forground white
Cell 7otsu.bmp
Cell 11otsu.bmp

Original Images:
Airplane256.bmp - Threshold: 178
Lena256.bmp - Threshold: 101
Cell 7.bmp - Threshold: 194
Cell 11.bmp- Threshold: 166


	The program first creates a pointer to all the pixels in the image file. I named the pointer "image".This is done using an open source library called CImg:http://cimg.sourceforge.net/. This library is included with the zip file in the right folder, so that at compilation it is automatically included.

This library allowed me to get and set the values of pixels. After creating a pointer to the image image, I am allowed to iterate through the entire image and create a histogram as an array of length 256 with int values. After the histogram is created, I use the sum of all histogram values to calculate the mean histogram value.I also create an array with probabilities.I could now implement Otsu's algorithm to find a threshhold. At the end of the algorithm, which loops through the entire image and calculates between group variance for each t value, the threshhold that produces the highest T value is obtained. I then apply this  threshhold to the image.

I loop through each pixel in the image.If a pixelvalue is < than the threshhold, 200 is used as the pixel value. If it is greater than the threshhold,0 is used as the pixel value. I had to set the r,g,b values each to the same value, 200 or 0. This allows the foreground pixels to be white and the background pixels to be black. This worked well for all of the images.With the Lena256 image, when this is used, the foreground pixels do not include her face, but include her hair, parts of her hat and the side of her face. If I change the algorithm to set the foreground pixels to black and the background pixels to white, the Lena256 image is more distinguishable. Because of this, I included 
two versions of Lena256: Lena256otsu has the foreground as black and the background white. Lena256otsu2 has the foreground as white and the background black.


Compilation:
This program was written using c++ and the MS Visual C++ Express 2010 GUI and compiler.
To compile, extract all contents into a folder, and run Otsu.sln. This will open Visual c++. Clicking the green debug arrow in the top bar will compile this program and also display and image of the converted image after saving it.