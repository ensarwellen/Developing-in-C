#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"

 
 Dllist dl, dtmp;  /* Sayılar için oluşturulan liste */
 Dllist sl, stmp;  /* Karakterler için oluşturulan liste */

 int i;
 int boyut[2];
 
 //DLL içindekileri yazdırma
void yazdir() {
  dtmp = dl->flink;
  stmp = sl->flink;
  int sayac = 0;
  dll_traverse(dtmp, dl){
     
     for(i=0; i<dtmp->val.i; i++){
     if(sayac<boyut[1]){
     if(strcmp(stmp->val.s, "s")){
       printf("%s", stmp->val.s);
       sayac++;
     }else {
      printf(" ");
      sayac++;
     }
     }else{
      printf("Boyut bilgisi bu karakterden sonrasına izin vermiyor.");  //Boyut bilgisinin 2.elemanına göre yazdırma yapmamızı sağlıyor. Örn: "boyut 10 5" ise 5 eleman yazar ve 6.sı varsa hata verir.
      exit(1);
     }
   }   
   stmp = stmp->flink;
 }
 printf("\n");
 
}

int main()
{
 
  int b, d;
  IS is;
  char *ptr;
  char a; 
  int j=0;
  

  /* DLL oluşturma ve stdinputtan dosya girişi */

  dl = new_dllist();
  sl = new_dllist();
  is = new_inputstruct(NULL);

  /* DLL içine eleman atma */
  
  while (get_line(is) >= 0) {    
    if(is->line < 2){
     if(strncmp(is->text1, "boyut bilgisi:", 14)){
       fprintf(stderr, "hatalı input dosyası: 1.satırda boyut bilgisi verilmemiş\n");
       exit(1);
     } else{
     	for (i = 0; i < is->NF; i++) {
         if (sscanf(is->fields[i], "%d", &b) == 1) {        
         boyut[j] = b;        
         j++;               
      }             
    }
     }
     }
    if(is->line == 2){
     if(strncmp(is->text1, "karakterler:", 12)){
       fprintf(stderr, "hatalı input dosyası: 2.satırda karakterler verilmemiş\n");
       exit(1);
     }   
    }    
     else if (is->line > 2 && is->line < boyut[0]+4) {           //burası boyut bilgisinin ilk hanesi kadar satır yazdırma yapmasını sağlıyor. örn: "boyut 10 20" ise inputtan 10 satır yazar.
    for (i = 0; i < is->NF; i++) {				//boyut[0]+4 olmasının nedeni ilk 3 satırın boyut bilgisi, karakterler ve 1 boş satırdan oluşması
      if (sscanf(is->fields[i], "%d", &d) == 1) {
        dll_append(dl, new_jval_i(d));
      } else {
        dll_append(sl, new_jval_s(strdup(is->fields[i])));
      }
 }
 yazdir();                         //Her satırdan sonra yazdır komutuna gidiyoruz. Yazdır fonksiyonundan geri dönünce node'ları boşaltıp siliyoruz.
 while(!dll_empty(sl)){
 free(sl->flink->val.s);           //SL node'ların içini boşaltma
 dll_delete_node(sl->flink);       //SL node'ları silme 
 }
 while(!dll_empty(dl))
 dll_delete_node(dl->flink);       //DL node'ları silme
 }
 }
 
          

 
  jettison_inputstruct(is);        //Programdan güvenli çıkış

  return 0;
}
