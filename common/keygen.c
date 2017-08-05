

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


