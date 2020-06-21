#include <systemlib/param/param.h>

/**                                              
 * Attitude Control ADRC Param TD_R                         
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 1                                        
 * @max 1000                                      
 * @decimal 0                                    
 * @increment 1                                  
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_TD_R, 100.0); 
/**                                              
 * Attitude Control ADRC Param TD_H                         
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 1                                        
 * @max 100                                    
 * @decimal 1.0                                 
 * @increment 1.0                                
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_TD_H, 1.0);
/**                                              
 * Attitude Control ADRC Param NLSEF_R 
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 1                                        
 * @max 1000                                    
 * @decimal 0.1                                 
 * @increment 1.0                                
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_NLSEF_R, 220.0);
/**                                              
 * Attitude Control ADRC Param NLSEF_H                        
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 1                                        
 * @max 100                                    
 * @decimal 1.0                                 
 * @increment 1.0                                
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_NLSEF_H, 25.0);
/**                                              
 * Attitude Control ADRC Param NLSEF_C                        
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 1                                        
 * @max 100                                    
 * @decimal 1.0                                 
 * @increment 1.0                                
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_NLSEF_C, 6.0);
/**                                              
 * Attitude Control ADRC Param ESO_B01                        
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 1                                        
 * @max 1000                                    
 * @decimal 1.0                                 
 * @increment 1.0                                
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_ESO_B01, 250.0);
/**                                              
 * Attitude Control ADRC Param ESO_B02                        
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 10                                        
 * @max 10000                                    
 * @decimal 1.0                                 
 * @increment 1.0                                
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_ESO_B02, 6000.0);
/**                                              
 * Attitude Control ADRC Param ESO_B03                        
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 100                                        
 * @max 500000                                    
 * @decimal 1.0                                 
 * @increment 1.0                                
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_ESO_B03, 1000.0);
/**                                              
 * Attitude Control ADRC Param ESO_B0                        
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 1                                        
 * @max 500                                   
 * @decimal 0.1                                 
 * @increment 0.1                                
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_ESO_B0, 47.4);
/**                                              
 * Attitude Control ADRC Param ESO_H                        
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 1                                        
 * @max 100                                    
 * @decimal 1.0                                 
 * @increment 1.0                                
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_ESO_H, 1.0);
/**                                              
 * Attitude Control ADRC Param ESO_D                        
 *                                               
 * <longer description, can be multi-line>       
 *                                               
 * @unit number                                  
 * @min 0.004                                        
 * @max 0.2                                    
 * @decimal 0.001                                 
 * @increment 0.001                                
 * @reboot_required false                        
 * @group simulink                               
 */                                              
PARAM_DEFINE_FLOAT(SL_ESO_D, 0.01);
