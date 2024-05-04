#include <stdio.h>
#include <locale.h>

struct list
{
   int elem;
   list *next;
   list(int _elem = 0, list *_next = NULL) : elem(_elem), next(_next) {}
} *l = new list;

int input(list *t)
{
   bool IsOk = true;
   FILE *f = NULL;
   
   if ((f = fopen("in.txt", "r")) != NULL)
   {
      fseek(f, 0, SEEK_END);
      if (!ftell(f))
      {
         printf("Файл in.txt пустой.");
         IsOk = false;
      }
      else
      {
         fseek(f, 0, SEEK_SET);
         for (list *p = t->next = new list; !feof(f) && IsOk; p = p->next = new list)
             IsOk = fscanf(f, "%d", &p->elem);
             
         if (!IsOk)
            printf("Файл содержит недопустимые данные.");
      }
   }
   else
   {
      printf("Файл in.txt не найден.");
      IsOk = false;
   }
   return IsOk;
}

void reverse(list *h, FILE *f)
{
   list *p = h->next;
   if (p->next)
   {
      reverse(p, f);
      fprintf(f, "%d ", p->elem);
   }
}

int main()
{
   setlocale(0, "");

   if (input(l))
   {
      FILE *f = NULL;
      f = fopen("out.txt", "w");

      reverse(l, f);
      fclose(f);
   }
   return 0;
}