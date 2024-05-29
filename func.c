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

char arr[4]={0},Title[100]={0},Artist[100]={0},Album[100]={0},Music[100]={0},Genre[100]={0},Year[4]={0},version[3]={0};

Status tag_reader(FILE *fptr,char *version)
{
    fseek(fptr,10,SEEK_SET);
    for(int i=0;i<6;i++)
    {
	fread(arr,4,1,fptr);
	int size=0;
	fread(&size,4,1,fptr);
	SWAP(size);
	fseek(fptr,3,SEEK_CUR);
	if(strncmp(arr,"TIT2",4) == 0)
	{
	    fread(Title,size-1,1,fptr);
	}
	else  if(strncmp(arr,"TYER",4) == 0)
	{
	    fread(Year,size-1,1,fptr);
	}
	else if(strncmp(arr,"TALB",4) == 0)
	{
	    fread(Album,size-1,1,fptr);
	}
	else if(strncmp(arr,"TPE1",4) == 0)
	{
	    fread(Artist,size-1,1,fptr);
	}
	else  if(strncmp(arr,"TCON",4) == 0)
	{
	    fread(Genre,size-1,1,fptr);
	}
	else  if(strncmp(arr,"COMM",4) == 0)
	{
	    fread(Music,size-1,1,fptr);
	}
    }
    printf("..........................................................\n");
    printf("MP3 Tag Reader and Editor for ID3 v%s\n",version);
    Year[4] ='\0';
    printf("..........................................................\n");
    printf("Title\t :\t %s\nArtist\t :\t %s\nAlbum\t :\t %s\nYear\t :\t %s\nMusic\t :\t%s\nGenre\t :\t %s\n",Title,Artist,Album,Year,Music,Genre);
    
    return e_success;
}

Status copy_remain(FILE *src, FILE *dest, char * user_tag, char * user_string)
{
    int size,sample_size;
    char str[100];
    fread(str,10,1,src);
    fwrite(str,10,1,dest);
    for(int i=0;i<6;i++)
    {
	fread(str,4,1,src);
	fwrite(str,4,1,dest);
	if(strncmp(str,user_tag,4) == 0)
	{
	    size = strlen(user_string);
	    int temp =size;
	    size++;
	    SWAP(size);
	    fwrite(&size,4,1,dest);
	    fread(&sample_size,4,1,src);
	    fread(str,3,1,src);
	    fwrite(str,3,1,dest);
	    fwrite(user_string,temp,1,dest);
	    SWAP(sample_size);
	    fseek(src,sample_size-1,SEEK_CUR);
	}
	else
	{

	    fread(str,4,1,src);
	    fwrite(str,4,1,dest);
	    fseek(src,-4,SEEK_CUR);

	    fread(&sample_size,4,1,src);

	    SWAP(sample_size);

	    fread(str,3,1,src);
	    fwrite(str,3,1,dest);

	    fread(str,sample_size-1,1,src);
	    str[sample_size-1] = '\0';
	    fwrite(str,sample_size-1,1,dest);
	}
    }
    return e_success;
}
