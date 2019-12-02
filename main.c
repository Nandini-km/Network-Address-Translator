#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main(int argc,char * argv[])
{
  //Check the number of input agruments.
  if(argc!=4){printf("The number of arguments are not correct.");exit(0);}

  FILE *input=fopen(argv[1],"rf");
  if (input==NULL){
    printf("Could not open input file");
    exit(0);
  }

  FILE *flow=fopen(argv[2],"rf");
  if (flow==NULL)
  {
    printf("Could not open flow file");
    exit(0);
  }
  FILE *out=fopen(argv[3],"w+");
  char*s;
  char buf[20];
  char str;
  int i;
  while(fgetc(input)!=EOF)
  {
    fseek(input,-1,SEEK_CUR);
    fgets(buf,20,input);
    int x=strlen(buf);
    char *star =strchr(buf,':');
    char temp[50];
    int flag=0;
      while(fgets(temp,50,flow)!=NULL)
      {
        //CHECK FOR EXACT MATCH

        char temp2[50];
        printf("%s",temp);
        strcpy(temp2,temp);
        printf("temp 2 %s", temp2);
        char *startemp =strchr(temp2,'*');
            if(strncmp(buf,temp,x-1)==0)
              {
                temp[x-1]= '-';
                buf[x-1]='-';
                fprintf(out, "%s",buf);
                fprintf(out, "%c",'>');
                fprintf(out, "%s",temp+x);
                flag=1;
                break;
              }

              else if (startemp!=NULL && temp[0]!='*')
              {
                printf("startemp %s",startemp);
                //printf("temp %s",temp2);
                int len=strlen(startemp);
                int len_temp=strlen(temp);
                if(strncmp(buf,temp,len_temp-len)==0)
                {
                  fprintf(out, "%s",buf);
                  fprintf(out, "%s","->");
                  fprintf(out, "%s",startemp+2);
                  flag =1;
                }
                break;
              }

        //CHECK IF *:PORT NO MATCHES
            else if(temp[0]=='*')
              {
              int len_star=strlen(star);
              if(strncmp(temp+1,star,len_star-1)==0){
              s=strchr(temp,',');
              buf[x-1]='-';
              fprintf(out, "%s",buf);
              fprintf(out, "%c",'>');
              fprintf(out, "%s",s+1);
              flag=1;
              break;}
            }
            //free(startemp);
        }
      //There is no match found
      if(flag!=1)
        {
          fprintf(out, "No nat match for ");
          fprintf(out, "%s",buf);
          flag=0;
        }
  //Set the pointer position to start of the file.
  fseek(flow,0,SEEK_SET);
  }
    fclose (input);
    fclose (flow);
    fclose (out);

}
