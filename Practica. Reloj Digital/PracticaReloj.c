 
  #asm
    .equ __lcd_port=0x02   //LCD en PuertoA
    .equ __lcd_EN=1
    .equ __lcd_RS=0
    .equ __lcd_D4=2
    .equ __lcd_D5=3
    .equ __lcd_D6=4
    .equ __lcd_D7=5
   #endasm                
 
#include <mega2560.h>
#include <delay.h>
#include <display.h>
#include <stdio.h>

unsigned char i=0;
signed char H=0,M=0,S=0;
char Hora[8];

void main(void)
{
    CLKPR=0x80;
    CLKPR=0x04;  
    PORTC = 0x1F;  // PC4, PC3, PC2, PC1, PC0 con Pull-UP
    SetupLCD();
    TCCR1A=0;
    TCCR1B=0x0A;    //Timer 1 en CTC con CK/8
    OCR1AH=31249/256;
    OCR1AL=31249%256;  
    while (1)      // El ciclo completo tarda 0.25seg
    {
       //Imprimir hora en el LCD 
       sprintf(Hora, "%02i:%02i:%02i",H,M,S);
       MoveCursor(4,0);
       StringLCDVar(Hora);  
       while(TIFR1.OCF1A==0);   //Espera a 0.25seg
       TIFR1.OCF1A=1;           //Borra Bandera
       i++;   
      
       if (i==4)
       {
            i=0;
            S++;
            if (S==60)
            {
                S=0;
                M++;
                if (M==60)
                {   
                    M=0;
                    H++;
                    if (H==24)
                        H=0;
                }     
                
            }
       }
       //Revisar switches  
       
       if(PINC.4 == 0){
            if(H==23) 
                H=0;
            else
                H++;
       } 
       if(PINC.3 == 0){
            if(H==0) 
                H=23;
            else
                H--;
       }
       if(PINC.2 == 0){
            if(M==59) 
                M=0;
            else
                M++;
       }  
       if(PINC.1 == 0){
            if(M==0) 
                M=59;
            else
                M--;
       }
       if(PINC.0 == 0){
            S=0;
       }   
    }
}
