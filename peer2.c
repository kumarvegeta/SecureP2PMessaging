
//The client peer

#include "common/common.h"
#include "myitoa.c"

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to send data

long long int n = 8191;
long long int g = 3; 
 
void die(char *s)
{
    perror(s);
    exit(1);
}

//long long int keygen(void);

//long long int power(long long int,long long int, long long int);

//void reverse(char[]);

//void myitoa(long long int, char[]);

//WE WRITE OUR SIGNAL HANDLER CODE HERE!!!

static void sigint_handler(int sig_no) {

int n=0;

n=sig_no;

printf("\n Signal number received is %d \n:",n);

printf("\n SIGINT received..going to terminate present state and restore defaults.\n");

//system("del recordedIP.txt");

printf("\n DONE.\n");

sleep(1);

exit(0);

} //Handler for SIG_INT


  char captcha[10];

  char captcha_copy[10];


int main(void)
{

    if(!(signal(SIGINT,sigint_handler))); //Signal generator in case of trouble!!

    long long int num = 0;

    long long int val = 0;

    long long int received_num = 0;

    long long int key = 0;

    char SERVER[17];

    struct stat statbuf;

    char pathname[BUFLEN];

    char command[BUFLEN];

    char ch;

    char username[BUFLEN];

    char password[BUFLEN];

    int recv_len = 0;

    memset((char *) captcha, '\0', sizeof(captcha));

    memset((char *) captcha_copy, '\0', sizeof(captcha_copy));
	
    FILE* fp;

    fp = fopen("stored_ip.txt","r+");

    fscanf(fp,"%s",SERVER); //This makes sure that the static server IP is now with the client in its memory.

    fclose(fp);

    //while ( (ch=getchar()) != EOF && ch != '\n' );

    int j = 0;

    while(j< sizeof(struct sockaddr_in)) {

	j++;

    }

    SERVER[j] = '\0';

    //printf("\n Testing STATIC IP read: ");	

    //puts(SERVER);

    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);

    long long int choice = 0;

    char buf[BUFLEN];

    char message[BUFLEN];
    
    char converted_key[8];

    char final_key[8];

    char ivec[8];

    memset((char *)converted_key, 'a', sizeof(converted_key));

    memset((char *) final_key, 'a', sizeof(final_key));

    memset((char *) ivec, 'a', sizeof(ivec));

    //bzero(converted_key, sizeof(converted_key));

    //bzero(final_key, sizeof(final_key));

    memset((char*) username, '\0', sizeof(username));

    memset((char*) password, '\0', sizeof(password));
 
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    fcntl(socket, F_SETFL, O_NONBLOCK); //Setting socket to non-blocking mode.
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

	while(1) {

	if(val == 0) {

	num = keygen();

	if (sendto(s, &num, sizeof(long long int) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }


	if (recvfrom(s, &received_num, sizeof(long long int) , 0 , (struct sockaddr *) &si_other, (socklen_t*)&slen)==-1)
        {
            die("sendto()");
        }	


	if((key=power(g,received_num, n))) {

	
	//printf("\n Shared key has been successfully created. \n");

	//printf("\n Testing shared key: %lld",key);

	// Now convert this key into a string.

	myitoa(key,converted_key);

	//printf("\n Testing size of converted key:\n");		

	//puts(converted_key);

	strcpy(final_key,converted_key);

	//printf("\n %d \n",sizeof(converted_key));

	//des_setparity(converted_key);
	
	//setkey(converted_key);

	//break;

	}

	else {

	printf("\n Failed to create shared key. Exiting.\n");

	exit(1);

	}


	val++;	

	}

	break; 

	} //End of containing while


	
     //WE need to do three things, generate a username and password here, send them to the server securely, and receive and send back a 

     //captcha securely. 


     printf("\n Enter your username : \n");


     gets(username);


     recv_len = (size_t)sizeof(username);

	
	if(cbc_crypt(final_key,username,BUFLEN,DES_ENCRYPT|DES_SW,ivec) == 0){

	printf("\n Data encryption successful \n");

	//printf("\n Generated cipher text is: \n");

	//puts(buf);
	
	}	

	

        if (sendto(s, username, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }

	printf("\n\n");


	//we're getting the ack from the server peer too. SO..

	
	bzero(username,BUFLEN);


	if ((recv_len = recvfrom(s, username, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) == -1)
        {
            die("recvfrom()");
        }
         	

	if(cbc_crypt(final_key,username,BUFLEN,DES_DECRYPT|DES_SW,ivec) == 0){

	printf("\n Data Decryption successful \n");

	printf("\n Acknowledged by server. \n");

	puts(username);
	
	}


     printf("\n Enter your password : \n");


     gets(password);


     recv_len = (size_t)sizeof(password);

	
	if(cbc_crypt(final_key,password,BUFLEN,DES_ENCRYPT|DES_SW,ivec) == 0){

	printf("\n Data encryption successful \n");

	//printf("\n Generated cipher text is: \n");

	//puts(password);
	
	}	

	

        if (sendto(s, password, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }

	printf("\n\n");


	//Again, the ack from the server.


	bzero(password,BUFLEN);


	if ((recv_len = recvfrom(s, password, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) == -1)
        {
            die("recvfrom()");
        }
         	

	if(cbc_crypt(final_key,password,BUFLEN,DES_DECRYPT|DES_SW,ivec) == 0){

	printf("\n Data Decryption successful \n");

	printf("\n Acknowledged by server. \n");

	puts(password);
	
	}


	// The captcha reception from the server.

	if (recvfrom(s, captcha, sizeof(captcha) , 0 , (struct sockaddr *) &si_other, (socklen_t*)&slen)==-1)
        {
            die("sendto()");
        }

	printf("\n Received captcha from %s:\n", inet_ntoa(si_other.sin_addr));

	if(cbc_crypt(final_key,captcha,sizeof(captcha),DES_DECRYPT|DES_SW,ivec) == 0){

	printf("\n Data decryption successful. \n");

	printf("\n Sent captcha text is: \n");

	puts(captcha);
	
	}

	
	// The comparison logic. If the message sent is not the same, the program terminates.

	
	strcpy(captcha_copy,captcha);

	bzero(captcha, sizeof(captcha));

	printf("\n Please re-enter the captcha for confirmation:\n");

	gets(captcha);

	//send the captcha

	if(cbc_crypt(final_key,captcha,sizeof(captcha),DES_ENCRYPT|DES_SW,ivec) == 0){

	printf("\n Captcha encryption successful \n");

	//printf("\n Generated cipher text is: \n");

	//puts(captcha);
	
	}

        if (sendto(s, captcha, sizeof(captcha) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }


	
	if(cbc_crypt(final_key,captcha,sizeof(captcha),DES_DECRYPT|DES_SW,ivec) == 0){

	//printf("\n Data decryption successful. \n");

	//printf("\n Sent captcha text is: \n");

	//puts(captcha);
	
	}


	if(strstr(captcha_copy,captcha) == NULL) {


		printf("\n Incorrect captcha entered. Exiting. \n");

		close(s);

		exit(1);


	}

	
	printf("\n 1. Engage secure communication. \n");

	printf("\n 2. Upload a file securely. \n");

	printf("\n 3. Download a file securely. \n");

	printf("\n 4. Track a remote file or directory. \n"); 

	printf("\n 5. Quit. \n");

	printf("\n Enter your choice :\n");

	scanf(" %ld", &choice);


	//sending the choice to the server

        if (sendto(s, &choice, sizeof(long long int) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
   

      
 

    while(1) {

	fflush(stdout);

	switch(choice) {

        case 1:

	if(val == 0) {

	val++;

	//printf("\n Trying to put in a key exchange here. \n");

	} 


	else {

	printf("\nMessage : ");
	
        gets(message);

	if(cbc_crypt(final_key,message,sizeof(message),DES_ENCRYPT|DES_SW,ivec) == 0){

	printf("\n Data encryption successful \n");

	//printf("\n Generated cipher text is: \n");

	//puts(message);
	
	}	
         
        //send the message

        if (sendto(s, message, BUFLEN , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
         
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        
	memset(buf,'\0', BUFLEN);

	printf("\n\n");


        //try to receive some data, this is a blocking call


        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen) == -1)
        {
            die("recvfrom()");
        }
        
	//print details of the client/peer and the data received
        printf("\nReceived message from %s:\n", inet_ntoa(si_other.sin_addr));

	if(cbc_crypt(final_key,buf,BUFLEN,DES_DECRYPT|DES_SW,ivec) == 0){

	printf("\n Data decryption successful. \n");

	//printf("\n Generated plain text is: \n");

	//puts(buf);
	
	}	

	printf("\n\n"); 
	
        puts(buf);

	printf("\n\n");

	} //End  of else

	break;


     case 2: printf("\n what's the name of the file you wish to upload? : \n");

	     scanf("%s",message);

	     bzero(pathname, BUFLEN);

             strcpy(pathname,"client_store/");

	     strcat(pathname,message);

	     bzero(buf, BUFLEN);


	     if(cbc_crypt(final_key,message,sizeof(message),DES_ENCRYPT|DES_SW,ivec) == 0){

	     printf("\n Data encryption successful \n");

	     //printf("\n Generated cipher text is: \n");

	     //puts(message);
	
	    }	
         
           //send the message

           if (sendto(s, message, BUFLEN , 0 , (struct sockaddr *) &si_other, slen)==-1)
         {
            die("sendto()");
         }

          fp = fopen(pathname,"r+");

	  if(fp == NULL) {

	printf("\n Sorry. The file or directory by the said name does not exist. Or, there is an error.\n") ;
               close(s);
	       return 0;
	
	}

	//Assuming it went past that, we have

	fread(buf, BUFLEN , 1, fp);
	
       
	while (sendto(s, buf, BUFLEN , 0 , (struct sockaddr *) &si_other, slen)== 0)

        {

           fread(buf, BUFLEN , 1, fp);

        }


	fclose(fp);
        
	printf("\n\n");

	     close(s);

	      return 0;

	     break;

     case 3: printf("\n what's the name of the file you wish to download? \n:");

	     scanf("%s",message);

	     bzero(pathname, BUFLEN);

             strcpy(pathname,"client_store/");

	     strcat(pathname,message);

	     bzero(buf, BUFLEN);


	     if(cbc_crypt(final_key,message,sizeof(message),DES_ENCRYPT|DES_SW,ivec) == 0){

	     printf("\n Data encryption successful \n");

	     //printf("\n Generated cipher text is: \n");

	     //puts(message);
	
	    }	
         
           //send the message

           if (sendto(s, message, BUFLEN , 0 , (struct sockaddr *) &si_other, slen)==-1)
         {
            die("sendto()");
         }


	 if (stat(pathname, &statbuf) == -1) {
               printf("\n Sorry. The file or directory by the said name does not exist. Or, there is an error.\n") ;
               close(s);
	       return 0;

           }

	//Assuming it passed that, the file was found. Now to erase, and recreate.

	bzero(command, BUFLEN);

	strcpy(command,"rm -rf ");

	strcat(command,pathname);


        /*if((unlink(pathname))!=0) {

	
	printf("\n Problem while replacing. Sorry. \n");

	close(s);

	return 0;

	}*/

	system(command); //Lets try this.
	
	bzero(command, BUFLEN);

	strcpy(command,"touch ");

	strcat(command,pathname);

	system(command); //Risky, but effective.

	bzero(buf, BUFLEN);

	fp = fopen(pathname,"w+");

	if(fp == NULL) {

	printf("\n Sorry. The file or directory by the said name does not exist. Or, there is an error.\n") ;
               close(s);
	       return 0;
	
	}

	//Assuming it went past that, we have
       

        while((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) == 0) {

	fwrite(buf, strlen(buf), 1, fp);
	

	}

	printf("\n\n");

	fclose(fp);

	    close(s);

	    return 0;

	    break;

     case 4: printf("\n what's the full path of the file or directory structure you wish to track, friend? \n:");

	     scanf(" %s",message);

	     bzero(pathname, BUFLEN);

             strcpy(pathname,"client_store/");

	     strcat(pathname,message);

	     bzero(buf, BUFLEN);


	     if(cbc_crypt(final_key,message,sizeof(message),DES_ENCRYPT|DES_SW,ivec) == 0){

	     printf("\n Data encryption successful \n");

	     //printf("\n Generated cipher text is: \n");

	     //puts(message);
	
	    }	
         
           //send the message

           if (sendto(s, message, BUFLEN , 0 , (struct sockaddr *) &si_other, slen)==-1)
         {
            die("sendto()");
         }
	     fflush(stdout);

	bzero(buf,BUFLEN);

	fp = fopen("client_store/statfile.txt","w+");

	if(fp == NULL) {

	printf("\n Sorry. The file or directory by the said name does not exist. Or, there is an error.\n") ;
               close(s);
	       return 0;
	
	}

	//Assuming it went past that, we have
       
        while((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) == 0) {

	fwrite(buf, strlen(buf), 1, fp);
	

	}

	printf("\n\n");

	fclose(fp);

	    close(s);

	    return 0;

	    break;


     case 5: close(s);

	     return 0;

	     break;

     default: printf("\n wrong choice. closing connection. \n");

	     close(s);

	     return 0;
	    

       } //End of switch

    }
 
    close(s);
    return 0;
}

//keygen function - Using Diffie Hellman method

long long int keygen(){

long long int x,num;
 
 // each person will choose the x value
 //printf("Enter the value of x: ");
 //scanf("%d",&x);

 x = (long long int)rand();

 if(x==0) {x = 10000;}

 num=power(g,x,n);
 
 return num;

}

long long int power(long long int g,long long int var, long long int n) {
long long int t;
long long int result = 0;

 if(var==1)
  return g;
 t=power(g,var/2,n);
 if(var%2==0)
	{

	result = (t*t)%n;
  return result;

	}
 else

	{	

  result = (((t*t)%n)*g)%n; 	

  return result;

	}

}




