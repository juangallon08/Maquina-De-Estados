

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

   
//0_*
    while (1)
    {
        // Add your application code
        updata_MEF (); 
         __delay_ms(200);
    }
}
/**
 End of File
*/