#include <systemlib/param/param.h>

/**                                              
 * Sample Simulink Param                         
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 0                                        
 * @max 100                                      
 * @decimal 0                                    
 * @increment 1                                  
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_INT32(SL_MSG, 10); 
/**                                              
 * Sample Simulink Param                         
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 0                                        
 * @max 10000                                    
 * @decimal 0.01                                 
 * @increment 1.0                                
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_TEST, 14.7);