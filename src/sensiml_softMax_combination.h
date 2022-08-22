/*
 * sensiml_softMax_combination.h
 *
 *  Created on: Aug 21, 2022
 *      Author: mbruner
 */

#ifndef SENSIML_SOFTMAX_COMBINATION_H_
#define SENSIML_SOFTMAX_COMBINATION_H_
#include <stdint.h>
#include "kb.h"

#define NUMBER_OF_CLASSES 5

void init_softMax_combinations ();
void set_audio_softMax (tf_micro_model_results_t * modelResults);
void set_imu_softMax (tree_ensemble_model_results_t modelResults);
void combine_softMax (uint8_t size);
#endif /* SENSIML_SOFTMAX_COMBINATION_H_ */
