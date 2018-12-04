
/*************************************************************************************************************/
/******************************Bubble sort in C language using function***************************************/
/*************************************************************************************************************/



//***************Reference: https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Bubble_sort *****************//
/****************~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~******************/



/*Bubble sort pairwise compares adjacent items and swaps them if they are not in the required order, till the list is sorted*/
/*Here we are trying to sort the string in the ascending order*/

#include<stdio.h>
#include<string.h> // Header file for usage of strings


void bubblesort(char string[]); // Required function for sorting character string

int main()

{
 /* Bubblesort algorithm should be used for sorting small strings only. So the same has been limited to 100 */
  char st[100]; 
  printf("enter Any Sting\n"); // Enter the string to be sorted
  scanf("%100[0-9a-zA-Z ]",st); //To consider spaces as well while sorting the complete string/sentence, character limit 100
  bubblesort(st); //Calling the function Bubblesort
  printf("\n");
}

void bubblesort(char st[])
{
 char temp, o[1];
 int l,i,j;
  printf("\n Print the required order of the sorted string. \n Enter 'a' if the required order is ascending. \n Enter 'd' if the required order is descending.\n");
  scanf("%s",o); //To consider spaces as well while sorting the complete string/sentence
  printf("You choose : %s",o); //To consider spaces as well while sorting the complete string/sentence

  l=strlen(st);
  for(i=1;i<l;i++)
     for(j=0;j<l-i;j++)
 
  if(o[0] == 'a' || o[0] == 'A'){
/*Swapping the values iff they are in ascending order */  
  if(st[j]>st[j+1])
 {
  temp=st[j];
  st[j]=st[j+1];
  st[j+1] =temp;
 }}else if(o[0] == 'd' || o[0]== 'D'){
/*Swapping the values iff they are in descending order */  
  if(st[j]<st[j+1])
 {
  temp=st[j];
  st[j]=st[j+1];
  st[j+1] =temp;
 }
 }else{
   printf("\n Please choose either 'a' or 'd'");
   bubblesort(st);
 }
 printf("\n sorted string  \n");
 printf("%s",st);

}
