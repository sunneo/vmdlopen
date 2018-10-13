#include <stdio.h>
void* vmdlopen(const char* fname, int dummy);
void* vmdlsym(void* handle, const char* symbol);
void vmdlclose(void* p);

int main(){
   void* handle = vmdlopen("./hello.ll",0);
   fprintf(stderr,"handle=%p\n",handle);
   if(handle){
      void(*hello)()=0;
      int (*one)()=0;
      int (*pmain)();
      hello = (void(*)())vmdlsym(handle,"hello");
      fprintf(stderr,"hello=%p\n",hello);

      one = (int(*)())vmdlsym(handle,"one");
      fprintf(stderr,"one=%p\n",one);

      pmain = (int(*)())vmdlsym(handle,"main");
      fprintf(stderr,"main=%p\n",pmain);

      if(pmain){
         fprintf(stderr,"main___\n");
         pmain();
         fprintf(stderr,"end of main___\n");

      }
     
      if(hello){
         hello();
      }
      if(one){
         one();
      }
//      vmdlclose(handle);
   }
   
}
