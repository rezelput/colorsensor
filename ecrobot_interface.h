#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "implementation.oil"

CPU ATMEL_AT91SAM7S256
{
  OS LEJOS_OSEK
  {
    STATUS = EXTENDED;
    STARTUPHOOK = FALSE;
    ERRORHOOK = FALSE;
    SHUTDOWNHOOK = FALSE;
    PRETASKHOOK = FALSE;
    POSTTASKHOOK = FALSE;
    USEGETSERVICEID = FALSE;
    USEPARAMETERACCESS = FALSE;
    USERESSCHEDULER = FALSE;
  };

  
  APPMODE appmode1{}; 


  TASK Motion    //определение свойств задачи Motion
  {
    AUTOSTART = FALSE;  //не запускаться самой при запуске //программы
PRIORITY = 2;  //приоритет. чем больше число, тем //выше приоритет
ACTIVATION = 1;  //максимально число одновременно //работающих задач Motion
SCHEDULE = FULL;    //возможность вытеснять эту задачу //задачами более высокого приоритета
    STACKSIZE = 512;    //размер стека
  };
  
  
  ALARM cyclic_alarm1  //определение будильника (генератора //событий запуска задачи)
  {
    COUNTER = SysTimerCnt;  //счетчик SysTimerCnt
    ACTION = ACTIVATETASK  //при запуске будильника вызвать //задачу Motion
    {
        TASK = Motion;
    };
    AUTOSTART = TRUE  //автоазапуск будильника
      {
        ALARMTIME = 1;  //время запуска будильника впервый //раз
        CYCLETIME = 50;    //период последующих запусков 
        APPMODE = appmode1;
      };
    };


 
  
  COUNTER SysTimerCnt  //определение счетчика
  {
    MINCYCLE = 1;  //минимально возможное число тиков //счетчика для использования //будильником
    MAXALLOWEDVALUE = 10000;  //максимально
//возможноезначение счетчика
    TICKSPERBASE = 1;  //размер тика (в миллисекундах) 
  };
};

void ecrobot_device_initialize(void)
{
    /* Инициализировать используемые устройства */
    ecrobot_set_light_sensor_active(NXT_PORT_S1);
    ecrobot_set_light_sensor_active(NXT_PORT_S3);
    ecrobot_init_sonar_sensor(NXT_PORT_S2); 
    ecrobot_set_motor_speed(NXT_PORT_B, 0);
    ecrobot_set_motor_speed(NXT_PORT_C, 0);
    ecrobot_init_bt_connection();
}
void ecrobot_device_terminate(void)
{
    /* Завершить работу датчиков, остановить моторы */
    ecrobot_set_light_sensor_inactive(NXT_PORT_S1);
    ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
    ecrobot_set_motor_speed(NXT_PORT_B, 0);
    ecrobot_set_motor_speed(NXT_PORT_C, 0);
    ecrobot_term_sonar_sensor(NXT_PORT_S2);
    ecrobot_term_bt_connection();
}