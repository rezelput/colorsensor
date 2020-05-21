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