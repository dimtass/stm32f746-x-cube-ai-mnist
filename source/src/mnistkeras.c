/**
  ******************************************************************************
  * @file    mnistkeras.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Wed Jul 24 15:39:42 2019
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */



#include "mnistkeras.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"

#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 4
#define AI_TOOLS_VERSION_MINOR 0
#define AI_TOOLS_VERSION_MICRO 0

#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_mnistkeras
 
#undef AI_MNISTKERAS_MODEL_SIGNATURE
#define AI_MNISTKERAS_MODEL_SIGNATURE     "cef02ff2b526a0cb1607630612c8607c"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Wed Jul 24 15:39:42 2019"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_MNISTKERAS_N_BATCHES
#define AI_MNISTKERAS_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array conv2d_2_scratch0_array;   /* Array #0 */
AI_STATIC ai_array conv2d_0_scratch0_array;   /* Array #1 */
AI_STATIC ai_array dense_6_bias_array;   /* Array #2 */
AI_STATIC ai_array dense_6_weights_array;   /* Array #3 */
AI_STATIC ai_array dense_5_bias_array;   /* Array #4 */
AI_STATIC ai_array dense_5_weights_array;   /* Array #5 */
AI_STATIC ai_array conv2d_4_bias_array;   /* Array #6 */
AI_STATIC ai_array conv2d_4_weights_array;   /* Array #7 */
AI_STATIC ai_array conv2d_2_bias_array;   /* Array #8 */
AI_STATIC ai_array conv2d_2_weights_array;   /* Array #9 */
AI_STATIC ai_array conv2d_0_bias_array;   /* Array #10 */
AI_STATIC ai_array conv2d_0_weights_array;   /* Array #11 */
AI_STATIC ai_array input_0_output_array;   /* Array #12 */
AI_STATIC ai_array conv2d_0_output_array;   /* Array #13 */
AI_STATIC ai_array conv2d_2_output_array;   /* Array #14 */
AI_STATIC ai_array conv2d_4_output_array;   /* Array #15 */
AI_STATIC ai_array dense_5_output_array;   /* Array #17 */
AI_STATIC ai_array nl_5_output_array;   /* Array #18 */
AI_STATIC ai_array dense_6_output_array;   /* Array #19 */
AI_STATIC ai_array nl_7_output_array;   /* Array #20 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor conv2d_2_scratch0;   /* Tensor #0 */
AI_STATIC ai_tensor conv2d_0_scratch0;   /* Tensor #1 */
AI_STATIC ai_tensor dense_6_bias;   /* Tensor #2 */
AI_STATIC ai_tensor dense_6_weights;   /* Tensor #3 */
AI_STATIC ai_tensor dense_5_bias;   /* Tensor #4 */
AI_STATIC ai_tensor dense_5_weights;   /* Tensor #5 */
AI_STATIC ai_tensor conv2d_4_bias;   /* Tensor #6 */
AI_STATIC ai_tensor conv2d_4_weights;   /* Tensor #7 */
AI_STATIC ai_tensor conv2d_2_bias;   /* Tensor #8 */
AI_STATIC ai_tensor conv2d_2_weights;   /* Tensor #9 */
AI_STATIC ai_tensor conv2d_0_bias;   /* Tensor #10 */
AI_STATIC ai_tensor conv2d_0_weights;   /* Tensor #11 */
AI_STATIC ai_tensor input_0_output;   /* Tensor #12 */
AI_STATIC ai_tensor conv2d_0_output;   /* Tensor #13 */
AI_STATIC ai_tensor conv2d_2_output;   /* Tensor #14 */
AI_STATIC ai_tensor conv2d_4_output;   /* Tensor #15 */
AI_STATIC ai_tensor conv2d_4_output0;   /* Tensor #16 */
AI_STATIC ai_tensor dense_5_output;   /* Tensor #17 */
AI_STATIC ai_tensor nl_5_output;   /* Tensor #18 */
AI_STATIC ai_tensor dense_6_output;   /* Tensor #19 */
AI_STATIC ai_tensor nl_7_output;   /* Tensor #20 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conv2d_0_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv2d_2_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain conv2d_4_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain dense_5_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain nl_5_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain dense_6_chain;   /* Chain #5 */
AI_STATIC_CONST ai_tensor_chain nl_7_chain;   /* Chain #6 */


/**  Subgraph network operator tensor chain declarations  *********************/


/**  Subgraph network operator declarations  *********************************/


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d_nl_pool conv2d_0_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_2_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d conv2d_4_layer; /* Layer #2 */
AI_STATIC ai_layer_dense dense_5_layer; /* Layer #3 */
AI_STATIC ai_layer_nl nl_5_layer; /* Layer #4 */
AI_STATIC ai_layer_dense dense_6_layer; /* Layer #5 */
AI_STATIC ai_layer_nl nl_7_layer; /* Layer #6 */


