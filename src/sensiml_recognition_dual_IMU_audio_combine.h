/*
 * sensiml_recognition_dual_IMU_audio_combine.h
 *
 *  Created on: Aug 18, 2022
 *      Author: mbruner
 */

#ifndef SENSIML_RECOGNITION_DUAL_IMU_AUDIO_COMBINE_H_
#define SENSIML_RECOGNITION_DUAL_IMU_AUDIO_COMBINE_H_
#include <stdint.h>




void set_imu_classification(int8_t classification);
void set_audio_classification(int8_t classification);
int8_t get_imu_classification();
int8_t get_audio_classification();
void combine_classifications(uint8_t size);
void set_audio_data(int16_t *data, int16_t sample_size);
void set_imu_data(int16_t *data);
void create_combined_buffer();
void combined_recognition();
void init_classification();

#endif /* SENSIML_RECOGNITION_DUAL_IMU_AUDIO_COMBINE_H_ */
