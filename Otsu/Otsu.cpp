// Otsu.cpp : Defines the entry point for the console application.
//Rajiev Timal Project 1 Computer Vision . Due 11/3/2011

#include "stdafx.h"
#include <iostream>
#include "CImg.h"//image processing library Cimg
#include <limits>
using namespace cimg_library;//namespace for image processing library 
using namespace std;
float histogram[256];//Array holding histogram values for each value of t
float probability[256];//Array holding probability values for each value of t


//main function
int _tmain()
{
	//Otsu's algorithm variables
	float p1; //first value of the probability in Otsu's algorithm with t = 1
	float q1; //first value of q qith t = 1
	float q1prev;//previos value of q1
	float q1next;//next value of q1 , aka q1(t+1)
	float mu1; //average of first group, before threshold
	float mu2;//average of second group, after threshold
	float mu1next;//next value of the mean for group 1(mu1(t+1))
	float mu2next;//next value of the mean for group 2(mu2(t+1))
	float mu;//the mean gray level value of the entire image before thresholding
	float betweenvariance=0;//between group variance
	float maxbetweenvariance=0;//max between group variance
	float sum=0;//sum of all histogram values to calculate the mean grey level value of the imagem values before threshholding
	int pixelvalue=0;//value of a pixel
	float optimizedthresh=0;//optimized threshhold, at the end of otsu's algorithm this will be the thresshold with the max between group vairance
	  CImg<unsigned int>  *image = new CImg<unsigned int>("lena256.bmp");//initialize point to image
	  //populate histogram with 0 for all values initially
	  for(int k =0;k<=255;k++){
	  histogram[k]=0;
  }
	 //populate probability array with 0 for all values initially
	for(int k =0;k<=255;k++){
	 probability[k]=0;
  }
	
	//cycle through entire image and get pixel values and populate the histogram with them
	for (int i =0;i<image->height();i++)
	{
		for (int j =0;j<image->width();j++){
			pixelvalue=image->atXY(j,i,0);//store pixel value of image at (width,height)
			sum+=pixelvalue;//increment the sum of all pixel values , used to calculate the average grey level value of the entire image later one
			histogram[pixelvalue]++;
		}
	}

	//calculate the probability of each histogram value and store them in the probability array
for(int k =0;k<=255;k++){
	  probability[k]=histogram[k]/(image->width()*image->height());
}

	//Initial probability p1 which is equal to just the probability of the 0 grey value
	p1 = probability[0];
	//initial q which is the sum of probabilities before 1, which is equal to p1
	q1=p1;
	//initial mean before the 1 has to be 0. mu(1)=0 
	mu1=0;
	//initial mean after the 0. Initially set to 0. This gets reset in the algorithm
	mu2=0;
	//mean grey level (mu) calculation
	 mu=sum/(image->width()*image->height());
	cout << "\n";
	
	q1prev=q1;//set previous q1, q1(t), to equal the current q1
	for (int t = 1;t<255;t++){
		q1next=q1prev+probability[t+1]; //q1next-q1(t+1)
		mu1next=(q1prev*mu1+(t+1)*(probability[t+1]))/q1next;//set mu1(t+1)
		mu2next= (mu-q1next*mu1next)/(1-q1next);//set mu2(t+1)
		betweenvariance = q1prev*(1-q1prev)*((mu1-mu2)*(mu1-mu2));//calculate between group variance
		//max between group variance is initially set to 0. Change the max between group variance, and change the optimized threshold to t if the current variance is > max.
		if (betweenvariance>maxbetweenvariance){
			maxbetweenvariance=betweenvariance;
			optimizedthresh=t;//set new optimized threshhold
		}
		
		q1prev=q1next;//set q1(t) to be used in the next iteration to be equal to the current q1(t+1) which is q1next
		mu1=mu1next;//do the same for mu1. set mu1(t) of next iteration to equal the current mu1(t+1)
		mu2=mu2next;//set mu2(t) of next iteration to equal the current mu2(t+1)
		
		if(q1next==0){
			mu1=0;//this eliminates divide by 0 errors because the calculate of the next mu1 would be undefend if the next value of q1 is 0, according to the otsu recursive algorithm
		}

	}
	//cout << optimizedthresh;
	//set image values based on the optimized threshhold calculated above.
	for (int i =0;i<image->height();i++)
	{
		for (int j =0;j<image->width();j++){
			pixelvalue=image->atXY(j,i,0);
			if (pixelvalue<optimizedthresh){//if pixelvalue is< than the threshhold, set it to 200
				pixelvalue=image->atXY(j,i,0)=200;
				pixelvalue=image->atXY(j,i,1)=200;
				pixelvalue=image->atXY(j,i,2)=200;}
			else //if pixelvalue is> than the threshhold, set it to 0
			{
				pixelvalue=image->atXY(j,i,0)=0;
				pixelvalue=image->atXY(j,i,1)=0;
				pixelvalue=image->atXY(j,i,2)=0;}
			{
			
			}
		}
	}
	cout << "\n";
 cout << "Threshold: "<< optimizedthresh;
cout << "\n";
cout << "\n";
cout << "\n";

image->save("lena256otsu2.bmp");//save edited image file with "otsu" concatenated to the end of the filename
image->display();//display image file
}
