/**
  ******************************************************************************
  * @file    logger.c
  * @brief   Debug log output utility implementation.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "logger.h"
#include "st_errno.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#if (USE_LOGGER == LOGGER_ON)

#define MAX_HEX_STR         4
#define MAX_HEX_STR_LENGTH  128
char hexStr[MAX_HEX_STR][MAX_HEX_STR_LENGTH];
uint8_t hexStrIdx = 0;
#endif /* #if USE_LOGGER == LOGGER_ON */

#if (USE_LOGGER == LOGGER_OFF && !defined(HAL_UART_MODULE_ENABLED))
#define hal_uart_handle_s void
#endif /* #if USE_LOGGER == LOGGER_ON */

#define USART_TIMEOUT          1000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_uart_handle_t *pLogUsart ;  /*!< pointer to the logger Handler */


/* Private function prototypes -----------------------------------------------*/
uint8_t logUsartTx(uint8_t *data, uint16_t dataLen);

/* Private functions ---------------------------------------------------------*/
/**
  *****************************************************************************
  * @brief  This function initialize the UART handle and UART IP.
  *
  * @param[in,out]  husart : handle to USART HW
  *
  * @return None
  *****************************************************************************
  */
void logUsartInit(hal_uart_handle_t *husart)
{

  pLogUsart = husart;

}

/**
  *****************************************************************************
  * @brief  This function Transmit data via USART.
  *
  * @param[in]  data    : data to be transmitted
  * @param[in]  dataLen : length of data to be transmitted
  *
  * @retval ERR_INVALID_HANDLE : in case the UART HW is not initialized yet
  * @retval others             : HAL status
  *****************************************************************************
  */
uint8_t logUsartTx(uint8_t *data, uint16_t dataLen)
{
  if (pLogUsart == 0)
  {
    return ERR_INVALID_HANDLE;
  }
#if (USE_LOGGER == LOGGER_ON)
  {
    return HAL_UART_Transmit(pLogUsart, data, dataLen, USART_TIMEOUT);
  }
#else
  {
    return 0;
  }
#endif /* #if USE_LOGGER == LOGGER_ON */
}

/**
  *****************************************************************************
  * @brief  This function is used to write a formatted string via the UART interface.
  *
  * @param[in]  format : data to be transmitted
  *
  * @return Number of data sent
  *****************************************************************************
  */
int32_t logUsart(const char *format, ...)
{
#if (USE_LOGGER == LOGGER_ON)
  {
#define LOG_BUFFER_SIZE 256
    char buf[LOG_BUFFER_SIZE];
    va_list argptr;
    va_start(argptr, format);
    int32_t cnt = vsnprintf(buf, LOG_BUFFER_SIZE, format, argptr);
    va_end(argptr);

    /* */
    logUsartTx((uint8_t *)buf, strlen(buf));
    return cnt;
  }
#else
  {
    return 0;
  }
#endif /* #if USE_LOGGER == LOGGER_ON */
}

/**
  *****************************************************************************
  * @brief  helper to convert hex data into formatted string.
  *
  * @param[in]  data : pointer to buffer to be dumped.
  * @param[in]  dataLen : buffer length
  *
  * @return pointer to converted data
  *****************************************************************************
  */
char *hex2Str(unsigned char *data, size_t dataLen)
{
#if (USE_LOGGER == LOGGER_ON)
  {
    unsigned char *pin = data;
    const char *hex = "0123456789ABCDEF";
    char *pout = hexStr[hexStrIdx];
    uint8_t i = 0;
    uint8_t idx = hexStrIdx;

    if (dataLen > (MAX_HEX_STR_LENGTH / 2))
    {
      dataLen = (MAX_HEX_STR_LENGTH / 2);
    }

    if (dataLen == 0)
    {
      pout[0] = 0;
    }
    else
    {
      for (; i < dataLen - 1; ++i)
      {
        *pout++ = hex[(*pin >> 4) & 0xF];
        *pout++ = hex[(*pin++) & 0xF];
      }
      *pout++ = hex[(*pin >> 4) & 0xF];
      *pout++ = hex[(*pin) & 0xF];
      *pout = 0;
    }

    hexStrIdx++;
    hexStrIdx %= MAX_HEX_STR;

    return hexStr[idx];
  }
#else
  {
    return NULL;
  }
#endif /* #if USE_LOGGER == LOGGER_ON */
}
