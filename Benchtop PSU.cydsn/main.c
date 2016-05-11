/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <ascii.h>
#include <stdio.h>

#define HIGH    (1u)
#define LOW     (0u)

// Function prototypes
void LCD_setup(void); // sets the required operating modes for the LCD
void LCD_send_command(uint8); // send one command byte
void LCD_send_data(uint8); // send one data byte
void LCD_write_character(char);
void LCD_write_string(char*);
void LCD_write_int(int);
void LCD_write_init(void); // initializes the display with text
void LCD_refresh_data();
void LCD_clear(void); // clears the rogue bits on the LCD
void LCD_set_xy(uint8 column, uint8 row); // Sets the exact XY of the display
void LCD_set_char_xy(uint8 column, uint8 row); // 14x6 characters on the display
void update_PWM(); // updates the PWM values as well as the values on the display

// Flags
uint8 flag_vcb = 0;

// PWM values
int16 pwm_voltage = 442; // 5V start value
int16 pwm_current = 480; // 500 mA current limit. Anything above 900mA behaves weird

// Variables
int16 brightness = 90; // percent
uint16 counter_decoder = 0x8000;
uint8 decoder_speed = 1;
uint16 sense_current = 0;
uint16 sense_voltage = 0;

// Constants
const float32 gain_v = 0.01208; // Interpolated voltage slope
const float32 gain_i = 1.097; // Interpolated current gain
const float32 gain_diff_i = 1.33333;
const float32 res_sense = 6.7;

// Interrupt prototypes
CY_ISR_PROTO(ADC_Done); // adc end of conversion
CY_ISR_PROTO(BTN_VCB); // v/c/b button
CY_ISR_PROTO(Quad_ISR);
CY_ISR_PROTO(Speed_ISR);

int main()
{
    
    // Attach interrupts
    isr_adc_StartEx(ADC_Done);
    isr_vcb_StartEx(BTN_VCB);
    isr_quad_StartEx(Quad_ISR);
    isr_speed_StartEx(Speed_ISR);
    
    // Setup and enable SPI
    SPIM_1_Start();
    // Setup and enable LCD & write data on LCD
    LCD_setup();
    // PWM's
    PWM_Brightness_Start(); // controls LCD brightness
    PWM_Brightness_WriteCompare(brightness*50/1024);
    
    PWM_V_Start();
    PWM_V_WriteCompare(pwm_voltage);
    
    PWM_C_Start();
    PWM_C_WriteCompare(pwm_current);
    
    ADC_Start();
    ADC_StartConvert(); 
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    
    QuadDec_Start();
    QuadDec_TriggerCommand(QuadDec_MASK, QuadDec_CMD_RELOAD);
    
    Count7_Start(); // ADC conversions are automatically started 10 times per second

    CyGlobalIntEnable; /* Enable global interrupts. */
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        
    }
}

void LCD_setup(){
    CyDelayCycles(60);
    ResetLCD_Write(HIGH);
    CyDelayCycles(60);
    ResetLCD_Write(LOW);
    CyDelayCycles(60);
    ResetLCD_Write(HIGH);
    
    LCD_send_command(0x21); // select extended instruction set
    LCD_send_command(0xB8); // set Vop = 6.42V 
    LCD_send_command(0x40); // TC = 0
    LCD_send_command(0x14); // Bias system 4
    LCD_send_command(0x20); // select normal instruction set
    
    LCD_send_command(0x0C); // Initialize normal display mode
    
    LCD_clear();            // Clear LCD
    
    LCD_write_init();       // Write the UI on the LCD
}

void LCD_write_int(int nr){
    char str_nr[5];
    sprintf(str_nr, "%05d", nr);
    LCD_write_string(str_nr);
}

void LCD_write_init(){
    
    LCD_write_string("Voltage:");
    LCD_set_char_xy(0, 1);
    LCD_write_string("Current:");
    LCD_set_char_xy(0, 2);
    LCD_write_string("C limit:");
    LCD_set_char_xy(0, 3);
    LCD_write_string("BRT:");
    LCD_set_char_xy(0, 5);
    LCD_write_string("Sel: ");
    LCD_write_string("Voltage  ");
    
    LCD_refresh_data();
}

void LCD_refresh_data(){
    /*
        Refreshes the Current Limit, Brightness and Status on the display
    */
    
    int16 str_current_limit = pwm_current * 1.059 - 7.456;
    if(sense_current > str_current_limit)
        str_current_limit = sense_current;
    
    char str_current[6];
    //sprintf(str_current, "%4dmA", current);
    sprintf(str_current, "%4dmA", str_current_limit);
    
    char str_brightness[6];
    sprintf(str_brightness, "%3d", brightness); 
    
    // TO-DO: Verify status of the PSU (by means of a button, watch out for voltages
    // higher than 2.048V and update the status here.
    
    LCD_set_char_xy(8, 2);
    LCD_write_string(str_current);
    
    LCD_set_char_xy(4, 3);
    LCD_write_string(str_brightness);
    
    
    LCD_set_char_xy(5, 5);
    if(flag_vcb == 0){ // voltage
        LCD_write_string("Voltage  ");
    }else if(flag_vcb == 1){
        LCD_write_string("Current  ");
    }else if(flag_vcb == 2){
        LCD_write_string("Bright   ");
    }
}

