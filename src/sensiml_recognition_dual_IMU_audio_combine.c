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

#define  WINDOW_SIZE 40

#define MIC_SAMPLE_BUFFER_SIZE  112
#define NUMBER_OF_CLASSES 6
static int8_t imu_classification;
static circular_buffer_t audio_classification_buffer;

void init_classifications ()
{
  cb_init ((circular_buffer_t*) &audio_classification_buffer, WINDOW_SIZE, 1);
}

void set_imu_classification (int8_t classification)
{
  imu_classification = classification;
}

void set_audio_classification (int8_t classification)
{

  push ((circular_buffer_t*) &audio_classification_buffer, (void*) &classification);
}

int8_t get_imu_classification ()
{
  return imu_classification;
}

void combine_classifications (uint8_t size)
{

  uint8_t audio_classifications[NUMBER_OF_CLASSES];
  uint8_t audio_classification;
  uint8_t best_index = 0;
  uint8_t i;
  int best_index_count;
  int unknown_bias = 2;
  int key_io_bias = 2;

  if ((imu_classification > -1) && (audio_classification_buffer.count >= size))
    {

      // try to use the last size elements
      for (i = 0; i < (audio_classification_buffer.count - size); i++)
        {
          pop ((circular_buffer_t*) &audio_classification_buffer, (void*) &audio_classification);
        }
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
          switch (i)
            {
            case 0:
              printf ("Vote count for Unknown  = %i\n\r", audio_classifications[i]);
              break;
            case 1:
              printf ("Vote count for Unknown  = %i\n\r", audio_classifications[i]);
              break;
            case 2:
              printf ("Vote count for Key_IO   = %i\n\r", audio_classifications[i]);
              break;
            case 3:
              printf ("Vote count for Knocking = %i\n\r", audio_classifications[i]);
              break;
            case 4:
              printf ("Vote count for Locking  = %i\n\r", audio_classifications[i]);
              break;
            case 5:
              printf ("Vote count for Filtered = %i\n\r", audio_classifications[i]);
              break;
            }
        }

      best_index_count = audio_classifications[0] - unknown_bias;

      if (audio_classifications[1] > 0 && audio_classifications[1] - unknown_bias > best_index_count)
        {
          best_index = 1;
          best_index_count = audio_classifications[1] - unknown_bias;
        }
      if (audio_classifications[2] > 0 && audio_classifications[2] > best_index_count)
        {
          best_index = 2;
          best_index_count = audio_classifications[2];
        }
      if (audio_classifications[3] > 0 && audio_classifications[3] > best_index_count)
        {
          best_index = 3;
          best_index_count = audio_classifications[3];
        }

      if (audio_classifications[4] > 0 && audio_classifications[4] > best_index_count)
        {
          best_index = 4;
          best_index_count = audio_classifications[4];
        }

      if (best_index == 2 && audio_classifications[4] > 0 && audio_classifications[4] >= best_index_count - key_io_bias)
        {
          best_index = 4;
          best_index_count = audio_classifications[4];
        }

      printf ("Majority vote = %i\n\r", best_index);
      printf ("IMU Classification = %i\n\r", imu_classification);

      if (best_index_count > 0)
        {
          printf ("{\"ModelNumber\":0,\"Classification\":%d}\n\r", best_index);
        }
      // Reset IMU classification to none
      set_imu_classification (-1);
    }
  else
    {
      if ((get_imu_classification () < 0) && (audio_classification_buffer.count >= size))
        {
          // pop out size elements since we won't use them

          pop ((circular_buffer_t*) &audio_classification_buffer, (void*) &audio_classification);

        }

    }
}

