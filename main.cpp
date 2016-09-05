#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <unistd.h>
#include <math.h>

using namespace cv;
Mat render[7];
int render_mat[7];
int screen=0;

void *capture_video( void *ptr );
void *capture_detecta_contorno( void *ptr );

main()
{
     pthread_t thread1, thread2;
     const char *message1 = "Thread 1";
     const char *message2 = "Thread 2";
     int  iret1, iret2;

    /* Create independent threads each of which will execute function */

     iret1 = pthread_create( &thread1, NULL, capture_video, (void*) message1);
     if(iret1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
         exit(EXIT_FAILURE);
     }
	/*
     iret2 = pthread_create( &thread2, NULL, print_message_function, (void*) message2);
     if(iret2)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
         exit(EXIT_FAILURE);
     }
	*/
     printf("pthread_create() for thread 1 returns: %d\n",iret1);
	namedWindow("Display Image", WINDOW_AUTOSIZE );
	namedWindow("Display Image2", WINDOW_AUTOSIZE );
     //printf("pthread_create() for thread 2 returns: %d\n",iret2);
waitKey(0); 
		while(1)
		{
		
			
			imshow("Display Image", render[screen]);
			if(waitKey(30) >= 0) break;
		}	
    return 0;
	
     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join( thread1, NULL);
    // pthread_join( thread2, NULL); 

     exit(EXIT_SUCCESS);
}


void *capture_detecta_contorno( void *ptr )
{
cv::Mat temp;
int temp_index= screen;
render_mat[temp_index]=1;
cvtColor(render[screen], temp, CV_BGR2GRAY);
imshow("Display Image2",temp);
render_mat[temp_index]=0;
}

void *capture_video( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
	
	int index=0;
cv::VideoCapture cap(0);
if (!cap.isOpened())
  
  	{
        printf("Camera  ERROR CONNECT\n");
        //return 1;
    }
	
	while (1){
	if(	render_mat[index]==1)
		{
		if(index<7)
			{
				index++;
			}
		else
			{
			if(render_mat[0]!=1)
				{
				index = 0;
				}
			else
				{
				printf("buffer overflow index.\n");
				}
			}
		
		
		}
	if(render_mat[index]!=1)
		{
		cap >> render[index];
			screen=index;
		}
	else
		{
		printf("buffer overflow 1.\n");
		}
	}
	printf("captura index %d\n", index);
}

