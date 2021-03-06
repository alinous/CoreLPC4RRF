#ifndef HARDWARESPI_H
#define HARDWARESPI_H

#include "Core.h"
#include "SharedSpi.h"
#include "chip.h"
#include "variant.h"
#include "SPI.h"
#include "DMA.h"

#include "FreeRTOS.h"
#include "semphr.h"

class HardwareSPI: public SPI
{
public:
    HardwareSPI(LPC_SSP_T* sspDevice) noexcept;
    spi_status_t sspi_transceive_packet(const uint8_t *tx_data, uint8_t *rx_data, size_t len) noexcept;
    spi_status_t sspi_transceive_packet_dma(const uint8_t *tx_data, uint8_t *rx_data, size_t len, DMA_TransferWidth_t transferWidth=DMA_WIDTH_BYTE) noexcept;
    void setup_device(const struct sspi_device *device) noexcept;
    bool waitForTxEmpty() noexcept;
    void interrupt() noexcept;

private:
    LPC_SSP_T* selectedSSPDevice;
    bool needInit;

   SemaphoreHandle_t spiTransferSemaphore;
    volatile bool dmaTransferComplete;
};




#endif
