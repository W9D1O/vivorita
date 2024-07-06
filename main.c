#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define pixel 40
#define ancho 10
#define alto 8
#define noentiendoX pixel*ancho * 2
#define noentiendoY pixel*alto * 2
typedef struct segm {
  Rectangle segmentos;
  struct segm* sig;
}segm;
//Coloca el cuerpo principal de la serpiente en medio del tablero
void init_s( Rectangle sn[2])
{
  for( int i = 0; i <= 2; ++i)
  {
    sn[i].x = ancho * (pixel / 2);
    sn[i].y = (alto + i)*(pixel/2);
    sn[i].height = 20;
    sn[i].width = 20;
    
  }
}
//Imprime el cuerpo principal de la serpiente
void imp_cab( Rectangle sn[1])
{
  for( int i = 0;i <= 2; ++i){
    DrawRectangleRounded(sn[i], 0.9, 6, BLACK);
  }
}
//Obtiene la dirección donde tiene que moverse la serpiente
int dir(int *p)
{
  if(IsKeyPressed(KEY_W) && *p != KEY_S){
     *p = KEY_W; 
      }
  if(IsKeyPressed(KEY_S) && *p != KEY_W){
     *p = KEY_S; 
      }
  if(IsKeyPressed(KEY_A) && *p != KEY_D){
     *p = KEY_A; 
      }
  if(IsKeyPressed(KEY_D) && *p != KEY_A){
     *p = KEY_D; 
      }
}
void cruza_pantalla(Rectangle sn[2])
{
  int aux;
  if(sn[0].y < 0.f ){
    sn[0].y = abs((int)sn[0].y % noentiendoY) ;
    printf("Dalee\n");
  }
  if(sn[0].y > noentiendoY / 2){
    sn[0].y = sn[0].y - sn[0].y;
}
  if(sn[0].x < 0.f){
    sn[0].x =abs((int)sn[0].x % noentiendoX);
  }

  if(sn[0].x > noentiendoX / 2){
    sn[0].x = sn[0].x - sn[0].x;
}
}
//Genera el movimiento de la serpiente
void mov(Rectangle sn[2], bool *juega,int *p){
  //dir(p);
  if(*juega){
    if(*p == KEY_W){
    sn[2].y = sn[1].y;
    sn[2].x = sn[1].x;
    sn[1].y = sn[0].y;
    sn[1].x = sn[0].x;
    sn[0].y -= 20;  
    }
    if(*p == KEY_S){
    sn[2].y = sn[1].y;
    sn[2].x = sn[1].x;
    sn[1].y = sn[0].y;
    sn[1].x = sn[0].x;
    sn[0].y += 20;  
    }
    if(*p == KEY_A){
    sn[2].y = sn[1].y;
    sn[2].x = sn[1].x;
    sn[1].y = sn[0].y;
    sn[1].x = sn[0].x;
    sn[0].x -= 20;  
    }
    if(*p == KEY_D){
    sn[2].y = sn[1].y;
    sn[2].x = sn[1].x;
    sn[1].y = sn[0].y;
    sn[1].x = sn[0].x;
    sn[0].x += 20;  
    }
  }
  cruza_pantalla(sn);
}

//Crea un nuvo nodo que forma parte de los segmentos del cuerpo de la serpiente
segm *initB(segm *body,Rectangle sn[2])
{
  segm *aux = (segm*)malloc(sizeof(segm));
  aux->segmentos.x = sn[2].x; //Estoy guardando en el nodo que se creo la posicion del ultimo elemento del cuerpo principal
  aux->segmentos.y = sn[2].y;
  aux->segmentos.height = 20;
  aux->segmentos.width = 20;
  aux->sig = body; //En tepria acá mi campo sig tiene el valor de Null que es como esa inicializado body
  return aux;
}
segm movS(segm *body,Rectangle sn[2], int contS){
  segm *aux = body;
  float auX,auxY,aux2,auxy2;
  if(aux != NULL){
    auX = aux->segmentos.x; // Acá le estoy dando la posicion que tiene el primer nodo creado
    auxY =aux->segmentos.y;
    aux->segmentos.x = sn[2].x; //Ahora actualizo la posicion del primer nodo creado a la posicion que tiene 
    aux->segmentos.y = sn[2].y; // el ultimo elemento del cuerpo principal
    aux = aux->sig;
    while(aux != NULL ){
      aux2 = aux->segmentos.x;
      auxy2 = aux->segmentos.y;
      aux->segmentos.x = auX;
      aux->segmentos.y = auxY;
      auX = aux2;
      auxY = auxy2;
      aux=aux->sig;
    }
  }
}
//Imprime los segmentos, acá aparentemente no tengo problemas
segm impB(segm *body){
  segm *aux = body;
  while(aux != NULL){
    DrawRectangleRounded(aux->segmentos,0.9,6,BLACK);
    aux = aux->sig;
  }
}
void cic_col(bool *haycomida,segm *body,int cx,int cy) //Esta es la unica manera que encontre para que los circulos que aparecen sobre el cuerpo de la serpiente desaparezcan PD: No crece cuando aparece la comida encima de cuerpo
{

  segm *aux = body;
  while(aux != NULL){
    if(aux->segmentos.x +20== (cx *20) && aux->segmentos.y +20 == (cy*20)){
      *haycomida = false;
      // printf("La condicion si se cumplio");
    }
    aux = aux->sig; 
  }
}
//Genera valores aleatoris para inicializar la posicion de la cicuta
void cicuta(int *cx,int *cy,Rectangle sn[2],segm *body,int cS,int p)
{// int cabe;
  *cx = GetRandomValue(1, ancho - 1 );
  *cy =GetRandomValue(1, alto - 1 );
  }

void col_serp(Rectangle sn[2], segm *body, bool *juega)
//Chequea si la serpiente se come a si misma.
{
 //if(sn[0].x + 20 == sn[2].x && sn[0].y +20 == sn[2].y){ 
 // *juega = false;
 //}
 segm *aux = body;
 while(aux != NULL){
   if(sn[0].x == aux->segmentos.x && sn[0].y== aux->segmentos.y){ 
    *juega = false;
    exit(1); 
   }
 aux = aux->sig;
 }
}

int main(){
  segm* body = NULL;
  bool juega= false;
  int player = 87;
  int cx,cy;
  bool haycomida = false;
  float delta = 0;
  Rectangle sn[2];
  init_s(sn);
  int contS = 3;
  InitWindow(pixel*ancho,pixel*alto,"Ya no digo nada");
  SetTargetFPS(60);
  while(!WindowShouldClose()){
    BeginDrawing();
      ClearBackground(GREEN);
      if(IsKeyPressed(KEY_SPACE)){
        juega = true;
      }
     imp_cab(sn);
      dir(&player);
      if(delta >= 0.2){
        movS(body,sn,contS);
        mov(sn,&juega,&player);
      delta = 0;
      }
      impB(body);
      if(!haycomida){
      cicuta(&cx,&cy,sn,body,contS,player);
      haycomida = true;
      cic_col(&haycomida,body, cx,cy);
      }
      //printf("%d %d\n esta es la posicion de la cicuta\n",cx, cy);
      DrawCircle((cx*20)-9, (cy*20)-9, 9.0, RED);
      if(sn[0].x +20== (cx *20) && sn[0].y+20 == (cy*20)){
        body =initB(body,sn);
        haycomida = false;
        // printf("La condicion si se cumplio");
      }
      col_serp(sn,body,&juega);
      delta += GetFrameTime();
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
