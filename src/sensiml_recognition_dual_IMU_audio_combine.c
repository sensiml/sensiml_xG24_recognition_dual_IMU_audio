/*
 * sensiml_recognition_dual_IMU_audio_combine.c
 *
 *  Created on: Aug 18, 2022
 *      Author: mbruner
 */

#include <stdint.h>
#include <stdio.h>
#include "circular_buff.h"
#include "sensiml_recognition_dual_IMU_audio_combine.h"

// storage for IMU and audio classifications.
// We will probably need more data, but for now we will
// Just stick with the classifications

#define MIC_SAMPLE_BUFFER_SIZE  112
#define NUMBER_OF_CLASSES 5
static int8_t imu_classification;
static circular_buffer_t audio_classification_buffer;

void init_classifications ()
{
  cb_init ((circular_buffer_t*) &audio_classification_buffer, 100, 1);
}

void set_imu_classification (int8_t classification)
{
  imu_classification = classification;
}

void set_audio_classification (int8_t classification)
{

  push ((circular_buffer_t*) &audio_classification_buffer, (void*) &classification);
  printf ("Audio buffer size = %i\n\r", audio_classification_buffer.count);
}

int8_t get_imu_classification ()
{
  return imu_classification;
}

int8_t get_audio_classification ()
{
  //return audio_classification;
  return 0;
}

void combine_classifications (uint8_t size)
{

  uint8_t audio_classifications[5];
  uint8_t audio_classification;
  uint8_t best_index = 0;
  uint8_t i;

  if ((imu_classification > -1) && (audio_classification_buffer.count >= (size)))
    {
      printf ("Integration of IMU and Audio data\n\r");
      printf ("IMU classification = %i\n\r", imu_classification);

      // first clear out the voting
      for (i = 0; i < NUMBER_OF_CLASSES; i++)
        {
          audio_classifications[i] = 0;
        }
      // now the voting
      for (i = 0; i < size; i++)
        {
          pop ((circular_buffer_t*) &audio_classification_buffer, (void*) &audio_classification);
          audio_classifications[audio_classification]++;
        }
      for (i = 0; i < NUMBER_OF_CLASSES; i++)
        {
          printf ("Vote count for %i = %i\n\r", i, audio_classifications[i]);
        }

      // Now to find the best one
      if (audio_classifications[1] > audio_classifications[best_index])
        {
          best_index = 1;
        }
      if (audio_classifications[2] > audio_classifications[best_index])
        {
          best_index = 2;
        }
      if (audio_classifications[3] > audio_classifications[best_index])
        {
          best_index = 3;
        }
      if (audio_classifications[4] > audio_classifications[best_index])
        {
          best_index = 4;
        }

      printf ("Majority vote = %i\n\r", best_index);
    }else {
        if ((get_imu_classification () < 0) && (audio_classification_buffer.count >= size)){
            // pop out size elements since we won't use them
            printf("No IMU so resyncing audio data");
            for(int i = 0; i < size; i++){
                pop ((circular_buffer_t*) &audio_classification_buffer, (void*) &audio_classification);
            }

        }

    }
}

