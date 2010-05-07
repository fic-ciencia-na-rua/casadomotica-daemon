#include<stdio.h>
union carbit
{
   char c;
   struct campo
   {
      unsigned int b1:1;
      unsigned int b2:1;
      unsigned int b3:1;
      unsigned int b4:1;
      unsigned int b5:1;
      unsigned int b6:1;
      unsigned int b7:1;
      unsigned int b8:1;
   }bit;
}dato;

