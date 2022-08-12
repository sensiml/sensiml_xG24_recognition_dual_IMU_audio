#include "sml_output.h"
#include "kb_debug.h"
#include "kb.h"

#define SERIAL_OUT_CHARS_MAX 2056

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

// Test to see if code is being used
static char serial_out_buf[SERIAL_OUT_CHARS_MAX];
static uint8_t recent_fv[MAX_VECTOR_SIZE];
static uint8_t recent_fv_len;
static uint8_t write_features = 0;
#if SML_PROFILER
float recent_fv_times[MAX_VECTOR_SIZE];
unsigned int recent_fv_cycles[MAX_VECTOR_SIZE];
#endif

static void sml_output_serial(uint16_t model, uint16_t classification)
{
    int32_t written = 0;
    memset(serial_out_buf, 0, SERIAL_OUT_CHARS_MAX);
    written += snprintf(serial_out_buf, sizeof(serial_out_buf)-1,
               "{\"ModelNumber\":%d,\"Classification\":%d", model, classification);
    if(write_features)
    {
        written += snprintf(serial_out_buf, sizeof(serial_out_buf)-written,
               ",\"FeatureLength\":%d,\"FeatureVector\":[",recent_fv_len);
        for(int j=0; j < recent_fv_len; j++)
        {
            written += snprintf(&serial_out_buf[written],sizeof(serial_out_buf)-written,"%d",recent_fv[j]);
            if(j < recent_fv_len -1)
            {
                serial_out_buf[written++] = ',';
            }
        }
        serial_out_buf[written++] = ']';
    }
    serial_out_buf[written++] = '}';

    printf("%s\r\n", serial_out_buf);
#if SML_PROFILER
    memset(serial_out_buf, 0, SERIAL_OUT_CHARS_MAX);
    kb_print_model_cycles(model, serial_out_buf, recent_fv_cycles);
    printf("%s\r\n", serial_out_buf);
    memset(serial_out_buf, 0, SERIAL_OUT_CHARS_MAX);
    kb_print_model_times(model, serial_out_buf, recent_fv_times);
    printf("%s\r\n", serial_out_buf);
#endif    
}

uint32_t sml_output_results(uint16_t model, uint16_t classification)
{
    sml_get_feature_vector(model, recent_fv, &recent_fv_len);
    memset(serial_out_buf, 0, SERIAL_OUT_CHARS_MAX);
    sml_output_serial(model, classification);


    return 0;
}

uint32_t sml_output_init(void *p_module)
{
    //unused for now
    return 0;
}
