//This is the server-side functionality.

#include "common/common.h"
#include "myitoa.c"

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

long long int n = 8191;
long long int g = 3;

//long long int keygen(void);

//long long int power(long long int,long long int, long long int);

//void reverse(char[]);

//void myitoa(long long int, char[]);
 
void gen_random(char *, const int); //We get to this later.

 
void die(char *s)
{
    perror(s);
    exit(1);
}

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

int main(int argc,char*argv[]) {

    struct sockaddr_in si_me, si_other;
     
    int s, i, slen = sizeof(si_other) , recv_len;

    struct stat statbuf;

    FILE *fp;

    char buf[BUFLEN];

    char pathname[BUFLEN];

    char command[BUFLEN];

    /*int ch;
 
    while ( (ch=getchar()) != EOF && ch != '\n' );*/

    long long int num = 0;

    long long int val = 0;

    long long int received_num = 0;
 
    long long int key = 0;

    long long int choice = 0;

    char converted_key[8];

    char final_key[8];

    char ivec[8];

    char username[BUFLEN];

    char password[BUFLEN];

    memset((char *)converted_key, 'a', sizeof(converted_key));

    memset((char *) final_key, 'a', sizeof(final_key));

    memset((char *) ivec, 'a', sizeof(ivec));

    memset((char*) username, '\0', sizeof(username));

    memset((char*) password, '\0', sizeof(password));

    memset((char *) captcha, '\0', sizeof(captcha));

    memset((char *) captcha_copy, '\0', sizeof(captcha_copy));

    //bzero(converted_key, sizeof(converted_key));

    //bzero(final_key, sizeof(final_key));

     if(!(signal(SIGINT,sigint_handler))); //Signal generator in case of trouble!!
     
label:    
	//create a UDP socket
    
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
     //fcntl(socket, F_SETFL, O_NONBLOCK); //Setting socket to non-blocking mode.


    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }

	fcntl(socket, F_SETFL, O_NONBLOCK); //Setting socket to non-blocking mode.

	while(1) {

	if(val == 0) {

	num = keygen();


	if (recvfrom(s, &received_num, sizeof(long long int) , 0 , (struct sockaddr *) &si_other, (socklen_t*)&slen)==-1)
        {
            die("sendto()");
        }	


	if (sendto(s, &num, sizeof(long long int) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }


	if((key=power(g,received_num, n))) {

	
	//printf("\n Shared key has been successfully created. \n");

	//printf("\n Testing shared key: %lld",key);

	// Now convert this key into a string.

	myitoa(key,converted_key);

	strcpy(final_key,converted_key);

	//printf("\n Testing size of converted key:\n");		

	//puts(converted_key);

	//printf("\n %d \n",sizeof(converted_key));

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
    

        //Now receiving username and password, and ack'ing.

 
	if ((recv_len = recvfrom(s, username, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) == -1)
        {
            die("recvfrom()");
        }
         
	

	if(cbc_crypt(final_key,username,BUFLEN,DES_DECRYPT|DES_SW,ivec) == 0){

	printf("\n Data Decryption successful \n");

	printf("\n Received username from client. \n");

	//puts(username);
	
	}	


	bzero(username, BUFLEN);

	strcpy(username, "I got it.");

	recv_len = (size_t)sizeof(username);

	//Need to encrypt ack here, thats one thing.


	if(cbc_crypt(final_key,username,BUFLEN,DES_ENCRYPT|DES_SW,ivec) == 0){

	printf("\n Data Encryption successful \n");

	printf("\n Sending username ack to client. \n");

	//puts(username);
	
	}	


        if (sendto(s, username, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }

	printf("\n\n");


     //Need to recv() password here.


	if ((recv_len = recvfrom(s, password, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) == -1)
        {
            die("recvfrom()");
        }
         
	

	if(cbc_crypt(final_key,password,BUFLEN,DES_DECRYPT|DES_SW,ivec) == 0){

	printf("\n Data Decryption successful \n");

	printf("\n Received password from client. \n");

	//puts(password);
	
	}	


	bzero(password, BUFLEN);

	strcpy(password, "I got it.");


	//Encrypt Ack for password again here.


	if(cbc_crypt(final_key,password,BUFLEN,DES_ENCRYPT|DES_SW,ivec) == 0){

	printf("\n Data Encryption successful \n");

	printf("\n Sending password ack to client. \n");

	//puts(password);
	
	}	

	
        recv_len = (size_t)sizeof(password);


        if (sendto(s, password, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }

	printf("\n\n");


     //Now we generate a captcha on the fly.

     gen_random(captcha, sizeof(captcha));

     myitoa(sizeof(captcha), captcha);

     strcpy(captcha_copy,captcha);


     //We try sending the captcha to the client.

     if(cbc_crypt(final_key,captcha,sizeof(captcha),DES_ENCRYPT|DES_SW,ivec) == 0){

	printf("\n CAPTCHA encryption successful. \n");

	//printf("\n Generated cipher text is: \n");

	//puts(captcha);
	
	}	


	printf("\n\n");

     
     if (sendto(s, captcha, sizeof(captcha) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }


	bzero(captcha, sizeof(captcha));


     //The client's reply. It is, ideally the same captcha. Will be compared here though.

       if (recvfrom(s, captcha, sizeof(captcha) , 0 , (struct sockaddr *) &si_other, (socklen_t*)&slen)==-1)
        {
            die("sendto()");
        }	

       if(cbc_crypt(final_key,captcha,sizeof(captcha),DES_DECRYPT|DES_SW,ivec) == 0){

	printf("\n CAPTCHA decryption successful. \n");

	//printf("\n Generated cipher text is: \n");

	//puts(captcha);
	
	}	


	if(strstr(captcha_copy,captcha) == NULL) {


		printf("\n Incorrect captcha entered by peer. Closing connection. \n");

		close(s);

		goto label;


	}


	puts(captcha);

	printf("\n\n");


 	
	// receive the choice of option from the client

	if (recvfrom(s, &choice, sizeof(long long int) , 0 , (struct sockaddr *) &si_other, (socklen_t*)&slen)==-1)
        {
            die("sendto()");
        }	


	printf("\n Client has sent option %ld \n",choice);

 
    //keep listening for data

    while(1)
    {
        
        switch(choice) {

    case 1:

	if(val == 0) {

	val++;

	//printf("\n Trying to put in a key exchange here. \n");

	}
	

	else {

	//printf("Waiting for data...");
	
	fflush(stdout);

	bzero(buf,BUFLEN);
	       
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) == -1)
        {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        printf("\n Received message from %s:\n", inet_ntoa(si_other.sin_addr));

        //printf("Data: %s\n" , buf);

	if(cbc_crypt(final_key,buf,BUFLEN,DES_DECRYPT|DES_SW,ivec) == 0){

	printf("\n Data decryption successful. \n");

	//printf("\n Generated cipher text is: \n");

	//puts(buf);
	
	}	

	printf("\n\n");

	puts(buf);

	printf("\n\n");
         
        //now reply to the client with the some data

	printf("\nMessage : ");

	bzero(buf,BUFLEN);

	//num = keygen();

	gets(buf);

	recv_len = (size_t)sizeof(buf);

	
	if(cbc_crypt(final_key,buf,BUFLEN,DES_ENCRYPT|DES_SW,ivec) == 0){

	printf("\n Data encryption successful \n");

	//printf("\n Generated cipher text is: \n");

	//puts(buf);
	
	}	

	

        if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }

	printf("\n\n");
 
	}

	break;

     case 2:  fflush(stdout);

	bzero(buf,BUFLEN);
	       
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) == -1)
        {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        printf("\n Received file name from %s:\n", inet_ntoa(si_other.sin_addr));

        //printf("Data: %s\n" , buf);

	if(cbc_crypt(final_key,buf,BUFLEN,DES_DECRYPT|DES_SW,ivec) == 0){

	printf("\n Data decryption successful. \n");

	//printf("\n Generated cipher text is: \n");

	//puts(buf);
	
	}	

	printf("\n\n");

	puts(buf);

	bzero(pathname, BUFLEN);

        strcpy(pathname,"server_store/");

	strcat(pathname,buf);

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
	
	bzero(buf, BUFLEN);

	}

	printf("\n\n");

	fclose(fp);

	close(s);

	return 0;

	break;


     case 3:

	fflush(stdout);

	bzero(buf,BUFLEN);
	       
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) == -1)
        {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        printf("\n Received file name from %s:\n", inet_ntoa(si_other.sin_addr));

        //printf("Data: %s\n" , buf);

	if(cbc_crypt(final_key,buf,BUFLEN,DES_DECRYPT|DES_SW,ivec) == 0){

	printf("\n Data decryption successful. \n");

	//printf("\n Generated cipher text is: \n");

	//puts(buf);
	
	}	

	printf("\n\n");

	puts(buf);

	
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
        
	printf("\n\n");

	fclose(fp);

	close(s);
	
	return 0;
	
	break;	
	
     
     case 4:
		       
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t*)&slen)) == -1)
        {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        printf("\n Received absolute path from %s:\n", inet_ntoa(si_other.sin_addr));

        //printf("Data: %s\n" , buf);

	if(cbc_crypt(final_key,buf,BUFLEN,DES_DECRYPT|DES_SW,ivec) == 0){

	printf("\n Data decryption successful. \n");

	//printf("\n Generated cipher text is: \n");

	//puts(buf);
	
	}	

	printf("\n\n");

	puts(buf);

	bzero(pathname,BUFLEN);

	strcpy(pathname,buf);

	bzero(command, BUFLEN);

	strcpy(command,"stat ");

	strcat(command,pathname);

	strcat(command," > statfile.txt");

	system(command);

	fp = fopen("statfile.txt","r+");

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

   } //End of the server main()

 

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

//Function that generates a random string

void gen_random(char *s, const int len) {
    static const char alphanum[] =     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~!@#$%^&*()_";
 
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
 
    s[len] = 0;
}


