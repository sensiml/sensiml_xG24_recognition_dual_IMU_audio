//SensiML Includes
#include "kb.h"
#include "sml_output.h"
#include "sml_recognition_run.h"

//FILL_USE_TEST_DATA

#ifdef SML_USE_TEST_DATA
#include "testdata.h"
int td_index = 0;
#endif //SML_USE_TEST_DATA
tf_micro_model_results_t modelResults;
tree_ensemble_model_results_t imu_modelResults;
int sml_recognition_run (signed short *data_batch, int batch_sz, uint8_t num_sensors, uint32_t model_id)
{
  int ret;

  int batch_index = 0;
  signed short *data;
  for (batch_index = 0; batch_index < batch_sz; batch_index++)
    {
#ifdef SML_USE_TEST_DATA
	ret = kb_run_model((SENSOR_DATA_T*)&testdata[td_index++], TD_NUMCOLS, 0);
	if(td_index >= TD_NUMROWS)
	{
		td_index = 0;
	}
	if(ret >= 0)
	{
		sml_output_results(0, ret);
		kb_reset_model(0);
	}
	#else
      data = &data_batch[batch_index * num_sensors];
      if (model_id == 1)
        {
          ret = kb_run_model ((SENSOR_DATA_T*) data, num_sensors, KB_MODEL_IMU_MODEL_INDEX);
          if (ret >= 0)
            {

              set_imu_classification (ret);

              //kb_get_classification_result_info (KB_MODEL_IMU_MODEL_INDEX, (void*) &imu_modelResults);
              //set_imu_softMax ( modelResults);
              //sml_output_results (KB_MODEL_IMU_MODEL_INDEX, ret);
              kb_reset_model (1);
            };
        }
      else if (model_id == 0)
        {
          ret = -2;
          ret = kb_run_model_with_cascade_features ((SENSOR_DATA_T*) data, num_sensors, KB_MODEL_AUDIO_MODEL_INDEX);
          if (ret >= 0)
            {
              //printf("Audio Classification %i\n\r",ret);
              set_audio_classification (ret);

              // kb_get_classification_result_info (KB_MODEL_AUDIO_MODEL_INDEX, (void*) &modelResults);
              // set_audio_softMax ((tf_micro_model_results_t*) &modelResults);
              //sml_output_results (KB_MODEL_AUDIO_MODEL_INDEX, ret);
              kb_reset_model (0);
            }
          else
            {
              if (ret == -2){
                  //printf("Audio Classification %i\n\r",ret);
                set_audio_classification (5);
              }
              //sml_output_results (KB_MODEL_AUDIO_MODEL_INDEX, ret);

            }
        }
      //FILL_RUN_MODEL_CUSTOM
#endif //SML_USE_TEST_DATA
    }
  return ret;
}
