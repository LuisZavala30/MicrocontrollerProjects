/*
 * Contador.c
 *
 * Created: 23/04/2021 12:10:28 p. m.
 * Author: luis_
 */
#asm
    .equ __lcd_port=0x02
    .equ __lcd_EN=1
    .equ __lcd_RS=0
    .equ __lcd_D4=2
    .equ __lcd_D5=3
    .equ __lcd_D6=4
    .equ __lcd_D7=5
#endasm


#include <mega2560.h>
#include <display.h>
#include <stdio.h>


unsigned int Cuenta = 992;
unsigned char Cadena[3];

void main(void)
{
    PORTC = 0x07; // PB0, PB1, PB2 pull up  
    SetupLCD(); 
    MoveCursor(0,0);
    StringLCD(" People Counter "); 
    
    sprintf(Cadena,"%03i",Cuenta);
    MoveCursor(7,1);   
    StringLCDVar(Cadena);  
      
    while (1)
    {   
        if(PINC.0 == 0){   //Incrementar
            if(Cuenta < 999){
                Cuenta++;  
                sprintf(Cadena,"%03i",Cuenta);
                MoveCursor(7,1);   
                StringLCDVar(Cadena); 
                delay_ms(30); //Rebote al presionar
                while(PINC.0==0); //espera a soltar boton
                delay_ms(10); //rebote al soltar  
            }                          
        }
        if(PINC.1 == 0){     //Disminuir
            if(Cuenta > 0){
                Cuenta--; 
                sprintf(Cadena,"%03i",Cuenta);
                MoveCursor(7,1);   
                StringLCDVar(Cadena);  
                delay_ms(30); //Rebote al presionar
                while(PINC.1==0); //espera a soltar boton
                delay_ms(10); //rebote al soltar 
            }
        } 
        if(PINC.2 == 0){     //Clear
            Cuenta = 0;  
            sprintf(Cadena,"%03i",Cuenta);
            MoveCursor(7,1);   
            StringLCDVar(Cadena); 
            delay_ms(30); //Rebote al presionar
            while(PINC.2==0); //espera a soltar boton
            delay_ms(10); //rebote al soltar
        }
    }
}
