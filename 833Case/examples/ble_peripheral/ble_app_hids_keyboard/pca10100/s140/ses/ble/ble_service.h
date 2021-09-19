 
#ifndef BLE_SERVICE_H
#define BLE_SERVICE_H
#include <stdbool.h>
#include <stdint.h>

void log_init(void);

  void timers_init(void);

 void power_management_init(void);

 void  ble_stack_init(void);
 void  gap_params_init(void);

 void gatt_init(void);
   void advertising_init(void);
   void services_init(void);
   void  conn_params_init(void);
   void buffer_init(void);
   void peer_manager_init(void);
   void timers_start(void);

   void advertising_start(bool erase_bonds);

  void keys_send(uint8_t key_pattern_len, uint8_t * p_key_pattern);/**@brief 清空所有绑定数据.
 */
void delete_bonds(void);

void switch_device_select(uint8_t id);
#endif