/**  Array declarations section  **********************************************/
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1408,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1664,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_6_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_6_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 640,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_5_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_5_weights_array, AI_ARRAY_FORMAT_LUT8_FLOAT,
  NULL, NULL, 36864,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 36864,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 18432,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 784,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 5408,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_2_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1600,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_4_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 576,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_5_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  nl_5_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_6_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  nl_7_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 10,
  AI_STATIC)


/**  Tensor declarations section  *********************************************/
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_scratch0,
  AI_SHAPE_INIT(2, 11, 64, 1),
  AI_STRIDE_INIT(2816, 256, 4, 4),
  &conv2d_2_scratch0_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_scratch0,
  AI_SHAPE_INIT(2, 26, 32, 1),
  AI_STRIDE_INIT(3328, 128, 4, 4),
  &conv2d_0_scratch0_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_6_bias,
  AI_SHAPE_INIT(1, 1, 10, 1),
  AI_STRIDE_INIT(40, 40, 4, 4),
  &dense_6_bias_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_6_weights,
  AI_SHAPE_INIT(1, 1, 10, 64),
  AI_STRIDE_INIT(2560, 2560, 256, 4),
  &dense_6_weights_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_5_bias,
  AI_SHAPE_INIT(1, 1, 64, 1),
  AI_STRIDE_INIT(256, 256, 4, 4),
  &dense_5_bias_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_5_weights,
  AI_SHAPE_INIT(1, 1, 64, 576),
  AI_STRIDE_INIT(36864, 36864, 576, 1),
  &dense_5_weights_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_bias,
  AI_SHAPE_INIT(1, 1, 64, 1),
  AI_STRIDE_INIT(256, 256, 4, 4),
  &conv2d_4_bias_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_weights,
  AI_SHAPE_INIT(64, 3, 3, 64),
  AI_STRIDE_INIT(2304, 768, 256, 4),
  &conv2d_4_weights_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_bias,
  AI_SHAPE_INIT(1, 1, 64, 1),
  AI_STRIDE_INIT(256, 256, 4, 4),
  &conv2d_2_bias_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_weights,
  AI_SHAPE_INIT(64, 3, 3, 32),
  AI_STRIDE_INIT(1152, 384, 128, 4),
  &conv2d_2_weights_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_bias,
  AI_SHAPE_INIT(1, 1, 32, 1),
  AI_STRIDE_INIT(128, 128, 4, 4),
  &conv2d_0_bias_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_weights,
  AI_SHAPE_INIT(32, 3, 3, 1),
  AI_STRIDE_INIT(36, 12, 4, 4),
  &conv2d_0_weights_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  input_0_output,
  AI_SHAPE_INIT(28, 28, 1, 1),
  AI_STRIDE_INIT(112, 4, 4, 4),
  &input_0_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_output,
  AI_SHAPE_INIT(13, 13, 32, 1),
  AI_STRIDE_INIT(1664, 128, 4, 4),
  &conv2d_0_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_2_output,
  AI_SHAPE_INIT(5, 5, 64, 1),
  AI_STRIDE_INIT(1280, 256, 4, 4),
  &conv2d_2_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_output,
  AI_SHAPE_INIT(3, 3, 64, 1),
  AI_STRIDE_INIT(768, 256, 4, 4),
  &conv2d_4_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_4_output0,
  AI_SHAPE_INIT(1, 1, 576, 1),
  AI_STRIDE_INIT(2304, 2304, 4, 4),
  &conv2d_4_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_5_output,
  AI_SHAPE_INIT(1, 1, 64, 1),
  AI_STRIDE_INIT(256, 256, 4, 4),
  &dense_5_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  nl_5_output,
  AI_SHAPE_INIT(1, 1, 64, 1),
  AI_STRIDE_INIT(256, 256, 4, 4),
  &nl_5_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_6_output,
  AI_SHAPE_INIT(1, 1, 10, 1),
  AI_STRIDE_INIT(40, 40, 4, 4),
  &dense_6_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  nl_7_output,
  AI_SHAPE_INIT(1, 1, 10, 1),
  AI_STRIDE_INIT(40, 40, 4, 4),
  &nl_7_output_array,
  AI_STATIC)


/**  Layer declarations section  **********************************************/



AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_0_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&input_0_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_0_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_0_weights, &conv2d_0_bias, NULL),
  AI_TENSOR_LIST_ENTRY(&conv2d_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_0_layer, 0,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &conv2d_2_layer, AI_STATIC,
  .tensors = &conv2d_0_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_ND_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_ND_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_2_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&conv2d_0_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_2_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_2_weights, &conv2d_2_bias, NULL),
  AI_TENSOR_LIST_ENTRY(&conv2d_2_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_2_layer, 2,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &conv2d_4_layer, AI_STATIC,
  .tensors = &conv2d_2_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_ND_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_ND_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_4_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&conv2d_2_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_4_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_4_weights, &conv2d_4_bias, NULL),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_4_layer, 4,
  CONV2D_TYPE,
  conv2d, forward_conv2d,
  &AI_NET_OBJ_INSTANCE, &dense_5_layer, AI_STATIC,
  .tensors = &conv2d_4_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_ND_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_5_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&conv2d_4_output0),
  AI_TENSOR_LIST_ENTRY(&dense_5_output),
  AI_TENSOR_LIST_ENTRY(&dense_5_weights, &dense_5_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_5_layer, 5,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &nl_5_layer, AI_STATIC,
  .tensors = &dense_5_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_5_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_5_output),
  AI_TENSOR_LIST_ENTRY(&nl_5_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_5_layer, 5,
  NL_TYPE,
  nl, forward_relu,
  &AI_NET_OBJ_INSTANCE, &dense_6_layer, AI_STATIC,
  .tensors = &nl_5_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_6_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&nl_5_output),
  AI_TENSOR_LIST_ENTRY(&dense_6_output),
  AI_TENSOR_LIST_ENTRY(&dense_6_weights, &dense_6_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_6_layer, 6,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &nl_7_layer, AI_STATIC,
  .tensors = &dense_6_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_7_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_6_output),
  AI_TENSOR_LIST_ENTRY(&nl_7_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_7_layer, 7,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &nl_7_layer, AI_STATIC,
  .tensors = &nl_7_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 263720, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 33664, 1,
                     NULL),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_MNISTKERAS_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_MNISTKERAS_OUT_NUM, &nl_7_output),
  &conv2d_0_layer, 0)



AI_DECLARE_STATIC
ai_bool mnistkeras_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT( activations )

  {
    /* Updating activations (byte) offsets */
    conv2d_2_scratch0_array.data = AI_PTR(activations + 0);
    conv2d_2_scratch0_array.data_start = AI_PTR(activations + 0);
    conv2d_0_scratch0_array.data = AI_PTR(activations + 0);
    conv2d_0_scratch0_array.data_start = AI_PTR(activations + 0);
    input_0_output_array.data = AI_PTR(NULL);
    input_0_output_array.data_start = AI_PTR(NULL);
    conv2d_0_output_array.data = AI_PTR(activations + 12032);
    conv2d_0_output_array.data_start = AI_PTR(activations + 12032);
    conv2d_2_output_array.data = AI_PTR(activations + 5632);
    conv2d_2_output_array.data_start = AI_PTR(activations + 5632);
    conv2d_4_output_array.data = AI_PTR(activations + 0);
    conv2d_4_output_array.data_start = AI_PTR(activations + 0);
    dense_5_output_array.data = AI_PTR(activations + 2304);
    dense_5_output_array.data_start = AI_PTR(activations + 2304);
    nl_5_output_array.data = AI_PTR(activations + 2304);
    nl_5_output_array.data_start = AI_PTR(activations + 2304);
    dense_6_output_array.data = AI_PTR(activations + 0);
    dense_6_output_array.data_start = AI_PTR(activations + 0);
    nl_7_output_array.data = AI_PTR(NULL);
    nl_7_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool mnistkeras_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT( weights )

  {
    /* Updating weights (byte) offsets */
    dense_6_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_6_bias_array.data = AI_PTR(weights + 263680);
    dense_6_bias_array.data_start = AI_PTR(weights + 263680);
  dense_6_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_6_weights_array.data = AI_PTR(weights + 261120);
    dense_6_weights_array.data_start = AI_PTR(weights + 261120);
  dense_5_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_5_bias_array.data = AI_PTR(weights + 260864);
    dense_5_bias_array.data_start = AI_PTR(weights + 260864);
  dense_5_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_5_weights_array.data = AI_PTR(weights + 224000);
    dense_5_weights_array.data_start = AI_PTR(weights + 222976);
  conv2d_4_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_4_bias_array.data = AI_PTR(weights + 222720);
    conv2d_4_bias_array.data_start = AI_PTR(weights + 222720);
  conv2d_4_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_4_weights_array.data = AI_PTR(weights + 75264);
    conv2d_4_weights_array.data_start = AI_PTR(weights + 75264);
  conv2d_2_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_bias_array.data = AI_PTR(weights + 75008);
    conv2d_2_bias_array.data_start = AI_PTR(weights + 75008);
  conv2d_2_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_2_weights_array.data = AI_PTR(weights + 1280);
    conv2d_2_weights_array.data_start = AI_PTR(weights + 1280);
  conv2d_0_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_0_bias_array.data = AI_PTR(weights + 1152);
    conv2d_0_bias_array.data_start = AI_PTR(weights + 1152);
  conv2d_0_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_0_weights_array.data = AI_PTR(weights + 0);
    conv2d_0_weights_array.data_start = AI_PTR(weights + 0);
  
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_mnistkeras_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_MNISTKERAS_MODEL_NAME,
      .model_signature   = AI_MNISTKERAS_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 2852598,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_mnistkeras_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_mnistkeras_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_mnistkeras_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_mnistkeras_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= mnistkeras_configure_weights(net_ctx, &params->params);
  ok &= mnistkeras_configure_activations(net_ctx, &params->activations);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_mnistkeras_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_mnistkeras_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}

#undef AI_MNISTKERAS_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

