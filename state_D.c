////	calculating cooking time in secends	////
unsigned long calc(char arr[4])
{
    unsigned long duration = 0;
    long i;
    for (i = 0; i<4 ;i++)	// convert from char --> number
    {
        arr [i]= (arr[i] - '0');
    }
    duration = arr[0] + arr[1]*10 + arr[2]*60 + arr[3]*600;
    return duration;
}