void LCD_send_command(uint8 command){
    DC_Write(LOW);
    SPIM_1_WriteTxData(command);
    // Wait for transmission to be done. If I do not wait, the next byte will be written
    // into the TX buffer and be sent by the SPI module automatically when he will be
    // done with the current byte.
    while (0u == (SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE)){}
}

void LCD_send_data(uint8 data){
    DC_Write(HIGH);
    SPIM_1_WriteTxData(data);
    while (0u == (SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE)){}
}

// Writes a character defined by a font
void LCD_write_character(char character){
    DC_Write(HIGH);
    // I skipped the first 32 ascii characters so I need
    // to subtract 32
    SPIM_1_PutArray(alphabet[character - 32], 6);
    // Wait until transmission is done!
    while (0u == (SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE)){}
}

void LCD_write_string(char* my_string){
    uint8 i = 0;
    while (i < strlen(my_string)){
        LCD_write_character(my_string[i]);
        i++;
    }
}

void LCD_clear(void){
    // Clear LCD
    uint8 i = 0;
    while (i < 84){
        LCD_write_character(0x20); // 0x20 is the clear char
        i++;
    }
    
    LCD_set_xy(0, 0);
}

void LCD_set_xy(uint8 column, uint8 row){
    if(column > 83 || row > 5){
        return;    
    }
    uint8 x_command = 0x80 + column;
    uint8 y_command = 0x40 + row;
    
    LCD_send_command(x_command);
    LCD_send_command(y_command);
}

void LCD_set_char_xy(uint8 x, uint8 y){
    // For a character width of 6, we have 14x6 = 84 characters
    // Split in 6 rows and 14 columns
    
    if(x > 13 || y > 5){
        return;   
    }
    uint8 x_coord = x*6;
    LCD_set_xy(x_coord, y);
}


void update_PWM(){
    PWM_V_WriteCompare(pwm_voltage);    
    PWM_C_WriteCompare(pwm_current);
    PWM_Brightness_WriteCompare(1023 - brightness*1023/100);
}


/* Interrupt Service Routines */
CY_ISR(ADC_Done){
    char str_voltage[6];
    char str_current[6];
    
    // Results got from calibration
    sense_current = ADC_GetResult16(1) * 1.091 - 6.94; //mA
    sense_voltage = ADC_GetResult16(0) * 12.105 + 18.26; //mV
    
    sprintf(str_voltage, "%2d.%02dV", sense_voltage/1000, (sense_voltage/10)%100);
    sprintf(str_current, "%4dmA", sense_current); 
    
    LCD_set_char_xy(8, 0);
    LCD_write_string(str_voltage);
    
    LCD_set_char_xy(8, 1);
    LCD_write_string(str_current);
    
    // ADC conversion is started again in hardware by Counter7
    isr_adc_ClearPending();
   
}

/*
    VCB_1   VCB_0   Setting
    0       0       voltage
    0       1       current
    1       X       brightness

    => Voltage = 0; Current = 1; Brightness = 2 or 3
*/
CY_ISR(BTN_VCB){
    flag_vcb = (flag_vcb + 1) % 3;
    
    LCD_refresh_data();
    
    isr_vcb_ClearPending();
}
uint16 steps = 0;
CY_ISR(Quad_ISR){
    // Se executa de mii de ori pe secunda
    int16 counter_decoder_new = QuadDec_ReadCounter();
    int8 direction = counter_decoder_new - counter_decoder;

    if(direction > 0){
        direction = 1;
        steps++;
    }
    else if (direction < 0){
        direction = -1;
        steps++;
    }
    int8 change = direction * decoder_speed;
    
    switch (flag_vcb){
        case 0:
            pwm_voltage += change;
            break;
        case 1:
            pwm_current += change;
            break;
        default:
            brightness += change;        
    }
    // TO-DO: Speed based on a counter. Direction practic nici nu ma intereseaza,
    // el trebuie sa fie ori 1 ori -1. Ca Decoderul detecteaza corect miscare, insa
    // valoarea lui direction depinde de zgomot. 
    // Prin urmare direction > 0 => direction = 1
    //             direction < 0 => direction = -1
    // Iar viteza o voi calcula cu counterul.
    
    // Check limits
    if(pwm_voltage > 1023)
        pwm_voltage = 1023;
    if(pwm_current > 1023)
        pwm_current = 1023;
    if(brightness > 100)
        brightness = 100;
    
    if(pwm_voltage < 0)
        pwm_voltage = 0;
    if(pwm_current < 0)
        pwm_current = 0;
    if(brightness < 0)
        brightness = 0;
    
    update_PWM();
    
    LCD_refresh_data();
    
    counter_decoder = counter_decoder_new;
    
    isr_quad_ClearPending();
    
}

int16 prev_steps = 0;
CY_ISR(Speed_ISR){
    uint16 difference = steps - prev_steps;
    if(difference >=2 ){
        if(difference >=3)
            decoder_speed = difference*15;
        else
            decoder_speed = difference*5;   
    }
    else
        decoder_speed = 1;
    
    prev_steps = steps;
    
    isr_speed_ClearPending();
}
/* [] END OF FILE */
