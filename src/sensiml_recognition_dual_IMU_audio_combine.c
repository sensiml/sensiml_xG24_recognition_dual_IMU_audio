/*
 * sensiml_recognition_dual_IMU_audio_combine.c
 *
 *  Created on: Aug 18, 2022
 *      Author: mbruner
 */

#include <stdint.h>
#include <stdio.h>
#include "sensiml_recognition_dual_IMU_audio_combine.h"

// storage for IMU and audio classifications.
// We will probably need more data, but for now we will
// Just stick with the classifications

static int8_t imu_classification;
static int8_t audio_classification;

void set_imu_classification(int8_t classification){
  imu_classification = classification;
}

void set_audio_classification(int8_t classification){
  audio_classification = classification;
}

int8_t get_imu_classification(){
  return imu_classification;
}

int8_t get_audio_classification(){
  return audio_classification;
}


void combine_classifications(){

    if((imu_classification >  -1 )&&(audio_classification > -1)){
        printf("Integration of IMU and Audio data\n\r");
    }

}
