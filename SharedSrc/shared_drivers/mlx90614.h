/**
 * @file mlx90614.h
 * @author Łukasz Kilaszewski (luktor99)
 * @date 6-July-2017
 * @brief This file contains the headers of MLX90614 sensor driver
 */

#ifndef SHARED_DRIVERS_MLX90614_H_
#define SHARED_DRIVERS_MLX90614_H_

void MLX90614_Init(void);
uint8_t MLX90614_readTemp(void);


#endif /* SHARED_DRIVERS_MLX90614_H_ */
