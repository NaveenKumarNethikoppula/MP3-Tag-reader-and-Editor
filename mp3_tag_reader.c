#include "header.h"
#define SWAP(num) \
{\
    unsigned char * str = (unsigned char *) &num; \
    for(int i=0;i<2;i++) \
    { \
	char temp =str[i]; \
	str[i] = str[4-i-1]; \
	str[4-i-1] = temp; \
    } \
}

int main(int argc,char * argv[])
{
    char version[3]={0};
    FILE *fptr;
    if(argc == 1)
    {
	printf("Error : Please pass valid either -t,-T,-a,-A,-y,-c,-g,-h,-v and MP3 file name\n");
	return 0;
    }
    if(strcmp(argv[1] ,"--help") == 0)
    {
	printf("Usage : mp3tag -[tTaAycg] ""value"" file1 mp3tg -v\n-t\tModifies a Title tag\n-T\tModifies a Track tag\n-a\tModifies an Artist tag\n-A\tModifies an Album tag\n-y\tModifies a Year tag\n-c\tModifies a Comment tag\n-g\tModifies a Genre tag\n-h\tDisplays this help info\n-v\tPrints Version info\n");
    }
    if(strcmp(argv[1],"-v") == 0)
    {
	if(argv[2] ==0)
	{
	    printf("Please pass file name\n");
	    return 0;
	}
	fptr = fopen(argv[2],"r");
	char arr[4]={0};
	fread(arr,3,1,fptr);
	if(strcmp(arr,"ID3") != 0)
	{
	    fprintf(stderr,"file is not a mp3 file name\n");
	    printf("Please pass a mp3 file name\n");
	    return 0;
	}
	fread(version,2,1,fptr);
	if(version[0] == 3 && version[1] == 00)
	{
	    strcpy(version,"2");
	}
	if(tag_reader(fptr,version) == e_success)
	{
	    printf("Read tags successfully Done\n");
	}
	else
	{
	    printf("Read tags Failure\n");
	}
	fclose(fptr);
    }
    if(strcmp(argv[1],"-e") == 0)
    {
	if(argv[4] == 0)
	{
	    printf("please provide the mp3 file\n");
	    return 0;
	}
	if(argv[2] == 0)
	{
	    printf("please pass any proper option to edit\n");
	    return 0;
	}
	FILE *src = fopen(argv[4],"r");
	FILE *dest = fopen("temp.mp3","w");
	char str[50],arr[5];
	if(dest == NULL)
	{
	    return 0;
	}
	strcpy(str,argv[3]);
	if(strcmp(argv[2],"-t") == 0)
	{
	    strcpy(arr,"TIT2");
	    printf("You choose title edit\n");
	}
	else if(strcmp(argv[2], "-a") == 0)
	{
	    strcpy(arr,"TPE1");
	    printf("You choose Artist edit\n");
	}
	else if(strcmp(argv[2], "-A") == 0)
	{
	    strcpy(arr,"TALB");
	    printf("You choose Album edit\n");
	}
	else if(strcmp(argv[2], "-y") == 0)
	{
	    strcpy(arr,"TYER");
	    printf("You choose Year edit\n");
	}
	else if(strcmp(argv[2],"-c") == 0)
	{
	    strcpy(arr,"COMM");
	    printf("You choose Composer edit\n");
	}
	else if(strcmp(argv[2], "-g") == 0)
	{
	    strcpy(arr,"TCON");
	    printf("You choose Language edit\n");
	}
	else
	{
	    printf("Enter a valid input\n");
	    return 0;
	}
	if(copy_remain(src,dest,arr,str) == e_success)
	{
	    printf("Successfully Completed the Tag edit\n");
	}
	else
	{
	    printf("Editing the tags was Failed\n");
	}
    }
    return 0;
}

