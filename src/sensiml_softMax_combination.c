/*
 * sensiml_softMax_combination.c
 *
 *  Created on: Aug 21, 2022
 *      Author: mbruner
 */

#include <stdint.h>
#include <stdio.h>
#include "circular_buff.h"
#include "sensiml_softMax_combination.h"

#include "sensiml_recognition_dual_IMU_audio_combine.h"

static circular_buffer_t audio_softMax_buffer;


tree_ensemble_model_results_t imu_model_softMax;

float imu_model_weights[] =
  { 0.5, 0.5, 0.5, 0.5, 0.5 };
float audio_model_weights[] =
  { 0.5, 0.5, 0.5, 0.5, 0.5 };

void init_softMax_combinations ()
{
  cb_init ((circular_buffer_t*) &audio_softMax_buffer, 100, sizeof(tf_micro_model_results_t));
}

void set_imu_softMax (tree_ensemble_model_results_t modelResults)
{
  imu_model_softMax = modelResults;
}

void set_audio_softMax (tf_micro_model_results_t * modelResults)
{

  push ((circular_buffer_t*) &audio_softMax_buffer, (void*) modelResults);
  printf ("Audio softMax size = %i\n\r", audio_softMax_buffer.count);
}

void combine_softMax (uint8_t size)
{
  tf_micro_model_results_t audio_softMax;
  uint8_t best_index = 0;
  float max_result;
  float running_total[NUMBER_OF_CLASSES];
  float combined_results[NUMBER_OF_CLASSES];

  if ((get_imu_classification () > -1) && (audio_softMax_buffer.count >= (size)))
    {
      printf ("Integration of IMU and Audio softMax\n\r");

      // first lets sum up the audio data;
      // clear previous data
      for (int i = 0; i < NUMBER_OF_CLASSES; i++)
        {
          running_total[i] = 0;
        }

      for (int i = 0; i < size; i++)
        {
          pop ((circular_buffer_t*) &audio_softMax_buffer, (void*) &audio_softMax);

          // add the softmax values to the running total
          for (int j = 0; j < NUMBER_OF_CLASSES; j++)
            {
              running_total[j] += audio_softMax.output_tensor[j];

            }
        }
      // divide the results by the size
      for (int i = 0; i < NUMBER_OF_CLASSES; i++)
        {
          running_total[i] /= size;
        }

      // next perform a weighted sum with the IMU and Audio
      for (int i = 0; i < NUMBER_OF_CLASSES; i++)
        {
          combined_results[i] = imu_model_weights[i] * imu_model_softMax.class_percentages[i]
              + audio_model_weights[i] * running_total[i];
        }

      // Now lets find the best classification
      max_result = combined_results[0];
      best_index = 0;
      for (int i = 1; i < NUMBER_OF_CLASSES; i++)
        {
          if (combined_results[i] > max_result)
            {
              max_result = combined_results[i];
              best_index = i;
            }
        }
      printf ("Best Index = %i\n\r", best_index);
      for (int i = 0; i < NUMBER_OF_CLASSES; i++)
        {
          printf ("Index %i, value %f \n\r", i, combined_results[i]);
        }
      set_imu_classification(-1);

    }else{
        if ((get_imu_classification () < 0) && (audio_softMax_buffer.count >= (size))){
            // pop out size elements since we won't use them
            printf("No IMU so resyncing audio data");
            for(int i = 0; i < size; i++){
                pop ((circular_buffer_t*) &audio_softMax_buffer, (void*) &audio_softMax);
            }


        }
    }
}

