#include<string.h> 
#include<stdlib.h> 
#include<stdio.h> 
struct sframe 
{ 
        int fno; 
        int random; 
        int len; 
        char msg[40]; 
}frame[100],temp; 
char mes[100]; 

int main() 
{ 
        int i,k,j,ml,fi,fcount,found,r,over,framel; 
        int maxflen; 
        int len; 
        printf("\nEnter message = "); 
        //scanf("%s",mes); 
        gets(mes);

        printf("\n Enter max frame size in characters Ex: 3  ) : "); 
        scanf("%d", &maxflen); 

        ml=strlen(mes); 
        i=0; 
        fi=0; 
        over=0; 
        while(1) 
        { 
                   j=0; 
                   len=1+(random()%maxflen); 
                   while(j<len) 
                   { 
                             frame[fi].msg[j++]=mes[i++]; 
               
                             if(mes[i]=='\0') 
                             { 
                             	over=1;
                                frame[fi].fno=fi; 
	                            frame[fi].len=j; 
                                frame[fi].random=random()%100; 
                                break; 
	                     }  //if 
                       
                    } //while j<len 
                    if(over==1)break; 
                  
                   
                    frame[fi].fno=fi; 
                    frame[fi].len=len; 
                    frame[fi].random=random()%100; 
                    fi++;                     
         }  //while outer 

         fcount=fi+1; 
         printf("\nThe frames created are :\n"); 
         printf("\nSequence_No  Random_num  Length            Content"); 
         for(i=0;i<fcount;i++) 
         { 
                printf("\n%d                %d          %d            %s", frame[i].fno,frame[i].random,frame[i].len,frame[i].msg);   
               
         } 
          //SORT wrt random --  simulate network delays 
         for(i=0;i<fcount;i++) 
         { 
                for(j=0;j<fcount;j++) 
                { 
                       if(frame[i].random<frame[j].random) 
                       { 
	                    
	                    temp=frame[i]; 
		                frame[i]=frame[j]; 
		                frame[j]=temp; 
	              }     
                 } 
         } 

        //print recieved message 
        printf("\n---------------------------------------------------------------------------"); 
        printf("\nFrames after simulting delay at router ="); 
        printf("\nSequence_No  Random_num  Length            Content"); 
        for(i=0;i<fcount;i++) 
        { 
                printf("\n%d                %d          %d            %s", frame[i].fno,frame[i].random,frame[i].len,frame[i].msg);   
        } 
        printf("\nMessage received at receiver = "); 
        for(i=0;i<fcount;i++) 
        {
            printf("%s",frame[i].msg);
        }   
        //sort wrt serial number 
        for(i=0;i<fcount;i++) 
        { 
                for(j=0;j<fcount;j++) 
                { 
                       if(frame[i].fno<frame[j].fno) 
                       { 
	                        temp=frame[i]; 
		                frame[i]=frame[j]; 
		                frame[j]=temp; 
	              }   
                 } 
         } 
        //print reordered message 
        printf("\n---------------------------------------------------------------------------"); 
        printf("\nFrames re constructed ="); 
        printf("\nSequence_No  Random_num  Length            Content"); 
         for(i=0;i<fcount;i++) 
        { 
                printf("\n%d                %d          %d            %s", frame[i].fno,frame[i].random,frame[i].len,frame[i].msg);   
        } 
        printf("\n\nMessage  at receiver = "); 
        for(i=0;i<fcount;i++) 
        { 
        	printf("%s",frame[i].msg);
        } 
        printf("\n"); 
} //main   

/* output

shree@dell-Inspiron-5559:~/network$ gcc A2.c
shree@dell-Inspiron-5559:~/network$ ./a.out

Enter message = vinay_siddesh

 Enter max frame size in characters Ex: 3  ) : 3

The frames created are :

Sequence_No  Random_num  Length            Content
0                86          2            vi
1                15          1            n
2                35          3            ay_
3                92          2            si
4                21          1            d
5                27          3            des
6                59          1            h
---------------------------------------------------------------------------
Frames after simulting delay at router =
Sequence_No  Random_num  Length            Content
1                15          1            n
4                21          1            d
5                27          3            des
2                35          3            ay_
6                59          1            h
0                86          2            vi
3                92          2            si
Message received at receiver = nddesay_hvisi
---------------------------------------------------------------------------
Frames re constructed =
Sequence_No  Random_num  Length            Content
0                86          2            vi
1                15          1            n
2                35          3            ay_
3                92          2            si
4                21          1            d
5                27          3            des
6                59          1            h

Message  at receiver = vinay_siddesh  */

