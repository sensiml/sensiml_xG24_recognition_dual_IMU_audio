/*
 * Copyright (c) 2022, SensiML Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _KB_TYPEDEFS_H_
#define _KB_TYPEDEFS_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef float FLOAT;
typedef signed short SENSOR_DATA_T;
typedef float FVCOMP_T;
typedef unsigned short NORMTYPE;

// clang-format off

/*
Expected sensor column ordering for each model

#define CHANNEL_0_S_AUDIO_MODEL 0
#define ACCELEROMETERX_S_IMU_MODEL 0
#define ACCELEROMETERY_S_IMU_MODEL 1
#define ACCELEROMETERZ_S_IMU_MODEL 2
#define GYROSCOPEX_S_IMU_MODEL 3
#define GYROSCOPEY_S_IMU_MODEL 4
#define GYROSCOPEZ_S_IMU_MODEL 5

*/

#ifdef __cplusplus
extern "C"
{
#endif

struct compx
{
    float real;
    float imag;
};

struct compx_int16_t
{
    int16_t real;
    int16_t imag;
};

typedef struct
{
    uint16_t influence; //influence of a pattern
    uint16_t category;  //category of pattern
    uint8_t *vector;    // vector containing the features of a pattern
} pme_pattern_t;

typedef struct
{
    uint16_t number_patterns; //influence of a pattern
    uint16_t pattern_length;  //category of pattern
} pme_model_header_t;



/** @struct tree_ensemble_model_results
 *  @brief This structure is used to get detailed model results information from decision tree ensemble classifiers
 *  @var tree_ensemble_model_results::number_of_trees 
 *  Number of trees in the ensemble model
 *  @var tree_ensemble_model_results::classification_counts 
 *  The number of models in the ensemble that made the prediction. The index corresponds to the result id
 *  @var tree_ensemble_model_results::class_percentages 
 *  Computes the percentage for each result that was associated with each class
 */
typedef struct tree_ensemble_model_results
{
    uint16_t number_of_trees; //number of trees in this model
    uint8_t *classification_counts; //number of classifications for each class
    float *class_percentages; //percentage results for this class
} tree_ensemble_model_results_t;


/** @struct tf_micro_model_results
 *  @brief This structure is used to get detailed model results information from decision tree ensemble classifiers
 *  @var tf_micro_model_results::num_outputs 
 *  Number of classes in the model
 *  @var tf_micro_model_results::output_tensor 
 *  The final output tensor of the model used as input into the final classification layer
 */
typedef struct tf_micro_model_results
{
    uint8_t num_outputs; //number of outputs
    float *output_tensor; //the output tensor results
} tf_micro_model_results_t;


/** KB Log levels. */
enum kb_log_levels
{
    KB_LOG_LEVEL_1 = 1, /*!< Default log level, classifier output */
    KB_LOG_CLASSIFIER_OUTPUT = KB_LOG_LEVEL_1,
    KB_LOG_LEVEL_2, /*!< A little verbose log level, feature output */
    KB_LOG_FEATURE_OUTPUT = KB_LOG_LEVEL_2,
    KB_LOG_LEVEL_3, /*!< Very Verbose log level, segmenter output */
    KB_LOG_SEGMENTER_OUTPUT = KB_LOG_LEVEL_3,
    KB_LOG_LEVEL_4, /*!< Very Very Verbose log level, kitchen sink included */
    KB_LOG_LEVEL_EVERYTHING = KB_LOG_LEVEL_4,
    KB_LOG_LEVEL_NUM = KB_LOG_LEVEL_4
};

#ifdef __cplusplus
}
#endif
// clang-format on

#endif //_KB_TYPEDEFS_H_
