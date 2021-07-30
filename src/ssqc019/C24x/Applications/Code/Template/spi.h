/* SPI.h */

#define SPICCR   *(volatile unsigned int *) 0x7040
#define SPICTL   *(volatile unsigned int *) 0x7041
#define SPISTS   *(volatile unsigned int *) 0x7042
#define SPIBRR   *(volatile unsigned int *) 0x7044
#define SPIRXEMU *(volatile unsigned int *) 0x7046
#define SPIRXBUF *(volatile unsigned int *) 0x7047
#define SPITXBUF *(volatile unsigned int *) 0x7048
#define SPIDAT   *(volatile unsigned int *) 0x7049
#define SPIPRI   *(volatile unsigned int *) 0x704F

/* For use with SPISTS */

#define SPI_INT_FLAG    0x0040 /* Data sent or received */
#define SPI_TX_BUF_FULL 0x0020 /* Data yet to be sent */
