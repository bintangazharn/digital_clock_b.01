#include <mega328p.h>
#include <delay.h>

int num[10] =   {0b00000000, //BCD 0
                 0b10000000, //BCD 1
                 0b01000000, //BCD 2
                 0b11000000, //BCD 3
                 0b00100000, //BCD 4
                 0b10100000, //BCD 5
                 0b01100000, //BCD 6
                 0b11100000, //BCD 7
                 0b00010000, //BCD 8
                 0b10010000, //BCD 9
                };  
                
int jamH=0, jamL=0, menitH=0, menitL=0, detik, ms = 0, ampm, hitungJ, count = 0;

void main(void) {
    DDRD = 0b11111100;
    PORTD = 0b00000011;

    while (1) {  
        if(ampm == 1)PORTD |= 0x04;
        else PORTD &= 0xFB;
            
        if(PIND.0 == 0){ // fungsi tombol kurang   
            while(PIND.0 == 0){};
            if(--menitL < 0){
                menitL = 9;
                if(--menitH < 0){
                    menitH = 5;
                    if(--jamL < 0){
                        jamL = 9;
                        if(--jamH < 0){
                            jamH = 5;
                        }
                    }
                }    
            }
        } 
        
        if(PIND.1 == 0){ // fungsi tombol tambah       
            while(PIND.1 == 0){};
            if(++menitL < 0){
                menitL = 9;
                if(++menitH < 0){
                    menitH = 5;
                    if(++jamL < 0){
                        jamL = 9;
                        if(++jamH < 0){
                            jamH = 5;
                        }
                    }
                }    
            }
        }    
            
        if(++ms>999){
            ms=0;
            if(++detik>1){
                detik = 0; 
                if(++menitL>9){
                    menitL = 0;
                    if(++menitH>5){
                        menitH = 0;
                        if(++jamL>9){
                            jamL = 0;
                            if(jamH == 1 && jamL > 2){
                                if(ampm == 1) {
                                    ampm = 0;
                                    jamH = 0;
                                    jamL = 0;
                                    }
                                else {
                                    ampm = 1; 
                                    jamH = 0;
                                    jamL = 0;
                                }
                                jamL = 0;
                                jamH = 0;
                            }   
                            if(++jamH>1){
                                jamH = 0;
//                                if(jamH == 1 && jamL == 2 && menitH == 5 && menitH > 9){  
//                                    if(ampm == 1) {
//                                        ampm = 0;
//                                        jamH = 0;
//                                        jamL = 0;
//                                    }
//                                    else {
//                                        ampm = 1; 
//                                        jamH = 0;
//                                        jamL = 0;
//                                    }
//                                }
//                                else {
//                                    jamH = 0;
//                                }
                            }
                        } 
                    }
                }
            }            
        }                
        
        PORTD.3 = 1;
        delay_us(500);                
        
        if(++count>3)count = 0;
        switch(count){
            case 0: PORTD &= 0x0F; PORTD |= num[jamH]; break;
            case 1: PORTD &= 0x0F; PORTD |= num[jamL]; break;
            case 2: PORTD &= 0x0F; PORTD |= num[menitH]; break;
            case 3: PORTD &= 0x0F; PORTD |= num[menitL]; break;
        }            
        
        
        PORTD.3 = 0;
        delay_us(500);           
    }
}
